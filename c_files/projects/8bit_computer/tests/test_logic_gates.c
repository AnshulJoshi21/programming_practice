#include "../cpu.h"
#include <assert.h>

void test_nand(void) {
    assert(nand_gate(0, 0) == 1);
    assert(nand_gate(0, 1) == 1);
    assert(nand_gate(1, 0) == 1);
    assert(nand_gate(1, 1) == 0);
}

void test_not(const u8 a) {
    assert(not_gate(0) == 1);
    assert(not_gate(1) == 0);
}

void test_and(const u8 a, const u8 b) {
    assert(and_gate(0, 0) == 0);
    assert(and_gate(0, 1) == 0);
    assert(and_gate(1, 0) == 0);
    assert(and_gate(1, 1) == 1);
}

void test_or(const u8 a, const u8 b) {
    assert(or_gate(0, 0) == 0);
    assert(or_gate(0, 1) == 1);
    assert(or_gate(1, 0) == 1);
    assert(or_gate(1, 1) == 1);
}

void test_nor(const u8 a, const u8 b) {
    assert(nor_gate(0, 0) == 1);
    assert(nor_gate(0, 1) == 0);
    assert(nor_gate(1, 0) == 0);
    assert(nor_gate(1, 1) == 0);
}

void test_xor(const u8 a, const u8 b) {
    assert(xor_gate(0, 0) == 0);
    assert(xor_gate(0, 1) == 1);
    assert(xor_gate(1, 0) == 1);
    assert(xor_gate(1, 1) == 0);
}

void test_xnor(const u8 a, const u8 b) {
    assert(xnor_gate(0, 0) == 1);
    assert(xnor_gate(0, 1) == 0);
    assert(xnor_gate(1, 0) == 0);
    assert(xnor_gate(1, 1) == 1);
}
