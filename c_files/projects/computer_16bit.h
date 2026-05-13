#ifndef COMPUTER_16BIT_H
#define COMPUTER_16BIT_H

#include <stdint.h>

#define MAX_BITS 16
#define MAX_REGISTERS 8
#define MAX_RAMS 8

typedef uint8_t u8;
typedef uint16_t u16;

// LOGIC GATES
u8 nand_(const u8 a, const u8 b);
u8 not_(const u8 a);
u8 and_(const u8 a, const u8 b);
u8 or_(const u8 a, const u8 b);
u8 nor_(const u8 a, const u8 b);
u8 xor_(const u8 a, const u8 b);
u8 xnor_(const u8 a, const u8 b);

// ADDERS
typedef struct AddResult {
  u8 sum;
  u8 carry;

} AddResult;

AddResult half_adder(const u8 a, const u8 b);
AddResult full_adder(const u8 a, const u8 b, const u8 cin);

// MUXes
u8 mux(const u8 a, const u8 b, const u8 sel);
u16 mux16(const u16 a, const u16 b, const u8 sel);

typedef struct Mux4Input {
  u16 a;
  u16 b;
  u16 c;
  u16 d;

} Mux4Input;
u16 mux4way(const Mux4Input mi, const u8 sel);

typedef struct Mux8Input {
  u16 a;
  u16 b;
  u16 c;
  u16 d;
  u16 e;
  u16 f;
  u16 g;
  u16 h;

} Mux8Input;
u16 mux8way(const Mux8Input mi, const u8 sel);

// DMUXes
typedef struct DmuxResult {
  u8 a;
  u8 b;

} DmuxResult;
DmuxResult dmux(const u8 in, const u8 sel);

typedef struct Dmux4Result {
  u8 a;
  u8 b;
  u8 c;
  u8 d;

} Dmux4Result;
Dmux4Result dmux4way(const u8 in, const u8 sel);

typedef struct Dmux8Result {
  u8 a;
  u8 b;
  u8 c;
  u8 d;
  u8 e;
  u8 f;
  u8 g;
  u8 h;

} Dmux8Result;
Dmux8Result dmux8way(const u8 in, const u8 sel);

// BASIC OPERATIONS
typedef struct OperationResult {
  u16 result;
  u8 carry;

} OperationResult;

u16 and16(const u16 a, const u16 b);
u16 or16(const u16 a, const u16 b);
u16 xor16(const u16 a, const u16 b);
u16 not16(const u16 a);
OperationResult add16(const u16 a, const u16 b);
OperationResult sub16(const u16 a, const u16 b);
OperationResult shl16(const u16 a);
OperationResult shr16(const u16 a);

// ALU
typedef struct Flag {
  u8 carry;
  u8 zero;
  u8 sign;
  u8 overflow;

} Flag;

typedef struct AluResult {
  u16 result;
  Flag flag;

} AluResult;

AluResult alu16(const u16 a, const u16 b, const u8 opcode);

// LATCHES
typedef struct DLatch {
  u8 q;
  u8 q_bar;

} DLatch;

void dlatch_init(DLatch *dl);
u8 dlatch_update(DLatch *dl, const u8 data, const u8 enable);

// FLIP FLOPS
typedef struct DFlipFlop {
  DLatch master;
  DLatch slave;

} DFlipFlop;

void dflipflop_init(DFlipFlop *dff);
u8 dflipflop_update(DFlipFlop *dff, const u8 data, const u8 clk);

// REGISTERS
typedef struct Register16 {
  DFlipFlop bits[MAX_BITS];
  u16 out;

} Register16;

void register_init(Register16 *reg);
u16 register_update(Register16 *reg, const u16 data, const u8 load,
                    const u8 clk);

typedef struct RegisterFileResult {
  u16 out_a;
  u16 out_b;

} RegisterFileResult;

typedef struct RegisterFile {
  Register16 registers[MAX_REGISTERS];

} RegisterFile;

void register_file_init(RegisterFile *rf);
RegisterFileResult register_file_update(RegisterFile *rf, const u16 data,
                                        const u8 addr, const u8 load,
                                        u8 read_addr_a, u8 read_addr_b,
                                        const u8 clk);

// RAMS
typedef struct Ram8 {
  Register16 registers[MAX_RAMS];

} Ram8;

void ram8_init(Ram8 *ram);
u16 ram8_update(Ram8 *ram, const u16 data, const u8 addr, const u8 load,
                const u8 clk);

typedef struct Ram64 {
  Ram8 rams[MAX_RAMS];

} Ram64;

void ram64_init(Ram64 *ram);
u16 ram64_update(Ram64 *ram, const u16 data, const u8 addr, const u8 load,
                 const u8 clk);

typedef struct Ram512 {
  Ram64 rams[MAX_RAMS];

} Ram512;

void ram512_init(Ram512 *ram);
u16 ram512_update(Ram512 *ram, const u16 data, const u16 addr, const u8 load,
                  const u8 clk);

typedef struct Ram4k {
  Ram512 rams[MAX_RAMS];

} Ram4k;

void ram4k_init(Ram4k *ram);
u16 ram4k_update(Ram4k *ram, const u16 data, const u16 addr, const u8 load,
                 const u8 clk);

typedef struct Ram16k {
  Ram4k rams[4];

} Ram16k;

void ram16k_init(Ram16k *ram);
u16 ram16k_update(Ram16k *ram, const u16 data, const u16 addr, const u8 load,
                  const u8 clk);

// PROGRAM COUNTER
typedef struct ProgramCounter {
  Register16 register16;
  u16 out;

} ProgramCounter;

void pc_init(ProgramCounter *pc);
u16 pc_update(ProgramCounter *pc, const u16 data, const u8 inc, const u8 load,
              const u8 reset, const u8 clk);

// CONTROL UNIT
typedef struct ControlSignals {
  u8 alu_opcode;
  u8 reg_write;
  u8 mem_write;
  u8 mem_to_reg;
  u8 alu_src;
  u8 pc_load;

  u8 reg_dest;
  u8 reg_src_a;
  u8 reg_src_b;
  u16 immediate_val;

} ControlSignals;

ControlSignals decode_instruction(const u16 instruction, const u8 zero_flag);

// CPU
typedef struct CpuResult {
  u16 out_m;
  u8 write_m;
  u16 addr_m;
  u16 pc_out;

} CpuResult;

typedef struct Cpu {
  ProgramCounter pc;
  RegisterFile reg_file;

  u8 current_zero;
  DFlipFlop zero_flag_dff;

} Cpu;

void cpu_init(Cpu *cpu);
CpuResult cpu_update(Cpu *cpu, const u16 instruction, const u16 in_m,
                     const u8 reset, const u8 clk);

// COMPUTER
typedef struct Computer {
  Cpu cpu;
  Ram16k ram;

  const u16 *rom;
  u16 rom_size;

  u8 clock_state;
  u8 reset;

} Computer;

void computer_init(Computer *comp, const u16 *rom, const u16 rom_size);
void computer_tick(Computer *comp);

#endif // COMPUTER_16BIT_H
