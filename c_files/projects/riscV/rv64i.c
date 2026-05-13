#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 65536
#define CSR_SIZE 4096

typedef uint64_t u64;
typedef uint64_t i64;

typedef uint32_t u32;
typedef uint32_t i32;

typedef uint8_t u8;

// utility functions
static inline i64 sign_extend(const u32 value, const int bits)
{
    const int shift = 64 - bits;
    return (i64)((u64)value << shift) >> shift;
}

static inline u32 get_bits(const u32 value, const u32 start, const int length)
{
    const u32 mask = (1U << length) - 1;
    return (value >> start) & mask;
}

// cpu
typedef struct Cpu {
    u8  memory[MEM_SIZE];
    u64 regs[32];
    u64 pc;
    u64 csrs[CSR_SIZE];

} Cpu;

static void cpu_init(Cpu *cpu)
{
    assert(cpu);

    memset(cpu->memory, 0, sizeof(cpu->memory));
    memset(cpu->regs, 0, sizeof(cpu->regs));
    cpu->pc = 0;
}

// load signed
static i64 cpu_load_byte(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    u32 value = cpu->memory[addr];
    return sign_extend(value, 8);
}

static i64 cpu_load_half(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    u32 value = cpu->memory[addr] | cpu->memory[addr + 1] << 8;
    return sign_extend(value, 16);
}

static i64 cpu_load_word(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    u32 value = cpu->memory[addr] | cpu->memory[addr + 1] << 8
              | cpu->memory[addr + 2] << 16 | cpu->memory[addr + 3] << 24;
    return sign_extend(value, 32);
}

static i64 cpu_load_double(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    i64 value = (i64)cpu->memory[addr] | ((i64)cpu->memory[addr + 1] << 8)
              | ((i64)cpu->memory[addr + 2] << 16)
              | ((i64)cpu->memory[addr + 3] << 24)
              | ((i64)cpu->memory[addr + 4] << 32)
              | ((i64)cpu->memory[addr + 5] << 40)
              | ((i64)cpu->memory[addr + 6] << 48)
              | ((i64)cpu->memory[addr + 7] << 56);
    return value;
}

// load unsigned
static u64 cpu_load_byte_u(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    return (u64)cpu->memory[addr];
}

static u64 cpu_load_half_u(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    return (u64)(cpu->memory[addr] | cpu->memory[addr + 1] << 8);
}

static u64 cpu_load_word_u(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    return (u64)(cpu->memory[addr] | cpu->memory[addr + 1] << 8
                 | cpu->memory[addr + 2] << 16 | cpu->memory[addr + 3] << 24);
}

static u64 cpu_load_double_u(const Cpu *cpu, const u64 addr)
{
    assert(cpu);

    return (u64)((u64)cpu->memory[addr] | ((u64)cpu->memory[addr + 1] << 8)
                 | ((u64)cpu->memory[addr + 2] << 16)
                 | ((u64)cpu->memory[addr + 3] << 24)
                 | ((u64)cpu->memory[addr + 4] << 32)
                 | ((u64)cpu->memory[addr + 5] << 40)
                 | ((u64)cpu->memory[addr + 6] << 48)
                 | ((u64)cpu->memory[addr + 7] << 56));
}

// store
static void cpu_store_byte(Cpu *cpu, const u64 addr, const u64 value)
{
    assert(cpu);

    cpu->memory[addr] = value & 0xFF;
}

static void cpu_store_half(Cpu *cpu, const u64 addr, const u64 value)
{
    assert(cpu);

    cpu->memory[addr]     = value & 0xFF;
    cpu->memory[addr + 1] = (value >> 8) & 0xFF;
}

static void cpu_store_word(Cpu *cpu, const u64 addr, const u64 value)
{
    assert(cpu);

    cpu->memory[addr]     = value & 0xFF;
    cpu->memory[addr + 1] = (value >> 8) & 0xFF;
    cpu->memory[addr + 2] = (value >> 16) & 0xFF;
    cpu->memory[addr + 3] = (value >> 24) & 0xFF;
}

