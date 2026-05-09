# NOTE: cpu from scratch using only nand gates. No shortcuts allowed
# NOTE: msb = a[0] and lsb = a[max_bits - 1]

from dataclasses import dataclass

MAX_BITS: int = 16
MAX_REGISTERS: int = 8


def validate_bit(a: int) -> None:
    assert a == 0 or a == 1


def validate_bit_arr(a: list[int]) -> None:
    assert len(a) == MAX_BITS

    for i in range(MAX_BITS):
        validate_bit(a[i])


def bits_to_int(bits: list[int]) -> int:
    result: int = 0
    count: int = 0
    for i in range(len(bits) - 1, -1, -1):
        result |= bits[i] << count
        count += 1

    return result


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


## sel - 2 bit
## 00 == a
## 01 == b
## 10 == c
## 11 == d
def mux4way16(
    a: list[int], b: list[int], c: list[int], d: list[int], sel: list[int]
) -> list[int]:
    validate_bit_arr(a)
    validate_bit_arr(b)
    validate_bit_arr(c)
    validate_bit_arr(d)
    assert len(sel) == 2
    for bit in sel:
        validate_bit(bit)

    r1: list[int] = mux16(a, b, sel[1])
    r2: list[int] = mux16(c, d, sel[1])

    return mux16(r1, r2, sel[0])


## sel - 3 bit
## 000 == a
## 001 == b
## 010 == c
## 011 == d
## 100 == e
## 101 == f
## 110 == g
## 111 == h
def mux8way16(
    a: list[int],
    b: list[int],
    c: list[int],
    d: list[int],
    e: list[int],
    f: list[int],
    g: list[int],
    h: list[int],
    sel: list[int],
) -> list[int]:
    validate_bit_arr(a)
    validate_bit_arr(b)
    validate_bit_arr(c)
    validate_bit_arr(d)
    validate_bit_arr(e)
    validate_bit_arr(f)
    validate_bit_arr(g)
    validate_bit_arr(h)
    assert len(sel) == 3
    for bit in sel:
        validate_bit(bit)

    r0: list[int] = mux4way16(a, b, c, d, [sel[1], sel[2]])
    r1: list[int] = mux4way16(e, f, g, h, [sel[1], sel[2]])

    return mux16(r0, r1, sel[0])


################################
#  DEMUX
###############################
@dataclass(slots=True)
class DemuxResult:
    a: int
    b: int


def demux(input_: int, sel: int) -> DemuxResult:
    validate_bit(input_)
    validate_bit(sel)

    a: int = and_(input_, not_(sel))
    b: int = and_(input_, sel)

    return DemuxResult(a=a, b=b)


@dataclass(slots=True)
class Demux4Result:
    a: int
    b: int
    c: int
    d: int


## sel - 2bit
## 00 == a
## 01 == b
## 10 == c
## 11 == d
def demux4way(input_: int, sel: list[int]) -> Demux4Result:
    validate_bit(input_)
    assert len(sel) == 2
    for bit in sel:
        validate_bit(bit)

    split: DemuxResult = demux(input_, sel[0])

    top: DemuxResult = demux(split.a, sel[1])
    bottom: DemuxResult = demux(split.b, sel[1])

    return Demux4Result(a=top.a, b=top.b, c=bottom.a, d=bottom.b)


@dataclass(slots=True)
class Demux8Result:
    a: int
    b: int
    c: int
    d: int
    e: int
    f: int
    g: int
    h: int


## sel - 3bit
## 000 == a
## 001 == b
## 010 == c
## 011 == d
## 100 == e
## 101 == f
## 110 == g
## 111 == h
def demux8way(input_: int, sel: list[int]) -> Demux8Result:
    validate_bit(input_)
    assert len(sel) == 3
    for bit in sel:
        validate_bit(bit)

    split: DemuxResult = demux(input_, sel[0])

    top: Demux4Result = demux4way(split.a, [sel[1], sel[2]])
    bottom: Demux4Result = demux4way(split.b, [sel[1], sel[2]])

    return Demux8Result(
        a=top.a,
        b=top.b,
        c=top.c,
        d=top.d,
        e=bottom.a,
        f=bottom.b,
        g=bottom.c,
        h=bottom.d,
    )


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


