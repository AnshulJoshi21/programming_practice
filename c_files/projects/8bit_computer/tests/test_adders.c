#include "../cpu.h"
#include <assert.h>

void test_half_adder(void) {
    OperationResult result;

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
    OperationResult result;

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
