#include "computer_16bit.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

static inline u8 get_bit(const u16 num, const u8 index) {
  return (num >> index) & 1u;
}

// LOGIC GATES
u8 nand_(const u8 a, const u8 b) { return ~(a & b) & 1u; }
u8 not_(const u8 a) { return nand_(a, a); }
u8 and_(const u8 a, const u8 b) { return not_(nand_(a, b)); }
u8 or_(const u8 a, const u8 b) { return nand_(not_(a), not_(b)); }
u8 nor_(const u8 a, const u8 b) { return not_(or_(a, b)); }
u8 xor_(const u8 a, const u8 b) {
  u8 r0 = nand_(a, b);
  u8 r1 = nand_(a, r0);
  u8 r2 = nand_(b, r0);
  return nand_(r1, r2);
}
u8 xnor_(const u8 a, const u8 b) { return not_(xor_(a, b)); }

// ADDERS
AddResult half_adder(const u8 a, const u8 b) {
  u8 sum = xor_(a, b);
  u8 carry = and_(a, b);

  return (AddResult){sum, carry};
}

AddResult full_adder(const u8 a, const u8 b, const u8 cin) {
  AddResult r0 = half_adder(a, b);
  AddResult r1 = half_adder(r0.sum, cin);

  return (AddResult){.sum = r1.sum, .carry = or_(r0.carry, r1.carry)};
}

// MUXes
u8 mux(const u8 a, const u8 b, const u8 sel) {
  return or_(and_(a, not_(sel)), and_(b, sel));
}

u16 mux16(const u16 a, const u16 b, const u8 sel) {
  u16 result = 0;

  for (u16 i = 0; i < MAX_BITS; i++) {
    u8 ai = get_bit(a, i);
    u8 bi = get_bit(b, i);

    u8 out = mux(ai, bi, sel);

    result |= (u16)out << i;
  }

  return result;
}

// sel == 2bits
u16 mux4way(const Mux4Input mi, const u8 sel) {
  u8 sel0 = get_bit(sel, 0);
  u8 sel1 = get_bit(sel, 1);

  u16 r0 = mux16(mi.a, mi.b, sel0);
  u16 r1 = mux16(mi.c, mi.d, sel0);

  return mux16(r0, r1, sel1);
}

// sel == 3bits
u16 mux8way(const Mux8Input mi, const u8 sel) {
  u8 sel0 = get_bit(sel, 0);
  u8 sel1 = get_bit(sel, 1);
  u8 sel2 = get_bit(sel, 2);

  u16 r0 = mux16(mi.a, mi.b, sel0);
  u16 r1 = mux16(mi.c, mi.d, sel0);
  u16 r2 = mux16(mi.e, mi.f, sel0);
  u16 r3 = mux16(mi.g, mi.h, sel0);

  u16 r4 = mux16(r0, r1, sel1);
  u16 r5 = mux16(r2, r3, sel1);

  return mux16(r4, r5, sel2);
}

// DMUXes
DmuxResult dmux(const u8 in, const u8 sel) {
  u8 a = and_(in, not_(sel));
  u8 b = and_(in, sel);

  return (DmuxResult){a, b};
}

// sel == 2bits
Dmux4Result dmux4way(const u8 in, const u8 sel) {
  u8 sel0 = get_bit(sel, 0);
  u8 sel1 = get_bit(sel, 1);

  DmuxResult split = dmux(in, sel1);

  DmuxResult top = dmux(split.a, sel0);
  DmuxResult bottom = dmux(split.b, sel0);

  return (Dmux4Result){top.a, top.b, bottom.a, bottom.b};
}

// sel == 3bits
Dmux8Result dmux8way(const u8 in, const u8 sel) {
  u8 sel0 = get_bit(sel, 0);
  u8 sel1 = get_bit(sel, 1);
  u8 sel2 = get_bit(sel, 2);

  DmuxResult split = dmux(in, sel2);

  DmuxResult top = dmux(split.a, sel1);
  DmuxResult top_a = dmux(top.a, sel0);
  DmuxResult top_b = dmux(top.b, sel0);

  DmuxResult bottom = dmux(split.b, sel1);
  DmuxResult bottom_a = dmux(bottom.a, sel0);
  DmuxResult bottom_b = dmux(bottom.b, sel0);

  return (Dmux8Result){top_a.a,    top_a.b,    top_b.a,    top_b.b,
                       bottom_a.a, bottom_a.b, bottom_b.a, bottom_b.b};
}

// BASIC OPERATIONS