################################
#  REGISTERS
###############################
class Register16:
    def __init__(self) -> None:
        self.bits: list[DFlipFlop] = [DFlipFlop() for _ in range(MAX_BITS)]
        self.out: list[int] = [0] * MAX_BITS

    def update(self, data: list[int], load: int, clk: int) -> list[int]:
        validate_bit_arr(data)
        validate_bit(load)
        validate_bit(clk)

        # selection: current state vs new data
        d_in: list[int] = mux16(self.out, data, load)

        for i in range(MAX_BITS - 1, -1, -1):
            self.out[i] = self.bits[i].update(d_in[i], clk)

        return self.out


@dataclass(slots=True)
class RegisterFileResult:
    out_a: list[int]
    out_b: list[int]


# write_data: list[int] (The 16-bit data coming from the ALU or Memory)
# write_addr: list[int] (A 3-bit address telling us which register to write to)
# load: int (1 if we are writing, 0 if not)
# read_addr_a: list[int] (A 3-bit address for the first ALU input)
# read_addr_b: list[int] (A 3-bit address for the second ALU input)
# clk: int
class RegisterFile:
    def __init__(self) -> None:
        self.registers: list[Register16] = [Register16() for _ in range(MAX_REGISTERS)]

    def update(
        self,
        write_data: list[int],
        write_addr: list[int],
        load: int,
        read_addr_a: list[int],
        read_addr_b: list[int],
        clk: int,
    ) -> RegisterFileResult:

        validate_bit_arr(write_data)

        assert len(write_addr) == 3
        for bit in write_addr:
            validate_bit(bit)

        validate_bit(load)

        assert len(read_addr_a) == 3
        for bit in read_addr_a:
            validate_bit(bit)

        assert len(read_addr_b) == 3
        for bit in read_addr_b:
            validate_bit(bit)

        validate_bit(clk)

        load_signals: Demux8Result = demux8way(load, write_addr)
        loads: list[int] = [
            load_signals.a,
            load_signals.b,
            load_signals.c,
            load_signals.d,
            load_signals.e,
            load_signals.f,
            load_signals.g,
            load_signals.h,
        ]

        reg_outs: list[list[int]] = []
        for i in range(MAX_REGISTERS):
            out: list[int] = self.registers[i].update(write_data, loads[i], clk)
            reg_outs.append(out)

        out_a: list[int] = mux8way16(
            reg_outs[0],
            reg_outs[1],
            reg_outs[2],
            reg_outs[3],
            reg_outs[4],
            reg_outs[5],
            reg_outs[6],
            reg_outs[7],
            read_addr_a,
        )
        out_b: list[int] = mux8way16(
            reg_outs[0],
            reg_outs[1],
            reg_outs[2],
            reg_outs[3],
            reg_outs[4],
            reg_outs[5],
            reg_outs[6],
            reg_outs[7],
            read_addr_b,
        )

        return RegisterFileResult(out_a=out_a, out_b=out_b)


################################
#  PROGRAM COUNTER
###############################
class ProgramCounter:
    def __init__(self) -> None:
        self.register: Register16 = Register16()
        self.out: list[int] = [0] * MAX_BITS

    def update(
        self, data: list[int], load: int, increment: int, reset: int, clk: int
    ) -> list[int]:

        validate_bit_arr(data)
        validate_bit(load)
        validate_bit(increment)
        validate_bit(reset)
        validate_bit(clk)

        one16: list[int] = [0] * MAX_BITS
        one16[MAX_BITS - 1] = 1
        inc_val: list[int] = add16(self.out, one16).result

        # increment or hold
        w0: list[int] = mux16(self.out, inc_val, increment)

        # load new addr or pass w0
        w1: list[int] = mux16(w0, data, load)

        # reset to 0 or pass w1
        zero: list[int] = [0] * MAX_BITS
        next_val: list[int] = mux16(w1, zero, reset)

        # update internal register
        # external logic handles the hold state, so we hardcode the register's internal load to 1
        self.out = self.register.update(next_val, 1, clk)

        return self.out


