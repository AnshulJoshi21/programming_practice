#include "computer_16bit.h"
#include <assert.h>

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
  AddResult r1 = half_adder(a, cin);

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
  DmuxResult bottom_a = dmux(bottom.b, sel1);
  DmuxResult bottom_b = dmux(bottom.b, sel1);

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

  u8 carry = mux(r4, r5, op2);

  // zero
  u8 zero = 0;
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
    dl->q_bar = nand_(s, dl->q);
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

  u8 master_q = dlatch_update(&dff->master, data, clk);
  u8 slave_q = dlatch_update(&dff->slave, master_q, not_(clk));

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

  for (u8 i = 0; i < MAX_BITS; i++) {
    u16 out = dflipflop_update(&reg->bits[i], get_bit(d_in, i), clk);
    reg->out |= out << i;
  }

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
  u16 out = 0;
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    out |= register_update(&rf->registers[i], data, loads[i], clk);
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
  u16 out = 0;
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    out |= register_update(&ram->registers[i], data, loads[i], clk);
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

  u8 addr_max = 6;
  u8 addr_ram_sel = 3;

  u8 ram_sel = 0;
  for (u8 i = 0; i < addr_ram_sel; i++) {
    ram_sel |= (u16)get_bit(addr, i) << i;
  }

  u8 reg_sel = 0;
  for (u8 i = addr_ram_sel; i < addr_max; i++) {
    reg_sel |= (u16)get_bit(addr, i) << i;
  }

  Dmux8Result load_signals = dmux8way(load, ram_sel);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  u16 out = 0;
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    out |= ram8_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                             reg_outs[4], reg_outs[5], reg_outs[6],
                             reg_outs[7]},
                 addr);
}

// addr 9bits
void ram512_init(Ram512 *ram) {
  assert(ram);

  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    ram64_init(&ram->rams[i]);
  }
}
u16 ram512_update(Ram512 *ram, const u16 data, const u8 addr, const u8 load,
                  const u8 clk) {
  assert(ram);

  // addr bits
  u8 addr_max = 9;
  u8 addr_ram_sel = 3;

  u8 ram_sel = 0;
  for (u8 i = 0; i < addr_ram_sel; i++) {
    ram_sel |= (u16)get_bit(addr, i) << i;
  }

  u8 reg_sel = 0;
  for (u8 i = addr_ram_sel; i < addr_max; i++) {
    reg_sel |= (u16)get_bit(addr, i) << i;
  }

  Dmux8Result load_signals = dmux8way(load, ram_sel);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  u16 out = 0;
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    out |= ram64_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                             reg_outs[4], reg_outs[5], reg_outs[6],
                             reg_outs[7]},
                 addr);
}

