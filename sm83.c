#include "sm83.h"

/* fix for warning, stdio.h include doesn't work... */
int snprintf(char *, size_t, const char *, ...);

#define S_ARG_BUFFER_SIZE 100

extern struct def_opcode opcodes[];

void
init_sm83(struct sm83_cpu *cpu) {
    cpu->reg.wr.af = 0x01b0;
    cpu->reg.wr.bc = 0x0013;
    cpu->reg.wr.de = 0x00d8;
    cpu->reg.wr.hl = 0x014d;

    cpu->pc = 0x0100;
    cpu->sp = 0xfffe;

    cpu->ticks = 0;
}

char*
bits_to_s(u8 b){
        static char rval[9];

        /*struct bits *bits;*/
        struct bits {
                int b0 : 1;
                int b1 : 1;
                int b2 : 1;
                int b3 : 1;
                int b4 : 1;
                int b5 : 1;
                int b6 : 1;
                int b7 : 1;
        } *bits;

        bits = (struct bits *)&b;

        rval[0] = bits->b7 ? '1' : '0';
        rval[1] = bits->b6 ? '1' : '0';
        rval[2] = bits->b5 ? '1' : '0';
        rval[3] = bits->b4 ? '1' : '0';
        rval[4] = bits->b3 ? '1' : '0';
        rval[5] = bits->b2 ? '1' : '0';
        rval[6] = bits->b1 ? '1' : '0';
        rval[7] = bits->b0 ? '1' : '0';
        rval[8] = '\0';

        /*printf("bts: %d\n", rval[0]);*/
        /*printf("bts: %d\n", rval[1]);*/
        /*printf("bts: %s\n", rval);*/

        return (char*)&rval;
}


void
sm83_print_regs_headers() {
        puts("    tick   "
             "pc op                 "
             "a  f   "
             "bc   de   hl   "
             "sp "
             "ZNHC "
             "[bc] [de] [hl]");
}


void
read_arg(
         size_t n,
         char s1[],
         int offset,
         struct def_opcode od,
         struct sm83_cpu *cpu) {

    struct def_opcode_operand arg;
    u8 a8;
    u16 a16;
    u8 d8;
    u16 d16;
    i8 r8;

    arg = od.operands[offset];

    /*printf("read_arg: %s\n", od.mnemonic);*/
    /*printf("%s %d %d\n", arg.name, arg.bytes, arg.immediate);*/

    switch (arg.type) {
        case ot_a8:
            a8 = read8(cpu, cpu->pc + 1);
            snprintf(s1, n, "%02x", a8);
            break;

        case ot_a16:
            a16 = read16(cpu, cpu->pc + 1);
            snprintf(s1, n, "%04x", a16);
            break;

        case ot_d8:
            d8 = read8(cpu, cpu->pc + 1);
            snprintf(s1, n, "%02x", d8);
            break;

        case ot_d16:
            d16 = read16(cpu, cpu->pc + 1);
            snprintf(s1, n, "%04x", d16);
            break;

        case ot_r8:
            r8 = read8(cpu, cpu->pc + 1);
            snprintf(s1, n, "%s%02x", (r8<0)?"-":"", (r8<0)?-r8:r8);
            break;

        case ot_A:
        case ot_F:
        case ot_B:
        case ot_C:
        case ot_D:
        case ot_E:
        case ot_H:
        case ot_L:
        case ot_AF:
        case ot_BC:
        case ot_DE:
        case ot_HL:
            snprintf(
                     s1,
                     n,
                     arg.immediate?"%s":"[%s]",
                     arg.name);
            break;

        case ot_zero:
        case ot_not_zero:
        case ot_carry:
        case ot_not_carry:
            snprintf(s1, n, "%s", arg.name);
            break;

        default:
            printf("\nunknown op: %s\n", arg.name);
            assert(false);
            break;
    }
}
    

