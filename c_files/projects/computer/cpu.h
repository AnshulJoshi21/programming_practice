#ifndef CPU_H
#define CPU_H

// NOTE: using u8 for 1 bit values
//
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;

// UTILITY
u16 get_bit(const u16 num, const u16 pos);
u16 set_bit(const u16 num, const u16 pos);

// LOGIC GATES
u8 nand_gate(const u8 a, const u8 b);
u8 not_gate(const u8 a);
u8 and_gate(const u8 a, const u8 b);
u8 or_gate(const u8 a, const u8 b);
u8 nor_gate(const u8 a, const u8 b);
u8 xor_gate(const u8 a, const u8 b);
u8 xnor_gate(const u8 a, const u8 b);

// ADDERS
typedef struct AdderResult {
    u8 sum;
    u8 carry;
} AdderResult;

AdderResult half_adder(const u8 a, const u8 b);
AdderResult full_adder(const u8 a, const u8 b, const u8 cin);

// MULTIPLEXERS // 2x1 == 2:1 and so on
typedef struct Mux2Input {
    u8 a1;
    u8 a2;
} Mux2Input;
u8 mux_2x1(const u8 sel, const Mux2Input in); // 2 bit input,  1 bit sel

typedef struct Mux4Input {
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
} Mux4Input;
u8 mux_4x1(const u8 sel, const Mux4Input in); // 4 bit input,  2 bit sel

typedef struct Mux8Input {
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
    u8 a5;
    u8 a6;
    u8 a7;
    u8 a8;
} Mux8Input;
u8 mux_8x1(const u8 sel, const Mux8Input in); // 8 bit input,  3 bit sel

typedef struct Mux16Input {
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
    u8 a5;
    u8 a6;
    u8 a7;
    u8 a8;
    u8 a9;
    u8 a10;
    u8 a11;
    u8 a12;
    u8 a13;
    u8 a14;
    u8 a15;
    u8 a16;
} Mux16Input;
u16 mux_16x1(const u8 sel, const Mux16Input in); // 16 bit input, 4 bit sel

// DEMULTIPLEXER
typedef struct Dmux2Output {
    u8 a1;
    u8 a2;
} Dmux2Output;
Dmux2Output dmux_1x2(const u8 sel, const u16 in);

typedef struct Dmux4Output {
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
} Dmux4Output;

typedef struct Dmux8Output {
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
    u8 a5;
    u8 a6;
    u8 a7;
    u8 a8;
} Dmux8Output;

typedef struct Dmux16Output {
    u8 a1;
    u8 a2;
    u8 a3;
    u8 a4;
    u8 a5;
    u8 a6;
    u8 a7;
    u8 a8;
    u8 a9;
    u8 a10;
    u8 a11;
    u8 a12;
    u8 a13;
    u8 a14;
    u8 a15;
    u8 a16;
} Dmux16Output;

#endif // CPU_H
