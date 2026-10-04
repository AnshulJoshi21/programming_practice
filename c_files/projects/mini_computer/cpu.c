// NOTE: NAND ONLY CPU, NO SHORTCUTS
// NOTE: num[0] = msb
// NOTE: num[size - 1] = lsb

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
    int c_out;
} AdderResult;

AdderResult half_adder(const int a, const int b) {
    const int sum   = xor_gate(a, b);
    const int c_out = and_gate(a, b);
    return (AdderResult){sum, c_out};
}

AdderResult full_adder(const int a, const int b, const int c_in) {
    const AdderResult r1 = half_adder(a, b);
    const AdderResult r2 = half_adder(r1.sum, c_in);
    return (AdderResult){.sum = r2.sum, .c_out = or_gate(r1.c_out, r2.c_out)};
}

// MUXES - 1 bit muxes
typedef struct {
    int a0;
    int a1;
} Mux2x1Input;

int mux_2x1(const int sel, const Mux2x1Input data) {
    return or_gate(and_gate(not_gate(sel), data.a0), and_gate(sel, data.a1));
}

typedef struct {
    int a0;
    int a1;
    int a2;
    int a3;
} Mux4x1Input;

// set = 2bits
int mux_4x1(const int sel[2], const Mux4x1Input data) {
    const int sel0 = sel[1];
    const int sel1 = sel[0];

    const int r1 = mux_2x1(sel0, (Mux2x1Input){data.a0, data.a1});
    const int r2 = mux_2x1(sel0, (Mux2x1Input){data.a2, data.a3});

    return mux_2x1(sel1, (Mux2x1Input){r1, r2});
}

typedef struct {
    int a0;
    int a1;
    int a2;
    int a3;
    int a4;
    int a5;
    int a6;
    int a7;
} Mux8x1Input;

// set = 3bits
int mux_8x1(const int sel[3], const Mux8x1Input data) {
    const int sel0 = sel[2];
    const int sel1 = sel[1];
    const int sel2 = sel[0];

    const int mux4sel[2] = {sel1, sel0};
    const int r1         = mux_4x1(mux4sel, (Mux4x1Input){data.a0, data.a1, data.a2, data.a3});
    const int r2         = mux_4x1(mux4sel, (Mux4x1Input){data.a4, data.a5, data.a6, data.a7});

    return mux_2x1(sel2, (Mux2x1Input){r1, r2});
}

// DEMUXES - 1bit demuxes
typedef struct {
    int a0;
    int a1;
} Dmux2x1Output;

Dmux2x1Output dmux_1x2(const int sel, const int data) {
    const int a0 = and_gate(not_gate(sel), data);
    const int a1 = and_gate(sel, data);
    return (Dmux2x1Output){a0, a1};
}

typedef struct {
    int a0;
    int a1;
    int a2;
    int a3;
} Dmux4x1Output;

// sel = 2bits
Dmux4x1Output dmux_1x4(const int sel[2], const int data) {
    const int sel0 = sel[1];
    const int sel1 = sel[0];

    const Dmux2x1Output r1 = dmux_1x2(sel1, data);

    const Dmux2x1Output r2 = dmux_1x2(sel0, r1.a0);
    const Dmux2x1Output r3 = dmux_1x2(sel0, r1.a1);

    return (Dmux4x1Output){r2.a0, r2.a1, r3.a0, r3.a1};
}

typedef struct {
    int a0;
    int a1;
    int a2;
    int a3;
    int a4;
    int a5;
    int a6;
    int a7;
} Dmux8x1Output;

// sel = 3bits
Dmux8x1Output dmux_1x8(const int sel[3], const int data) {
    const int sel0 = sel[2];
    const int sel1 = sel[1];
    const int sel2 = sel[0];

    const Dmux2x1Output r1 = dmux_1x2(sel2, data);

    const int           dmux4sel[2] = {sel1, sel0};
    const Dmux4x1Output r2          = dmux_1x4(dmux4sel, r1.a0);
    const Dmux4x1Output r3          = dmux_1x4(dmux4sel, r1.a1);

    return (Dmux8x1Output){r2.a0, r2.a1, r2.a2, r2.a3, r3.a0, r3.a1, r3.a2, r3.a3};
}

// BASIC OPERATIONS - 8bits
typedef struct {
    int result[MAX_BITS];
    int c_out;
} OperationResult;

OperationResult add8(const int a[MAX_BITS], const int b[MAX_BITS]) {
    OperationResult oresult = {0};

    for (int i = MAX_BITS - 1; i > 0; i--) {
        const AdderResult ar = full_adder(a[i], b[i], oresult.c_out);
        oresult.result[i]    = ar.sum;
        oresult.c_out        = ar.c_out;
    }

    return oresult;
}

OperationResult sub8(const int a[MAX_BITS], const int b[MAX_BITS]) {
    OperationResult oresult = {0};
    oresult.c_out           = 1;

    for (int i = MAX_BITS - 1; i > 0; i--) {
        const AdderResult ar = full_adder(a[i], not_gate(b[i]), oresult.c_out);
        oresult.result[i]    = ar.sum;
        oresult.c_out        = ar.c_out;
    }

    return oresult;
}

OperationResult and8(const int a[MAX_BITS], const int b[MAX_BITS]) {
    OperationResult oresult = {0};
    for (int i = MAX_BITS - 1; i > 0; i--) {
        oresult.result[i] = and_gate(a[i], b[i]);
    }

    return oresult;
}

OperationResult or8(const int a[MAX_BITS], const int b[MAX_BITS]) {
    OperationResult oresult = {0};
    for (int i = MAX_BITS - 1; i > 0; i--) {
        oresult.result[i] = or_gate(a[i], b[i]);
    }

    return oresult;
}

