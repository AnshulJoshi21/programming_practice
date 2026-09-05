#include "cpu.h"
#include <assert.h>

// UTILITY
u8 get_bit(const u8 num, const u8 pos) {
    return (num >> pos) & 1U;
}

// LOGIC GATES
u8 not_gate(const u8 a) {
    return ~a & 1U;
}

u8 and_gate(const u8 a, const u8 b) {
    return (a & b) & 1U;
}

u8 or_gate(const u8 a, const u8 b) {
    return (a | b) & 1U;
}

u8 nand_gate(const u8 a, const u8 b) {
    return not_gate(and_gate(a, b));
}

u8 nor_gate(const u8 a, const u8 b) {
    return not_gate(or_gate(a, b));
}

u8 xor_gate(const u8 a, const u8 b) {
    return (a ^ b) & 1U;
}

u8 xnor_gate(const u8 a, const u8 b) {
    return not_gate(xor_gate(a, b));
}

// ADDERS
OperationResult half_adder(const u8 a, const u8 b) {
    const u8 sum   = xor_gate(a, b);
    const u8 carry = and_gate(a, b);
    return (OperationResult){sum, carry};
}

OperationResult full_adder(const u8 a, const u8 b, const u8 cin) {
    const OperationResult r1 = half_adder(a, b);
    const OperationResult r2 = half_adder(r1.sum, cin);
    return (OperationResult){r2.sum, or_gate(r1.carry, r2.carry)};
}

// MUXES
u8 mux2x1(const Mux2x1Input input, const u8 sel) {
    return or_gate(and_gate(not_gate(sel & 1U), input.a), and_gate((sel & 1U), input.b));
}

u8 mux4x1(const Mux4x1Input input, const u8 sel) {
    const u8 sel0 = get_bit(sel, 0);
    const u8 sel1 = get_bit(sel, 1);

    const u8 r1 = mux2x1((Mux2x1Input){input.a, input.b}, sel0);
    const u8 r2 = mux2x1((Mux2x1Input){input.c, input.d}, sel0);

    return mux2x1((Mux2x1Input){r1, r2}, sel1);
}

u8 mux8x1(const Mux8x1Input input, const u8 sel) {
    const u8 sel2 = get_bit(sel, 2);

    // sel[1, 0] pos values
    const u8 r1 = mux4x1((Mux4x1Input){input.a, input.b, input.c, input.d}, sel & 0x03);
    const u8 r2 = mux4x1((Mux4x1Input){input.e, input.f, input.g, input.h}, sel & 0x03);

    return mux2x1((Mux2x1Input){r1, r2}, sel2);
}

// DE-MUXES
Demux1x2Output demux1x2(const u8 input, const u8 sel) {
    Demux1x2Output out;
    out.a = and_gate(not_gate(sel & 1U), input);
    out.b = and_gate((sel & 1U), input);
    return out;
}

Demux1x4Output demux1x4(const u8 input, const u8 sel) {
    const u8 sel0 = get_bit(sel, 0);
    const u8 sel1 = get_bit(sel, 1);

    const Demux1x2Output r1 = demux1x2(input, sel1);

    const Demux1x2Output r2 = demux1x2(r1.a, sel0);
    const Demux1x2Output r3 = demux1x2(r1.b, sel0);

    return (Demux1x4Output){r2.a, r2.b, r3.a, r3.b};
}

Demux8x1Output demux1x8(const u8 input, const u8 sel) {
    const u8 sel2 = get_bit(sel, 2);

    const Demux1x2Output r1 = demux1x2(input, sel2);

    const Demux1x4Output r2 = demux1x4(r1.a, (sel & 0x03));
    const Demux1x4Output r3 = demux1x4(r1.b, (sel & 0x03));

    return (Demux1x8Output){
        r2.a,
        r2.b,
        r2.c,
        r2.d,
        r3.a,
        r3.b,
        r3.c,
        r3.d,
    };
}

// BASIC OPERATIONS
u8 not8(const u8 a) {
    return ~a;
}

u8 and8(const u8 a, const u8 b) {
    return a & b;
}

u8 or8(const u8 a, const u8 b) {
    return a | b;
}

u8 xor8(const u8 a, const u8 b) {
    return a ^ b;
}

OperationResult add8(const u8 a, const u8 b) {
    u8 sum   = 0;
    u8 carry = 0;

    for (u8 i = 0; i < MAX_BITS; i++) {
        const u8 ai = get_bit(a, i);
        const u8 bi = get_bit(b, i);

        OperationResult result = full_adder(ai, bi, carry);
        sum |= (result.sum << i);
        carry = result.carry;
    }
    return (OperationResult){sum, carry};
}

