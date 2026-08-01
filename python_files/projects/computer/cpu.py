# NOTE: 16BIT CPU
# NOTE: lsb  ---> msb for every list[int]
#
from dataclasses import dataclass
from enum import IntEnum, auto


# LOGIC GATES
def nand_gate(a: int, b: int) -> int:
    return ~(a & b) & 1


def not_gate(a: int) -> int:
    return ~a & 1


def and_gate(a: int, b: int) -> int:
    return (a & b) & 1


def or_gate(a: int, b: int) -> int:
    return (a | b) & 1


def nor_gate(a: int, b: int) -> int:
    return ~(a | b) & 1


def xor_gate(a: int, b: int) -> int:
    return (a ^ b) & 1


def xnor_gate(a: int, b: int) -> int:
    return ~(a ^ b) & 1


# ADDERS
@dataclass(slots=True)
class AdderResult:
    sum: int
    carry: int


def half_adder(a: int, b: int) -> AdderResult:
    sum: int = (a ^ b) & 1
    carry: int = (a & b) & 1
    return AdderResult(sum=sum, carry=carry)


def full_adder(a: int, b: int, cin: int) -> AdderResult:
    r1: AdderResult = half_adder(a, b)
    r2: AdderResult = half_adder(r1.sum, cin)
    return AdderResult(sum=r2.sum, carry=(or_gate(r2.carry, r1.carry)))


# MULTIPLEXER
def mux(sel: int, a: int, b: int) -> int:
    return (~sel & a) | (sel & b)


def mux4(sel: list[int], a: list[int], b: list[int]) -> list[int]:
    assert len(a) == 4
    assert len(b) == 4

    result: list[int] = []

    return result


# BASIC OPERATIONS


# ALU
