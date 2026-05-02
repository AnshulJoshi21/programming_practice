// 16 BIT CPU FROM SCRATCH USING ONLY NAND GATES. NO SHORTCUTS

#include <stdbool.h>
#include <stdint.h>

// NOTE: bool for 1 bit operations

#define GET_BIT(num, index) (((num) >> (index)) & 1)
#define SET_BIT(num, index) (((num) & 1) << (index))

#define MAX_BITS 16

typedef uint16_t u16;

// LOGIC GATES

bool nand_(const bool a, const bool b) { return !(a & b); }
bool not_(const bool a) { return nand_(a, a); }
bool and_(const bool a, const bool b) { return not_(nand_(a, b)); }
bool or_(const bool a, const bool b) { return nand_(not_(a), not_(b)); }
bool nor_(const bool a, const bool b) { return not_(or_(a, b)); }
bool xor_(const bool a, const bool b) {
  return or_(and_(not_(a), b), and_(a, not_(b)));
}
bool xnor_(const bool a, const bool b) { return not_(xor_(a, b)); }

// ADDERS
typedef struct AddResult {
  bool sum;
  bool carry;

} AddResult;

AddResult half_adder(const bool a, const bool b) {
  bool sum = xor_(a, b);
  bool carry = and_(a, b);
  return (AddResult){.sum = sum, .carry = carry};
}

AddResult full_adder(const bool a, const bool b, const bool cin) {
  AddResult r1 = half_adder(a, b);
  AddResult r2 = half_adder(r1.sum, cin);

  return (AddResult){.sum = r2.sum, .carry = or_(r1.carry, r2.carry)};
}

// MUX
bool mux_(const bool a, const bool b, const bool sel) {
  return or_(and_(a, not_(sel)), and_(b, sel));
}

u16 mux16(const u16 a, const u16 b, const bool sel) {
  u16 result = 0;

  for (int i = 0; i < MAX_BITS; i++) {
    bool ai = GET_BIT(a, i);
    bool bi = GET_BIT(b, i);

    bool r = mux_(ai, bi, sel);

    result |= SET_BIT(r, i);
  }

  return result;
}

// BASIC 16BIT OPERATSIONS
u16 not16(const u16 a) {
  u16 result = 0;

  for (int i = 0; i < MAX_BITS; i++) {
    bool ai = GET_BIT(a, i);

    bool r = not_(ai);

    result |= SET_BIT(r, i);
  }

  return result;
}

u16 and16(const u16 a, const u16 b) {
  u16 result = 0;

  for (int i = 0; i < MAX_BITS; i++) {
    bool ai = GET_BIT(a, i);
    bool bi = GET_BIT(b, i);

    bool r = and_(ai, bi);

    result |= SET_BIT(r, i);
  }

  return result;
}

u16 or16(const u16 a, const u16 b) {
  u16 result = 0;

  for (int i = 0; i < MAX_BITS; i++) {
    bool ai = GET_BIT(a, i);
    bool bi = GET_BIT(b, i);

    bool r = or_(ai, bi);

    result |= SET_BIT(r, i);
  }

  return result;
}

u16 xor16(const u16 a, const u16 b) {
  u16 result = 0;

  for (int i = 0; i < MAX_BITS; i++) {
    bool ai = GET_BIT(a, i);
    bool bi = GET_BIT(b, i);

    bool r = xor_(ai, bi);

    result |= SET_BIT(r, i);
  }

  return result;
}

typedef struct OperationResult {
  u16 sum;
  bool carry;

} OperationResult;

OperationResult add16(const u16 a, const u16 b) {
  u16 sum = 0;
  bool carry = 0;

  for (int i = 0; i < MAX_BITS; i++) {
    bool ai = GET_BIT(a, i);
    bool bi = GET_BIT(b, i);

    AddResult r = full_adder(ai, bi, carry);

    sum |= SET_BIT(r.sum, i);
    carry = r.carry;
  }

  return (OperationResult){.sum = sum, carry = carry};
}

// 2's complement
OperationResult sub16(const u16 a, const u16 b) {
  u16 one = 1;

  OperationResult r1 = add16(not16(b), one);
  return add16(a, r1.sum);
}

