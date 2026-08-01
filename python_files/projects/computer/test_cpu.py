import pytest

import cpu


# LOGIC GATES
@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 1),
        (1, 0, 1),
        (0, 1, 1),
        (1, 1, 0),
    ],
    ids=["00", "01", "10", "11"],
)
def test_nand(a: int, b: int, expected: int) -> None:
    assert cpu.nand_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, expected",
    [
        (0, 1),
        (1, 0),
    ],
    ids=["0", "1"],
)
def test_not(a: int, expected: int) -> None:
    assert cpu.not_gate(a) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (1, 0, 0),
        (0, 1, 0),
        (1, 1, 1),
    ],
    ids=["00", "01", "10", "11"],
)
def test_and(a: int, b: int, expected: int) -> None:
    assert cpu.and_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (1, 0, 1),
        (0, 1, 1),
        (1, 1, 1),
    ],
    ids=["00", "01", "10", "11"],
)
def test_or(a: int, b: int, expected: int) -> None:
    assert cpu.or_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 1),
        (1, 0, 0),
        (0, 1, 0),
        (1, 1, 0),
    ],
    ids=["00", "01", "10", "11"],
)
def test_nor(a: int, b: int, expected: int) -> None:
    assert cpu.nor_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (1, 0, 1),
        (0, 1, 1),
        (1, 1, 0),
    ],
    ids=["00", "01", "10", "11"],
)
def test_xor(a: int, b: int, expected: int) -> None:
    assert cpu.xor_gate(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 1),
        (1, 0, 0),
        (0, 1, 0),
        (1, 1, 1),
    ],
    ids=["00", "01", "10", "11"],
)
def test_xnor(a: int, b: int, expected: int) -> None:
    assert cpu.xnor_gate(a, b) == expected


# ADDERS
@pytest.mark.parametrize(
    "a, b, sum, carry",
    [
        (0, 0, 0, 0),
        (1, 0, 1, 0),
        (0, 1, 1, 0),
        (1, 1, 0, 1),
    ],
    ids=["00", "01", "10", "11"],
)
def test_half_adder(a: int, b: int, sum: int, carry: int) -> None:
    assert cpu.half_adder(a, b) == cpu.AdderResult(sum, carry)


@pytest.mark.parametrize(
    "a, b, cin, sum, carry",
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
    ids=["000", "001", "010", "011", "100", "101", "110", "111"],
)
def test_full_adder(a: int, b: int, cin: int, sum: int, carry: int) -> None:
    assert cpu.full_adder(a, b, cin) == cpu.AdderResult(sum, carry)


# MULTIPLEXERS
@pytest.mark.parametrize(
    "sel,a, b, expected",
    [
        (0, 0, 0, 0),
        (0, 0, 1, 0),
        (0, 1, 0, 1),
        (0, 1, 1, 1),
        (1, 0, 0, 0),
        (1, 0, 1, 1),
        (1, 1, 0, 0),
        (1, 1, 1, 1),
    ],
    ids=["000", "001", "010", "011", "100", "101", "110", "111"],
)
def test_mux(sel: int, a: int, b: int, expected: int) -> None:
    assert cpu.mux(sel, a, b) == expected
