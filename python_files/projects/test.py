from dataclasses import dataclass

MAX_REGISTERS: int = 8
MAX_BITS: int = 16


# LOGIC GATES
def nand_(a: int, b: int) -> int:
    return 1 if a == 0 or b == 0 else 0


def not_(a: int) -> int:
    return nand_(a, a)


def and_(a: int, b: int) -> int:
    return not_(nand_(a, b))


def or_(a: int, b: int) -> int:
    return nand_(not_(a), not_(b))


def nor_(a: int, b: int) -> int:
    return not_(or_(a, b))


def xor_(a: int, b: int) -> int:
    return or_(and_(not_(a), b), and_(a, not_(b)))


def xnor_(a: int, b: int) -> int:
    return not_(xor_(a, b))


# ADDERS
@dataclass(slots=True)
class AddResult:
    sum: int
    carry: int


def half_adder(a: int, b: int) -> AddResult:
    sum: int = xor_(a, b)
    carry: int = and_(a, b)

    return AddResult(sum, carry)


def full_adder(a: int, b: int, cin: int) -> AddResult:
    r0: AddResult = half_adder(a, b)
    r1: AddResult = half_adder(r0.sum, cin)

    return AddResult(sum=r1.sum, carry=or_(r0.carry, r1.carry))


# MUXes
def mux(a: int, b: int, sel: int) -> int:
    return or_(and_(a, not_(sel)), and_(b, sel))


def mux16(a: list[int], b: list[int], sel: int) -> list[int]:
    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = mux(a[i], b[i], sel)

    return result


# sel = 2bits
def mux4way16(
    a: list[int], b: list[int], c: list[int], d: list[int], sel: list[int]
) -> list[int]:

    sel0: int = sel[1]
    sel1: int = sel[0]

    ab: list[int] = mux16(a, b, sel0)
    cd: list[int] = mux16(c, d, sel0)

    return mux16(ab, cd, sel1)


# sel = 3bits
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

    sel0: int = sel[2]
    sel1: int = sel[1]
    sel2: int = sel[0]

    ab: list[int] = mux16(a, b, sel0)
    cd: list[int] = mux16(c, d, sel0)
    ef: list[int] = mux16(e, f, sel0)
    gh: list[int] = mux16(g, h, sel0)

    abcd: list[int] = mux16(ab, cd, sel1)
    efgh: list[int] = mux16(ef, gh, sel1)

    return mux16(abcd, efgh, sel2)


# DMUXes
@dataclass(slots=True)
class DmuxResult:
    a: int
    b: int


def dmux(in_: int, sel: int) -> DmuxResult:
    a: int = and_(in_, not_(sel))
    b: int = and_(in_, sel)

    return DmuxResult(a, b)


@dataclass(slots=True)
class Dmux4Result:
    a: int
    b: int
    c: int
    d: int


# sel = 2bits
def dmux4way(in_: int, sel: list[int]) -> Dmux4Result:
    sel0: int = sel[1]
    sel1: int = sel[0]

    split: DmuxResult = dmux(in_, sel1)

    top: DmuxResult = dmux(split.a, sel0)
    bottom: DmuxResult = dmux(split.b, sel0)

    return Dmux4Result(top.a, top.b, bottom.a, bottom.b)


@dataclass(slots=True)
class Dmux8Result:
    a: int
    b: int
    c: int
    d: int
    e: int
    f: int
    g: int
    h: int


# sel = 2bits
def dmux8way(in_: int, sel: list[int]) -> Dmux8Result:
    sel0: int = sel[2]
    sel1: int = sel[1]
    sel2: int = sel[0]

    split: DmuxResult = dmux(in_, sel2)

    top: Dmux4Result = dmux4way(split.a, [sel1, sel0])
    bottom: Dmux4Result = dmux4way(split.b, [sel1, sel0])

    return Dmux8Result(
        top.a, top.b, top.c, top.d, bottom.a, bottom.b, bottom.c, bottom.d
    )


# BASIC OPERATIONS
def and16(a: list[int], b: list[int]) -> list[int]:
    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = and_(a[i], b[i])

    return result


def or16(a: list[int], b: list[int]) -> list[int]:
    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = or_(a[i], b[i])

    return result


def xor16(a: list[int], b: list[int]) -> list[int]:
    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = xor_(a[i], b[i])

    return result