OperationResult shl16(const u16 a) {
  u16 sum = 0;
  bool carry = GET_BIT(a, 15);

  sum |= 0;
  sum |= SET_BIT(GET_BIT(a, 0), 1);
  sum |= SET_BIT(GET_BIT(a, 1), 2);
  sum |= SET_BIT(GET_BIT(a, 2), 3);
  sum |= SET_BIT(GET_BIT(a, 3), 4);
  sum |= SET_BIT(GET_BIT(a, 4), 5);
  sum |= SET_BIT(GET_BIT(a, 5), 6);
  sum |= SET_BIT(GET_BIT(a, 6), 7);
  sum |= SET_BIT(GET_BIT(a, 7), 8);
  sum |= SET_BIT(GET_BIT(a, 8), 9);
  sum |= SET_BIT(GET_BIT(a, 9), 10);
  sum |= SET_BIT(GET_BIT(a, 10), 11);
  sum |= SET_BIT(GET_BIT(a, 11), 12);
  sum |= SET_BIT(GET_BIT(a, 12), 13);
  sum |= SET_BIT(GET_BIT(a, 13), 14);
  sum |= SET_BIT(GET_BIT(a, 14), 15);

  return (OperationResult){.sum = sum, carry = carry};
}

OperationResult shr16(const u16 a) {
  u16 sum = 0;
  bool carry = GET_BIT(a, 0);

  sum |= SET_BIT(GET_BIT(a, 1), 0);
  sum |= SET_BIT(GET_BIT(a, 2), 1);
  sum |= SET_BIT(GET_BIT(a, 3), 2);
  sum |= SET_BIT(GET_BIT(a, 4), 3);
  sum |= SET_BIT(GET_BIT(a, 5), 4);
  sum |= SET_BIT(GET_BIT(a, 6), 5);
  sum |= SET_BIT(GET_BIT(a, 7), 6);
  sum |= SET_BIT(GET_BIT(a, 8), 7);
  sum |= SET_BIT(GET_BIT(a, 9), 8);
  sum |= SET_BIT(GET_BIT(a, 10), 9);
  sum |= SET_BIT(GET_BIT(a, 11), 10);
  sum |= SET_BIT(GET_BIT(a, 12), 11);
  sum |= SET_BIT(GET_BIT(a, 13), 12);
  sum |= SET_BIT(GET_BIT(a, 14), 13);
  sum |= SET_BIT(GET_BIT(a, 15), 14);
  sum |= SET_BIT(0, 15);

  return (OperationResult){.sum = sum, carry = carry};
}

// ALU
typedef struct {
  bool carry;
  bool zero;
  bool sign;
  bool overflow;

} FLAG;

typedef struct {
  u16 result;
  FLAG flag;

} AluResult;

// 000 ADD
// 001 SUB
// 010 AND
// 011 OR
// 100 XOR
// 101 NOT
// 110 SHL
// 111 SHR

AluResult alu16(const u16 a, const u16 b, const uint8_t op) {

  bool op0 = GET_BIT(op, 0);
  bool op1 = GET_BIT(op, 1);
  bool op2 = GET_BIT(op, 2);

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
  u16 r0 = mux16(add_res.sum, sub_res.sum, op0);
  u16 r1 = mux16(and_res, or_res, op0);
  u16 r2 = mux16(xor_res, not_res, op0);
  u16 r3 = mux16(shl_res.sum, shr_res.sum, op0);

  u16 r4 = mux16(r0, r1, op1);
  u16 r5 = mux16(r2, r3, op1);

  u16 result = mux16(r4, r5, op2);

  // carry selection
  bool c0 = mux_(add_res.carry, sub_res.carry, op0);
  bool c1 = 0; // no carry operation
  bool c2 = 0; // no carry operation
  bool c3 = mux_(shl_res.carry, shr_res.carry, op0);

  bool c4 = mux_(c0, c1, op1);
  bool c5 = mux_(c2, c3, op1);

  bool carry = mux_(c4, c5, op2);

  // zero
  bool zero = 1;
  for (int i = 0; i < MAX_BITS; i++) {
    zero = and_(zero, not_(GET_BIT(result, i)));
  }

  // sign
  bool sign = GET_BIT(result, 15);

  // overflow
  bool msb_a = GET_BIT(a, 15);
  bool msb_b = GET_BIT(b, 15);
  bool msb_r = GET_BIT(result, 15);

  bool overflow_add = and_(xnor_(msb_a, msb_b), xor_(msb_a, msb_r));
  bool overflow_sub = and_(xor_(msb_a, msb_b), xor_(msb_a, msb_r));
  bool overflow = mux_(overflow_add, overflow_sub, op0);

  // check if add or sub
  bool is_arith = and_(not_(op2), not_(op1));
  overflow = and_(is_arith, overflow);

  return (AluResult){
      .result = result,
      .flag = (FLAG){
          .carry = carry, .zero = zero, .sign = sign, .overflow = overflow}};
}
