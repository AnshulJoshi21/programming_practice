# NOTE: binary number = msb(0) ..... lsb(7)
from dataclasses import dataclass

####################################################
# LOGIC GATES
####################################################


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


####################################################
# ADDERS
####################################################


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


####################################################
# MUX
####################################################
#
def mux(a: int, b: int, sel: int) -> int:
    return OR(AND(a, NOT(sel)), AND(b, sel))


def mux8(a: list[int], b: list[int], sel: int) -> list[int]:
    result: list[int] = [0] * 8
    for i in range(7, -1, -1):
        result[i] = mux(a[i], b[i], sel)

    return result


####################################################
# BASIC OPERATIONS
####################################################


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
    op_res: OperationResult = OperationResult(sum=[0] * 8, carry=0)

    for i in range(7, -1, -1):
        add_res: AddResult = full_adder(a[i], b[i], op_res.carry)
        op_res.sum[i] = add_res.sum
        op_res.carry = add_res.carry

    return op_res


def sub8(a: list[int], b: list[int]) -> OperationResult:
    one: list[int] = [0] * 8
    one[7] = 1

    temp: OperationResult = add8(not8(b), one)

    return add8(a, temp.sum)


def shl8(a: list) -> OperationResult:
    op_res: OperationResult = OperationResult(sum=[0] * 8, carry=a[0])

    op_res.sum[0] = a[6]
    op_res.sum[1] = a[5]
    op_res.sum[2] = a[4]
    op_res.sum[3] = a[3]
    op_res.sum[4] = a[2]
    op_res.sum[5] = a[1]
    op_res.sum[6] = a[0]
    op_res.sum[7] = 0

    return op_res


def shr8(a: list) -> OperationResult:
    op_res: OperationResult = OperationResult(sum=[0] * 8, carry=a[7])

    op_res.sum[0] = 0
    op_res.sum[1] = a[7]
    op_res.sum[2] = a[6]
    op_res.sum[3] = a[5]
    op_res.sum[4] = a[4]
    op_res.sum[5] = a[3]
    op_res.sum[6] = a[2]
    op_res.sum[7] = a[1]

    return op_res


####################################################
# ALU
####################################################

# op codes
# 000	ADD
# 001	SUB
# 010	AND
# 011	OR
# 100	XOR
# 101	NOT (on A)
# 110	SHL (A << 1)
# 111	SHR (A >> 1)


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


def alu8(a: list[int], b: list[int], op: list[int]) -> AluResult:
    op0: int = op[2]
    op1: int = op[1]
    op2: int = op[0]

    # operations
    add_res: OperationResult = add8(a, b)
    sub_res: OperationResult = sub8(a, b)

    and_res: list[int] = and8(a, b)
    or_res: list[int] = or8(a, b)
    xor_res: list[int] = xor8(a, b)
    not_res: list[int] = not8(a)

    shl_res: OperationResult = shl8(a)
    shr_res: OperationResult = shr8(a)

    # result selection
    g0: list[int] = mux8(add_res.sum, sub_res.sum, op0)
    g1: list[int] = mux8(and_res, or_res, op0)
    g2: list[int] = mux8(xor_res, not_res, op0)
    g3: list[int] = mux8(shl_res.sum, shr_res.sum, op0)

    g4: list[int] = mux8(g0, g1, op1)
    g5: list[int] = mux8(g2, g3, op1)

    result: list[int] = mux8(g4, g5, op2)

    # carry
    c0: int = mux(add_res.carry, sub_res.carry, op0)
    c1: int = 0  # no carry operation
    c2: int = 0  # no carry operation
    c3: int = mux(shl_res.carry, shr_res.carry, op0)

    c4: int = mux(c0, c1, op1)
    c5: int = mux(c2, c3, op1)

    carry: int = mux(c4, c5, op2)

    # zero
    zero: int = 1
    for i in range(7, -1, -1):
        zero = AND(zero, NOT(result[i]))

    # sign
    sign: int = result[0]

    # overflow
    a_msb: int = a[0]
    b_msb: int = b[0]
    r_msb: int = result[0]

    overflow_add: int = AND(NOT(XOR(a_msb, b_msb)), XOR(a_msb, r_msb))
    overflow_sub: int = AND(XOR(a_msb, b_msb), XOR(a_msb, r_msb))
    overflow: int = mux(overflow_add, overflow_sub, op0)

    return AluResult(
        result=result,
        flag=Flag(carry=carry, zero=zero, sign=sign, overflow=overflow),
    )


####################################################
# SR LATCH + D LATCH
####################################################

####################################################
# REGISTERS
####################################################


####################################################
# TESTING
####################################################
def bin_list_to_decimal(bits: list[int]) -> int:
    return int("".join(map(str, bits)), 2)


a = [0, 0, 0, 0, 0, 1, 0, 1]  # 5
b = [0, 0, 0, 0, 0, 0, 1, 1]  # 3
op = [0, 0, 0]  # ADD

res = alu8(a, b, op)
print(f"Binary: {res}")
print(f"Decimal: {bin_list_to_decimal(res.result)}")
