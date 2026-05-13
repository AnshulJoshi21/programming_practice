#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MEMORY_SIZE 1024

typedef uint32_t u32;
typedef int32_t i32;
typedef uint8_t u8;

typedef struct {
  u32 regs[2];
  u32 pc;

} RV32I_Cpu;

u8 memory[MEMORY_SIZE];

#define OPCODE(inst) (inst & 0x7F)         // 0-6
#define RD(inst) ((inst >> 7) & 0x1F)      // 7-11
#define FUNCT3(inst) ((inst >> 12) & 0x07) // 12-14
#define RS1(inst) ((inst >> 15) & 0x1F)    // 15-19
#define RS2(inst) ((inst >> 20) & 0x1F)    // 20-24
#define FUNCT7(inst) ((inst >> 25) & 0x7F) // 25-31

i32 extract_imm_i(u32 inst) { return ((i32)inst) >> 20 }
