#include "cpu.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

// LOGIC GATES
void test_nand(void) {
    assert(nand_gate(0, 0) == 1);
    assert(nand_gate(0, 1) == 1);
    assert(nand_gate(1, 0) == 1);
    assert(nand_gate(1, 1) == 0);
}

void test_not(void) {
    assert(not_gate(0) == 1);
    assert(not_gate(1) == 0);
}

void test_and(void) {
    assert(and_gate(0, 0) == 0);
    assert(and_gate(0, 1) == 0);
    assert(and_gate(1, 0) == 0);
    assert(and_gate(1, 1) == 1);
}

void test_or(void) {
    assert(or_gate(0, 0) == 0);
    assert(or_gate(0, 1) == 1);
    assert(or_gate(1, 0) == 1);
    assert(or_gate(1, 1) == 1);
}

void test_nor(void) {
    assert(nor_gate(0, 0) == 1);
    assert(nor_gate(0, 1) == 0);
    assert(nor_gate(1, 0) == 0);
    assert(nor_gate(1, 1) == 0);
}

void test_xor(void) {
    assert(xor_gate(0, 0) == 0);
    assert(xor_gate(0, 1) == 1);
    assert(xor_gate(1, 0) == 1);
    assert(xor_gate(1, 1) == 0);
}

void test_xnor(void) {
    assert(xnor_gate(0, 0) == 1);
    assert(xnor_gate(0, 1) == 0);
    assert(xnor_gate(1, 0) == 0);
    assert(xnor_gate(1, 1) == 1);
}

void test_logic_gates(void) {
    printf("============LOGIC GATE TESTS=============\n\n");

    test_nand();
    printf("Nand Gate - All Test Passed\n");

    test_not();
    printf("Not Gate  - All Test Passed\n");

    test_and();
    printf("And Gate  - All Test Passed\n");

    test_or();
    printf("Or Gate   - All Test Passed\n");

    test_nor();
    printf("Nor Gate  - All Test Passed\n");

    test_xor();
    printf("Xor Gate  - All Test Passed\n");

    test_xnor();
    printf("Xnor Gate - All Test Passed\n");

    printf("\n=========================================\n\n");
}

// ADDERS
void test_half_adder(void) {
    AdderResult result;

    result = half_adder(0, 0);
    assert(result.sum == 0);
    assert(result.carry == 0);

    result = half_adder(0, 1);
    assert(result.sum == 1);
    assert(result.carry == 0);

    result = half_adder(1, 0);
    assert(result.sum == 1);
    assert(result.carry == 0);

    result = half_adder(1, 1);
    assert(result.sum == 0);
    assert(result.carry == 1);
}

void test_full_adder(void) {
    AdderResult result;

    result = full_adder(0, 0, 0);
    assert(result.sum == 0);
    assert(result.carry == 0);

    result = full_adder(0, 0, 1);
    assert(result.sum == 1);
    assert(result.carry == 0);

    result = full_adder(0, 1, 0);
    assert(result.sum == 1);
    assert(result.carry == 0);

    result = full_adder(0, 1, 1);
    assert(result.sum == 0);
    assert(result.carry == 1);

    result = full_adder(1, 0, 0);
    assert(result.sum == 1);
    assert(result.carry == 0);

    result = full_adder(1, 0, 1);
    assert(result.sum == 0);
    assert(result.carry == 1);

    result = full_adder(1, 1, 0);
    assert(result.sum == 0);
    assert(result.carry == 1);

    result = full_adder(1, 1, 1);
    assert(result.sum == 1);
    assert(result.carry == 1);
}

void test_adders(void) {
    printf("================ADDER TESTS===============\n\n");

    test_half_adder();
    printf("Half Adder - All Test Passed\n");

    test_full_adder();
    printf("Full Adder - All Test Passed\n");

    printf("\n=========================================\n\n");
}

// MULTIPLEXERS
void test_mux_2x1(void) {
    // ranges are possible combinations of bits
    for (int sel = 0; sel < 2; sel++) {
        for (int inputs = 0; inputs < pow(2, 2); inputs++) {
            const Mux2Input in = (Mux2Input){
                .a1 = (inputs >> 0) & 1u,
                .a2 = (inputs >> 1) & 1u,
            };

            int expected = -1;

            switch (sel) {
                case 0:
                    expected = in.a1;
                    break;
                case 1:
                    expected = in.a2;
                    break;
            }

            assert(mux_2x1(sel, in) == expected);
        }
    }
}

