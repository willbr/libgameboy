import json
from pprint import pprint

with open("Opcodes.json") as f:
    # raw = f.read()
    opcodes = json.load(f)


def operand_repr(operand):
    name = operand['name']
    increment = "+" if operand.get('increment', False) else ""

    if operand.get('immediate'):
        return "%s%s" % (name, increment)
    else:
        return '(%s%s)' % (name, increment)


def operand_to_c(operand):
    name = operand.get('name', None)

    if name is None:
        return

    increment = "++" if operand.get('increment', False) else ""

    if is_8bit_register(operand):
        return "cpu->reg.br.%s%s" % (name.lower(), increment)

    elif is_16bit_register(operand):
        return "cpu->reg.wr.%s%s" % (name.lower(), increment)

    elif name in ["SP", "PC"]:
        return "cpu->%s%s" % (name.lower(), increment)

    elif name in ["d8", "d16", "a8","a16","r8"]:
        return name

    elif name in ['Z', 'NZ', 'C', 'NC']:
        return name

    elif name[-1] == 'H':
        return name

    else:
        pprint(operand)
        raise ValueError


def is_8bit_register(operand):
    return operand.get('name') in "A F B C D E H L".split()


def is_16bit_register(operand):
    return operand.get('name') in "AF BC DE HL".split()


for op_type in ['unprefixed']:
    print("switch (opcode)")
    print("{")

    for i in range(256):
        s_opcode = "0x%02X" % i
        opcode = opcodes['unprefixed'][s_opcode]
        m = opcode['mnemonic']

        prefix = []
        body = []
        postfix = []

        args = ', '.join(operand_repr(operand) for operand in opcode['operands'])
        args = args.strip()
        cmd = '%s %s' % (opcode['mnemonic'], args)
        cmd = cmd.strip()

        prefix.append("case %s: /* %s */" % (s_opcode, cmd))

        try:
            o0 = opcode['operands'][0]
        except IndexError:
            o0 = dict()

        try:
            o1 = opcode['operands'][1]
        except IndexError:
            o1 = dict()

        lhs = operand_to_c(o0)
        rhs = operand_to_c(o1)

        names = set([o0.get('name'), o1.get('name')])
        val16 = names & set(['a16', 'd16'])
        if val16:
            temp = list(val16)[0]
            prefix.append("%s = read16(cpu, cpu->pc);" % temp)
            postfix.append("cpu->pc += 2;")

        val8 = names & set(['a8', 'd8', 'r8'])
        if val8:
            temp = list(val8)[0]
            prefix.append("%s = read8(cpu, cpu->pc);" % temp)
            postfix.append("cpu->pc += 1;")

        if m == "LD":
            if not o0.get('immediate'):
                body.extend((
                "write8(cpu, %s, %s);" % (lhs, rhs),
                ))

            elif not o1.get('immediate'):
                body.extend((
                "deref = read8(cpu, %s);" % rhs,
                "%s = deref;" % lhs,
                ))

            else:
                body.extend((
                "%s = %s;" % (lhs, rhs),
                ))
            # postfix.append("assert(false);")

        elif m == "JP":
            argc = len(opcode['operands'])

            if argc == 1:
                body.append("cpu->pc = %s;" % lhs)
                postfix = []

            elif argc == 2:
                lhs = o0.get('name')

                if lhs[-1] == 'Z':
                    neg = "!" if lhs[0] == 'N' else ""
                    body.extend([
                        'if (%scpu->reg.flag.zero)' % neg,
                        '{',
                        "    cpu->pc = %s;" % rhs,
                        ])

                elif lhs[-1] == 'C':
                    neg = "!" if lhs[0] == 'N' else ""
                    body.extend([
                        'if (%scpu->reg.flag.carry)' % neg,
                        '{',
                        "    cpu->pc = %s;" % rhs,
                        ])

                else:
                    pprint(opcode)
                    print(lhs, rhs)
                    raise ValueError

                body.extend([
                    "}",
                    "else",
                    "{",
                    "    " + postfix[0],
                    "}",
                    ])
                
                postfix = []

        elif m == "JR":
            argc = len(opcode['operands'])

            if argc == 1:
                body.append("cpu->pc += %s;" % lhs)
                postfix = []

            elif argc == 2:
                lhs = o0.get('name')

                if lhs[-1] == 'Z':
                    neg = "!" if lhs[0] == 'N' else ""
                    body.extend([
                        'if (%scpu->reg.flag.zero)' % neg,
                        '{',
                        "    cpu->pc += %s;" % rhs,
                        ])

                elif lhs[-1] == 'C':
                    neg = "!" if lhs[0] == 'N' else ""
                    body.extend([
                        'if (%scpu->reg.flag.carry)' % neg,
                        '{',
                        "    cpu->pc += %s;" % rhs,
                        ])

                else:
                    pprint(opcode)
                    print(lhs, rhs)
                    raise ValueError

                body.extend([
                    "}",
                    "else",
                    "{",
                    "    " + postfix[0],
                    "}",
                    ])
                postfix = []

            else:
                pass
                # print(opcode)
                # raise ValueError

            postfix.append("assert(false);")

        elif m == "NOP":
            pass

        elif m in ['INC', 'DEC']:
            lhs = operand_to_c(o0)
            prefix.append("old_8reg = %s;" % lhs)

            direction = "+" if m == "INC" else "-"

            body.append("%s %s= 1;" % (lhs, direction))

            postfix.extend([
                "if (%s == 0)" % lhs,
                "    cpu->reg.flag.zero = true;",
                "",
                "cpu->reg.flag.add_or_sub = true;",
                "",
                "if(bit4(old_8reg) != bit4(%s))" % lhs,
                "    cpu->reg.flag.half_carry = true;",
                "",
                ])

        elif m == "OR":
            lhs = operand_to_c(o0)

            body.append("cpu->reg.br.a |= %s;" % lhs)

        elif m == "XOR":
            lhs = operand_to_c(o0)

            body.append("cpu->reg.br.a ^= %s;" % lhs)

        else:
            postfix.append("assert(false);")

        body.append('printf("%%02x %s\\n", opcode);' % cmd)

        flags_string = "%s%s%s%s" % (
            opcode['flags']['Z'],
            opcode['flags']['N'],
            opcode['flags']['H'],
            opcode['flags']['C'],
            )

        flags_changed = flags_string.replace('-','')

        if flags_changed:
            postfix.append("assert(false); /* flags changed %s */" % flags_string)

        postfix.append("break;")
        postfix.append("")

        print('\n\t'.join((prefix + body + postfix)))

    print("default:")
    print("\tbreak;")
    print("}")