def not16(a: list[int]) -> list[int]:
    result: list[int] = [0] * MAX_BITS

    for i in range(MAX_BITS - 1, -1, -1):
        result[i] = not_(a[i])

    return result


@dataclass(slots=True)
class OperationResult:
    result: list[int]
    carry: int


def add16(a: list[int], b: list[int]) -> OperationResult:
    result: list[int] = [0] * MAX_BITS
    carry: int = 0

    for i in range(MAX_BITS - 1, -1, -1):
        r: AddResult = full_adder(a[i], b[i], carry)

        result[i] = r.sum
        carry = r.carry

    return OperationResult(result, carry)


def sub16(a: list[int], b: list[int]) -> OperationResult:
    result: list[int] = [0] * MAX_BITS
    carry: int = 1  # for 2's complement

    for i in range(MAX_BITS - 1, -1, -1):
        r: AddResult = full_adder(a[i], not_(b[i]), carry)

        result[i] = r.sum
        carry = r.carry

    return OperationResult(result, carry)


def shl16(a: list[int]) -> OperationResult:
    result: list[int] = [0] * MAX_BITS
    carry: int = a[0]

    for i in range(MAX_BITS - 1):
        result[i] = a[i + 1]

    result[MAX_BITS - 1] = 0

    return OperationResult(result, carry)


def shr16(a: list[int]) -> OperationResult:
    result: list[int] = [0] * MAX_BITS
    carry: int = a[15]

    result[0] = 0
    for i in range(MAX_BITS - 1):
        result[i + 1] = a[i]

    return OperationResult(result, carry)


# ALU
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


# opcode = 3bits, op_order = add, sub, and, or, xor, not, shl, shr
def alu16(a: list[int], b: list[int], op: list[int]) -> AluResult:
    op0: int = op[2]
    op1: int = op[1]
    op2: int = op[0]

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

    # carry selection
    c0: int = mux(add_res.carry, sub_res.carry, op0)
    c1: int = 0
    c2: int = 0
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

    overflow_add: int = and_(xnor_(msb_a, msb_b), xor_(msb_a, msb_r))
    overflow_sub: int = and_(xor_(msb_a, msb_b), xor_(msb_a, msb_r))
    overflow: int = mux(overflow_add, overflow_sub, op0)

    is_arith: int = and_(not_(op2), not_(op0))
    overflow = and_(is_arith, overflow)

    return AluResult(result, Flag(carry, zero, sign, overflow))


# LATCHES + FLIPFLOPS
class DLatch:
    def __init__(self) -> None:
        self.q: int = 0
        self.q_bar: int = not_(self.q)

    def update(self, data: int, enable: int) -> int:
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
        master_q: int = self.master.update(data, clk)
        slave_q: int = self.slave.update(master_q, not_(clk))

        return slave_q


# REGISTERS
class Register16:
    def __init__(self) -> None:
        self.bits: list[DFlipFlop] = [DFlipFlop() for _ in range(MAX_BITS)]
        self.out: list[int] = [0] * MAX_BITS

    def update(self, data: list[int], load: int, clk: int) -> list[int]:
        d_in: list[int] = mux16(self.out, data, load)

        for i in range(MAX_BITS):
            self.out[i] = self.bits[i].update(d_in[i], clk)

        return self.out


@dataclass(slots=True)
class RegisterFileResult:
    out_a: list[int]
    out_b: list[int]


class RegisterFile:
    def __init__(self) -> None:
        self.registers: list[Register16] = [Register16() for _ in range(MAX_REGISTERS)]

    def update(
        self,
        data: list[int],
        addr: list[int],
        load: int,
        read_addr_a: list[int],
        read_addr_b: list[int],
        clk: int,
    ) -> RegisterFileResult:

        load_signals: Dmux8Result = dmux8way(load, addr)
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

        return RegisterFileResult(out_a, out_b)


# RAMS
class Ram8:
    def __init__(self) -> None:
        self.registers: list[Register16] = [Register16() for _ in range(MAX_REGISTERS)]

    def update(
        self,
        data: list[int],
        addr: list[int],
        load: int,
        clk: int,
    ) -> list[int]:

        load_signals: Dmux8Result = dmux8way(load, addr)
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


