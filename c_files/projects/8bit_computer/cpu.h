#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define MAX_BITS 8

typedef uint8_t u8;
typedef struct {
    u8 sum;
    u8 carry;
} OperationResult;

u8 get_bit(const u8 num, const u8 pos);

// LOGIC GATES
u8 not_gate(const u8 a);
u8 and_gate(const u8 a, const u8 b);
u8 or_gate(const u8 a, const u8 b);
u8 nand_gate(const u8 a, const u8 b);
u8 nor_gate(const u8 a, const u8 b);
u8 xor_gate(const u8 a, const u8 b);
u8 xnor_gate(const u8 a, const u8 b);

// ADDERS
OperationResult half_adder(const u8 a, const u8 b);
OperationResult full_adder(const u8 a, const u8 b, const u8 cin);

// MUXES
typedef struct {
    u8 a;
    u8 b;
} Mux2x1Input;

u8 mux2x1(const Mux2x1Input input, const u8 sel);

typedef struct {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} Mux4x1Input;

u8 mux4x1(const Mux4x1Input input, const u8 sel);

typedef struct {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 f;
    u8 g;
    u8 h;
} Mux8x1Input;

u8 mux8x1(const Mux8x1Input input, const u8 sel);

// DE-MUXES
typedef struct {
    u8 a;
    u8 b;
} Demux1x2Output;

Demux1x2Output demux1x2(const u8 input, const u8 sel);

typedef struct {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} Demux1x4Output;

Demux1x4Output demux1x4(const u8 input, const u8 sel);

typedef struct {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 f;
    u8 g;
    u8 h;
} Demux1x8Output;

Demux1x8Output demux1x8(const u8 input, const u8 sel);

// BASIC OPERATIONS
u8              not8(const u8 a);
u8              and8(const u8 a, const u8 b);
u8              or8(const u8 a, const u8 b);
u8              xor8(const u8 a, const u8 b);
OperationResult add8(const u8 a, const u8 b);
OperationResult sub8(const u8 a, const u8 b);
OperationResult shl(const u8 a); // shift left
OperationResult shr(const u8 a); // shift right

// ALU
typedef struct {
    u8 carry;
    u8 sign;
    u8 zero;
    u8 overflow;
} Flag;

typedef struct {
    u8   result;
    Flag flag;
} AluResult;

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
AluResult alu(const u8 opcode, const u8 a, const u8 b);

// LATCH AND FLIPFLOPs
typedef struct {
    u8 q;
    u8 q_bar;
} Dlatch;

u8 dlatch_update(Dlatch* dl, const u8 data, const u8 enable);

typedef struct {
    Dlatch master;
    Dlatch slave;
} DFlipFlop;

u8 dflipflop_update(DFlipFlop* df, const u8 data, const u8 clk);

#endif // CPU_H