exit()

# for op_type in ['unprefixed', 'cbprefixed']:
for op_type in ['unprefixed']:

    mnemonic_set = set()
    headers = []

    for i in range(256):
        s_opcode = "0x%02X" % i
        opcode = opcodes['unprefixed'][s_opcode]

        m = opcode['mnemonic']
        if m in mnemonic_set:
            continue

        mnemonic_set.add(m)

        header = """
void eval_%s(struct sm83_cpu *cpu, u8 opcode, u8 arg1, u8 arg2)
        """.strip() % m.lower()
        headers.append(header)

    # for h in headers:
        # print(h.strip() + ";")

    # for h in headers:
        # print(h.strip() + "{}\n")

    check = dict()
    for i in range(256):
        s_opcode = "0x%02X" % i
        opcode = opcodes['unprefixed'][s_opcode]

        m = opcode['mnemonic']
        operands = opcode['operands']
        n_operands = len(opcode['operands'])
        try:
            check[m].append(n_operands)
        except KeyError:
            check[m] = [n_operands]

    # pprint(check)

    for k, v in check.items():
        sv = set(v)
        if len(sv) > 1:
            pass
            # print(k, sv)

    operand_names = set()

    switch_cases = []

    s_opcodes = []


    for i in range(256):
        s_opcode = "0x%02X" % i
        opcode = opcodes['unprefixed'][s_opcode]

        mnemonic = opcode['mnemonic']

        args = ', '.join(operand_repr(operand) for operand in opcode['operands'])
        args = args.strip()
        cmd = '%s %s' % (opcode['mnemonic'], args)
        switch_cases.append( """
    case %s: /* %s */
    \tprintf("%s\\n");
    \tassert(false);
    \tbreak;
                """.strip("\n") %
                (
                    s_opcode.lower(),
                    cmd,
                    cmd))


        cycles = "{ " + \
            ', '.join('%d' % x for x in opcode['cycles']) +\
            " }"

        flags = "{ " + ', '.join([
            "'%s'" % opcode['flags']['Z'],
            "'%s'" % opcode['flags']['N'],
            "'%s'" % opcode['flags']['H'],
            "'%s'" % opcode['flags']['C'],
            ]) + " }"

        assert len(opcode['operands']) < 3

        operands = []
        for operand in opcode['operands']:
            operand_names.add(operand.get('name', ''))

            s_operand = "{ " + ', '.join([
                '"%s"' % operand.get('name', '""'),
                "%d" % operand.get('bytes', 0),
                ("%s" % operand['immediate']).lower(),
                ]) + " }"
            operands.append(s_operand)

        if len(operands) == 0:
            operands = ['{""}']

        operands = "{ " + ', '.join(operands) + " }"

        tokens = [
                "0x%02x" % i,
                '"%s"' % opcode['mnemonic'],
                "%d" % opcode['bytes'],
                "%d" % len(opcode['cycles']),
                cycles,
                'true' if opcode['immediate'] else 'false',
                flags,
                "%d" % len(opcode['operands']),
                operands,
                # 'eval_%s' % opcode['mnemonic'].lower(),
                ]

        line = "{ " + ', '.join(tokens) + " }"
        # print(line)
        s_opcodes.append(line)

    # print("struct opcode opcodes[256] = {")
    # print(',\n'.join(s_opcodes))
    # print("};\n")


    # for op in operand_names:
        # print("operand_%s" % op)

    print("switch (opcode)")
    print("{")
    print('\n'.join(switch_cases))
    print("    default:");
    print("        break;")
    print("}")


