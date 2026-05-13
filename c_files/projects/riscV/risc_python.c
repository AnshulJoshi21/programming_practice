#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 65536

typedef uint32_t u32;
typedef int32_t  i32;
typedef uint8_t  u8;

static inline i32 sign_extend(const u32 value, const int bits)
{
    const u32 sign_bit = 1U << (bits - 1);
    return (value & (sign_bit - 1)) - (value & sign_bit);
}

static inline u32 get_bits(const u32 value, const u32 start, const int length)
{
    return (value >> start) & ((1U << length) - 1);
}

typedef struct Cpu {
    u8  memory[MEM_SIZE];
    u32 regs[32];
    u32 pc;

} Cpu;

static void cpu_init(Cpu *cpu)
{
    assert(cpu);

    memset(cpu->memory, 0, sizeof(cpu->memory));
    memset(cpu->regs, 0, sizeof(cpu->regs));
    cpu->pc = 0;
}

static u32 cpu_load_word(const Cpu *cpu, const u32 addr)
{
    assert(cpu);

    return cpu->memory[addr] | (cpu->memory[addr + 1] << 8)
         | (cpu->memory[addr + 2] << 16) | (cpu->memory[addr + 3] << 24);
}

static void cpu_store_word(Cpu *cpu, const u32 addr, const u32 value)
{
    assert(cpu);

    cpu->memory[addr]     = value & 0xFF;
    cpu->memory[addr + 1] = (value >> 8) & 0xFF;
    cpu->memory[addr + 2] = (value >> 16) & 0xFF;
    cpu->memory[addr + 3] = (value >> 24) & 0xFF;
}

static u32 cpu_fetch(const Cpu *cpu)
{
    assert(cpu);

    return cpu_load_word(cpu, cpu->pc);
}

static void cpu_step(Cpu *cpu)
{
    assert(cpu);

    const u32 instr = cpu_fetch(cpu);

    const u32 opcode = get_bits(instr, 0, 7);

    const u32 old_pc = cpu->pc;

    cpu->pc += 4;

    u32 rd     = get_bits(instr, 7, 5);
    u32 funct3 = get_bits(instr, 12, 3);
    u32 rs1    = get_bits(instr, 15, 5);
    u32 rs2    = get_bits(instr, 20, 5);
    u32 funct7 = get_bits(instr, 25, 7);

    if (opcode == 0x33) {
        // add
        if (funct3 == 0x0 && funct7 == 0x00) {
            cpu->regs[rd] = (cpu->regs[rs1] + cpu->regs[rs2]) & 0xFFFFFFFF;
        } else if (funct3 == 0x0 && funct7 == 0x20) {
            cpu->regs[rd] = (cpu->regs[rs1] - cpu->regs[rs2]) & 0XFFFFFFFF;
        } else {
            printf("Unknown R-type instruction\n");
            exit(EXIT_FAILURE);
        }
    } else if (opcode == 0x13) {
        i32 imm = sign_extend(get_bits(instr, 20, 12), 12);

        // addi
        if (funct3 == 0x0) {
            cpu->regs[rd] = (cpu->regs[rs1] + imm) & 0xFFFFFFFF;
        } else {
            printf("Unknown I-type instruction\n");
            exit(EXIT_FAILURE);
        }
    } else if (opcode == 0x03) {
        i32 imm = sign_extend(get_bits(instr, 20, 12), 12);

        u32 addr = (cpu->regs[rs1] + imm) & 0xFFFFFFFF;

        // lw = load word
        if (funct3 == 0x2) {
            cpu->regs[rd] = cpu_load_word(cpu, addr);
        } else {
            printf("Unknown load instruction\n");
            exit(EXIT_FAILURE);
        }
    } else if (opcode == 0x23) {
        i32 imm_low  = get_bits(instr, 7, 5);
        i32 imm_high = get_bits(instr, 25, 7);
        i32 imm      = sign_extend((imm_high << 5 | imm_low), 12);

        u32 addr = (cpu->regs[rs1] + imm) & 0xFFFFFFFF;

        // sw = store word
        if (funct3 == 0x2) {
            cpu_store_word(cpu, addr, cpu->regs[rs2]);
        } else {
            printf("Unknown store instruction\n");
            exit(EXIT_FAILURE);
        }
    } else if (opcode == 0x63) {
        i32 imm = (get_bits(instr, 31, 1) << 12 | get_bits(instr, 7, 1) << 11
                   | get_bits(instr, 25, 6) << 5 | get_bits(instr, 8, 4));
        imm     = sign_extend(imm, 13);

        // beq
        if (funct3 == 0x0) {
            if (cpu->regs[rs1] == cpu->regs[rs2]) {
                cpu->pc = old_pc + imm;
            }
        } else if (funct3 == 0x1) {
            if (cpu->regs[rs1] != cpu->regs[rs2]) {
                cpu->pc = old_pc + imm;
            }
        } else {
            printf("Unknown branch instruction\n");
            exit(EXIT_FAILURE);
        }
    } else if (opcode == 0x6F) {
        i32 imm = (get_bits(instr, 31, 1) << 20 | get_bits(instr, 12, 8) << 12
                   | get_bits(instr, 20, 1) << 11
                   | get_bits(instr, 21, 10) << 1);
        imm     = sign_extend(imm, 21);

        // save return addr
        cpu->regs[rd] = cpu->pc;

        // jump
        cpu->pc = old_pc + imm;
    } else if (opcode == 0x37) {
        i32 imm = get_bits(instr, 12, 20) << 12;

        cpu->regs[rd] = imm;
    } else {
        printf("Unknown opcode\n");
        exit(EXIT_FAILURE);
    }

    // harcode reg[0]
    cpu->regs[0] = 0;
}

static void cpu_load_program(Cpu         *cpu,
                             const u32   *program,
                             const size_t program_size,
                             const u32    start_addr)
{
    assert(cpu);

    cpu->pc = start_addr;

    for (size_t i = 0; i < program_size; i++) {
        u32 addr = start_addr + (i * 4);
        cpu_store_word(cpu, addr, program[i]);
    }
}

static void cpu_run(Cpu *cpu, const int steps)
{
    assert(cpu);

    for (int i = 0; i < steps; i++) {
        cpu_step(cpu);
    }
}

int main(int argc, char **argv)
{
    Cpu cpu;
    cpu_init(&cpu);

    const u32 program[] = {
            // addi x1, x0, 10
            0x00A00093,
            // addi x2, x0, 20
            0x01400113,
            // add x3, x1, x2
            0x002081B3,
    };
    const size_t program_size = sizeof(program) / sizeof(program[0]);

    cpu_load_program(&cpu, program, program_size, 0);
    cpu_run(&cpu, 3);

    printf("x1 = %d\n", cpu.regs[1]);
    printf("x2 = %d\n", cpu.regs[2]);
    printf("x3 = %d\n", cpu.regs[3]);

    return 0;
}