u16 and16(const u16 a, const u16 b) {
  u16 result = 0;

  for (u8 i = 0; i < MAX_BITS; i++) {
    u8 ai = get_bit(a, i);
    u8 bi = get_bit(b, i);

    u8 out = and_(ai, bi);
    result |= (u16)out << i;
  }

  return result;
}

u16 or16(const u16 a, const u16 b) {
  u16 result = 0;

  for (u8 i = 0; i < MAX_BITS; i++) {
    u8 ai = get_bit(a, i);
    u8 bi = get_bit(b, i);

    u8 out = or_(ai, bi);
    result |= (u16)out << i;
  }

  return result;
}

u16 xor16(const u16 a, const u16 b) {
  u16 result = 0;

  for (u8 i = 0; i < MAX_BITS; i++) {
    u8 ai = get_bit(a, i);
    u8 bi = get_bit(b, i);

    u8 out = xor_(ai, bi);
    result |= (u16)out << i;
  }

  return result;
}

u16 not16(const u16 a) {
  u16 result = 0;

  for (u8 i = 0; i < MAX_BITS; i++) {
    u8 ai = get_bit(a, i);

    u8 out = not_(ai);
    result |= (u16)out << i;
  }

  return result;
}

OperationResult add16(const u16 a, const u16 b) {
  u16 result = 0;
  u8 carry = 0;

  for (u8 i = 0; i < MAX_BITS; i++) {
    u8 ai = get_bit(a, i);
    u8 bi = get_bit(b, i);

    AddResult out = full_adder(ai, bi, carry);

    result |= (u16)out.sum << i;
    carry = out.carry;
  }

  return (OperationResult){result, carry};
}

OperationResult sub16(const u16 a, const u16 b) {
  u16 result = 0;
  u8 carry = 1; // for 2's complement

  for (u8 i = 0; i < MAX_BITS; i++) {
    u8 ai = get_bit(a, i);
    u8 bi = get_bit(b, i);

    AddResult out = full_adder(ai, not_(bi), carry);

    result |= (u16)out.sum << i;
    carry = out.carry;
  }

  return (OperationResult){result, carry};
}

OperationResult shl16(const u16 a) {
  u16 result = 0;
  u8 carry = get_bit(a, MAX_BITS - 1);

  for (u8 i = 0; i < MAX_BITS - 1; i++) {
    u8 ai = get_bit(a, i);

    result |= (u16)ai << (i + 1);
  }

  return (OperationResult){result, carry};
}

OperationResult shr16(const u16 a) {
  u16 result = 0;
  u8 carry = get_bit(a, 0);

  for (u8 i = 0; i < MAX_BITS - 1; i++) {
    u8 ai = get_bit(a, i + 1);

    result |= (u16)ai << i;
  }

  return (OperationResult){result, carry};
}

// ALU
// opcode = 3bits, op_order = add, sub, and, or, xor, not, shl, shr
AluResult alu16(const u16 a, const u16 b, const u8 opcode) {
  u8 op0 = get_bit(opcode, 0);
  u8 op1 = get_bit(opcode, 1);
  u8 op2 = get_bit(opcode, 2);

  // basic operations
  OperationResult add_res = add16(a, b);
  OperationResult sub_res = sub16(a, b);
  u16 and_res = and16(a, b);
  u16 or_res = or16(a, b);
  u16 xor_res = xor16(a, b);
  u16 not_res = not16(a);
  OperationResult shl_res = shl16(a);
  OperationResult shr_res = shr16(a);

  // result selection
  u16 r0 = mux16(add_res.result, sub_res.result, op0);
  u16 r1 = mux16(and_res, or_res, op0);
  u16 r2 = mux16(xor_res, not_res, op0);
  u16 r3 = mux16(shl_res.result, shr_res.result, op0);

  u16 r4 = mux16(r0, r1, op1);
  u16 r5 = mux16(r2, r3, op1);

  u16 result = mux16(r4, r5, op2);

  // carry selection
  u8 c0 = mux(add_res.carry, sub_res.carry, op0);
  u8 c1 = 0; // no carry operation
  u8 c2 = 0; // no carry operation
  u8 c3 = mux(shl_res.carry, shr_res.carry, op0);

  u8 c4 = mux(c0, c1, op1);
  u8 c5 = mux(c2, c3, op1);

  u8 carry = mux(c4, c5, op2);

  // zero
  u8 zero = 1;
  for (u8 i = 0; i < MAX_BITS; i++) {
    zero = and_(zero, not_(get_bit(result, i)));
  }

  // sign
  u8 sign = get_bit(result, MAX_BITS - 1);

  // overflow
  u8 msb_a = get_bit(a, MAX_BITS - 1);
  u8 msb_b = get_bit(b, MAX_BITS - 1);
  u8 msb_r = get_bit(result, MAX_BITS - 1);

  u8 overflow_add = and_(xnor_(msb_a, msb_b), xor_(msb_a, msb_r));
  u8 overflow_sub = and_(xor_(msb_a, msb_b), xor_(msb_a, msb_r));
  u8 overflow = mux(overflow_add, overflow_sub, op0);

  u8 is_arith = and_(not_(op2), not_(op1));
  overflow = and_(is_arith, overflow);

  return (AluResult){result, (Flag){carry, zero, sign, overflow}};
}