################################
#  RAM
###############################
# addr = 3bits
class Ram8:
    def __init__(self) -> None:
        self.registers: list[Register16] = [Register16() for _ in range(MAX_REGISTERS)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
    ) -> list[int]:
        assert len(addr) == 3
        for bit in addr:
            validate_bit(bit)

        validate_bit_arr(data)
        validate_bit(load)
        validate_bit(clk)

        load_signals: Demux8Result = demux8way(load, addr)
        loads: list[int] = [
            load_signals.a,
            load_signals.b,
            load_signals.c,
            load_signals.d,
            load_signals.e,
            load_signals.f,
            load_signals.g,
            load_signals.h,
        ]

        reg_outs: list[list[int]] = []
        for i in range(MAX_REGISTERS):
            out: list[int] = self.registers[i].update(data, loads[i], clk)
            reg_outs.append(out)

        return mux8way16(
            reg_outs[0],
            reg_outs[1],
            reg_outs[2],
            reg_outs[3],
            reg_outs[4],
            reg_outs[5],
            reg_outs[6],
            reg_outs[7],
            addr,
        )


class Ram64:
    def __init__(self) -> None:
        self.rams: list[Ram8] = [Ram8() for _ in range(8)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
    ) -> list[int]:
        assert len(addr) == 6
        for bit in addr:
            validate_bit(bit)

        validate_bit_arr(data)
        validate_bit(load)
        validate_bit(clk)

        ram_sel: list[int] = addr[0:3]
        reg_sel: list[int] = addr[3:6]

        load_signals: Demux8Result = demux8way(load, ram_sel)
        loads: list[int] = [
            load_signals.a,
            load_signals.b,
            load_signals.c,
            load_signals.d,
            load_signals.e,
            load_signals.f,
            load_signals.g,
            load_signals.h,
        ]

        ram_outs: list[list[int]] = []
        for i in range(8):
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
            ram_outs.append(out)

        return mux8way16(
            ram_outs[0],
            ram_outs[1],
            ram_outs[2],
            ram_outs[3],
            ram_outs[4],
            ram_outs[5],
            ram_outs[6],
            ram_outs[7],
            ram_sel,
        )


# 9 bit addr
class Ram512:
    def __init__(self) -> None:
        self.rams: list[Ram64] = [Ram64() for _ in range(8)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
    ) -> list[int]:
        assert len(addr) == 9
        for bit in addr:
            validate_bit(bit)

        validate_bit_arr(data)
        validate_bit(load)
        validate_bit(clk)

        ram_sel: list[int] = addr[0:3]
        reg_sel: list[int] = addr[3:9]

        load_signals: Demux8Result = demux8way(load, ram_sel)
        loads: list[int] = [
            load_signals.a,
            load_signals.b,
            load_signals.c,
            load_signals.d,
            load_signals.e,
            load_signals.f,
            load_signals.g,
            load_signals.h,
        ]

        ram_outs: list[list[int]] = []
        for i in range(8):
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
            ram_outs.append(out)

        return mux8way16(
            ram_outs[0],
            ram_outs[1],
            ram_outs[2],
            ram_outs[3],
            ram_outs[4],
            ram_outs[5],
            ram_outs[6],
            ram_outs[7],
            ram_sel,
        )


# 12 bit addr
class Ram4K:
    def __init__(self) -> None:
        self.rams: list[Ram64] = [Ram64() for _ in range(8)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
    ) -> list[int]:
        assert len(addr) == 12
        for bit in addr:
            validate_bit(bit)

        validate_bit_arr(data)
        validate_bit(load)
        validate_bit(clk)

        ram_sel: list[int] = addr[0:3]
        reg_sel: list[int] = addr[3:12]

        load_signals: Demux8Result = demux8way(load, ram_sel)
        loads: list[int] = [
            load_signals.a,
            load_signals.b,
            load_signals.c,
            load_signals.d,
            load_signals.e,
            load_signals.f,
            load_signals.g,
            load_signals.h,
        ]

        ram_outs: list[list[int]] = []
        for i in range(8):
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
            ram_outs.append(out)

        return mux8way16(
            ram_outs[0],
            ram_outs[1],
            ram_outs[2],
            ram_outs[3],
            ram_outs[4],
            ram_outs[5],
            ram_outs[6],
            ram_outs[7],
            ram_sel,
        )


class Ram16K:
    def __init__(self) -> None:
        self.rams: list[Ram4K] = [Ram4K() for _ in range(4)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
    ) -> list[int]:
        assert len(addr) == 14
        for bit in addr:
            validate_bit(bit)

        validate_bit_arr(data)
        validate_bit(load)
        validate_bit(clk)

        ram_sel: list[int] = addr[0:2]  # 2 bits
        reg_sel: list[int] = addr[2:14]

        load_signals: Demux4Result = demux4way(load, ram_sel)
        loads: list[int] = [
            load_signals.a,
            load_signals.b,
            load_signals.c,
            load_signals.d,
        ]

        ram_outs: list[list[int]] = []
        for i in range(4):
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
            ram_outs.append(out)

        return mux4way16(
            ram_outs[0],
            ram_outs[1],
            ram_outs[2],
            ram_outs[3],
            ram_sel,
        )


