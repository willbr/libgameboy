#ifndef _SM83_OPCODES_H
#define _SM83_OPCODES_H

#include "types.h"

enum operand_type {
    ot_none,
    ot_zero, ot_not_zero,
    ot_carry, ot_not_carry,
    ot_d8, ot_d16,
    ot_a8, ot_a16,
    ot_r8,
    ot_A, ot_F, ot_B, ot_C, ot_D, ot_E, ot_H, ot_L,
    ot_AF, ot_BC, ot_DE, ot_HL,
    ot_SP, ot_PC,
    ot_00h, ot_08h, ot_10h, ot_18h, ot_20h, ot_28h, ot_30h, ot_38h
};


struct def_opcode_flags {
        char z;
        char n;
        char h;
        char c;
};


struct def_opcode_operand {
    enum operand_type type;
    char* name;
    int bytes;
    enum bool immediate;
};


struct def_opcode {
        u8 code;
        char *mnemonic;
        int bytes;
        int n_cycles;
        int cycles[2];
        enum bool immediate;
        struct def_opcode_flags flags;
        int n_operands;
        struct def_opcode_operand operands[2];
};

#endif

