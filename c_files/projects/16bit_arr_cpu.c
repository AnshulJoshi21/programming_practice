#include <stdbool.h>

#define MAX_BITS 16

// NOTE: BOOL FOR 1 BIT OPERATIONS
// NOTE: A[16] = MSB <------- LSB // a[0] = msb and a[15] = lsb

typedef struct {
  bool arr[MAX_BITS];

} BoolArray;

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

bool mux(const bool a, const bool b, const bool sel) {
  return or_(and_(a, not_(sel)), and_(b, sel));
}

BoolArray mux16(const BoolArray a, const BoolArray b, const bool sel) {
  BoolArray result = {0};

  for (int i = MAX_BITS - 1; i > -1; i--) {
    result.arr[i] = mux(a.arr[i], b.arr[i], sel);
  }

  return result;
}

// BASIC OPERATIONS
BoolArray not16(const BoolArray a) {
  BoolArray result = {0};

  for (int i = MAX_BITS - 1; i > -1; i--) {
    result.arr[i] = not_(a.arr[i]);
  }

  return result;
}

BoolArray and16(const BoolArray a, const BoolArray b) {
  BoolArray result = {0};

  for (int i = MAX_BITS - 1; i > -1; i--) {
    result.arr[i] = and_(a.arr[i], b.arr[i]);
  }

  return result;
}

BoolArray or16(const BoolArray a, const BoolArray b) {
  BoolArray result = {0};

  for (int i = MAX_BITS - 1; i > -1; i--) {
    result.arr[i] = or_(a.arr[i], b.arr[i]);
  }

  return result;
}

BoolArray xr16(const BoolArray a, const BoolArray b) {
  BoolArray result = {0};

  for (int i = MAX_BITS - 1; i > -1; i--) {
    result.arr[i] = xor_(a.arr[i], b.arr[i]);
  }

  return result;
}

typedef struct OperationResult {
  BoolArray result;
  bool carry;

} OperationResult;

OperationResult add16(const BoolArray a, const BoolArray b) {
  BoolArray result = {0};
  bool carry = 0;

  for (int i = MAX_BITS - 1; i > -1; i--) {
    AddResult r = full_adder(a.arr[i], b.arr[i], carry);

    result.arr[i] = r.sum;
    carry = r.carry;
  }

  return (OperationResult){.result = result, carry = carry};
}

OperationResult sub16(const BoolArray a, const BoolArray b) {
  BoolArray result = {0};
  bool carry = 0;
}