################################
#  CONTROL UNIT
###############################
# The Bit Layout:
# [Opcode: 4 bits] [Dest Reg: 3 bits] [SrcA Reg: 3 bits] [SrcB Reg: 3 bits] [Unused: 3 bits]

#     Bits 12-15: Opcode (What are we doing?)

#     Bits 9-11: Destination Register (Where does the answer go?)

#     Bits 6-8: Source A Register (First input)

#     Bits 3-5: Source B Register (Second input)

#     Bits 0-8 (Alternative): Immediate Value. If we are loading a constant number (like SCORE = 0), we ignore the Source registers and just treat the bottom 9 bits as a raw number.
# opcodes
# Math Operations (MSB is 0)

#     0 000 - ADD

#     0 001 - SUB

#     0 010 - AND

#     0 011 - OR

#     0 100 - XOR

#     0 101 - NOT

#     0 110 - SHL

#     0 111 - SHR

# Memory & Control (MSB is 1)

#     1 000 - LDI (Load Immediate)

#     1 001 - LDR (Load from RAM)

#     1 010 - STR (Store to RAM)

#     1 011 - JMP (Jump)

#     1 100 - JEQ (Jump if Equal)

# (We still have 1101, 1110, and 1111 left over for future expansion!)


@dataclass(slots=True)
class ControlSignals:
    alu_op: list[int]  # 3 bits alu instruction
    reg_write: int  # load for register file
    mem_write: int  # load for main ram
    mem_to_reg: int  # data from alu(0) or ram(1)
    alu_src: int  # data from regb(0) or immediate(1)
    pc_load: int  # jump

    reg_dst_addr: list[int]
    reg_src_a_addr: list[int]
    reg_src_b_addr: list[int]
    immediate_val: list[int]


def decode_instruction(instruction: list[int], zero_flag: int) -> ControlSignals:
    validate_bit_arr(instruction)
    validate_bit(zero_flag)

    opcode: list[int] = instruction[12:16]  # 4bits
    reg_dest_addr: list[int] = instruction[9:12]
    reg_src_a_addr: list[int] = instruction[6:9]
    reg_src_b_addr: list[int] = instruction[3:6]

    # pad the rest with zeroes - except [0 : 9]
    immediate_val: list[int] = [0] * 7 + instruction[0:9]

    is_alu_op: int = not_(opcode[0])

    is_ldi: int = and_(
        and_(opcode[0], not_(opcode[1])), and_(not_(opcode[2]), not_(opcode[3]))
    )

    is_ldr: int = and_(
        and_(opcode[0], not_(opcode[1])), and_(not_(opcode[2]), opcode[3])
    )

    is_str: int = and_(
        and_(opcode[0], not_(opcode[1])), and_(opcode[2], not_(opcode[3]))
    )

    is_jmp: int = and_(and_(opcode[0], not_(opcode[1])), and_(opcode[2], opcode[3]))

    is_jeq: int = and_(
        and_(opcode[0], opcode[1]), and_(not_(opcode[2]), not_(opcode[3]))
    )

    alu_op: list[int] = [opcode[1], opcode[2], opcode[3]]

    # register write only on - alu_op, load immediate and load from ram
    reg_write: int = or_(is_alu_op, or_(is_ldi, is_ldr))
    mem_write: int = is_str
    # register file save - alu_output(0) or ram_output(1)
    mem_to_reg: int = is_ldr
    # alu second input - reg_b(0) or immediate_value(1)
    alu_src: int = is_ldi

    # new pc addr - on jmp, or if jeq and zero both 1
    pc_load: int = or_(is_jmp, and_(is_jeq, zero_flag))

    return ControlSignals(
        alu_op=alu_op,
        reg_write=reg_write,
        mem_write=mem_write,
        mem_to_reg=mem_to_reg,
        alu_src=alu_src,
        pc_load=pc_load,
        reg_dst_addr=reg_dest_addr,
        reg_src_a_addr=reg_src_a_addr,
        reg_src_b_addr=reg_src_b_addr,
        immediate_val=immediate_val,
    )


