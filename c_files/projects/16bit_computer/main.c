#include "cpu.h"
#include "test_cpu.h"

int main(void) {
    test_logic_gates();
    test_adders();
    test_muxes();

    return 0;
}
