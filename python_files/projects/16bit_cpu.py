# NOTE: cpu from scratch using only nand gates. No shortcuts allowed
# NOTE: msb = a[0] and lsb = a[max_bits - 1]

from dataclasses import dataclass

MAX_BITS: int = 16


def validate_bit(a: int) -> None:
    assert a == 0 or a == 1


def validate_bit_arr(a: list[int]) -> None:
    assert len(a) == MAX_BITS

    for i in range(MAX_BITS):
        validate_bit(a[i])


################################
#  LOGIC GATES
###############################


def nand_(a: int, b: int) -> int:
    validate_bit(a)
    validate_bit(b)

    return 1 if (a == 0 or b == 0) else 0


def not_(a: int) -> int:
    validate_bit(a)

    return nand_(a, a)


def and_(a: int, b: int) -> int:
    validate_bit(a)
    validate_bit(b)

    return not_(nand_(a, b))


def or_(a: int, b: int) -> int:
    validate_bit(a)
    validate_bit(b)

    return nand_(not_(a), not_(b))


def nor_(a: int, b: int) -> int:
    validate_bit(a)
    validate_bit(b)

    return not_(or_(a, b))


def xor_(a: int, b: int) -> int:
    validate_bit(a)
    validate_bit(b)

    return or_(and_(not_(a), b), and_(a, not_(b)))


def xnor_(a: int, b: int) -> int:
    validate_bit(a)
    validate_bit(b)

    return not_(xor_(a, b))


################################
#  ADDERS
###############################
@dataclass(slots=True)
class AddResult:
    sum: int
    carry: int


def half_adder(a: int, b: int) -> AddResult:
    validate_bit(a)
    validate_bit(b)

    sum: int = xor_(a, b)
    carry: int = and_(a, b)

    return AddResult(sum=sum, carry=carry)


def full_adder(a: int, b: int, cin: int) -> AddResult:
    validate_bit(a)
    validate_bit(b)
    validate_bit(cin)

    r1: AddResult = half_adder(a, b)
    r2: AddResult = half_adder(r1.sum, cin)

    return AddResult(sum=r2.sum, carry=or_(r1.carry, r2.carry))


################################
#  MUX
###############################
def mux(a: int, b: int, sel: int) -> int:
    validate_bit(a)
    validate_bit(b)
    validate_bit(sel)

    return or_(and_(a, not_(sel)), and_(b, sel))


def mux16(a: list[int], b: list[int], sel: int) -> list[int]:
    validate_bit(sel)
    validate_bit_arr(a)
    validate_bit_arr(b)

    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = mux(a[i], b[i], sel)

    return result


################################
#  BASIC OPERATIONS
###############################
def not16(a: list[int]) -> list[int]:
    validate_bit_arr(a)

    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = not_(a[i])

    return result


def and16(a: list[int], b: list[int]) -> list[int]:
    validate_bit_arr(a)
    validate_bit_arr(b)

    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = and_(a[i], b[i])

    return result


def or16(a: list[int], b: list[int]) -> list[int]:
    validate_bit_arr(a)
    validate_bit_arr(b)

    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = or_(a[i], b[i])

    return result


def xor16(a: list[int], b: list[int]) -> list[int]:
    validate_bit_arr(a)
    validate_bit_arr(b)

    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = xor_(a[i], b[i])

    return result


@dataclass(slots=True)
class OperationResult:
    result: list[int]
    carry: int


def add16(a: list[int], b: list[int]) -> OperationResult:
    validate_bit_arr(a)
    validate_bit_arr(b)

    result: list[int] = [0] * MAX_BITS
    carry: int = 0

    for i in range(MAX_BITS - 1, -1, -1):
        r: AddResult = full_adder(a[i], b[i], carry)

        result[i] = r.sum
        carry = r.carry

    return OperationResult(result=result, carry=carry)


def sub16(a: list[int], b: list[int]) -> OperationResult:
    validate_bit_arr(a)
    validate_bit_arr(b)

    result: list[int] = [0] * MAX_BITS
    carry: int = 1

    for i in range(MAX_BITS - 1, -1, -1):
        r: AddResult = full_adder(a[i], not_(b[i]), carry)

        result[i] = r.sum
        carry = r.carry

    return OperationResult(result=result, carry=carry)