// LATCHES
void dlatch_init(DLatch *dl) {
  assert(dl);

  dl->q = 0;
  dl->q_bar = not_(dl->q);
}

u8 dlatch_update(DLatch *dl, const u8 data, const u8 enable) {
  assert(dl);

  u8 s = nand_(data, enable);
  u8 r = nand_(not_(data), enable);

  for (u8 i = 0; i < 2; i++) {
    dl->q = nand_(s, dl->q_bar);
    dl->q_bar = nand_(r, dl->q);
  }

  return dl->q;
}

// FLIP FLOPS
void dflipflop_init(DFlipFlop *dff) {
  assert(dff);

  dlatch_init(&dff->master);
  dlatch_init(&dff->slave);
}

u8 dflipflop_update(DFlipFlop *dff, const u8 data, const u8 clk) {
  assert(dff);

  u8 master_q = dlatch_update(&dff->master, data, not_(clk));
  u8 slave_q = dlatch_update(&dff->slave, master_q, clk);

  return slave_q;
}

// REGISTERS
void register_init(Register16 *reg) {
  assert(reg);

  for (u8 i = 0; i < MAX_BITS; i++) {
    dflipflop_init(&reg->bits[i]);
  }

  reg->out = 0;
}

u16 register_update(Register16 *reg, const u16 data, const u8 load,
                    const u8 clk) {
  assert(reg);

  u16 d_in = mux16(reg->out, data, load);

  u16 new_out = 0;
  for (u8 i = 0; i < MAX_BITS; i++) {
    u16 out = dflipflop_update(&reg->bits[i], get_bit(d_in, i), clk);
    new_out |= (u16)out << i;
  }

  if (clk)
    reg->out = new_out;

  return reg->out;
}

// register file
void register_file_init(RegisterFile *rf) {
  assert(rf);

  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    register_init(&rf->registers[i]);
  }
}

RegisterFileResult register_file_update(RegisterFile *rf, const u16 data,
                                        const u8 addr, const u8 load,
                                        u8 read_addr_a, u8 read_addr_b,
                                        const u8 clk) {
  assert(rf);

  Dmux8Result load_signals = dmux8way(load, addr);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    reg_outs[i] = register_update(&rf->registers[i], data, loads[i], clk);
  }

  u16 out_a =
      mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                          reg_outs[4], reg_outs[5], reg_outs[6], reg_outs[7]},
              read_addr_a);
  u16 out_b =
      mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                          reg_outs[4], reg_outs[5], reg_outs[6], reg_outs[7]},
              read_addr_b);

  return (RegisterFileResult){out_a, out_b};
}

// RAMS
void ram8_init(Ram8 *ram) {
  assert(ram);

  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    register_init(&ram->registers[i]);
  }
}

// addr = 3bits
u16 ram8_update(Ram8 *ram, const u16 data, const u8 addr, const u8 load,
                const u8 clk) {
  assert(ram);

  Dmux8Result load_signals = dmux8way(load, addr);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    reg_outs[i] = register_update(&ram->registers[i], data, loads[i], clk);
  }

  return mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                             reg_outs[4], reg_outs[5], reg_outs[6],
                             reg_outs[7]},
                 addr);
}

// addr 6bits
void ram64_init(Ram64 *ram) {
  assert(ram);

  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    ram8_init(&ram->rams[i]);
  }
}
u16 ram64_update(Ram64 *ram, const u16 data, const u8 addr, const u8 load,
                 const u8 clk) {
  assert(ram);

  u8 ram_sel = (addr >> 3) & 0x07; // addr 6bits in 8bit num
  u8 reg_sel = addr & 0x07;

  Dmux8Result load_signals = dmux8way(load, ram_sel);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    reg_outs[i] = ram8_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                             reg_outs[4], reg_outs[5], reg_outs[6],
                             reg_outs[7]},
                 ram_sel);
}