@dataclass(slots=True)
class CPUResult:
    out_m: list[int]  # 16bit data we want to write in main ram
    write_m: int  # load pin for main ram
    address_m: list[int]  # 16bit addr for main ram
    pc_out: list[int]  # 16bit addr for instruction rom


class CPU:
    def __init__(self) -> None:
        self.pc: ProgramCounter = ProgramCounter()
        self.registers: RegisterFile = RegisterFile()

        # 1bit dflipflop to hold zero_flag from prev clock cycle for jeq(jump if equal) in current cycle
        self.zero_flag_ff: DFlipFlop = DFlipFlop()
        self.current_zero: int = 0

    def update(
        self, instruction: list[int], in_m: list[int], reset: int, clk: int
    ) -> CPUResult:
        validate_bit_arr(instruction)
        validate_bit_arr(in_m)
        validate_bit(reset)
        validate_bit(clk)

        ## combinational flow - wire routing

        # 1. decode
        ctrl: ControlSignals = decode_instruction(instruction, self.current_zero)

        # 2. read current registers
        # since registerfile.update does both read and write at the same time.
        # "dummy read" with clk=0 to avoid accidentally overwriting data
        zero16: list[int] = [0] * MAX_BITS
        reg_read: RegisterFileResult = self.registers.update(
            write_data=zero16,
            write_addr=ctrl.reg_dst_addr,
            load=0,
            read_addr_a=ctrl.reg_src_a_addr,
            read_addr_b=ctrl.reg_src_b_addr,
            clk=0,
        )

        # 3. route alu input b - reg_b(0) or immediate_val(1)
        alu_in_b: list[int] = mux16(reg_read.out_b, ctrl.immediate_val, ctrl.alu_src)

        # 4. execute alu
        alu_out: AluResult = alu16(reg_read.out_a, alu_in_b, ctrl.alu_op)

        # 5. route register write data - alu answer (0) or data from main ram(1)
        reg_write_data: list[int] = mux16(alu_out.result, in_m, ctrl.mem_to_reg)

        ## sequential flow (clock edge)

        # 6. write to register file
        reg_read = self.registers.update(
            write_data=reg_write_data,
            write_addr=ctrl.reg_dst_addr,
            load=ctrl.reg_write,
            read_addr_a=ctrl.reg_src_a_addr,
            read_addr_b=ctrl.reg_src_b_addr,
            clk=clk,
        )

        # 7. update status register
        self.current_zero = self.zero_flag_ff.update(alu_out.flag.zero, clk)

        # 8. update pc - if not jumping(pc_load = 0), then increment
        pc_inc: int = not_(ctrl.pc_load)

        next_pc: list[int] = self.pc.update(
            data=reg_read.out_a,  # jmp always go to the addr reg A
            load=ctrl.pc_load,
            increment=pc_inc,
            reset=reset,
            clk=clk,
        )

        return CPUResult(
            out_m=reg_read.out_b,  # data to store in ram - reg b
            write_m=ctrl.mem_write,
            address_m=reg_read.out_a,  # ram addr comes from reg A
            pc_out=next_pc,  # next instruction
        )


################################
#  COMPUTER
###############################
class Computer:
    def __init__(self, program_rom: list[list[int]]) -> None:
        self.cpu: CPU = CPU()
        self.ram: Ram64 = Ram64()

        self.rom: list[list[int]] = program_rom

        self.reset: int = 0
        self.clock_state: int = 0

    def tick(self) -> None:
        pc_addr: int = bits_to_int(self.cpu.pc.out)
        instruction: list[int]
        if pc_addr < len(self.rom):
            instruction = self.rom[pc_addr]
        else:
            instruction = [0] * 16

        # dummy read
        current_ram_out: list[int] = self.ram.update(
            data=[0] * 16,
            addr=self.cpu.registers.registers[0].out[10:16],  # part of reg A output
            load=0,
            clk=0,
        )

        self.clock_state = 1

        cpu_out: CPUResult = self.cpu.update(
            instruction=instruction,
            in_m=current_ram_out,
            reset=self.reset,
            clk=self.clock_state,
        )

        self.ram.update(
            data=cpu_out.out_m,
            addr=cpu_out.address_m[10:16],  # sliced to 6bits
            load=cpu_out.write_m,
            clk=self.clock_state,
        )

        self.clock_state = 0