def shl16(a: list[int]) -> OperationResult:
    validate_bit_arr(a)

    result: list[int] = [0] * MAX_BITS
    carry: int = a[0]

    for i in range(MAX_BITS - 1):
        result[i] = a[i + 1]

    result[MAX_BITS - 1] = 0

    return OperationResult(result=result, carry=carry)


def shr16(a: list[int]) -> OperationResult:
    validate_bit_arr(a)

    result: list[int] = [0] * MAX_BITS
    carry: int = a[MAX_BITS - 1]

    result[0] = 0
    for i in range(MAX_BITS - 1):
        result[i + 1] = a[i]

    return OperationResult(result=result, carry=carry)


################################
#  ALU
###############################
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


## OP CODES
# 000 ADD
# 001 SUB
# 010 AND
# 011 OR
# 100 XOR
# 101 NOT
# 110 SHL
# 111 SHR
def alu16(a: list[int], b: list[int], op: list[int]) -> AluResult:
    validate_bit_arr(a)
    validate_bit_arr(b)

    for bit in op:
        validate_bit(bit)

    op0: int = op[len(op) - 1]
    op1: int = op[len(op) - 2]
    op2: int = op[len(op) - 3]

    # basic operations
    add_res: OperationResult = add16(a, b)
    sub_res: OperationResult = sub16(a, b)

    and_res: list[int] = and16(a, b)
    or_res: list[int] = or16(a, b)
    xor_res: list[int] = xor16(a, b)
    not_res: list[int] = not16(a)

    shl_res: OperationResult = shl16(a)
    shr_res: OperationResult = shr16(a)

    # result selection
    r0: list[int] = mux16(add_res.result, sub_res.result, op0)
    r1: list[int] = mux16(and_res, or_res, op0)
    r2: list[int] = mux16(xor_res, not_res, op0)
    r3: list[int] = mux16(shl_res.result, shr_res.result, op0)

    r4: list[int] = mux16(r0, r1, op1)
    r5: list[int] = mux16(r2, r3, op1)

    result: list[int] = mux16(r4, r5, op2)

    # carry seletection
    c0: int = mux(add_res.carry, sub_res.carry, op0)
    c1: int = 0  # no carry operation
    c2: int = 0  # no carry operation
    c3: int = mux(shl_res.carry, shr_res.carry, op0)

    c4: int = mux(c0, c1, op1)
    c5: int = mux(c2, c3, op1)

    carry: int = mux(c4, c5, op2)

    # zero
    zero: int = 1
    for i in range(MAX_BITS - 1, -1, -1):
        zero = and_(zero, not_(result[i]))

    # sign
    sign: int = result[0]

    # overflow
    msb_a: int = a[0]
    msb_b: int = b[0]
    msb_r: int = result[0]

    # same sign addition, different sign result
    overflow_add: int = and_(xnor_(msb_a, msb_b), xor_(msb_a, msb_r))

    # different sign sub, different sign result
    overflow_sub: int = and_(xor_(msb_a, msb_b), xor_(msb_a, msb_r))

    overflow: int = mux(overflow_add, overflow_sub, op0)

    is_arith: int = and_(not_(op2), not_(op1))
    overflow = and_(is_arith, overflow)

    return AluResult(
        result=result, flag=Flag(carry=carry, zero=zero, sign=sign, overflow=overflow)
    )


################################
#  LATCH
###############################
class DLatch:
    def __init__(self) -> None:
        self.q: int = 0
        self.q_bar: int = not_(self.q)

    def update(self, data: int, enable: int) -> int:
        validate_bit(data)
        validate_bit(enable)

        s: int = nand_(data, enable)
        r: int = nand_(not_(data), enable)

        for _ in range(2):
            self.q = nand_(s, self.q_bar)
            self.q_bar = nand_(r, self.q)

        return self.q


class DFlipFlop:
    def __init__(self) -> None:
        self.master: DLatch = DLatch()
        self.slave: DLatch = DLatch()

    def update(self, data: int, clk: int) -> int:
        validate_bit(data)
        validate_bit(clk)

        master_q: int = self.master.update(data, clk)
        slave_q: int = self.slave.update(master_q, not_(clk))

        return slave_q
