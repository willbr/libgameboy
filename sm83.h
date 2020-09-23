#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "sm83_opcodes.h"

#define SYSTEM_IS_BIG_ENDIAN false

#define bit4(x) (x & (1 <<4))

union registers {
        struct {
#if SYSTEM_IS_BIG_ENDIAN
                u8 b; u8 c;
                u8 d; u8 e;
                u8 h; u8 l;
                u8 a; u8 f;
#else
                u8 c; u8 b;
                u8 e; u8 d;
                u8 l; u8 h;
                u8 f; u8 a;
#endif
        } br;

        struct {
                u16 bc;
                u16 de;
                u16 hl;
                u16 af;
        } wr;

        struct {
#if SYSTEM_IS_BIG_ENDIAN
                u8 ignore[7];
#else
                u8 ignore[6];
#endif
                u32 f0 : 1;
                u32 f1 : 1;
                u32 f2 : 1;
                u32 f3 : 1;
                u32 carry      : 1; /* Bit 4 */
                u32 half_carry : 1; /* Bit 5 */
                u32 add_or_sub : 1; /* Bit 6 */
                u32 zero       : 1; /* Bit 7 */
        } flag;
};

struct sm83_cpu {
        union registers reg;
        u16 pc;
        u16 sp;

        u8 *memory;

        u32 ticks;
};

void test_sm83();
void init_sm83();
void sm83_print_regs_headers();
void sm83_print_regs(struct sm83_cpu *cpu);
void sm83_cpu_step(struct sm83_cpu *cpu);


u8 read8(struct sm83_cpu *cpu, u16 a16);
u16 read16(struct sm83_cpu *cpu, u16 a16);

void eval_opcode(struct sm83_cpu *cpu, u8 opcode);