// addr 9bits
void ram512_init(Ram512 *ram) {
  assert(ram);

  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    ram64_init(&ram->rams[i]);
  }
}
u16 ram512_update(Ram512 *ram, const u16 data, const u16 addr, const u8 load,
                  const u8 clk) {
  assert(ram);

  u8 ram_sel = (addr >> 6) & 0x07;
  u16 reg_sel = addr & 0x3F;

  Dmux8Result load_signals = dmux8way(load, ram_sel);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    reg_outs[i] = ram64_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                             reg_outs[4], reg_outs[5], reg_outs[6],
                             reg_outs[7]},
                 ram_sel);
}

// addr 12bits
void ram4k_init(Ram4k *ram) {
  assert(ram);

  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    ram512_init(&ram->rams[i]);
  }
}
u16 ram4k_update(Ram4k *ram, const u16 data, const u16 addr, const u8 load,
                 const u8 clk) {
  assert(ram);

  // addr bits
  u8 ram_sel = (addr >> 9) & 0x07;
  u16 reg_sel = addr & 0x1FF;

  Dmux8Result load_signals = dmux8way(load, ram_sel);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    reg_outs[i] = ram512_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                             reg_outs[4], reg_outs[5], reg_outs[6],
                             reg_outs[7]},
                 ram_sel);
}

// addr 14bits
void ram16k_init(Ram16k *ram) {
  assert(ram);

  for (u8 i = 0; i < 4; i++) {
    ram4k_init(&ram->rams[i]);
  }
}

