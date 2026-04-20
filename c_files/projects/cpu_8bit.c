#include <stdint.h>

typedef uint8_t u8;

#define GET_BIT(num, index) (((num) >> (index)) & 1)

// LOGIC GATES
static u8 nand_(const u8 a, const u8 b) { return ~(a & b); }
static u8 not_(const u8 a) { return nand_(a, a); }
static u8 and_(const u8 a, const u8 b) { return not_(nand_(a, b)); }
static u8 or_(const u8 a, const u8 b) { return nand_(not_(a), not_(b)); }
static u8 nor_(const u8 a, const u8 b) { return not_(or_(a, b)); }
static u8 xor_(const u8 a, const u8 b)
{
    return or_(and_(not_(a), b), and_(a, not_(b)));
}
static u8 xnor_(const u8 a, const u8 b) { return not_(xor_(a, b)); }

// ADDERS

typedef struct OperationResult {
    u8 sum;
    u8 carry;

} OperationResult;

static OperationResult half_adder(const u8 a, const u8 b)
{
    u8 sum = xor_(a, b);
    u8 carry = and_(a, b);

    return (OperationResult){.sum = sum, .carry = carry};
}

static OperationResult full_adder(const u8 a, const u8 b, const u8 cin)
{
    OperationResult r1 = half_adder(a, b);
    OperationResult r2 = half_adder(r1.sum, cin);
    return (OperationResult){.sum = r2.sum, .carry = or_(r1.carry, r2.carry)};
}

// MUX

static u8 mux(const u8 a, const u8 b, const u8 sel)
{
    return or_(and_(a, not_(sel)), and_(b, sel));
}

static u8 mux8(const u8 a, const u8 b, const u8 sel)
{
    u8 result = 0;

    for (u8 i = 0; i < 8; i++) {
        u8 ai = GET_BIT(a, i);
        u8 bi = GET_BIT(b, i);

        result |= (mux8(ai, bi, sel) << i);
    }

    return result;
}

// BASIC OPERATIONS

static u8 not8(const u8 a)
{
    u8 result = 0;

    for (u8 i = 0; i < 8; i++) {
        u8 ai = GET_BIT(a, i);

        result |= (not_(ai) << i);
    }

    return result;
}

static u8 and8(const u8 a, const u8 b)
{
    u8 result = 0;

    for (u8 i = 0; i < 8; i++) {
        u8 ai = GET_BIT(a, i);
        u8 bi = GET_BIT(b, i);

        result |= ((and_(ai, bi)) << i);
    }

    return result;
}

static u8 or8(const u8 a, const u8 b)
{
    u8 result = 0;

    for (u8 i = 0; i < 8; i++) {
        u8 ai = GET_BIT(a, i);
        u8 bi = GET_BIT(b, i);

        result |= ((or_(ai, bi)) << i);
    }

    return result;
}

static u8 xor8(const u8 a, const u8 b)
{
    u8 result = 0;

    for (u8 i = 0; i < 8; i++) {
        u8 ai = GET_BIT(a, i);
        u8 bi = GET_BIT(b, i);

        result |= ((xor_(ai, bi)) << i);
    }

    return result;
}

static OperationResult add8(const u8 a, const u8 b)
{
    u8 sum = 0;
    u8 carry = 0;

    for (u8 i = 0; i < 8; i++) {
        u8 ai = GET_BIT(a, i);
        u8 bi = GET_BIT(b, i);

        OperationResult r = full_adder(ai, bi, carry);

        sum |= (r.sum << i);
        carry = r.carry;
    }

    return (OperationResult){.sum = sum, .carry = carry};
}

static OperationResult sub8(const u8 a, const u8 b)
{
    u8 sum = 0;
    u8 carry = 1;

    for (u8 i = 0; i < 8; i++) {
        u8 ai = GET_BIT(a, i);
        u8 bi = GET_BIT(b, i);

        OperationResult r = full_adder(ai, not_(bi), carry);

        sum |= (r.sum << i);
        carry = r.carry;
    }

    return (OperationResult){.sum = sum, .carry = carry};
}