OperationResult sub8(const u8 a, const u8 b) {
    u8 sum   = 0;
    u8 carry = 1;

    for (u8 i = 0; i < MAX_BITS; i++) {
        const u8 ai = get_bit(a, i);
        const u8 bi = get_bit(not_gate(b), i);

        OperationResult result = full_adder(ai, bi, carry);
        sum |= (result.sum << i);
        carry = result.carry;
    }
    return (OperationResult){sum, carry};
}

// shift left
OperationResult shl(const u8 a) {
    return (OperationResult){.sum = a << 1, .carry = get_bit(a, MAX_BITS - 1)};
}

// shift right
OperationResult shr(const u8 a) {
    return (OperationResult){.sum = a >> 1, .carry = get_bit(a, 0)};
}

// ALU
/*
    opcodes
    000 - and
    001 - or
    010 - xor
    011 - not - a
    100 - add
    101 - sub
    110 - shl - a
    111 - shr - a
*/
AluResult alu(const u8 opcode, const u8 a, const u8 b) {
    const u8 op0 = get_bit(opcode, 0);
    const u8 op1 = get_bit(opcode, 1);
    const u8 op2 = get_bit(opcode, 2);

    // basic operations
    const u8              result_and = and8(a, b);
    const u8              result_or  = or8(a, b);
    const u8              result_xor = xor8(a, b);
    const u8              result_not = not8(a);
    const OperationResult result_add = add8(a, b);
    const OperationResult result_sub = sub8(a, b);
    const OperationResult result_shl = shl(a);
    const OperationResult result_shr = shr(a);

    // result - sum
    const u8 r1 = mux2x1((Mux2x1Input){result_and, result_or}, op0);
    const u8 r2 = mux2x1((Mux2x1Input){result_xor, result_not}, op0);
    const u8 r3 = mux2x1((Mux2x1Input){result_add.sum, result_sub.sum}, op0);
    const u8 r4 = mux2x1((Mux2x1Input){result_shl.sum, result_shr.sum}, op0);

    const u8 r5 = mux2x1((Mux2x1Input){r1, r2}, op1);
    const u8 r6 = mux2x1((Mux2x1Input){r3, r4}, op1);

    const u8 result = mux2x1((Mux2x1Input){r5, r6}, op2);

    // carry
    const u8 c1 = 0; // not carry operation
    const u8 c2 = 0; // not carry operation
    const u8 c3 = mux2x1((Mux2x1Input){result_add.carry, result_sub.carry}, op0);
    const u8 c4 = mux2x1((Mux2x1Input){result_shl.carry, result_shr.carry}, op0);

    const u8 c5 = mux2x1((Mux2x1Input){c1, c2}, op1);
    const u8 c6 = mux2x1((Mux2x1Input){c3, c4}, op1);

    const u8 carry = mux2x1((Mux2x1Input){c5, c6}, op2);

    // sign
    const u8 sign = get_bit(result, MAX_BITS - 1);

    // zero
    u8 zero = 1;
    for (u8 i = 0; i < MAX_BITS; i++) {
        const u8 ri = get_bit(result, i);
        zero        = and_gate(zero, not_gate(ri));
    }

    // overflow
    const u8 msb_a      = get_bit(a, MAX_BITS - 1);
    const u8 msb_b      = get_bit(b, MAX_BITS - 1);
    const u8 msb_result = get_bit(result, MAX_BITS - 1);

    const u8 overflow_add = and_gate(xnor_gate(msb_a, msb_b), xor_gate(msb_a, msb_result));
    const u8 overflow_sub = and_gate(xor_gate(msb_a, msb_b), xor_gate(msb_a, msb_result));

    const u8 is_add   = and_gate(op2, and_gate(not_gate(op1), not_gate(op0)));
    const u8 is_sub   = and_gate(op2, and_gate(not_gate(op1), op0));
    const u8 is_arith = or_gate(is_add, is_sub);

    u8 overflow = mux2x1((Mux2x1Input){overflow_add, overflow_sub}, op0);
    overflow    = and_gate(is_arith, overflow);

    return (AluResult){result, (Flag){carry, sign, zero, overflow}};
}

// LATCH AND FLIPFLOPs
u8 dlatch_update(Dlatch* dl, const u8 data, const u8 enable) {
    assert(dl);

    const u8 set   = nand_gate(data, enable);
    const u8 reset = nand_gate(not_gate(data), enable);

    for (u8 i = 0; i < 4; i++) {
        dl->q     = nand_gate(set, dl->q_bar);
        dl->q_bar = nand_gate(reset, dl->q);
    }
    return dl->q;
}

u8 dflipflop_update(DFlipFlop* df, const u8 data, const u8 clk);
