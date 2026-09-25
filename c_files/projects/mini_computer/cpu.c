// NOTE: nand only 8bit cpu
// NOTE: bit arr = [msb ... lsb];
// NOTE: lsb = arr[max_bits - 1];
// NOTE: msb = arr[0];

#include <assert.h>

#define MAX_BITS 8

// LOGIC GATES
int nand_gate(const int a, const int b) {
    return (a == 1 && b == 1) ? 0 : 1;
}

int not_gate(const int a) {
    return nand_gate(a, a);
}

int and_gate(const int a, const int b) {
    return not_gate(nand_gate(a, b));
}

int or_gate(const int a, const int b) {
    return nand_gate(not_gate(a), not_gate(b));
}

int nor_gate(const int a, const int b) {
    return not_gate(or_gate(a, b));
}

int xor_gate(const int a, const int b) {
    return or_gate(and_gate(not_gate(a), b), and_gate(a, not_gate(b)));
}

int xnor_gate(const int a, const int b) {
    return not_gate(xor_gate(a, b));
}

// ADDERS
typedef struct {
    int sum;
    int carry;
} AdderResult;

AdderResult half_adder(const int a, const int b) {
    const int sum   = xor_gate(a, b);
    const int carry = and_gate(a, b);
    return (AdderResult){sum, carry};
}

AdderResult full_adder(const int a, const int b, const int cin) {
    const AdderResult r1 = half_adder(a, b);
    const AdderResult r2 = half_adder(r1.sum, cin);
    return (AdderResult){.sum = r2.sum, .carry = or_gate(r1.carry, r2.carry)};
}

// MUXES
typedef struct {
    int a;
    int b;
} Mux2x1Input;

int mux_2x1(const int sel, const Mux2x1Input data) {
    return or_gate(and_gate(not_gate(sel), data.a), and_gate(sel, data.b));
}

typedef struct {
    int a;
    int b;
    int c;
    int d;
} Mux4x1Input;

// sel = 2 bits
int mux_4x1(const int sel[], const Mux4x1Input data) {
    const int sel0 = sel[1];
    const int sel1 = sel[0];

    const int r1 = mux_2x1(sel0, (Mux2x1Input){data.a, data.b});
    const int r2 = mux_2x1(sel0, (Mux2x1Input){data.c, data.d});

    return mux_2x1(sel1, (Mux2x1Input){r1, r2});
}

typedef struct {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
} Mux8x1Input;

// sel = 3 bits
int mux_8x1(const int sel[], const Mux8x1Input data) {
    const int sel0 = sel[2];
    const int sel1 = sel[1];
    const int sel2 = sel[0];

    const int sel4x1[] = {sel1, sel0};
    const int r1       = mux_4x1(sel4x1, (Mux4x1Input){data.a, data.b, data.c, data.d});
    const int r2       = mux_4x1(sel4x1, (Mux4x1Input){data.e, data.f, data.g, data.h});

    return mux_2x1(sel2, (Mux2x1Input){r1, r2});
}

// DE-MUXES
typedef struct {
    int a;
    int b;
} Dmux1x2Output;

Dmux1x2Output dmux_1x2(const int sel, const int data) {
    const int a = and_gate(not_gate(sel), data);
    const int b = and_gate(sel, data);
    return (Dmux1x2Output){a, b};
}

typedef struct {
    int a;
    int b;
    int c;
    int d;
} Dmux1x4Output;

// sel = 2bits
Dmux1x4Output dmux_1x4(const int sel[], const int data) {
    const int sel0 = sel[1];
    const int sel1 = sel[0];

    const Dmux1x2Output r1 = dmux_1x2(sel1, data);

    const Dmux1x2Output r2 = dmux_1x2(sel0, r1.a);
    const Dmux1x2Output r3 = dmux_1x2(sel0, r1.b);

    return (Dmux1x4Output){r2.a, r2.b, r3.a, r3.b};
}

typedef struct {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
} Dmux1x8Output;

// sel = 3bits
Dmux1x8Output dmux_1x8(const int sel[], const int data) {
    const int sel0 = sel[2];
    const int sel1 = sel[1];
    const int sel2 = sel[0];

    const Dmux1x2Output r1 = dmux_1x2(sel2, data);

    const int           sel1x4[] = {sel1, sel0};
    const Dmux1x4Output r2       = dmux_1x4(sel1x4, r1.a);
    const Dmux1x4Output r3       = dmux_1x4(sel1x4, r1.b);

    return (Dmux1x8Output){r2.a, r2.b, r2.c, r2.d, r3.a, r3.b, r3.c, r3.d};
}

// BASIC OPERATIONS
//
// result[max_bits]
//
void and8(const int a[], const int b[], int* result) {
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        result[i] = and_gate(a[i], b[i]);
    }
}

void or8(const int a[], const int b[], int* result) {
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        result[i] = or_gate(a[i], b[i]);
    }
}

void xor8(const int a[], const int b[], int* result) {
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        result[i] = xor_gate(a[i], b[i]);
    }
}

void not8(const int a[], int* result) {
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        result[i] = not_gate(a[i]);
    }
}

typedef struct {
    int result[MAX_BITS];
    int carry;
} OperationResult;

