#include "cpu.h"
#include <assert.h>

u16 get_bit(const u16 num, const u16 pos) {
    assert(pos < 16);
    return (num >> pos) & 1u;
}

u16 set_bit(const u16 num, const u16 pos) {
    assert(pos < 16);
    return num | (1 << pos);
}

// LOGIC GATES
u8 nand_gate(const u8 a, const u8 b) {
    return ~(a & b) & 1u;
}

u8 not_gate(const u8 a) {
    return ~a & 1u;
}

u8 and_gate(const u8 a, const u8 b) {
    return (a & b) & 1u;
}

u8 or_gate(const u8 a, const u8 b) {
    return (a | b) & 1u;
}

u8 nor_gate(const u8 a, const u8 b) {
    return ~(a | b) & 1u;
}

u8 xor_gate(const u8 a, const u8 b) {
    return (a ^ b) & 1u;
}

u8 xnor_gate(const u8 a, const u8 b) {
    return ~(a ^ b) & 1u;
}

// ADDERS
AdderResult half_adder(const u8 a, const u8 b) {
    const u8 sum   = xor_gate(a, b);
    const u8 carry = and_gate(a, b);

    return (AdderResult){sum, carry};
}

AdderResult full_adder(const u8 a, const u8 b, const u8 cin) {
    const AdderResult r1 = half_adder(a, b);
    const AdderResult r2 = half_adder(r1.sum, cin);

    return (AdderResult){.sum = r2.sum, .carry = or_gate(r1.carry, r2.carry)};
}

// MULTIPLEXERS // 2x1 == 2:1 and so on

// 2 bit input,  1 bit sel
u8 mux_2x1(const u8 sel, const Mux2Input in) {
    return or_gate(and_gate(not_gate(sel), in.a1), and_gate(sel, in.a2));
}

// 2 bit sel
u8 mux_4x1(const u8 sel, const Mux4Input in) {
    const u8 sel0 = get_bit(sel, 0);
    const u8 sel1 = get_bit(sel, 1);

    const u8 r1 = mux_2x1(sel0, (Mux2Input){in.a1, in.a2});
    const u8 r2 = mux_2x1(sel0, (Mux2Input){in.a3, in.a4});

    return mux_2x1(sel1, (Mux2Input){r1, r2});
}

// 3 bit sel
u8 mux_8x1(const u8 sel, const Mux8Input in) {
    const u8 sel0 = get_bit(sel, 0);
    const u8 sel1 = get_bit(sel, 1);
    const u8 sel2 = get_bit(sel, 2);

    const u8 sel_2bit = (sel1 << 1) | sel0;

    const u8 r1 = mux_4x1(sel_2bit, (Mux4Input){in.a1, in.a2, in.a3, in.a4});
    const u8 r2 = mux_4x1(sel_2bit, (Mux4Input){in.a5, in.a6, in.a7, in.a8});

    return mux_2x1(sel2, (Mux2Input){.a1 = r1, .a2 = r2});
}

// 4 bit sel
u16 mux_16x1(const u8 sel, const Mux16Input in) {
    const u8 sel0 = get_bit(sel, 0);
    const u8 sel1 = get_bit(sel, 1);
    const u8 sel2 = get_bit(sel, 2);
    const u8 sel3 = get_bit(sel, 3);

    const u8 sel_3bit = (sel2 << 2) | (sel1 << 1) | sel0;

    const u8 r1 = mux_8x1(sel_3bit,
                          (Mux8Input){
                              in.a1,
                              in.a2,
                              in.a3,
                              in.a4,
                              in.a5,
                              in.a6,
                              in.a7,
                              in.a8,
                          });

    const u8 r2 = mux_8x1(sel_3bit,
                          (Mux8Input){
                              in.a9,
                              in.a10,
                              in.a11,
                              in.a12,
                              in.a13,
                              in.a14,
                              in.a15,
                              in.a16,
                          });

    return mux_2x1(sel3, (Mux2Input){.a1 = r1, .a2 = r2});
}