OperationResult xor8(const int a[MAX_BITS], const int b[MAX_BITS]) {
    OperationResult oresult = {0};
    for (int i = MAX_BITS - 1; i > 0; i--) {
        oresult.result[i] = xor_gate(a[i], b[i]);
    }

    return oresult;
}

OperationResult not8(const int a[MAX_BITS]) {
    OperationResult oresult = {0};
    for (int i = MAX_BITS - 1; i > 0; i--) {
        oresult.result[i] = not_gate(a[i]);
    }

    return oresult;
}

OperationResult shl8(const int a[MAX_BITS]) {
    OperationResult oresult = {0};
    oresult.c_out           = a[0];

    for (int i = 0; i < MAX_BITS - 2; i++) {
        oresult.result[i] = a[i + 1];
    }

    oresult.result[MAX_BITS - 1] = 0;

    return oresult;
}

OperationResult shr8(const int a[MAX_BITS]) {
    OperationResult oresult = {0};
    oresult.c_out           = a[MAX_BITS - 1];

    for (int i = 1; i < MAX_BITS - 1; i++) {
        oresult.result[i] = a[i - 1];
    }

    oresult.result[0] = 0;

    return oresult;
}

// ALU
typedef struct {
    int carry;
    int sign;
    int zero;
    int overflow;
} Flag;

typedef struct {
    int  result[MAX_BITS];
    Flag flag;
} AluResult;

// opcode = 3bits
// 000 = ADD
// 001 = SUB
// 010 = AND
// 011 = OR
// 100 = XOR
// 101 = NOT - a
// 110 = SHL (logical) - a
// 111 = SHR (logical) - a
AluResult alu8(const int opcode[3], const int a[MAX_BITS], const int b[MAX_BITS]) {
    AluResult aresult;

    // basic operations
    OperationResult add_result = add8(a, b);
    OperationResult sub_result = sub8(a, b);
    OperationResult and_result = and8(a, b);
    OperationResult or_result  = or8(a, b);
    OperationResult xor_result = xor8(a, b);
    OperationResult not_result = not8(a);
    OperationResult shl_result = shl8(a);
    OperationResult shr_result = shr8(a);

    // result calculation
    for (int i = 0; i < MAX_BITS; i++) {
        aresult.result[i] = mux_8x1(opcode,
                                    (Mux8x1Input){
                                        add_result.result[i],
                                        sub_result.result[i],
                                        and_result.result[i],
                                        or_result.result[i],
                                        xor_result.result[i],
                                        not_result.result[i],
                                        shl_result.result[i],
                                        shr_result.result[i],
                                    });
    }

    // carry calculation
    aresult.flag.carry = mux_8x1(opcode,
                                 (Mux8x1Input){
                                     add_result.c_out,
                                     sub_result.c_out,
                                     0, // no carry operation
                                     0, // no carry operation
                                     0, // no carry operation
                                     0, // no carry operation
                                     shl_result.c_out,
                                     shr_result.c_out,
                                 });

    // sign
    aresult.flag.sign = aresult.result[0];

    // zero
    aresult.flag.zero = 1;
    for (int i = 0; i < MAX_BITS; i++) {
        aresult.flag.zero = and_gate(aresult.flag.zero, not_gate(aresult.result[i]));
    }

    // overflow
    const int msb_a = a[0];
    const int msb_b = b[0];
    const int msb_r = aresult.result[0];

    const int overflow_add = and_gate(xnor_gate(msb_a, msb_b), xor_gate(msb_a, msb_r));
    const int overflow_sub = and_gate(xor_gate(msb_a, msb_b), xor_gate(msb_a, msb_r));
    const int selected_overflow
        = mux_2x1(opcode[2], (Mux2x1Input){overflow_add, overflow_sub}); // opcode lsb

    const int is_arith
        = and_gate(not_gate(opcode[0]), not_gate(opcode[1])); // 000 + 001 = op2'.op1';

    aresult.flag.overflow = and_gate(is_arith, selected_overflow);

    return aresult;
}

// LATCHES + FLIPFLOPS - rising edge
typedef struct {
    int q;
    int q_bar;
} DLatch;

void dl_init(DLatch* dl) {
    assert(dl);

    dl->q     = 0;
    dl->q_bar = not_gate(dl->q);
}

void dl_update(DLatch* dl, const int data, const int enable) {
    assert(dl);

    const int set_bar   = nand_gate(enable, data);
    const int reset_bar = nand_gate(enable, not_gate(data));

    for (int i = 0; i < 2; i++) {
        dl->q     = nand_gate(set_bar, dl->q_bar);
        dl->q_bar = nand_gate(reset_bar, dl->q);
    }
}

typedef struct {
    DLatch master;
    DLatch slave;
} DFlipFlop;

void dff_init(DFlipFlop* dff) {
    assert(dff);

    dl_init(&dff->master);
    dl_init(&dff->slave);
}

void dff_write(DFlipFlop* dff, const int data, const int clk) {
    assert(dff);

    dl_update(&dff->master, data, not_gate(clk));
    dl_update(&dff->slave, dff->master.q, clk);
}

// REGISTERS + RAMS
typedef struct {
    DFlipFlop bits[8];
} Register8;

void register8_init(Register8* reg) {
    assert(reg);

    for (int i = 0; i < MAX_BITS; i++) {
        dff_init(&reg->bits[i]);
    }
}

void register8_read(const Register8* reg) {
    assert(reg);

    for (int i = 0; i < MAX_BITS; i++) {
    }
}

void register8_write(Register8* reg) {
    assert(reg);
}