void
read_args(size_t n, char s1[], char s2[], struct def_opcode od, struct sm83_cpu *cpu) {

    /*printf("%s %d %d\n", arg.name, arg.bytes, arg.immediate);*/
    /*puts("read_args");*/

    s1[0] = '\0';
    s2[0] = '\0';

    switch (od.n_operands) 
    {
        case 0:
            break;

        case 1:
            read_arg(n, s1, 0, od, cpu);
            break;

        case 2:
            read_arg(n, s1, 0, od, cpu);
            read_arg(n, s2, 1, od, cpu);
            break;

        default:
            assert(false);
    }
}

void
sm83_print_regs(struct sm83_cpu *cpu) {
        u8 bc, de, hl;
        u8 opcode;
        struct def_opcode od;
        char s_arg1[S_ARG_BUFFER_SIZE] = {'\0'};
        char s_arg2[S_ARG_BUFFER_SIZE] = {'\0'};

        bc = cpu->memory[cpu->reg.wr.bc];
        de = cpu->memory[cpu->reg.wr.de];
        hl = cpu->memory[cpu->reg.wr.hl];

        opcode = cpu->memory[cpu->pc];
        od = opcodes[opcode];

        read_args(S_ARG_BUFFER_SIZE, s_arg1, s_arg2, od, cpu);

        /*switch (od.n_operands) */
        /*{*/
            /*case 0:*/
                /*break;*/

            /*case 1:*/
                /*printf("%s ", s_arg1);*/
                /*break;*/

            /*case 2:*/
                /*printf("%s ", s_arg1);*/
                /*printf("%s ", s_arg2);*/
                /*break;*/

            /*default:*/
                /*assert(false);*/
        /*}*/

        printf("%8x "
               "%04x "
               "%02x "
               "%4s %4s %4s "
               "%02x %02x "
               "%04x %04x %04x %04x "
               "%d%d%d%d  "
               "%02x   %02x   %02x\n",
               cpu->ticks,
               cpu->pc,
               opcode,
               opcodes[opcode].mnemonic,
               s_arg1,
               s_arg2,
               cpu->reg.br.a,
               cpu->reg.br.f,
               cpu->reg.wr.bc,
               cpu->reg.wr.de,
               cpu->reg.wr.hl,
               cpu->sp,
               cpu->reg.flag.zero,
               cpu->reg.flag.add_or_sub,
               cpu->reg.flag.half_carry,
               cpu->reg.flag.carry,
               bc, de, hl
               );
}


void
test_sm83() {
        u8 memory[0x10000] = {
                0x01,
                0x02,
                0x03,
                0x04,
                0x05,
                0x06,
                0x07,
                0x08
        };

        struct sm83_cpu cpu;
        cpu.memory = (u8*)&memory;

        cpu.reg.wr.hl = 0xBEEF;
        cpu.reg.br.f = 0x00;

        memory[cpu.reg.wr.hl] = 0xFF;
        memory[cpu.reg.wr.bc] = memory[cpu.reg.wr.hl];

        init_sm83(&cpu);

        sm83_print_regs(&cpu);
}


u8 read8(struct sm83_cpu *cpu, u16 a16) {
        return cpu->memory[a16];
}


u16 read16(struct sm83_cpu *cpu, u16 a16){
        return *(u16*)&cpu->memory[a16];
}


void
write8(struct sm83_cpu *cpu, u16 a16, u8 d8) {
        cpu->memory[a16] = d8;
}


void
sm83_cpu_step(struct sm83_cpu *cpu) {
        u8 opcode;

        opcode = read8(cpu, cpu->pc++);
        eval_opcode(cpu, opcode);
        cpu->ticks++;
}


void eval_opcode(struct sm83_cpu *cpu, u8 opcode) {
        /*int i;*/
        /*struct def_opcode o;*/
    u8  a8;
    u16 a16;
    u8  d8;
    u16 d16;
    i8  r8;
    u8  deref;
    u8  old_8reg;
    u16 old_16reg;

        /*o = opcodes[opcode];*/

        /*printf("%02x %s\n", opcode, o.mnemonic);*/

#include "switch.c"

}