void test_mux_4x1(void) {
    // ranges are possible combinations of bits
    for (int sel = 0; sel < pow(2, 2); sel++) {
        for (int inputs = 0; inputs < pow(2, 4); inputs++) {
            const Mux4Input in = (Mux4Input){
                .a1 = (inputs >> 0) & 1u,
                .a2 = (inputs >> 1) & 1u,
                .a3 = (inputs >> 2) & 1u,
                .a4 = (inputs >> 3) & 1u,
            };

            int expected = -1;

            switch (sel) {
                case 0:
                    expected = in.a1;
                    break;
                case 1:
                    expected = in.a2;
                    break;
                case 2:
                    expected = in.a3;
                    break;
                case 3:
                    expected = in.a4;
                    break;
            }

            assert(mux_4x1(sel, in) == expected);
        }
    }
}

void test_mux_8x1(void) {
    // ranges are possible combinations of bits
    for (int sel = 0; sel < pow(2, 3); sel++) {
        for (int inputs = 0; inputs < pow(2, 8); inputs++) {
            const Mux8Input in = (Mux8Input){
                .a1 = (inputs >> 0) & 1u,
                .a2 = (inputs >> 1) & 1u,
                .a3 = (inputs >> 2) & 1u,
                .a4 = (inputs >> 3) & 1u,
                .a5 = (inputs >> 4) & 1u,
                .a6 = (inputs >> 5) & 1u,
                .a7 = (inputs >> 6) & 1u,
                .a8 = (inputs >> 7) & 1u,
            };

            int expected = -1;

            switch (sel) {
                case 0:
                    expected = in.a1;
                    break;
                case 1:
                    expected = in.a2;
                    break;
                case 2:
                    expected = in.a3;
                    break;
                case 3:
                    expected = in.a4;
                    break;
                case 4:
                    expected = in.a5;
                    break;
                case 5:
                    expected = in.a6;
                    break;
                case 6:
                    expected = in.a7;
                    break;
                case 7:
                    expected = in.a8;
                    break;
            }

            assert(mux_8x1(sel, in) == expected);
        }
    }
}

void test_mux_16x1(void) {
    // ranges are possible combinations of bits
    for (int sel = 0; sel < pow(2, 4); sel++) {
        for (int inputs = 0; inputs < pow(2, 16); inputs++) {
            const Mux16Input in = (Mux16Input){
                .a1  = (inputs >> 0) & 1u,
                .a2  = (inputs >> 1) & 1u,
                .a3  = (inputs >> 2) & 1u,
                .a4  = (inputs >> 3) & 1u,
                .a5  = (inputs >> 4) & 1u,
                .a6  = (inputs >> 5) & 1u,
                .a7  = (inputs >> 6) & 1u,
                .a8  = (inputs >> 7) & 1u,
                .a9  = (inputs >> 8) & 1u,
                .a10 = (inputs >> 9) & 1u,
                .a11 = (inputs >> 10) & 1u,
                .a12 = (inputs >> 11) & 1u,
                .a13 = (inputs >> 12) & 1u,
                .a14 = (inputs >> 13) & 1u,
                .a15 = (inputs >> 14) & 1u,
                .a16 = (inputs >> 15) & 1u,
            };

            int expected = -1;

            switch (sel) {
                case 0:
                    expected = in.a1;
                    break;
                case 1:
                    expected = in.a2;
                    break;
                case 2:
                    expected = in.a3;
                    break;
                case 3:
                    expected = in.a4;
                    break;
                case 4:
                    expected = in.a5;
                    break;
                case 5:
                    expected = in.a6;
                    break;
                case 6:
                    expected = in.a7;
                    break;
                case 7:
                    expected = in.a8;
                    break;
                case 8:
                    expected = in.a9;
                    break;
                case 9:
                    expected = in.a10;
                    break;
                case 10:
                    expected = in.a11;
                    break;
                case 11:
                    expected = in.a12;
                    break;
                case 12:
                    expected = in.a13;
                    break;
                case 13:
                    expected = in.a14;
                    break;
                case 14:
                    expected = in.a15;
                    break;
                case 15:
                    expected = in.a16;
                    break;
            }

            assert(mux_16x1(sel, in) == expected);
        }
    }
}

void test_muxes(void) {
    printf("==================MUX TESTS===============\n\n");

    test_mux_2x1();
    printf("Mux 2:1  - All Test Passed\n");

    test_mux_4x1();
    printf("Mux 4:1  - All Test Passed\n");

    test_mux_8x1();
    printf("Mux 8:1  - All Test Passed\n");

    test_mux_16x1();
    printf("Mux 16:1 - All Test Passed\n");

    printf("\n=========================================\n\n");
}
