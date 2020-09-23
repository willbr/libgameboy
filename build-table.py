import json
from pprint import pprint

flag_alias = {
        'Z':  'ot_zero',
        'NZ': 'ot_not_zero',
        'C':  'ot_carry',
        'NC': 'ot_not_carry',
        }


def operand_type_to_c(mnemonic, operand_name):
    if mnemonic in ["JP", "JR", "RET", "CALL"]:
        return flag_alias.get(operand_name, "ot_" + operand_name)

    elif mnemonic == "RST":
        return "ot_%s" % operand_name.lower()

    else:
        return "ot_" + operand_name


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
            operand_name = operand.get('name', '')
            operand_type = operand_type_to_c(
                    opcode['mnemonic'],
                    operand_name,
                    )

            # print(operand)
            # print(operand_name)
            # print(operand_type)

            s_operand = "{ " + ', '.join([
                '%s' % operand_type,
                '"%s"' % operand_name,
                "%d" % operand.get('bytes', 0),
                ("%s" % operand['immediate']).lower(),
                ]) + " }"

            operands.append(s_operand)

        if len(operands) == 0:
            operands = ['{ot_none, ""}']

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

    print('#include "sm83.h"')
    print("struct def_opcode opcodes[256] = {")
    print(',\n'.join(s_opcodes))
    print("};\n")




