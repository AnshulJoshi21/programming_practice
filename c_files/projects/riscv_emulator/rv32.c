#include <assert.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>

typedef uint32_t u32;
typedef int32_t  i32;
typedef uint8_t  u8;

#define MEM_SIZE 65536
#define CSRS_SIZE 4096

// MCAUSE VALUES
#define CAUSE_MISALIGNED_FETCH 0
#define CAUSE_ILLEGAL_INSTRUCTION 2
#define CAUSE_BREAKPOINT 3
#define CAUSE_ECALL_UMODE 8  // user
#define CAUSE_ECALL_MMODE 11 // machine

// UTILITY
static i32 sign_extend(const u32 value, const int bits) {
    u32 mask = 1U << (bits - 1);
    return (value ^ mask) - mask;
}

static u32 get_bits(const u32 value, const u32 start, const int length) {
    u32 mask = (1U << length) - 1;
    return (value >> start) & mask;
}

// CPU
typedef struct {
    u8  memory[MEM_SIZE];
    u32 registers[32];
    u32 pc;
    u32 csrs[CSRS_SIZE];

} Cpu;

static void cpu_init(Cpu* cpu) {
    assert(cpu);

    memset(cpu->memory, 0, sizeof(cpu->memory));
    memset(cpu->registers, 0, sizeof(cpu->registers));
    cpu->pc = 0;
    memset(cpu->csrs, 0, sizeof(cpu->csrs));
}

// unsigned
static u32 cpu_load_byte_u(const Cpu* cpu, u32 addr) {
    assert(cpu);

    return (u32) cpu->memory[addr];
}

static u32 cpu_load_half_u(const Cpu* cpu, u32 addr) {
    assert(cpu);

    return ((u32) cpu->memory[addr]) | ((u32) cpu->memory[addr + 1] << 8);
}

static u32 cpu_load_word_u(const Cpu* cpu, u32 addr) {
    assert(cpu);

    return ((u32) cpu->memory[addr]) | ((u32) cpu->memory[addr + 1] << 8)
           | ((u32) cpu->memory[addr + 2] << 16) | ((u32) cpu->memory[addr + 3] << 24);
}

// signed
static i32 cpu_load_byte(const Cpu* cpu, u32 addr) {
    assert(cpu);

    return sign_extend(cpu->memory[addr], 8);
}

static i32 cpu_load_half(const Cpu* cpu, u32 addr) {
    assert(cpu);

    u32 value = ((u32) cpu->memory[addr]) | ((u32) cpu->memory[addr + 1] << 8);
    return sign_extend(value, 16);
}

static i32 cpu_load_word(const Cpu* cpu, u32 addr) {
    assert(cpu);

    u32 value = ((u32) cpu->memory[addr]) | ((u32) cpu->memory[addr + 1] << 8)
                | ((u32) cpu->memory[addr + 2] << 16) | ((u32) cpu->memory[addr + 3] << 24);

    return (i32) value;
}

// store
static void cpu_store_byte(Cpu* cpu, u32 value, u32 addr) {
    assert(cpu);

    cpu->memory[addr] = get_bits(value, 0, 8);
}

static void cpu_store_half(Cpu* cpu, u32 value, u32 addr) {
    assert(cpu);

    cpu->memory[addr]     = get_bits(value, 0, 8);
    cpu->memory[addr + 1] = get_bits(value, 8, 8);
}

static void cpu_store_word(Cpu* cpu, u32 value, u32 addr) {
    assert(cpu);

    cpu->memory[addr]     = get_bits(value, 0, 8);
    cpu->memory[addr + 1] = get_bits(value, 8, 8);
    cpu->memory[addr + 2] = get_bits(value, 16, 8);
    cpu->memory[addr + 3] = get_bits(value, 24, 8);
}

// csrs helpers
static u32 cpu_csrs_read(const Cpu* cpu, const u32 addr) {
    assert(cpu);

    return cpu->csrs[addr];
}

static void cpu_csrs_write(Cpu* cpu, const u32 addr, const u32 value) {
    assert(cpu);

    cpu->csrs[addr] = value;
}

static void cpu_trap(Cpu* cpu, const u32 cause, const u32 bad_pc) {
    assert(cpu);

    cpu_csrs_write(cpu, 0x341, bad_pc); // mepc = faulting pc
    cpu_csrs_write(cpu, 0x342, cause);  // mcause = why

    // mstatus: save mie to mpie, clear mie (disable interrrupts)
    u32 mstatus = cpu_csrs_read(cpu, 0x300);
    u32 mie     = get_bits(mstatus, 3, 1); // current mie bit
    mstatus &= ~(1U << 7);                 // clear mpie
    mstatus |= (mie << 7);                 // mpie = old mie
    mstatus &= ~(1U << 3);                 // clear mie
    cpu_csrs_write(cpu, 0x300, mstatus);

    // jump to handler
    cpu->pc = cpu_csrs_read(cpu, 0x305); // mtvec
}