static void cpu_store_double(Cpu *cpu, const u64 addr, const u64 value)
{
    assert(cpu);

    cpu->memory[addr]     = value & 0xFF;
    cpu->memory[addr + 1] = (value >> 8) & 0xFF;
    cpu->memory[addr + 2] = (value >> 16) & 0xFF;
    cpu->memory[addr + 3] = (value >> 24) & 0xFF;
    cpu->memory[addr + 4] = (value >> 32) & 0xFF;
    cpu->memory[addr + 5] = (value >> 40) & 0xFF;
    cpu->memory[addr + 6] = (value >> 48) & 0xFF;
    cpu->memory[addr + 7] = (value >> 56) & 0xFF;
}

static u32 cpu_fetch_instruction(const Cpu *cpu)
{
    assert(cpu);

    return cpu_load_word_u(cpu, cpu->pc);
}

static void cpu_step(Cpu *cpu)
{
    assert(cpu);

    const u32 instr  = cpu_fetch_instruction(cpu);
    const u64 old_pc = cpu->pc;

    const u32 opcode = get_bits(instr, 0, 7);
    const u32 rd     = get_bits(instr, 7, 5);
    const u32 funct3 = get_bits(instr, 12, 3);
    const u32 rs1    = get_bits(instr, 15, 5);
    const u32 rs2    = get_bits(instr, 20, 5);
    const u32 funct7 = get_bits(instr, 25, 7);

    // i type
    const i64 imm_i = sign_extend(get_bits(instr, 20, 12), 12);

    // s type
    i64       imm_temp = get_bits(instr, 7, 5) | get_bits(instr, 25, 7) << 5;
    const i64 imm_s    = sign_extend(imm_temp, 12);

    // b type
    imm_temp = get_bits(instr, 8, 4) << 1 | get_bits(instr, 25, 6) << 5
             | get_bits(instr, 7, 1) << 11 | get_bits(instr, 31, 1) << 12;
    const i64 imm_b = sign_extend(imm_temp, 13);

    // j type
    imm_temp = get_bits(instr, 21, 10) << 1 | get_bits(instr, 20, 1) << 11
             | get_bits(instr, 12, 8) << 12 | get_bits(instr, 31, 1) << 20;
    const i64 imm_j = sign_extend(imm_temp, 21);

    // u type
    const i64 imm_u = sign_extend((instr & 0xFFFFF000), 32);

    const u64 shamt64 = (u64)get_bits(instr, 20, 6);  // shift amount
    const u32 shamt32 = (u32)get_bits(instr, 20, 5);  // shift amount

    // system
    const u32 csr_addr = get_bits(instr, 20, 12);

    cpu->pc += 4;

    switch (opcode) {
        // r type integer operations
        case 0x33:
            switch (funct3) {
                // add and sub
                case 0x0:
                    // add
                    if (funct7 == 0x00) {
                        cpu->regs[rd] = cpu->regs[rs1] + cpu->regs[rs2];
                    }
                    // sub
                    else if (funct7 == 0x20) {
                        cpu->regs[rd] = cpu->regs[rs1] - cpu->regs[rs2];
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                // sll = shift logical left - 6bits of rs2
                case 0x1:
                    if (funct7 == 0x00) {
                        cpu->regs[rd]
                                = cpu->regs[rs1] << (cpu->regs[rs2] & 0x3F);
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                // slt = set less than
                case 0x2:
                    if (funct7 == 0x00) {
                        cpu->regs[rd]
                                = ((i64)cpu->regs[rs1] < (i64)cpu->regs[rs2])
                                        ? 1
                                        : 0;
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                // sltu = set less than unsigned
                case 0x3:
                    if (funct7 == 0x00) {
                        cpu->regs[rd]
                                = ((u64)cpu->regs[rs1] < (u64)cpu->regs[rs2])
                                        ? 1
                                        : 0;
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                // xor
                case 0x4:
                    if (funct7 == 0x00) {
                        cpu->regs[rd] = cpu->regs[rs1] ^ cpu->regs[rs2];
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                // srl and sra - rs2 6bits
                // shift right logical and shift right arithmetic
                case 0x5:
                    if (funct7 == 0x00) {
                        // srl
                        cpu->regs[rd] = (u64)cpu->regs[rs1]
                                     >> (cpu->regs[rs2] & 0x3F);

                    } else if (funct7 == 0x20) {
                        // sra
                        cpu->regs[rd] = (i64)cpu->regs[rs1]
                                     >> (cpu->regs[rs2] & 0x3F);

                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                // or
                case 0x6:
                    if (funct7 == 0x00) {
                        cpu->regs[rd] = cpu->regs[rs1] | cpu->regs[rs2];
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                // and
                case 0x7:
                    if (funct7 == 0x00) {
                        cpu->regs[rd] = cpu->regs[rs1] & cpu->regs[rs2];
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                default:
                    printf("Unknown instruction\n");
                    exit(EXIT_FAILURE);
                    break;
            }

            break;

        // i type - integer immediate operations
        case 0x13:
            switch (funct3) {
                // addi
                case 0x0:
                    cpu->regs[rd] = cpu->regs[rs1] + imm_i;
                    break;

                // slli = shift logical left imm
                case 0x1:
                    if (funct7 == 0x00) {
                        cpu->regs[rd] = cpu->regs[rs1] << shamt64;
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }
                    break;

                // slti = set less than imm
                case 0x2:
                    cpu->regs[rd] = ((i64)cpu->regs[rs1] < (i64)imm_i) ? 1 : 0;
                    break;

                // sltiu = set less than imm unsigned
                case 0x3:
                    cpu->regs[rd] = ((u64)cpu->regs[rs1] < (u64)imm_i) ? 1 : 0;
                    break;

                // xori
                case 0x4:
                    cpu->regs[rd] = cpu->regs[rs1] ^ imm_i;
                    break;

                // srli and srai
                // shift right logical and shift right arithmetic
                case 0x5:
                    if (funct7 == 0x00) {
                        cpu->regs[rd] = (u64)cpu->regs[rs1] >> shamt64;
                    } else if (funct7 == 0x20) {
                        cpu->regs[rd] = (i64)cpu->regs[rs1] >> shamt64;
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }
                    break;

                // ori
                case 0x6:
                    cpu->regs[rd] = cpu->regs[rs1] | imm_i;
                    break;

                // andi
                case 0x7:
                    cpu->regs[rd] = cpu->regs[rs1] & imm_i;
                    break;

                default:
                    printf("Unknown instruction\n");
                    exit(EXIT_FAILURE);
                    break;
            }

            break;

        // word operations - (reg to reg)
        case 0x3B:
            switch (funct3) {
                case 0x0:
                    if (funct7 == 0x00) {
                        // addw
                        cpu->regs[rd]
                                = sign_extend((u32)cpu->regs[rs1]
                                                      + (u32)cpu->regs[rs2],
                                              32);
                    } else if (funct7 == 0x20) {
                        // subw
                        cpu->regs[rd]
                                = sign_extend((u32)cpu->regs[rs1]
                                                      - (u32)cpu->regs[rs2],
                                              32);
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                case 0x1:
                    if (funct7 == 0x00) {
                        // sllw = shift left logical
                        cpu->regs[rd] = sign_extend(((u32)cpu->regs[rs1]
                                                     << get_bits(cpu->regs[rs2],
                                                                 0,
                                                                 5)),
                                                    32);
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                case 0x5:
                    if (funct7 == 0x00) {
                        // srlw = shift right logical
                        cpu->regs[rd] = sign_extend(((u32)cpu->regs[rs1]
                                                     >> get_bits(cpu->regs[rs2],
                                                                 0,
                                                                 5)),
                                                    32);
                    } else if (funct7 == 0x20) {
                        // sraw = shift right arithmetic
                        cpu->regs[rd] = sign_extend(((i32)cpu->regs[rs1]
                                                     >> get_bits(cpu->regs[rs2],
                                                                 0,
                                                                 5)),
                                                    32);

                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                default:
                    printf("Unknown instruction\n");
                    exit(EXIT_FAILURE);
                    break;
            }

            break;

        // immediate word operations
        case 0x1B:
            switch (funct3) {
                case 0x0:
                    // addiw
                    cpu->regs[rd]
                            = sign_extend(((u32)cpu->regs[rs1] + imm_i), 32);
                    break;

                case 0x1:
                    // slliw = shift left logical
                    if (funct7 == 0x00) {
                        cpu->regs[rd]
                                = sign_extend(((u32)cpu->regs[rs1] << shamt32),
                                              32);
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }
                    break;

                case 0x5:
                    if (funct7 == 0x00) {
                        // srliw = shift right logical
                        cpu->regs[rd]
                                = sign_extend(((u32)cpu->regs[rs1] >> shamt32),
                                              32);
                    } else if (funct7 == 0x20) {
                        // sraiw = shift right arithmetic
                        cpu->regs[rd]
                                = sign_extend(((i32)cpu->regs[rs1] >> shamt32),
                                              32);
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    break;

                default:
                    printf("Unknown instruction\n");
                    exit(EXIT_FAILURE);
                    break;
            }
            break;

        // load instructions
        case 0x03:
            switch (funct3) {
                case 0x0:
                    // lb = load byte - signed
                    cpu->regs[rd] = cpu_load_byte(cpu, cpu->regs[rs1] + imm_i);
                    break;

                case 0x1:
                    // lh = load half - signed
                    cpu->regs[rd] = cpu_load_half(cpu, cpu->regs[rs1] + imm_i);
                    break;

                case 0x2:
                    // lw = load word - signed
                    cpu->regs[rd] = cpu_load_word(cpu, cpu->regs[rs1] + imm_i);
                    break;

                case 0x3:
                    // ld = load double - signed
                    cpu->regs[rd]
                            = cpu_load_double(cpu, cpu->regs[rs1] + imm_i);
                    break;

                case 0x4:
                    // lbu = load byte - unsigned
                    cpu->regs[rd]
                            = cpu_load_byte_u(cpu, cpu->regs[rs1] + imm_i);
                    break;

                case 0x5:
                    // lhu = load half - unsigned
                    cpu->regs[rd]
                            = cpu_load_half_u(cpu, cpu->regs[rs1] + imm_i);
                    break;

                case 0x6:
                    // lwu = load word - unsigned
                    cpu->regs[rd]
                            = cpu_load_word_u(cpu, cpu->regs[rs1] + imm_i);
                    break;

                default:
                    printf("Unknown instruction\n");
                    exit(EXIT_FAILURE);
                    break;
            }

            break;

        // store instructions
        case 0x23:
            switch (funct3) {
                case 0x0:
                    // sb = store byte
                    cpu_store_byte(cpu, cpu->regs[rs1] + imm_s, cpu->regs[rs2]);
                    break;

                case 0x1:
                    // sh = store half
                    cpu_store_half(cpu, cpu->regs[rs1] + imm_s, cpu->regs[rs2]);
                    break;

                case 0x2:
                    // sw = store word
                    cpu_store_word(cpu, cpu->regs[rs1] + imm_s, cpu->regs[rs2]);
                    break;

                case 0x3:
                    // sd = store double
                    cpu_store_double(cpu,
                                     cpu->regs[rs1] + imm_s,
                                     cpu->regs[rs2]);
                    break;

                default:
                    printf("Unknown instruction\n");
                    exit(EXIT_FAILURE);
                    break;
            }

            break;

        // branch instructions
        case 0x63:
            switch (funct3) {
                case 0x0:
                    // beq = branch if equal
                    if (cpu->regs[rs1] == cpu->regs[rs2]) {
                        cpu->pc += imm_b;
                    }
                    break;

                case 0x1:
                    // bne = branch if not equal
                    if (cpu->regs[rs1] != cpu->regs[rs2]) {
                        cpu->pc += imm_b;
                    }
                    break;

                case 0x4:
                    // blt = branch if less than
                    if ((i64)cpu->regs[rs1] < (i64)cpu->regs[rs2]) {
                        cpu->pc += imm_b;
                    }
                    break;

                case 0x5:
                    // bge = branch if greater than or equal
                    if ((i64)cpu->regs[rs1] >= (i64)cpu->regs[rs2]) {
                        cpu->pc += imm_b;
                    }
                    break;

                case 0x6:
                    // bltu = branch if less than (unsigned)
                    if ((u64)cpu->regs[rs1] < (u64)cpu->regs[rs2]) {
                        cpu->pc += imm_b;
                    }
                    break;

                case 0x7:
                    // bgeu = branch if greater than or equal (unsigned)
                    if ((u64)cpu->regs[rs1] >= (u64)cpu->regs[rs2]) {
                        cpu->pc += imm_b;
                    }
                    break;

                default:
                    printf("Unknown instruction\n");
                    exit(EXIT_FAILURE);
                    break;
            }
            break;

        // jump instructions
        //
        // jal = jump and link
        case 0x6F:
            cpu->regs[rd] = cpu->pc;
            cpu->pc += imm_j;
            break;

        // jalr = jump and link register
        case 0x67:
            if (funct3 == 0x0) {
                cpu->regs[rd] = cpu->pc;
                cpu->pc += (cpu->regs[rs1] + imm_i) & ~1ULL;
            } else {
                printf("Unknown instruction\n");
                exit(EXIT_FAILURE);
            }
            break;

        // upper immediate instructions
        //
        // lui = load upper immediate
        case 0x37:
            cpu->regs[rd] = imm_u;
            break;

        // auipc = add upper immediate to pc
        case 0x17:
            cpu->regs[rd] = cpu->pc + imm_u;
            break;

        // memory ordering - fence (i type) (misc-mem)
        case 0x0F:
            break;

        // system instructions
        case 0x73:
            const u64 t    = cpu->csrs[csr_addr];
            const u64 uimm = (u64)rs1;

            switch (funct3) {
                // ecall and ebreak
                case 0x0:
                    // ecall = environment call
                    if (csr_addr == 0x00) {
                        printf("ECALL at pc=0x%lX\n", old_pc);
                        exit(EXIT_SUCCESS);
                    } else if (csr_addr == 0x01) {
                        printf("EBREAK at pc=0x%lX\n", old_pc);
                    } else {
                        printf("Unknown instruction\n");
                        exit(EXIT_FAILURE);
                    }

                    // ebreak = breakpoint
                    break;

                // csrrw = atomic read/ write csr
                case 0x1:
                    cpu->csrs[csr_addr] = cpu->regs[rs1];
                    cpu->regs[rd]       = t;
                    break;

                // csrrs = atomic read/set csr
                case 0x2:
                    cpu->csrs[csr_addr] |= cpu->regs[rs1];
                    cpu->regs[rd] = t;
                    break;

                // csrrc = atomic read/ clear csr
                case 0x3:
                    cpu->csrs[csr_addr] &= ~cpu->regs[rs1];
                    cpu->regs[rd] = t;
                    break;

                // csrrwi = immediate csr write
                case 0x5:
                    cpu->csrs[csr_addr] = uimm;
                    cpu->regs[rd]       = t;
                    break;

                // csrrsi = immediate csr set
                case 0x6:
                    cpu->csrs[csr_addr] |= uimm;
                    cpu->regs[rd] = t;
                    break;

                // csrrci = immediate csr clear
                case 0x7:
                    cpu->csrs[csr_addr] &= uimm;
                    cpu->regs[rd] = t;
                    break;
            }
            break;

        default:
            printf("Unknown instruction\n");
            exit(EXIT_FAILURE);
            break;
    }

    // reg[0] is hardwired to 0 in riscV
    cpu->regs[0] = 0;
}

static void cpu_load_program(Cpu         *cpu,
                             const u32   *program,
                             const size_t program_size,
                             const u64    start_addr)
{
    assert(cpu);

    cpu->pc = start_addr;

    for (size_t i = 0; i < program_size; i++) {
        u64 addr = (u64)(start_addr + (i * 4));
        cpu_store_word(cpu, addr, program[i]);
    }
}

static void cpu_run(Cpu *cpu, const uint steps)
{
    assert(cpu);

    for (uint i = 0; i < steps; i++) {
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

    printf("x1 = %lu\n", cpu.regs[1]);
    printf("x2 = %lu\n", cpu.regs[2]);
    printf("x3 = %lu\n", cpu.regs[3]);

    return 0;
}