// addr 12bits
void ram4k_init(Ram4k *ram) {
  assert(ram);

  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    ram512_init(&ram->rams[i]);
  }
}
u16 ram4k_update(Ram4k *ram, const u16 data, const u8 addr, const u8 load,
                 const u8 clk) {
  assert(ram);

  // addr bits
  u8 addr_max = 12;
  u8 addr_ram_sel = 3;

  u8 ram_sel = 0;
  for (u8 i = 0; i < addr_ram_sel; i++) {
    ram_sel |= (u16)get_bit(addr, i) << i;
  }

  u8 reg_sel = 0;
  for (u8 i = addr_ram_sel; i < addr_max; i++) {
    reg_sel |= (u16)get_bit(addr, i) << i;
  }

  Dmux8Result load_signals = dmux8way(load, ram_sel);
  u8 loads[] = {
      load_signals.a, load_signals.b, load_signals.c, load_signals.d,
      load_signals.e, load_signals.f, load_signals.g, load_signals.h,
  };

  u16 reg_outs[MAX_REGISTERS];
  u16 out = 0;
  for (u8 i = 0; i < MAX_REGISTERS; i++) {
    out |= ram512_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux8way((Mux8Input){reg_outs[0], reg_outs[1], reg_outs[2], reg_outs[3],
                             reg_outs[4], reg_outs[5], reg_outs[6],
                             reg_outs[7]},
                 addr);
}

// addr 14bits
void ram16k_init(Ram16k *ram) {
  assert(ram);

  for (u8 i = 0; i < 4; i++) {
    ram4k_init(&ram->rams[i]);
  }
}

u16 ram16k_update(Ram16k *ram, const u16 data, const u8 addr, const u8 load,
                  const u8 clk) {
  assert(ram);

  // addr bits
  u8 addr_max = 14;
  u8 addr_ram_sel = 2;

  u8 ram_sel = 0;
  for (u8 i = 0; i < addr_ram_sel; i++) {
    ram_sel |= (u16)get_bit(addr, i) << i;
  }

  u8 reg_sel = 0;
  for (u8 i = addr_ram_sel; i < addr_max; i++) {
    reg_sel |= (u16)get_bit(addr, i) << i;
  }

  Dmux4Result load_signals = dmux4way(load, ram_sel);
  u8 loads[] = {
      load_signals.a,
      load_signals.b,
      load_signals.c,
      load_signals.d,
  };

  u16 reg_outs[4];
  u16 out = 0;
  for (u8 i = 0; i < 4; i++) {
    out |= ram4k_update(&ram->rams[i], data, reg_sel, loads[i], clk);
  }

  return mux4way(
      (Mux4Input){
          reg_outs[0],
          reg_outs[1],
          reg_outs[2],
          reg_outs[3],
      },
      addr);
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

  pc->out =
      register_update(&pc->register16, r2, 1, clk); // load handled beforehand

  return pc->out;
}

// CONTROL UNIT
ControlSignals decode_instruction(const u16 instruction, const u8 zero_flag) {
  u8 opcode = 0;
  opcode |= (get_bit(instruction, 0)) << 0;
  opcode |= (get_bit(instruction, 1)) << 1;
  opcode |= (get_bit(instruction, 2)) << 2;
  opcode |= (get_bit(instruction, 3)) << 3;

  u8 op0 = get_bit(opcode, 0);
  u8 op1 = get_bit(opcode, 1);
  u8 op2 = get_bit(opcode, 2);
  u8 op3 = get_bit(opcode, 3);

  u8 reg_dest = 0;
  reg_dest |= (get_bit(instruction, 4)) << 0;
  reg_dest |= (get_bit(instruction, 5)) << 1;
  reg_dest |= (get_bit(instruction, 6)) << 2;

  u8 reg_src_a = 0;
  reg_src_a |= (get_bit(instruction, 7)) << 0;
  reg_src_a |= (get_bit(instruction, 8)) << 1;
  reg_src_a |= (get_bit(instruction, 9)) << 2;

  u8 reg_src_b = 0;
  reg_src_b |= (get_bit(instruction, 10)) << 0;
  reg_src_b |= (get_bit(instruction, 11)) << 1;
  reg_src_b |= (get_bit(instruction, 12)) << 2;

  u16 immediate_val = 0;
  immediate_val |= (get_bit(instruction, 0)) << 0;
  immediate_val |= (get_bit(instruction, 1)) << 1;
  immediate_val |= (get_bit(instruction, 2)) << 2;
  immediate_val |= (get_bit(instruction, 3)) << 3;
  immediate_val |= (get_bit(instruction, 4)) << 4;
  immediate_val |= (get_bit(instruction, 5)) << 5;
  immediate_val |= (get_bit(instruction, 6)) << 6;
  immediate_val |= (get_bit(instruction, 7)) << 7;
  immediate_val |= (get_bit(instruction, 8)) << 8;

  u8 is_alu_op = not_(get_bit(opcode, 3));
  u8 is_ldi = and_(and_(op0, not_(op1)), and_(not_(op2), not_(op3)));
  u8 is_ldr = and_(and_(op0, not_(op1)), and_(not_(op2), op3));
  u8 is_str = and_(and_(op0, not_(op1)), and_(op2, not_(op3)));
  u8 is_jmp = and_(and_(op0, not_(op1)), and_(op2, op3));
  u8 is_jeq = and_(and_(op0, op1), and_(not_(op2), not_(op3)));

  u8 alu_opcode = 0;
  alu_opcode |= op0 << 0;
  alu_opcode |= op1 << 1;
  alu_opcode |= op2 << 2;

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

// COMPUTER

int main(void) { return 0; }