// fetch
static u32 cpu_fetch(const Cpu* cpu) {
    assert(cpu);

    return cpu_load_word_u(cpu, cpu->pc);
}

// decode + execute
static void cpu_step(Cpu* cpu) {
    assert(cpu);

    u32 instruction = cpu_fetch(cpu);

    const u32 opcode = get_bits(instruction, 0, 7);
    const u32 rd     = get_bits(instruction, 7, 5);
    const u32 funct3 = get_bits(instruction, 12, 3);
    const u32 rs1    = get_bits(instruction, 15, 5);
    const u32 rs2    = get_bits(instruction, 20, 5);
    const u32 funct7 = get_bits(instruction, 25, 7);

    // immediate types
    //
    const i32 imm_i = sign_extend(get_bits(instruction, 20, 12), 12);

    const i32 imm_s
        = sign_extend((get_bits(instruction, 7, 5) | get_bits(instruction, 25, 7) << 5), 12);

    const i32 imm_b = sign_extend(
        ((get_bits(instruction, 8, 4) << 1) | (get_bits(instruction, 25, 6) << 5)
         | (get_bits(instruction, 7, 1) << 11) | (get_bits(instruction, 31, 1) << 12)),
        13);

    const i32 imm_u = (i32) (instruction & 0xFFFFF000);

    const i32 imm_j = sign_extend(
        (get_bits(instruction, 21, 10) << 1) | (get_bits(instruction, 20, 1) << 11)
            | (get_bits(instruction, 12, 8) << 12) | (get_bits(instruction, 31, 1) << 20),
        21);

    // shift amount
    u32 shamt;
    u32 shamt_i;

    // temp
    u32 addr;

    const u32 old_pc = cpu->pc;
    cpu->pc += 4;

    switch (opcode) {
        // r type
        case 0x33:
            shamt = get_bits(cpu->registers[rs2], 0, 5);

            switch (funct3) {
                case 0x0:
                    switch (funct7) {
                        // add
                        case 0x00:
                            cpu->registers[rd] = cpu->registers[rs1] + cpu->registers[rs2];
                            break;

                        // sub
                        case 0x20:
                            cpu->registers[rd] = cpu->registers[rs1] - cpu->registers[rs2];
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                case 0x4:
                    switch (funct7) {
                        // xor
                        case 0x00:
                            cpu->registers[rd] = cpu->registers[rs1] ^ cpu->registers[rs2];
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }
                    break;

                case 0x6:
                    switch (funct7) {
                        // or
                        case 0x00:
                            cpu->registers[rd] = cpu->registers[rs1] | cpu->registers[rs2];
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                case 0x7:
                    switch (funct7) {
                        // and
                        case 0x00:
                            cpu->registers[rd] = cpu->registers[rs1] & cpu->registers[rs2];
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                case 0x1:
                    switch (funct7) {
                        // sll = shift left logical
                        case 0x00:
                            cpu->registers[rd] = (u32) cpu->registers[rs1] << shamt;
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                case 0x5:
                    switch (funct7) {
                        // srl = shift right logical
                        case 0x00:
                            cpu->registers[rd] = (u32) cpu->registers[rs1] >> shamt;
                            break;

                        // sra = shift right arithmetic
                        case 0x20:
                            cpu->registers[rd] = (i32) cpu->registers[rs1] >> shamt;
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                case 0x2:
                    switch (funct7) {
                        // slt = set less than
                        case 0x00:
                            cpu->registers[rd]
                                = ((i32) cpu->registers[rs1] < (i32) cpu->registers[rs2]) ? 1 : 0;
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                case 0x3:
                    switch (funct7) {
                        // sltu = set less than unsigned
                        case 0x00:
                            cpu->registers[rd]
                                = ((u32) cpu->registers[rs1] < (u32) cpu->registers[rs2]) ? 1 : 0;
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                // unknown
                default:
                    cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                    break;
            }

            break;

        // immediate = i type
        case 0x13:
            shamt_i = get_bits(imm_i, 0, 5);

            switch (funct3) {
                // addi
                case 0x0:
                    cpu->registers[rd] = cpu->registers[rs1] + imm_i;
                    break;

                // xori
                case 0x4:
                    cpu->registers[rd] = cpu->registers[rs1] ^ imm_i;
                    break;

                // ori
                case 0x6:
                    cpu->registers[rd] = cpu->registers[rs1] | imm_i;
                    break;

                // andi
                case 0x7:
                    cpu->registers[rd] = cpu->registers[rs1] & imm_i;
                    break;

                // slli = shift left logical imm
                case 0x1:
                    switch (funct7) {
                        case 0x00:
                            cpu->registers[rd] = (u32) cpu->registers[rs1] << shamt_i;
                            break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                // srli and srai
                case 0x5:
                    switch (funct7) {
                        // srli = shift right logical imm
                        case 0x00:
                            cpu->registers[rd] = (u32) cpu->registers[rs1] >> shamt_i;
                            break;
                        // srai = shift right arithmetic imm
                        case 0x20:
                            cpu->registers[rd] = (i32) cpu->registers[rs1] >> shamt_i;
                            break;
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }
                    break;

                // slti = set less than imm
                case 0x2:
                    cpu->registers[rd] = ((i32) cpu->registers[rs1] < (i32) imm_i) ? 1 : 0;
                    break;

                // sltiu = set less than imm unsigned
                case 0x3:
                    cpu->registers[rd] = ((u32) cpu->registers[rs1] < (u32) imm_i) ? 1 : 0;
                    break;

                // unknown
                default:
                    cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                    break;
            }

            break;

        // load  - i type
        case 0x03:
            addr = cpu->registers[rs1] + imm_i;

            switch (funct3) {
                case 0x0:
                    cpu->registers[rd] = cpu_load_byte(cpu, addr);
                    break;

                case 0x1:
                    cpu->registers[rd] = cpu_load_half(cpu, addr);
                    break;

                case 0x2:
                    cpu->registers[rd] = cpu_load_word(cpu, addr);
                    break;

                case 0x4:
                    cpu->registers[rd] = cpu_load_byte_u(cpu, addr);
                    break;

                case 0x5:
                    cpu->registers[rd] = cpu_load_half_u(cpu, addr);
                    break;

                // unknown
                default:
                    cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                    break;
            }

            break;

        // store  = s type
        case 0x23:
            addr = cpu->registers[rs1] + imm_s;

            switch (funct3) {
                case 0x0:
                    cpu_store_byte(cpu, cpu->registers[rs2], addr);
                    break;

                case 0x1:
                    cpu_store_half(cpu, cpu->registers[rs2], addr);
                    break;

                case 0x2:
                    cpu_store_word(cpu, cpu->registers[rs2], addr);
                    break;

                // unknown
                default:
                    cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                    break;
            }

            break;

        // branch  = b type
        case 0x63:
            switch (funct3) {
                case 0x0:
                    // beq = branch equal to
                    if ((i32) cpu->registers[rs1] == (i32) cpu->registers[rs2])
                        cpu->pc = old_pc + imm_b;
                    break;

                case 0x1:
                    // bne = branch not equal to
                    if ((i32) cpu->registers[rs1] != (i32) cpu->registers[rs2])
                        cpu->pc = old_pc + imm_b;
                    break;

                case 0x4:
                    // blt = branch less than
                    if ((i32) cpu->registers[rs1] < (i32) cpu->registers[rs2])
                        cpu->pc = old_pc + imm_b;
                    break;

                case 0x5:
                    // bge = branch greater than equal to
                    if ((i32) cpu->registers[rs1] >= (i32) cpu->registers[rs2])
                        cpu->pc = old_pc + imm_b;
                    break;

                case 0x6:
                    // bltu = branch less than unsigned
                    if ((u32) cpu->registers[rs1] < (u32) cpu->registers[rs2])
                        cpu->pc = old_pc + imm_b;
                    break;

                case 0x7:
                    // bgeu = branch greater than equal to unsigned
                    if ((u32) cpu->registers[rs1] >= (u32) cpu->registers[rs2])
                        cpu->pc = old_pc + imm_b;
                    break;

                // unknown
                default:
                    cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                    break;
            }

            break;

        // jump and link = j type
        case 0x6F:
            cpu->registers[rd] = old_pc + 4;
            cpu->pc            = old_pc + imm_j;

            break;

        // jump and link register = i type
        case 0x67:
            switch (funct3) {
                case 0x0:
                    cpu->registers[rd] = old_pc + 4;
                    cpu->pc            = (cpu->registers[rs1] + imm_i) & ~1U;
                    break;

                // unknown
                default:
                    cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                    break;
            }

            break;

        // lui  = load upper immediate = u type
        case 0x37:
            cpu->registers[rd] = imm_u;
            break;

        // auipc = add upper immediate to pc = u type
        case 0x17:
            cpu->registers[rd] = old_pc + imm_u;
            break;

        // system = i type
        // csrs - control and status registers
        case 0x73:
            switch (funct3) {
                case 0x0:
                    switch (imm_i) {
                        // ecall
                        case 0x0:
                            cpu_trap(cpu, CAUSE_ECALL_MMODE, old_pc);
                            break;

                        // ebreak
                        case 0x1:
                            cpu_trap(cpu, CAUSE_BREAKPOINT, old_pc);
                            break;

                        // mret = machine return from trap
                        case 0x302: { // restore pc from mepc
                            cpu->pc = cpu_csrs_read(cpu, 0x341);
                            // restore mstatus: mie = mpie, set mpie
                            u32 mstatus = cpu_csrs_read(cpu, 0x300);
                            u32 mpie    = get_bits(mstatus, 7, 1);
                            mstatus &= ~(1U << 3);  // clear mie
                            mstatus |= (mpie << 3); // mie = mpie
                            mstatus |= (1U << 7);   // mpie = 1
                            cpu_csrs_write(cpu, 0x300, mstatus);

                        } break;

                        // unknown
                        default:
                            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                            break;
                    }

                    break;

                // csrrw - atomic read/write
                case 0x1: {
                    u32 old = cpu_csrs_read(cpu, imm_i & 0xFFF);
                    cpu_csrs_write(cpu, imm_i & 0xFFF, cpu->registers[rs1]);
                    cpu->registers[rd] = old;
                } break;

                // csrrs - atomic read/set bits
                case 0x2: {
                    u32 old = cpu_csrs_read(cpu, imm_i & 0xFFF);
                    cpu_csrs_write(cpu, imm_i & 0xFFF, old | cpu->registers[rs1]);
                    cpu->registers[rd] = old;
                } break;

                // csrrc - atomic read/clear bits
                case 0x3: {
                    u32 old = cpu_csrs_read(cpu, imm_i & 0xFFF);
                    cpu_csrs_write(cpu, imm_i & 0xFFF, old & ~cpu->registers[rs1]);
                    cpu->registers[rd] = old;
                } break;

                // csrrwi - csrrw with uimm5 instead of rs1
                case 0x5: {
                    u32 old = cpu_csrs_read(cpu, imm_i & 0xFFF);
                    cpu_csrs_write(cpu, imm_i & 0xFFF, rs1); // rs1 field is the immediate
                    cpu->registers[rd] = old;
                } break;

                // csrsi
                case 0x6: {
                    u32 old = cpu_csrs_read(cpu, imm_i & 0xFFF);
                    cpu_csrs_write(cpu, imm_i & 0xFFF, old | rs1);
                    cpu->registers[rd] = old;
                } break;

                // csrrci
                case 0x7: {
                    u32 old = cpu_csrs_read(cpu, imm_i & 0xFFF);
                    cpu_csrs_write(cpu, imm_i & 0xFFF, old & ~rs1);
                    cpu->registers[rd] = old;
                } break;

                // unknown
                default:
                    cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
                    break;
            }

            break;

        default:
            cpu_trap(cpu, CAUSE_ILLEGAL_INSTRUCTION, old_pc);
            break;
    }

    // hardcode reg0
    cpu->registers[0] = 0;
}

static void
cpu_load_program(Cpu* cpu, const u32 program[], const int program_size, const u32 start_addr) {
    assert(cpu);
    assert(program);

    cpu->pc  = start_addr;
    u32 addr = start_addr;

    for (int i = 0; i < program_size; i++) {
        cpu_store_word(cpu, program[i], addr);
        addr += 4;
    }
}

static void cpu_run(Cpu* cpu, const int steps) {
    assert(cpu);

    for (int i = 0; i < steps; i++) {
        cpu_step(cpu);
    }
}

// MAIN
int main(void) {
    Cpu cpu;
    cpu_init(&cpu);

    const u32 program[] = {
        // addi x1, x0, 100
        0x06400093,
        // addi x2, x0, 50
        0x03200113,
        // add x3, x1, x2
        0x002081B3,
    };
    const int program_size = sizeof(program) / sizeof(program[0]);

    cpu_load_program(&cpu, program, program_size, 0);
    cpu_run(&cpu, 3);

    printf("x1 = %d\n", cpu.registers[1]);
    printf("x2 = %d\n", cpu.registers[2]);
    printf("x3 = %d\n", cpu.registers[3]);

    return 0;
}