static OperationResult shl8(const u8 a)
{
    u8 carry = GET_BIT(a, 7);
    u8 result = 0;

    result |= 0;
    result |= GET_BIT(a, 0);
    result |= GET_BIT(a, 1);
    result |= GET_BIT(a, 2);
    result |= GET_BIT(a, 3);
    result |= GET_BIT(a, 4);
    result |= GET_BIT(a, 5);
    result |= GET_BIT(a, 6);

    return (OperationResult){.sum = result, carry = carry};
}

static OperationResult shr8(const u8 a)
{
    u8 carry = GET_BIT(a, 0);
    u8 result = 0;

    result |= GET_BIT(a, 1);
    result |= GET_BIT(a, 2);
    result |= GET_BIT(a, 3);
    result |= GET_BIT(a, 4);
    result |= GET_BIT(a, 5);
    result |= GET_BIT(a, 6);
    result |= GET_BIT(a, 7);
    result |= 0;

    return (OperationResult){.sum = result, carry = carry};
}

// ALU

typedef struct Flag {
    u8 carry;
    u8 zero;
    u8 sign;
    u8 overflow;

} Flag;

typedef struct AluResult {
    u8 result;
    Flag flag;

} AluResult;

// op codes
// 000	ADD
// 001	SUB
// 010	AND
// 011	OR
// 100	XOR
// 101	NOT (on A)
// 110	SHL (A << 1)
// 111	SHR (A >> 1)
static AluResult alu8(const u8 a, const u8 b, const u8 op)
{
    u8 op0 = GET_BIT(op, 0);
    u8 op1 = GET_BIT(op, 1);
    u8 op2 = GET_BIT(op, 2);

    // operations
    OperationResult add_res = add8(a, b);
    OperationResult sub_res = sub8(a, b);

    u8 and_res = and8(a, b);
    u8 or_res = or8(a, b);
    u8 xor_res = xor8(a, b);
    u8 not_res = not8(a);

    OperationResult shl_res = shl8(a);
    OperationResult shr_res = shr8(a);

    // result selection
    u8 g0 = mux8(add_res.sum, sub_res.sum, op0);
    u8 g1 = mux8(and_res, or_res, op0);
    u8 g2 = mux8(xor_res, not_res, op0);
    u8 g3 = mux8(shl_res.sum, shr_res.sum, op0);

    u8 g4 = mux8(g0, g1, op1);
    u8 g5 = mux8(g2, g3, op1);

    u8 result = mux8(g4, g5, op2);

    // carry
    u8 c0 = mux(add_res.carry, sub_res.carry, op0);
    u8 c1 = 0; // no carry operation
    u8 c2 = 0; // no carry operation
    u8 c3 = mux(shl_res.carry, shr_res.carry, op0);

    u8 c4 = mux(c0, c1, op1);
    u8 c5 = mux(c2, c3, op1);

    u8 carry = mux(c4, c5, op2);

    // zero
    u8 zero = 1;
    for (u8 i = 0; i < 8; i++) {
        zero = and_(zero, GET_BIT(result, i));
    }

    // sign
    u8 sign = GET_BIT(result, 7);

    // overflow
    u8 msb_a = GET_BIT(a, 7);
    u8 msb_b = GET_BIT(b, 7);
    u8 msb_r = GET_BIT(result, 7);

    u8 overflow_add = and_(xnor_(msb_a, msb_b), xor_(msb_a, msb_r));
    u8 overflow_sub = and_(xor_(msb_a, msb_b), xor_(msb_a, msb_r));
    u8 overflow = mux(overflow_add, overflow_sub, op0);

    return (AluResult){.result = result,
                       .flag = (Flag){.carry = carry,
                                      .zero = zero,
                                      .sign = sign,
                                      .overflow = overflow}};
}

// LATCH
