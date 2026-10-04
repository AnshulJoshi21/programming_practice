import cpu
import pytest
from cpu import BIT, WORD


# LOGIC GATES
@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 1),
        (0, 1, 1),
        (1, 0, 1),
        (1, 1, 0),
    ],
)
def test_nand_gate(a: BIT, b: BIT, expected: BIT):
    assert cpu.nand_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, expected",
    [
        (0, 1),
        (1, 0),
    ],
)
def test_not_gate(a: BIT, expected: BIT):
    assert cpu.not_gate(a) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (0, 1, 0),
        (1, 0, 0),
        (1, 1, 1),
    ],
)
def test_and_gate(a: BIT, b: BIT, expected: BIT):
    assert cpu.and_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (0, 1, 1),
        (1, 0, 1),
        (1, 1, 1),
    ],
)
def test_or_gate(a: BIT, b: BIT, expected: BIT):
    assert cpu.or_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (0, 1, 1),
        (1, 0, 1),
        (1, 1, 0),
    ],
)
def test_xor_gate(a: BIT, b: BIT, expected: BIT):
    assert cpu.xor_gate(a, b) == expected


# ADDERS
@pytest.mark.parametrize(
    "a, b, sum, cout",
    [
        (0, 0, 0, 0),
        (0, 1, 1, 0),
        (1, 0, 1, 0),
        (1, 1, 0, 1),
    ],
)
def test_half_adder(a: BIT, b: BIT, sum: BIT, cout: BIT):
    assert cpu.half_adder(a, b) == cpu.AdderResult(sum, cout)


@pytest.mark.parametrize(
    "a, b, cin, sum, cout",
    [
        (0, 0, 0, 0, 0),
        (0, 0, 1, 1, 0),
        (0, 1, 0, 1, 0),
        (0, 1, 1, 0, 1),
        (1, 0, 0, 1, 0),
        (1, 0, 1, 0, 1),
        (1, 1, 0, 0, 1),
        (1, 1, 1, 1, 1),
    ],
)
def test_full_adder(a: BIT, b: BIT, cin: BIT, sum: BIT, cout: BIT):
    assert cpu.full_adder(a, b, cin) == cpu.AdderResult(sum, cout)


# MUXES
def test_mux_2x1(sel: BIT, data: cpu.Mux2x1Input):
    for s in range(2):
        for d in range(4):
            pass