# addr = 6bits
class Ram64:
    def __init__(self) -> None:
        self.rams: list[Ram8] = [Ram8() for _ in range(MAX_REGISTERS)]

    def update(
        self,
        data: list[int],
        addr: list[int],
        load: int,
        clk: int,
    ) -> list[int]:

        ram_sel: list[int] = addr[0:3]
        reg_sel: list[int] = addr[3:]

        load_signals: Dmux8Result = dmux8way(load, ram_sel)
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
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
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
            ram_sel,
        )


# addr = 9bits
class Ram512:
    def __init__(self) -> None:
        self.rams: list[Ram64] = [Ram64() for _ in range(MAX_REGISTERS)]

    def update(
        self,
        data: list[int],
        addr: list[int],
        load: int,
        clk: int,
    ) -> list[int]:

        ram_sel: list[int] = addr[0:3]
        reg_sel: list[int] = addr[3:]

        load_signals: Dmux8Result = dmux8way(load, ram_sel)
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
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
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
            ram_sel,
        )


# addr = 12bits
class Ram4k:
    def __init__(self) -> None:
        self.rams: list[Ram512] = [Ram512() for _ in range(MAX_REGISTERS)]

    def update(
        self,
        data: list[int],
        addr: list[int],
        load: int,
        clk: int,
    ) -> list[int]:

        ram_sel: list[int] = addr[0:3]
        reg_sel: list[int] = addr[3:]

        load_signals: Dmux8Result = dmux8way(load, ram_sel)
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
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
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
            ram_sel,
        )


# addr = 14bits
class Ram16k:
    def __init__(self) -> None:
        self.rams: list[Ram4k] = [Ram4k() for _ in range(4)]

    def update(
        self,
        data: list[int],
        addr: list[int],
        load: int,
        clk: int,
    ) -> list[int]:

        ram_sel: list[int] = addr[0:2]
        reg_sel: list[int] = addr[2:]

        load_signals: Dmux4Result = dmux4way(load, ram_sel)
        loads: list[int] = [
            load_signals.a,
            load_signals.b,
            load_signals.c,
            load_signals.d,
        ]

        reg_outs: list[list[int]] = []
        for i in range(4):
            out: list[int] = self.rams[i].update(data, reg_sel, loads[i], clk)
            reg_outs.append(out)

        return mux4way16(
            reg_outs[0],
            reg_outs[1],
            reg_outs[2],
            reg_outs[3],
            ram_sel,
        )


# PROGRAM COUNTER
class ProgramCounter:
    def __init__(self) -> None:
        self.register: Register16 = Register16()
        self.out: list[int] = [0] * MAX_BITS

    def update(
        self, data: list[int], inc: int, load: int, reset: int, clk: int
    ) -> list[int]:

        one16: list[int] = ([0] * (MAX_BITS - 1)) + [1]
        inc_val: list[int] = add16(self.out, one16).result

        r0: list[int] = mux16(self.out, inc_val, inc)
        r1: list[int] = mux16(r0, data, load)
        zero16: list[int] = [0] * MAX_BITS
        r2: list[int] = mux16(r1, zero16, reset)

        # loading is already handled above so 1 for load
        self.out = self.register.update(r2, 1, clk)

        return self.out


# CONTROL UNIT
@dataclass(slots=True)
class ControlSignals:
    alu_op: list[int]
    reg_write: int
    mem_write: int
    mem_to_reg: int
    alu_src: int
    pc_load: int

    reg_dest: list[int]
    reg_src_a: list[int]
    reg_src_b: list[int]
    immediate_val: list[int]


def decode_instruction(instruction: list[int], zero_flag: int) -> ControlSignals:
    opcode: list[int] = instruction[12:]
    reg_dest: list[int] = instruction[9:12]
    reg_src_a: list[int] = instruction[6:9]
    reg_src_b: list[int] = instruction[3:9]
    immediate_val: list[int] = [0] * 7 + instruction[7:]

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
    reg_write: int = or_(is_alu_op, or_(is_ldi, is_ldr))
    mem_write: int = is_str
    mem_to_reg: int = is_ldr
    alu_src: int = is_ldi
    pc_load: int = or_(is_jmp, and_(zero_flag, is_jeq))

    return ControlSignals(
        alu_op,
        reg_write,
        mem_write,
        mem_to_reg,
        alu_src,
        pc_load,
        reg_dest,
        reg_src_a,
        reg_src_b,
        immediate_val,
    )


# CPU
@dataclass(slots=True)
class CpuResults:
    out_m: list[int]
    address_m: list[int]