OperationResult add8(const int a[], const int b[]) {
    OperationResult result = {0};

    for (int i = MAX_BITS - 1; i >= 0; i--) {
        const AdderResult temp_result = full_adder(a[i], b[i], result.carry);
        result.result[i]              = temp_result.sum;
        result.carry                  = temp_result.carry;
    }

    return result;
}

OperationResult sub8(const int a[], const int b[]) {
    OperationResult result = {0};
    result.carry           = 1;

    for (int i = MAX_BITS - 1; i >= 0; i--) {
        const AdderResult temp_result = full_adder(a[i], not_gate(b[i]), result.carry);
        result.result[i]              = temp_result.sum;
        result.carry                  = temp_result.carry;
    }

    return result;
}

OperationResult shl8(const int a[]) {
    OperationResult result = {0};
    result.carry           = a[0];

    for (int i = 0; i < MAX_BITS - 1; i++) {
        result.result[i] = a[i + 1];
    }
    result.result[MAX_BITS - 1] = 0;

    return result;
}

OperationResult shr8(const int a[]) {
    OperationResult result = {0};
    result.carry           = a[MAX_BITS - 1];

    for (int i = 1; i < MAX_BITS; i++) {
        result.result[i] = a[i - 1];
    }
    result.result[0] = 0;

    return result;
}

// ALU
typedef struct {
    int carry;
    int zero;
    int sign;
    int overflow;
} Flag;

typedef struct {
    int  result[MAX_BITS];
    Flag flag;
} AluResult;

// opcode = 3bits
// 000 = add
// 001 = sub
// 010 = and
// 011 = or
// 100 = xor
// 101 = not = a[]
// 110 = shl(logical) = a[]
// 111 = shr(logical) = a[]
AluResult cpu8(const int opcode[], const int a[], const int b[]) {
    AluResult result = {0};

    // basic operations
    int and_result[MAX_BITS];
    int or_result[MAX_BITS];
    int xor_result[MAX_BITS];
    int not_result[MAX_BITS];
    and8(a, b, and_result);
    or8(a, b, or_result);
    xor8(a, b, xor_result);
    not8(a, not_result);

    const OperationResult add_result = add8(a, b);
    const OperationResult sub_result = sub8(a, b);
    const OperationResult shl_result = shl8(a);
    const OperationResult shr_result = shr8(a);

    // result
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        result.result[i] = mux_8x1(opcode,
                                   (Mux8x1Input){add_result.result[i],
                                                 sub_result.result[i],
                                                 and_result[i],
                                                 or_result[i],
                                                 xor_result[i],
                                                 not_result[i],
                                                 shl_result.result[i],
                                                 shr_result.result[i]});
    }

    // carry
    //
    // 0 == no carry operation
    //
    result.flag.carry = mux_8x1(
        opcode,
        (Mux8x1Input){
            add_result.carry, sub_result.carry, 0, 0, 0, 0, shl_result.carry, shr_result.carry});

    // zero
    result.flag.zero = 1;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        result.flag.zero = and_gate(result.flag.zero, not_gate(result.result[i]));
    }

    // sign
    result.flag.sign = result.result[0];

    // overflow
    const int msb_a = a[0];
    const int msb_b = b[0];
    const int msb_r = result.result[0];

    const int overflow_add = and_gate(xnor_gate(msb_a, msb_b), xor_gate(msb_a, msb_r));
    const int overflow_sub = and_gate(xor_gate(msb_a, msb_b), xor_gate(msb_a, msb_r));

    // opcode 2 == [0] and 1 == [1]
    const int is_arith = and_gate(not_gate(opcode[0]), not_gate(opcode[1]));

    result.flag.overflow = and_gate(is_arith, or_gate(overflow_add, overflow_sub));

    return result;
}

// LATCHES + FLIPFLOPS - rising edge triggered
typedef struct {
    int q;
    int q_bar;
} DLatch;

void dl_init(DLatch* dl, const int q) {
    assert(dl);

    dl->q     = q;
    dl->q_bar = not_gate(dl->q);
}

int dl_update(DLatch* dl, const int data, const int enable) {
    assert(dl);

    const int set   = nand_gate(data, enable);
    const int reset = nand_gate(not_gate(data), enable);

    for (int i = 0; i < 2; i++) {
        dl->q     = nand_gate(set, dl->q_bar);
        dl->q_bar = nand_gate(reset, dl->q);
    }

    return dl->q;
}

typedef struct {
    DLatch master;
    DLatch slave;
} DFlipFlop;

void dff_init(DFlipFlop* dff) {
    assert(dff);

    dl_init(&dff->master, 0);
    dl_init(&dff->slave, dff->master.q);
}

int dff_update(DFlipFlop* dff, const int data, const int clk) {
    assert(dff);

    const int qm = dl_update(&dff->master, data, not_gate(clk));
    const int qs = dl_update(&dff->slave, qm, clk);

    return qs;
}

// REGISTERS AND RAMS
typedef struct {
    DFlipFlop bit[MAX_BITS];
} Register8;

void reg8_init(Register8* reg8) {
    assert(reg8);

    for (int i = 0; i < MAX_BITS; i++) {
        dff_init(&reg8->bit[i]);
    }
}

void reg8_update(Register8* reg8, const int data[MAX_BITS], const int enable, const int clk) {
    assert(reg8);
}