u16 ram16k_update(Ram16k *ram, const u16 data, const u16 addr, const u8 load,
                  const u8 clk) {
  assert(ram);

  // addr bits
  u8 ram_sel = (addr >> 12) & 0x03;
  u16 reg_sel = addr & 0xFFF;

  Dmux4Result load_signals = dmux4way(load, ram_sel);
  u8 loads[] = {
      load_signals.a,
      load_signals.b,
      load_signals.c,
      load_signals.d,
  };

  u16 reg_outs[4];
  for (u8 i = 0; i < 4; i++) {
    reg_outs[i] = ram4k_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux4way(
      (Mux4Input){
          reg_outs[0],
          reg_outs[1],
          reg_outs[2],
          reg_outs[3],
      },
      ram_sel);
}

// PROGRAM COUNTER
void pc_init(ProgramCounter *pc) {
  assert(pc);

  register_init(&pc->register16);
  pc->out = 0;
}

u16 pc_update(ProgramCounter *pc, const u16 data, const u8 inc, const u8 load,
              const u8 reset, const u8 clk) {
  assert(pc);

  u16 inc_val = add16(pc->out, (u16)1).result;

  u16 r0 = mux16(pc->out, inc_val, inc);
  u16 r1 = mux16(r0, data, load);
  u16 r2 = mux16(r1, (u16)0, reset);

  u16 new_out =
      register_update(&pc->register16, r2, 1, clk); // load handled beforehand

  if (clk)
    pc->out = new_out;

  return pc->out;
}

// CONTROL UNIT
ControlSignals decode_instruction(const u16 instruction, const u8 zero_flag) {
  u8 opcode = 0;
  opcode = (instruction >> 12) & 0x0F;

  u8 op0 = get_bit(opcode, 0);
  u8 op1 = get_bit(opcode, 1);
  u8 op2 = get_bit(opcode, 2);
  u8 op3 = get_bit(opcode, 3);

  u8 reg_dest = (instruction >> 9) & 0x07;
  u8 reg_src_a = (instruction >> 6) & 0x07;
  u8 reg_src_b = (instruction >> 3) & 0x07;
  u16 immediate_val = instruction & 0x01FF; // pad with 7 0's

  u8 is_alu_op = not_(op3);
  u8 is_ldi = and_(and_(op3, not_(op2)), and_(not_(op1), not_(op0))); // 1000
  u8 is_ldr = and_(and_(op3, not_(op2)), and_(not_(op1), op0));       // 1001
  u8 is_str = and_(and_(op3, not_(op2)), and_(op1, not_(op0)));       // 1010
  u8 is_jmp = and_(and_(op3, not_(op2)), and_(op1, op0));             // 1011
  u8 is_jeq = and_(and_(op3, op2), and_(not_(op1), not_(op0)));       // 1100

  u8 alu_opcode = opcode & 0x07;

  u8 reg_write = or_(is_alu_op, or_(is_ldi, is_ldr));
  u8 mem_write = is_str;
  u8 mem_to_reg = is_ldr;
  u8 alu_src = is_ldi;
  u8 pc_load = or_(is_jmp, and_(zero_flag, is_jeq));

  return (ControlSignals){alu_opcode, reg_write,    mem_write, mem_to_reg,
                          alu_src,    pc_load,      reg_dest,  reg_src_a,
                          reg_src_b,  immediate_val};
}

// CPU
void cpu_init(Cpu *cpu) {
  assert(cpu);

  pc_init(&cpu->pc);
  register_file_init(&cpu->reg_file);

  cpu->current_zero = 0;
  dflipflop_init(&cpu->zero_flag_dff);
}

CpuResult cpu_update(Cpu *cpu, const u16 instruction, const u16 in_m,
                     const u8 reset, const u8 clk) {
  assert(cpu);

  ControlSignals ctrl = decode_instruction(instruction, cpu->current_zero);

  const u16 reg_out_a = cpu->reg_file.registers[ctrl.reg_src_a].out;
  const u16 reg_out_b = cpu->reg_file.registers[ctrl.reg_src_b].out;

  u16 alu_in_b = mux16(reg_out_b, ctrl.immediate_val, ctrl.alu_src);
  AluResult alu_out = alu16(reg_out_a, alu_in_b, ctrl.alu_opcode);

  printf("clk=%d | instr=0x%04X | opcode=%d | dest=%d | src_a=%d src_b=%d | "
         "reg_a=%d reg_b=%d | alu_src=%d imm=%d | alu_in_b=%d | alu_out=%d | "
         "reg_write=%d\n",
         clk, instruction, ctrl.alu_opcode, ctrl.reg_dest, ctrl.reg_src_a,
         ctrl.reg_src_b, reg_out_a, reg_out_b, ctrl.alu_src, ctrl.immediate_val,
         alu_in_b, alu_out.result, ctrl.reg_write);

  u16 reg_write_data = mux16(alu_out.result, in_m, ctrl.mem_to_reg);

  reg_write_data = mux16(reg_write_data, ctrl.immediate_val, ctrl.alu_src);

  register_file_update(&cpu->reg_file, reg_write_data, ctrl.reg_dest,
                       ctrl.reg_write, ctrl.reg_src_a, ctrl.reg_src_b, clk);

  u8 new_zero = dflipflop_update(&cpu->zero_flag_dff, alu_out.flag.zero, clk);
  if (clk)
    cpu->current_zero = new_zero;

  u8 pc_inc = not_(ctrl.pc_load);

  u16 pc_next =
      pc_update(&cpu->pc, reg_out_a, pc_inc, ctrl.pc_load, reset, clk);

  return (CpuResult){reg_out_b, ctrl.mem_write, reg_out_a, pc_next};
}

// COMPUTER
void computer_init(Computer *comp, const u16 *rom, const u16 rom_size) {
  assert(comp);
  assert(rom);

  cpu_init(&comp->cpu);
  ram16k_init(&comp->ram);

  comp->rom = rom;
  comp->rom_size = rom_size;

  comp->clock_state = 0;
  comp->reset = 0;
}

void computer_tick(Computer *comp) {
  assert(comp);
  u16 pc_addr = comp->cpu.pc.out;
  u16 instruction = 0;
  if (pc_addr < comp->rom_size) {
    instruction = comp->rom[pc_addr];
  }

  u16 reg0_out = comp->cpu.reg_file.registers[0].out;

  // dummy
  u16 current_ram_out =
      ram16k_update(&comp->ram, (u16)0, reg0_out & 0x3FFF, 0, 0);

  cpu_update(&comp->cpu, instruction, current_ram_out, comp->reset, 0);

  CpuResult cpu_out =
      cpu_update(&comp->cpu, instruction, current_ram_out, comp->reset, 1);

  ram16k_update(&comp->ram, cpu_out.out_m, cpu_out.addr_m, cpu_out.write_m, 1);
}

static u16 bin2dec(const u16 bin) {
  u16 total = 0;

  for (u8 i = 0; i < MAX_BITS; i++) {
    u8 bit = get_bit(bin, i);

    total += (pow(2, i) * bit);
  }

  return total;
}

int main(void) {
  const u16 my_rom[] = {
      0x8005, // LDI R0, 5
      0x8203, // LDI R1, 3
      0x0408  // ADD R2, R0, R1  → expect R2 = 8
  };
  const u16 my_rom_size = sizeof(my_rom) / sizeof(my_rom[0]);

  Computer computer;
  computer_init(&computer, my_rom, my_rom_size);

  printf("Booting up... \n");
  printf("\n");

  for (u8 i = 0; i < 3; i++) {
    computer_tick(&computer);
  }

  const u16 r2_bin = computer.cpu.reg_file.registers[2].out;
  printf("Binary: %d\n", r2_bin);
  printf("Decimal: %d\n", bin2dec(r2_bin));

  return 0;
}
