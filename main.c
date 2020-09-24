#include "libgameboy.h"

FILE *f_rom;
unsigned char rom[0x10000];

int
main(int argc, char **argv)
{

        struct sm83_cpu cpu;
        int i;

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

        cpu.memory = (u8*)&memory;

        f_rom = fopen("./Tetris (World).gb", "rb");

        if (!f_rom) {
                puts("failed to open rom");
                return 1;
        };

        fread(rom, sizeof(rom), 1, f_rom);
        fclose(f_rom);

        /*for (i = 0x100; i < 0x105; i++) { printf("%02x", rom[i]); } puts("");*/

        memcpy(cpu.memory, rom, 0x10000);

        /*for (i = 0x100; i < 0x105; i++) { printf("%02x", memory[i]); } puts("");*/
        /*for (i = 0x100; i < 0x105; i++) { printf("%02x", cpu.memory[i]); } puts("");*/

        assert(sizeof(u8)  == 1);
        assert(sizeof(i8)  == 1);
        assert(sizeof(u16) == 2);
        assert(sizeof(i16) == 2);
        assert(sizeof(u32) == 4);
        assert(sizeof(i32) == 4);

        init_sm83(&cpu);

        sm83_print_regs_headers();
        sm83_print_regs(&cpu);
        
        for (i = 0; i < 0xFF; i++) {
            sm83_cpu_step(&cpu);
            sm83_print_regs(&cpu);
        }

        return 0;
}

