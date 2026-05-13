import pytest

from computer16bit import *

zero16: list[int] = [0] * MAX_BITS
one16: list[int] = [1] * MAX_BITS
random_a16: list[int] = [0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1]
random_b16: list[int] = [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0]
random_c16: list[int] = [1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1]
random_d16: list[int] = [0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0]
random_e16: list[int] = [1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0]
random_f16: list[int] = [0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1]
random_g16: list[int] = [1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0]
random_h16: list[int] = [0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1]
random_i16: list[int] = [1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1]
random_j16: list[int] = [0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0]
random_k16: list[int] = [1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0]
random_l16: list[int] = [0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1]


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
def test_nand(a, b, expected):
    assert nand_(a, b) == expected


@pytest.mark.parametrize(
    "a, expected",
    [
        (0, 1),
        (1, 0),
    ],
)
def test_not(a, expected):
    assert not_(a) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (0, 1, 0),
        (1, 0, 0),
        (1, 1, 1),
    ],
)
def test_and(a, b, expected):
    assert and_(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (0, 1, 1),
        (1, 0, 1),
        (1, 1, 1),
    ],
)
def test_or(a, b, expected):
    assert or_(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 1),
        (0, 1, 0),
        (1, 0, 0),
        (1, 1, 0),
    ],
)
def test_nor(a, b, expected):
    assert nor_(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 0),
        (0, 1, 1),
        (1, 0, 1),
        (1, 1, 0),
    ],
)
def test_xor(a, b, expected):
    assert xor_(a, b) == expected


@pytest.mark.parametrize(
    "a, b, expected",
    [
        (0, 0, 1),
        (0, 1, 0),
        (1, 0, 0),
        (1, 1, 1),
    ],
)
def test_xnor(a, b, expected):
    assert xnor_(a, b) == expected


# ADDERS
@pytest.mark.parametrize(
    "a, b, sum, carry",
    [
        (0, 0, 0, 0),
        (0, 1, 1, 0),
        (1, 0, 1, 0),
        (1, 1, 0, 1),
    ],
)
def test_half_adder(a, b, sum, carry):
    assert half_adder(a, b) == AddResult(sum, carry)


@pytest.mark.parametrize(
    "a, b, cin, sum,  cout",
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
def test_full_adder(a, b, cin, sum, cout):
    assert full_adder(a, b, cin) == AddResult(sum, cout)


# MUXES
@pytest.mark.parametrize(
    "a, b, sel, expected",
    [
        (0, 0, 0, 0),
        (0, 0, 1, 0),
        (0, 1, 0, 0),
        (0, 1, 1, 1),
        (1, 0, 0, 1),
        (1, 0, 1, 0),
        (1, 1, 0, 1),
        (1, 1, 1, 1),
    ],
)
def test_mux(a, b, sel, expected):
    assert mux(a, b, sel) == expected


@pytest.mark.parametrize(
    "a, b, sel, expected",
    [
        (zero16, one16, 0, zero16),
        (one16, zero16, 0, one16),
        (zero16, one16, 1, one16),
        (one16, zero16, 1, zero16),
        (random_a16, random_b16, 0, random_a16),
        (random_b16, random_a16, 0, random_b16),
        (random_a16, random_b16, 1, random_b16),
        (random_b16, random_a16, 1, random_a16),
    ],
)
def test_mux16(a, b, sel, expected):
    assert mux16(a, b, sel) == expected


@pytest.mark.parametrize(
    "a, b, c, d, sel, expected",
    [
        (zero16, one16, random_a16, random_b16, [0, 0], zero16),
        (zero16, one16, random_a16, random_b16, [0, 1], one16),
        (zero16, one16, random_a16, random_b16, [1, 0], random_a16),
        (zero16, one16, random_a16, random_b16, [1, 1], random_b16),
    ],
)
def test_mux4way16(a, b, c, d, sel, expected):
    assert mux4way16(a, b, c, d, sel) == expected


@pytest.mark.parametrize(
    "a, b, c, d,e, f, g, h, sel, expected",
    [
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [0, 0, 0],
            zero16,
        ),
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [0, 0, 1],
            one16,
        ),
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [0, 1, 0],
            random_a16,
        ),
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [0, 1, 1],
            random_b16,
        ),
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [1, 0, 0],
            random_c16,
        ),
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [1, 0, 1],
            random_d16,
        ),
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [1, 1, 0],
            random_e16,
        ),
        (
            zero16,
            one16,
            random_a16,
            random_b16,
            random_c16,
            random_d16,
            random_e16,
            random_f16,
            [1, 1, 1],
            random_f16,
        ),
    ],
)
def test_mux8way16(a, b, c, d, e, f, g, h, sel, expected):
    assert mux8way16(a, b, c, d, e, f, g, h, sel) == expected


# DMUXES
@pytest.mark.parametrize(
    "in_, sel, a, b",
    [
        (0, 0, 0, 0),
        (0, 1, 0, 0),
        (1, 0, 1, 0),
        (1, 1, 0, 1),
    ],
)
def test_dmux(in_, sel, a, b):
    assert dmux(in_, sel) == DmuxResult(a, b)


@pytest.mark.parametrize(
    "in_, sel, a, b, c, d",
    [
        (0, [0, 0], 0, 0, 0, 0),
        (0, [0, 1], 0, 0, 0, 0),
        (0, [1, 0], 0, 0, 0, 0),
        (0, [1, 1], 0, 0, 0, 0),
        (1, [0, 0], 1, 0, 0, 0),
        (1, [0, 1], 0, 1, 0, 0),
        (1, [1, 0], 0, 0, 1, 0),
        (1, [1, 1], 0, 0, 0, 1),
    ],
)
def test_dmux4way(in_, sel, a, b, c, d):
    assert dmux4way(in_, sel) == Dmux4Result(a, b, c, d)


@pytest.mark.parametrize(
    "in_, sel, a, b, c, d, e, f, g, h",
    [
        (0, [0, 0, 0], 0, 0, 0, 0, 0, 0, 0, 0),
        (0, [0, 0, 1], 0, 0, 0, 0, 0, 0, 0, 0),
        (0, [0, 1, 0], 0, 0, 0, 0, 0, 0, 0, 0),
        (0, [0, 1, 1], 0, 0, 0, 0, 0, 0, 0, 0),
        (0, [1, 0, 0], 0, 0, 0, 0, 0, 0, 0, 0),
        (0, [1, 0, 1], 0, 0, 0, 0, 0, 0, 0, 0),
        (0, [1, 1, 0], 0, 0, 0, 0, 0, 0, 0, 0),
        (0, [1, 1, 1], 0, 0, 0, 0, 0, 0, 0, 0),
        (1, [0, 0, 0], 1, 0, 0, 0, 0, 0, 0, 0),
        (1, [0, 0, 1], 0, 1, 0, 0, 0, 0, 0, 0),
        (1, [0, 1, 0], 0, 0, 1, 0, 0, 0, 0, 0),
        (1, [0, 1, 1], 0, 0, 0, 1, 0, 0, 0, 0),
        (1, [1, 0, 0], 0, 0, 0, 0, 1, 0, 0, 0),
        (1, [1, 0, 1], 0, 0, 0, 0, 0, 1, 0, 0),
        (1, [1, 1, 0], 0, 0, 0, 0, 0, 0, 1, 0),
        (1, [1, 1, 1], 0, 0, 0, 0, 0, 0, 0, 1),
    ],
)
def test_dmux8way(in_, sel, a, b, c, d, e, f, g, h):
    assert dmux8way(in_, sel) == Dmux8Result(a, b, c, d, e, f, g, h)
