#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 65536

typedef uint8_t  u8;
typedef uint32_t u32;
typedef int32_t  i32;

u8 memory[MEM_SIZE];

typedef struct Cpu {
    u32 regs[32];
    u32 pc;

} Cpu;

Cpu cpu;

u32 load_word(u32 addr)
{
    if (addr + 3 >= MEM_SIZE) {
        printf("Memory access violation: 0x%08X\n", addr);
        exit(EXIT_FAILURE);
    }

    return (memory[addr]) | (memory[addr + 1] << 8) | (memory[addr + 2] << 16) |
           (memory[addr + 3] << 24);
}

void store_word(u32 addr, u32 value)
{
    if (addr + 3 >= MEM_SIZE) {
        printf("Memory access violation: 0x%08X\n", addr);
        exit(EXIT_FAILURE);
    }

    memory[addr]     = value & 0xFF;
    memory[addr + 1] = (value >> 8) & 0xFF;
    memory[addr + 2] = (value >> 16) & 0xFF;
    memory[addr + 3] = (value >> 24) & 0xFF;
}

i32 sign_extend(u32 value, int bits)
{
    u32 mask = 1U << (bits - 1);
    return (value ^ mask) - mask;
}

void execute(u32 instruction)
{
    // funct7, rs2, rs1, funct3, rd, opcode
    //
    u32 opcode = instruction & 0x7F;
    u32 rd     = (instruction >> 7) & 0x1F;
    u32 funct3 = (instruction >> 12) & 0x7;
    u32 rs1    = (instruction >> 15) & 0x1F;
    u32 rs2    = (instruction >> 20) & 0x1F;
    u32 funct7 = (instruction >> 25) & 0x7F;

    i32 imm_i = sign_extend(instruction >> 20, 12);
    i32 imm_s = sign_extend(((instruction >> 7) & 0x1F) | (((instruction >> 25) & 0x7F) << 5), 12);
    i32 imm_b =
        sign_extend((((instruction >> 8) & 0xF) << 1) | (((instruction >> 25) & 0x3F) << 5) |
                        (((instruction >> 7) & 0x1) << 11) | (((instruction >> 31) & 0x1) << 12),
                    13);
    i32 imm_j =
        sign_extend((((instruction >> 21) & 0x3FF) << 1) | (((instruction >> 20) & 0x1) << 11) |
                        (((instruction >> 12) & 0xFF) << 12) | (((instruction >> 31) & 0x1) << 20),
                    21);

    switch (opcode) {
            // r type instruction
        case 0x33:
            switch (funct3) {
                case 0x0:
                    // add
                    if (funct7 == 0x00) {
                        cpu.regs[rd] = cpu.regs[rs1] + cpu.regs[rs2];
                    }
                    // sub
                    if (funct7 == 0x20) {
                        cpu.regs[rd] = cpu.regs[rs1] - cpu.regs[rs2];
                    }
                    break;
            }

            // each instruction = 4bytes
            cpu.pc += 4;
            break;

        // i type instruction
        case 0x13:
            switch (funct3) {
                case 0x0:
                    cpu.regs[rd] = cpu.regs[rs1] + imm_i;
                    break;
            }

            cpu.pc += 4;
            break;

        // load instruction
        case 0x03:
            switch (funct3) {
                // lw = load word
                // rd = memory[rs1 + offset]
                case 0x2:
                    cpu.regs[rd] = load_word(cpu.regs[rs1] + imm_i);
            }

            cpu.pc += 4;
            break;

        // store instruction
        case 0x23:
            switch (funct3) {
                    // sw = store word
                    // memory[rs1 + offset] <- rs2

                case 0x2:
                    store_word(cpu.regs[rs1] + imm_s, cpu.regs[rs2]);
                    break;
            }

            cpu.pc += 4;
            break;

        // branch instructions
        case 0x63:
            switch (funct3) {
                    // beq = branch if equal
                    // if (rs1 == rs2)
                    // { jump }

                case 0x0:
                    if (cpu.regs[rs1] == cpu.regs[rs2]) {
                        cpu.pc += imm_b;
                    } else {
                        cpu.pc += 4;
                    }

                    break;
            }

            break;

        // jump instructions
        case 0x6F:
            // jal = jump and link
            //
            // rd = return address
            // pc = pc + offset

            cpu.regs[rd] = cpu.pc + 4;
            cpu.pc += imm_j;

            break;

        // system instructions
        case 0x73:
            // ecall - stop emulator
            if (instruction == 0x00000073) {
                printf("ECALL encountered\n");
                exit(EXIT_SUCCESS);
            }

            break;

        // unknown opcode
        default:
            printf("Unknown opcode: 0x%02X\n", opcode);
            exit(EXIT_FAILURE);
    }

    // reg 0 is hardwired to 0
    cpu.regs[0] = 0;
}

void load_program(const char *filename)
{
    FILE *f = fopen(filename, "rb");

    if (!f) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // load entire binary into ram
    size_t n = fread(memory, 1, MEM_SIZE, f);
    printf("Loaded %zu bytes\n", n);

    fclose(f);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage %s program.bin\n", argv[0]);
    }

    // cpu clear state
    memset(&cpu, 0, sizeof(cpu));

    // load binary program
    load_program(argv[1]);

    // start at addr 0
    cpu.pc = 0;

    // initialize stack pointer (x2 = sp)
    cpu.regs[2] = MEM_SIZE - 4;

    // fetch/decode/execute loop
    while (1) {
        u32 instr = load_word(cpu.pc);

        // debug
        printf("PC: 0x%08X INSTR: 0x%08X\n", cpu.pc, instr);

        // execute instruction
        execute(instr);
    }

    return 0;
}
