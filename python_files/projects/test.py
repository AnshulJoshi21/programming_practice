# NOTE: binary number: list[int] = msb ...... lsb
from dataclasses import dataclass

# ================================================
# LOGIC GATES
# ================================================


def NAND(a: int, b: int) -> int:
    return 1 if (a == 0 or b == 0) else 0


def NOT(a: int) -> int:
    return NAND(a, a)


def AND(a: int, b: int) -> int:
    return NOT(NAND(a, b))


def OR(a: int, b: int) -> int:
    return NAND(NOT(a), NOT(b))


def NOR(a: int, b: int) -> int:
    return NOT(OR(a, b))


def XOR(a: int, b: int) -> int:
    return OR(AND(NOT(a), b), AND(a, NOT(b)))


def XNOR(a: int, b: int) -> int:
    return NOT(XOR(a, b))


# ================================================
# ADDERS
# ================================================


@dataclass(slots=True)
class AddResult:
    sum: int
    carry: int


def half_adder(a: int, b: int) -> AddResult:
    sum: int = XOR(a, b)
    carry: int = AND(a, b)

    return AddResult(sum=sum, carry=carry)


def full_adder(a: int, b: int, cin: int) -> AddResult:
    r1: AddResult = half_adder(a, b)
    r2: AddResult = half_adder(r1.sum, cin)

    return AddResult(sum=r2.sum, carry=OR(r1.carry, r2.carry))


# ================================================
# MUX
# ================================================


def mux(a: int, b: int, sel: int) -> int:
    return OR(AND(a, NOT(sel)), AND(b, sel))


def mux8(a: list[int], b: list[int], sel: int) -> list[int]:
    result: list[int] = [0] * 8

    for i in range(7, -1, -1):
        result[i] = mux(a[i], b[i], sel)

    return result


# ================================================
# BASIC OPERTAIONS
# ================================================


@dataclass(slots=True)
class OperationResult:
    sum: list[int]
    carry: int


def not8(a: list[int]) -> list[int]:
    result: list[int] = [0] * 8

    for i in range(7, -1, -1):
        result[i] = NOT(a[i])

    return result


def and8(a: list[int], b: list[int]) -> list[int]:
    result: list[int] = [0] * 8

    for i in range(7, -1, -1):
        result[i] = AND(a[i], b[i])

    return result


def or8(a: list[int], b: list[int]) -> list[int]:
    result: list[int] = [0] * 8

    for i in range(7, -1, -1):
        result[i] = OR(a[i], b[i])

    return result


def xor8(a: list[int], b: list[int]) -> list[int]:
    result: list[int] = [0] * 8

    for i in range(7, -1, -1):
        result[i] = XOR(a[i], b[i])

    return result


def add8(a: list[int], b: list[int]) -> OperationResult:
    sum: list[int] = [0] * 8
    carry: int = 0

    for i in range(7, -1, -1):
        temp: AddResult = full_adder(a[i], b[i], carry)

        sum[i] = temp.sum
        carry = temp.carry

    return OperationResult(sum=sum, carry=carry)


def sub8(a: list[int], b: list[int]) -> OperationResult:
    carry: int = 1
    sum: list[int] = [0] * 8
    not8_b: list[int] = not8(b)

    for i in range(7, -1, -1):
        temp: AddResult = full_adder(a[i], not8_b[i], carry)
        sum[i] = temp.sum
        carry = temp.carry

    return OperationResult(sum=sum, carry=carry)


# ================================================
# SHIFT OPERTAIONS
# ================================================


def shl8(a: list[int]) -> OperationResult:
    sum: list[int] = [0] * 8
    carry: int = a[0]

    sum[0] = a[1]
    sum[1] = a[2]
    sum[2] = a[3]
    sum[3] = a[4]
    sum[4] = a[5]
    sum[5] = a[6]
    sum[6] = a[7]
    sum[7] = 0

    return OperationResult(sum=sum, carry=carry)


def shr8(a: list[int]) -> OperationResult:
    sum: list[int] = [0] * 8
    carry: int = a[7]

    sum[0] = 0
    sum[1] = a[0]
    sum[2] = a[1]
    sum[3] = a[2]
    sum[4] = a[3]
    sum[5] = a[4]
    sum[6] = a[5]
    sum[7] = a[6]

    return OperationResult(sum=sum, carry=carry)


# ================================================
# ALU
# ================================================


@dataclass(slots=True)
class Flag:
    carry: int
    zero: int
    sign: int
    overflow: int


@dataclass(slots=True)
class AluResult:
    result: list[int]
    flag: Flag


# op codes
# 000	ADD
# 001	SUB
# 010	AND
# 011	OR
# 100	XOR
# 101	NOT (on A)
# 110	SHL (A << 1)
# 111	SHR (A >> 1)
def alu8(a: list[int], b: list[int], op: list[int]) -> AluResult:
    op0: int = op[2]
    op1: int = op[1]
    op2: int = op[0]

    ## operations
    add_res: OperationResult = add8(a, b)
    sub_res: OperationResult = sub8(a, b)

    and_res: list[int] = and8(a, b)
    or_res: list[int] = or8(a, b)
    xor_res: list[int] = xor8(a, b)
    not_res: list[int] = not8(a)

    shl_res: OperationResult = shl8(a)
    shr_res: OperationResult = shr8(a)

    ## result selection
    g0: list[int] = mux8(add_res.sum, sub_res.sum, op0)
    g1: list[int] = mux8(and_res, or_res, op0)
    g2: list[int] = mux8(xor_res, not_res, op0)
    g3: list[int] = mux8(shl_res.sum, shr_res.sum, op0)

    g4: list[int] = mux8(g0, g1, op1)
    g5: list[int] = mux8(g2, g3, op1)

    result: list[int] = mux8(g4, g5, op2)

    ## carry selection
    c0: int = mux(add_res.carry, sub_res.carry, op0)
    c1: int = 0  # no carry operation
    c2: int = 0  # no carry operation
    c3: int = mux(shl_res.carry, shr_res.carry, op0)

    c4: int = mux(c0, c1, op1)
    c5: int = mux(c2, c3, op1)

    carry: int = mux(c4, c5, op2)

    ## zero
    zero: int = 1

    for bit in result:
        zero = AND(zero, bit)

    ## sign
    sign: int = result[0]

    ## overflow

    msb_a: int = a[0]
    msb_b: int = b[0]
    msb_r: int = result[0]

    overflow_add: int = AND(XNOR(msb_a, msb_b), XOR(msb_a, msb_r))
    overflow_sub: int = AND(XOR(msb_a, msb_b), XOR(msb_a, msb_r))

    is_add_sub: int = AND(NOT(op2), NOT(op1))
    overflow: int = AND(is_add_sub, mux(overflow_add, overflow_sub, op0))

    return AluResult(
        result=result, flag=Flag(carry=carry, zero=zero, sign=sign, overflow=overflow)
    )


# ================================================
# LATCH
# ================================================


# ================================================
# REGISTER
# ================================================


# ================================================
# TESTS
# ================================================


def binary_list_to_decimal(bits: list[int]) -> int:
    return int("".join(map(str, bits)), 2)


a: list[int] = [0, 0, 0, 0, 0, 1, 0, 1]  # 5
b: list[int] = [0, 0, 0, 0, 0, 0, 1, 1]  # 3
op: list[int] = [0, 0, 1]
result: AluResult = alu8(a, b, op)

print(f"Binary: {result}")
print(f"Decimal: {binary_list_to_decimal(result.result)}")
