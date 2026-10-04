# NOTE: 8bit nand gate up cpu
# NOTE: msb = num[size-1]
# NOTE: lsb = num[0]

from dataclasses import dataclass
from typing import Final

BIT = int
WORD = list[int]

MAX_BITS: int = 8


def validate_bit(bit: BIT) -> None:
    assert bit == 0 or bit == 1


def validate_word(word: WORD, intended_size: int) -> None:
    assert len(word) == intended_size

    for bit in word:
        validate_bit(bit)


# LOGIC GATES
def nand_gate(a: BIT, b: BIT) -> BIT:
    validate_bit(a)
    validate_bit(b)

    return 0 if (a == 1 and b == 1) else 1


def not_gate(a: BIT) -> BIT:
    validate_bit(a)

    return nand_gate(a, a)


def and_gate(a: BIT, b: BIT) -> BIT:
    validate_bit(a)
    validate_bit(b)

    return not_gate(nand_gate(a, b))


def or_gate(a: BIT, b: BIT) -> BIT:
    validate_bit(a)
    validate_bit(b)

    return nand_gate(not_gate(a), not_gate(b))


def xor_gate(a: BIT, b: BIT) -> BIT:
    validate_bit(a)
    validate_bit(b)

    return or_gate(and_gate(not_gate(a), b), and_gate(a, not_gate(b)))


# ADDERS
@dataclass(slots=True)
class AdderResult:
    sum: BIT
    cout: BIT


def half_adder(a: BIT, b: BIT) -> AdderResult:
    validate_bit(a)
    validate_bit(b)

    sum: int = xor_gate(a, b)
    cout: int = and_gate(a, b)
    return AdderResult(sum, cout)


def full_adder(a: BIT, b: BIT, cin: BIT) -> AdderResult:
    validate_bit(a)
    validate_bit(b)
    validate_bit(cin)

    r1: AdderResult = half_adder(a, b)
    r2: AdderResult = half_adder(r1.sum, cin)
    return AdderResult(sum=r2.sum, cout=or_gate(r1.cout, r2.cout))


# MUXES
@dataclass(slots=True)
class Mux2x1Input:
    a: BIT
    b: BIT


def mux_2x1(sel: BIT, data: Mux2x1Input) -> BIT:
    validate_bit(sel)
    validate_bit(data.a)
    validate_bit(data.b)

    return or_gate(and_gate(not_gate(sel), data.a), and_gate(sel, data.b))


@dataclass(slots=True)
class Mux4x1Input:
    a: BIT
    b: BIT
    c: BIT
    d: BIT


# sel = 2bits
def mux_4x1(sel: WORD, data: Mux4x1Input) -> BIT:
    validate_word(sel, 2)
    validate_bit(data.a)
    validate_bit(data.b)
    validate_bit(data.c)
    validate_bit(data.d)

    r1: BIT = mux_2x1(sel[0], Mux2x1Input(data.a, data.b))
    r2: BIT = mux_2x1(sel[0], Mux2x1Input(data.c, data.d))
    return mux_2x1(sel[1], Mux2x1Input(r1, r2))


@dataclass(slots=True)
class Mux8x1Input:
    a: BIT
    b: BIT
    c: BIT
    d: BIT
    e: BIT
    f: BIT
    g: BIT
    h: BIT


# sel = 3bits
def mux_8x1(sel: WORD, data: Mux8x1Input) -> BIT:
    validate_word(sel, 3)
    validate_bit(data.a)
    validate_bit(data.b)
    validate_bit(data.c)
    validate_bit(data.d)
    validate_bit(data.e)
    validate_bit(data.f)
    validate_bit(data.g)
    validate_bit(data.h)

    r1: BIT = mux_4x1([sel[0], sel[1]], Mux4x1Input(data.a, data.b, data.c, data.d))
    r2: BIT = mux_4x1([sel[0], sel[1]], Mux4x1Input(data.e, data.f, data.g, data.h))
    return mux_2x1(sel[2], Mux2x1Input(r1, r2))


# DEMUXES
@dataclass(slots=True)
class Dmux1x2Output:
    a: BIT
    b: BIT


def dmux_1x2(sel: BIT, data: BIT) -> Dmux1x2Output:
    validate_bit(sel)
    validate_bit(data)

    a: BIT = and_gate(not_gate(sel), data)
    b: BIT = and_gate(sel, data)
    return Dmux1x2Output(a, b)


@dataclass(slots=True)
class Dmux1x4Output:
    a: BIT
    b: BIT
    c: BIT
    d: BIT


# sel = 2bits
def dmux_1x4(sel: WORD, data: BIT) -> Dmux1x4Output:
    validate_word(sel, 2)
    validate_bit(data)

    r1: Dmux1x2Output = dmux_1x2(sel[1], data)
    r2: Dmux1x2Output = dmux_1x2(sel[0], r1.a)
    r3: Dmux1x2Output = dmux_1x2(sel[0], r1.b)
    return Dmux1x4Output(r2.a, r2.b, r3.a, r3.b)


@dataclass(slots=True)
class Dmux1x8Output:
    a: BIT
    b: BIT
    c: BIT
    d: BIT
    e: BIT
    f: BIT
    g: BIT
    h: BIT


# sel = 3bits
def dmux_1x8(sel: WORD, data: BIT) -> Dmux1x8Output:
    validate_word(sel, 3)
    validate_bit(data)

    r1: Dmux1x2Output = dmux_1x2(sel[2], data)
    r2: Dmux1x4Output = dmux_1x4([sel[0], sel[1]], r1.a)
    r3: Dmux1x4Output = dmux_1x4([sel[0], sel[1]], r1.b)
    return Dmux1x8Output(r2.a, r2.b, r2.c, r2.d, r3.a, r3.b, r3.c, r3.d)


# BASIC OPERATIONS
@dataclass(slots=True)
class OperationResult:
    result: WORD
    cout: BIT


def add8(a: WORD, b: WORD) -> OperationResult:
    validate_word(a, MAX_BITS)
    validate_word(b, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    cout: BIT = 0
    for i in range(MAX_BITS):
        temp_res: AdderResult = full_adder(a[i], b[i], cout)
        result[i] = temp_res.sum
        cout = temp_res.cout

    return OperationResult(result, cout)


def sub8(a: WORD, b: WORD) -> OperationResult:
    validate_word(a, MAX_BITS)
    validate_word(b, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    cout: BIT = 1
    for i in range(MAX_BITS):
        temp_res: AdderResult = full_adder(a[i], not_gate(b[i]), cout)
        result[i] = temp_res.sum
        cout = temp_res.cout

    return OperationResult(result, cout)


def and8(a: WORD, b: WORD) -> WORD:
    validate_word(a, MAX_BITS)
    validate_word(b, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    for i in range(MAX_BITS):
        result[i] = and_gate(a[i], b[i])

    return result


def or8(a: WORD, b: WORD) -> WORD:
    validate_word(a, MAX_BITS)
    validate_word(b, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    for i in range(MAX_BITS):
        result[i] = or_gate(a[i], b[i])

    return result


def xor8(a: WORD, b: WORD) -> WORD:
    validate_word(a, MAX_BITS)
    validate_word(b, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    for i in range(MAX_BITS):
        result[i] = xor_gate(a[i], b[i])

    return result


def not8(a: WORD) -> WORD:
    validate_word(a, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    for i in range(MAX_BITS):
        result[i] = not_gate(a[i])

    return result


def shl8(a: WORD) -> OperationResult:
    validate_word(a, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    cout: BIT = a[MAX_BITS - 1]
    for i in range(1, MAX_BITS):
        result[i] = a[i - 1]

    result[0] = 0

    return OperationResult(result, cout)


def shr8(a: WORD) -> OperationResult:
    validate_word(a, MAX_BITS)

    result: WORD = [0] * MAX_BITS
    cout: BIT = a[0]
    for i in range(MAX_BITS - 1):
        result[i] = a[i + 1]

    result[MAX_BITS - 1] = 0

    return OperationResult(result, cout)


# ALU
@dataclass(slots=True)
class Flag:
    cout: BIT
    sign: BIT
    zero: BIT
    overflow: BIT


@dataclass(slots=True)
class AluResult:
    result: WORD
    flag: Flag


# opcode = 3bits
# 000 = ADD
# 001 = SUB
# 010 = AND
# 011 = OR
# 100 = XOR
# 101 = NOT
# 110 = SHL (logical)
# 111 = SHR (logical)
def alu8(opcode: WORD, a: WORD, b: WORD) -> AluResult:
    validate_word(opcode, 3)
    validate_word(a, MAX_BITS)
    validate_word(b, MAX_BITS)

    # basic operations
    add_result: OperationResult = add8(a, b)
    sub_result: OperationResult = sub8(a, b)
    and_result: WORD = and8(a, b)
    or_result: WORD = or8(a, b)
    xor_result: WORD = xor8(a, b)
    not_result: WORD = not8(a)
    shl_result: OperationResult = shl8(a)
    shr_result: OperationResult = shr8(a)

    # result calculation
    result: WORD = [0] * MAX_BITS
    for i in range(MAX_BITS):
        result[i] = mux_8x1(
            opcode,
            Mux8x1Input(
                add_result.result[i],
                sub_result.result[i],
                and_result[i],
                or_result[i],
                xor_result[i],
                not_result[i],
                shl_result.result[i],
                shr_result.result[i],
            ),
        )

    # carry calculation
    cout: BIT = mux_8x1(
        opcode,
        Mux8x1Input(
            add_result.cout,
            sub_result.cout,
            0,  # no carry op
            0,  # no carry op
            0,  # no carry op
            0,  # no carry op
            shl_result.cout,
            shr_result.cout,
        ),
    )

    # sign
    sign: BIT = result[MAX_BITS - 1]

    # zero calculation
    zero: BIT = 1
    for i in range(MAX_BITS):
        zero = and_gate(zero, not_gate(result[i]))

    # overlfow calculation
    msb_a: BIT = a[MAX_BITS - 1]
    msb_b: BIT = b[MAX_BITS - 1]
    msb_r: BIT = result[MAX_BITS - 1]

    overflow_add: BIT = and_gate(
        not_gate(xor_gate(msb_a, msb_b)), xor_gate(msb_a, msb_r)
    )
    overflow_sub: BIT = and_gate(xor_gate(msb_a, msb_b), xor_gate(msb_a, msb_r))

    overflow_selected: BIT = mux_2x1(opcode[0], Mux2x1Input(overflow_add, overflow_sub))

    is_arith: BIT = and_gate(not_gate(opcode[2]), not_gate(opcode[1]))

    overflow: BIT = and_gate(is_arith, overflow_selected)

    return AluResult(result, Flag(cout, sign, zero, overflow))


# LATCHES AND FLIPFLOPS
class DLatch:
    def __init__(self) -> None:
        self.q: BIT = 0
        self.q_bar: BIT = not_gate(self.q)

    def update(self, data: BIT, enable: BIT) -> None:
        validate_bit(data)
        validate_bit(enable)

        set_bar: BIT = nand_gate(data, enable)
        reset_bar: BIT = nand_gate(not_gate(data), enable)

        for _ in range(2):
            self.q = nand_gate(set_bar, self.q_bar)
            self.q_bar = nand_gate(reset_bar, self.q)


class DFlipFlop:
    def __init__(self) -> None:
        self.master: DLatch = DLatch()
        self.slave: DLatch = DLatch()

    def update(self, data: BIT, clk: BIT) -> None:
        validate_bit(data)
        validate_bit(clk)

        self.master.update(data, not_gate(clk))
        self.slave.update(self.master.q, clk)


# REGISTERS + RAMS
class Register8:
    def __init__(self) -> None:
        self.reg: list[DFlipFlop] = [DFlipFlop() for _ in range(MAX_BITS)]

    def read(self) -> WORD:
        return [dff.slave.q for dff in self.reg]

    def write(self, data: WORD, load: BIT, clk: BIT) -> None:
        validate_word(data, MAX_BITS)
        validate_bit(load)
        validate_bit(clk)

        current: WORD = self.read()

        for i in range(MAX_BITS):
            next_bit: int = mux_2x1(load, Mux2x1Input(current[i], data[i]))

            self.reg[i].update(next_bit, clk)


class Ram8:
    def __init__(self) -> None:
        self.rams: list[Register8] = [Register8() for _ in range(MAX_BITS)]

    # addr 3bits
    def read(self, addr: WORD) -> WORD:
        validate_word(addr, 3)

        rams: list[WORD] = [ram.read() for ram in self.rams]
        result: WORD = [0] * MAX_BITS

        for i in range(MAX_BITS):
            result[i] = mux_8x1(
                addr,
                Mux8x1Input(
                    rams[0][i],
                    rams[1][i],
                    rams[2][i],
                    rams[3][i],
                    rams[4][i],
                    rams[5][i],
                    rams[6][i],
                    rams[7][i],
                ),
            )

        return result

    # addr = 3bits
    def write(self, addr: WORD, data: WORD, load: BIT, clk: BIT) -> None:
        validate_word(addr, 3)
        validate_word(data, MAX_BITS)
        validate_bit(load)
        validate_bit(clk)

        load_signals: Dmux1x8Output = dmux_1x8(addr, load)
        self.rams[0].write(data, load_signals.a, clk)
        self.rams[1].write(data, load_signals.b, clk)
        self.rams[2].write(data, load_signals.c, clk)
        self.rams[3].write(data, load_signals.d, clk)
        self.rams[4].write(data, load_signals.e, clk)
        self.rams[5].write(data, load_signals.f, clk)
        self.rams[6].write(data, load_signals.g, clk)
        self.rams[7].write(data, load_signals.h, clk)


class Ram64:
    def __init__(self) -> None:
        self.rams: list[Ram8] = [Ram8() for _ in range(MAX_BITS)]

    # addr = 6bits
    def read(self, addr: WORD) -> WORD:
        validate_word(addr, 6)

        rams: list[WORD] = [ram.read([addr[0], addr[1], addr[2]]) for ram in self.rams]
        result: WORD = [0] * MAX_BITS

        for i in range(MAX_BITS):
            result[i] = mux_8x1(
                [addr[3], addr[4], addr[5]],
                Mux8x1Input(
                    rams[0][i],
                    rams[1][i],
                    rams[2][i],
                    rams[3][i],
                    rams[4][i],
                    rams[5][i],
                    rams[6][i],
                    rams[7][i],
                ),
            )

        return result

    # addr = 6bits
    def write(self, addr: WORD, data: WORD, load: BIT, clk: BIT) -> None:
        validate_word(data, MAX_BITS)
        validate_word(addr, 6)
        validate_bit(load)
        validate_bit(clk)

        top_addr: WORD = [addr[3], addr[4], addr[5]]
        bottom_addr: WORD = [addr[0], addr[1], addr[2]]

        load_signals: Dmux1x8Output = dmux_1x8(top_addr, load)
        self.rams[0].write(bottom_addr, data, load_signals.a, clk)
        self.rams[1].write(bottom_addr, data, load_signals.b, clk)
        self.rams[2].write(bottom_addr, data, load_signals.c, clk)
        self.rams[3].write(bottom_addr, data, load_signals.d, clk)
        self.rams[4].write(bottom_addr, data, load_signals.e, clk)
        self.rams[5].write(bottom_addr, data, load_signals.f, clk)
        self.rams[6].write(bottom_addr, data, load_signals.g, clk)
        self.rams[7].write(bottom_addr, data, load_signals.h, clk)


class Ram256:
    def __init__(self) -> None:
        self.rams: list[Ram64] = [Ram64() for _ in range(4)]

    # addr = 8bits
    def read(self, addr: WORD) -> WORD:
        validate_word(addr, 8)

        rams: list[WORD] = [
            ram.read(
                [
                    addr[0],
                    addr[1],
                    addr[2],
                    addr[3],
                    addr[4],
                    addr[5],
                ]
            )
            for ram in self.rams
        ]
        result: WORD = [0] * MAX_BITS

        for i in range(MAX_BITS):
            result[i] = mux_4x1(
                [addr[6], addr[7]],
                Mux4x1Input(
                    rams[0][i],
                    rams[1][i],
                    rams[2][i],
                    rams[3][i],
                ),
            )

        return result

    # addr = 8bits
    def write(self, addr: WORD, data: WORD, load: BIT, clk: BIT) -> None:
        validate_word(addr, 8)
        validate_word(data, MAX_BITS)
        validate_bit(load)
        validate_bit(clk)

        top_addr: WORD = [addr[6], addr[7]]
        bottom_addr: WORD = [addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]]

        load_signals: Dmux1x4Output = dmux_1x4(top_addr, load)
        self.rams[0].write(bottom_addr, data, load_signals.a, clk)
        self.rams[1].write(bottom_addr, data, load_signals.b, clk)
        self.rams[2].write(bottom_addr, data, load_signals.c, clk)
        self.rams[3].write(bottom_addr, data, load_signals.d, clk)


class ProgramCounter:
    def __init__(self) -> None:
        self.reg: Register8 = Register8()

    def read(self) -> WORD:
        return self.reg.read()

    def write(self, data: WORD, inc: BIT, load: BIT, reset: BIT, clk: BIT) -> None:
        validate_word(data, MAX_BITS)
        validate_bit(inc)
        validate_bit(load)
        validate_bit(reset)
        validate_bit(clk)

        current: WORD = self.reg.read()
        zero: WORD = [0] * MAX_BITS
        one: WORD = [1] + [0] * (MAX_BITS - 1)
        incremented: WORD = add8(current, one).result

        next_value: WORD = [0] * MAX_BITS

        for i in range(MAX_BITS):
            next_value[i] = mux_2x1(inc, Mux2x1Input(current[i], incremented[i]))
            next_value[i] = mux_2x1(load, Mux2x1Input(next_value[i], data[i]))
            next_value[i] = mux_2x1(reset, Mux2x1Input(next_value[i], zero[i]))

        pc_load: BIT = or_gate(inc, or_gate(load, reset))

        self.reg.write(next_value, pc_load, clk)


# CONTROL SIGNALS + INSTRUCTION DECODER
@dataclass(slots=True)
class ControlSignals:
    pc_inc: BIT
    pc_load: BIT
    pc_reset: BIT

    ram_load: BIT  # ram enable bit for ram256

    alu_op: WORD  # alu opcode = 3bits
    imm: WORD  # immediate value

    reg_a_load: BIT  # reg A write enable
    reg_b_load: BIT  # reg B write enable

    mux_a_src_imm: BIT  # load imm to reg A
    mux_a_src_alu: BIT  # load alu result to reg A
    mux_b_src: BIT  #
    mux_a_src_b: BIT  # load reg A from reg B


# instruction = 8bits
# if instruction[msb] == 0: alu_operation; else: memory and control;
#
# instruction[7:4] [3:0]
# LDI A, n	1000 nnnn	Load 4-bit immediate n into Reg A
# LDA [n]	1001 nnnn	Load RAM address n into Reg A
# STA [n]	1010 nnnn	Store Reg A into RAM address n
# MOV A, B	1011 xxxx	Copy Reg B into Reg A
# MOV B, A	1100 xxxx	Copy Reg A into Reg B
# JMP n	    1101 nnnn	Jump to instruction at address n
# JZ n	    1110 nnnn	Jump to n IF ALU Zero flag == 1
# HLT	    1111 xxxx	Halt CPU (Stop PC from incrementing)
#
def instruction_decoder(instruction: WORD, alu_flag: Flag) -> ControlSignals:
    validate_word(instruction, MAX_BITS)

    is_ctrl: BIT = instruction[MAX_BITS - 1]
    is_alu: BIT = not_gate(is_ctrl)

    op0: BIT = instruction[4]
    op1: BIT = instruction[5]
    op2: BIT = instruction[6]

    # control instructions
    c_000: BIT = and_gate(not_gate(op2), and_gate(not_gate(op1), not_gate(op0)))
    c_001: BIT = and_gate(not_gate(op2), and_gate(not_gate(op1), op0))
    c_010: BIT = and_gate(not_gate(op2), and_gate(op1, not_gate(op0)))
    c_011: BIT = and_gate(not_gate(op2), and_gate(op1, op0))
    c_100: BIT = and_gate(op2, and_gate(not_gate(op1), not_gate(op0)))
    c_101: BIT = and_gate(op2, and_gate(not_gate(op1), op0))
    c_110: BIT = and_gate(op2, and_gate(op1, not_gate(op0)))
    c_111: BIT = and_gate(op2, and_gate(op1, op0))

    is_ldi: BIT = and_gate(is_ctrl, c_000)
    is_lda: BIT = and_gate(is_ctrl, c_001)
    is_sta: BIT = and_gate(is_ctrl, c_010)
    is_mov_ab: BIT = and_gate(is_ctrl, c_011)
    is_mov_ba: BIT = and_gate(is_ctrl, c_100)
    is_jmp: BIT = and_gate(is_ctrl, c_101)
    is_jz: BIT = and_gate(is_ctrl, c_110)
    is_hlt: BIT = and_gate(is_ctrl, c_111)

    # generate control signals
    do_jz: BIT = and_gate(is_jz, alu_flag.zero)  # jump if alu_flag.zero
    pc_load: BIT = or_gate(do_jz, is_jmp)  # based on jump

    # inc if not jumping and not halting
    pc_inc: BIT = not_gate(or_gate(pc_load, is_hlt))

    pc_reset: BIT = 0  # default = 0, reset externally

    ram_load: BIT = is_sta

    alu_op: WORD = [op0, op1, op2]
    imm: WORD = [
        instruction[0],
        instruction[1],
        instruction[2],
        instruction[3],
        0,
        0,
        0,
        0,
    ]

    reg_a_load: BIT = or_gate(or_gate(is_alu, is_mov_ab), or_gate(is_ldi, is_lda))
    reg_b_load: BIT = is_mov_ba

    mux_a_src_imm: BIT = is_ldi
    mux_a_src_alu: BIT = is_alu
    mux_b_src: BIT = 0
    mux_a_src_b: BIT = is_mov_ab

    return ControlSignals(
        pc_inc,
        pc_load,
        pc_reset,
        ram_load,
        alu_op,
        imm,
        reg_a_load,
        reg_b_load,
        mux_a_src_imm,
        mux_a_src_alu,
        mux_b_src,
        mux_a_src_b,
    )


class Cpu8:
    def __init__(self) -> None:
        self.regA: Register8 = Register8()
        self.regB: Register8 = Register8()
        self.ram: Ram256 = Ram256()
        self.pc: ProgramCounter = ProgramCounter()

    def tick(self, reset: BIT, clk: BIT) -> None:
        validate_bit(reset)
        validate_bit(clk)

        pc_val: WORD = self.pc.read()
        instruction: WORD = self.ram.read(pc_val)

        temp_ctrl: ControlSignals = instruction_decoder(instruction, Flag(0, 0, 0, 0))

        val_a: WORD = self.regA.read()
        val_b: WORD = self.regB.read()

        alu_result: AluResult = alu8(temp_ctrl.alu_op, val_a, val_b)

        ctrl: ControlSignals = instruction_decoder(instruction, alu_result.flag)

        # data memory read (for lda instrction, address is immediate)
        ram_data: WORD = self.ram.read(ctrl.imm)

        reg_a_in: WORD = [0] * MAX_BITS
        for i in range(MAX_BITS):
            w1: BIT = mux_2x1(ctrl.mux_a_src_imm, Mux2x1Input(ram_data[i], ctrl.imm[i]))
            w2: BIT = mux_2x1(ctrl.mux_a_src_alu, Mux2x1Input(w1, alu_result.result[i]))
            reg_a_in[i] = mux_2x1(ctrl.mux_a_src_b, Mux2x1Input(w2, val_b[i]))

        reg_b_in: WORD = [0] * MAX_BITS
        for i in range(MAX_BITS):
            reg_b_in[i] = mux_2x1(ctrl.mux_b_src, Mux2x1Input(val_a[i], 0))

        final_reset: BIT = or_gate(ctrl.pc_reset, reset)

        self.regA.write(reg_a_in, ctrl.reg_a_load, clk)
        self.regB.write(reg_b_in, ctrl.reg_b_load, clk)
        self.ram.write(ctrl.imm, val_a, ctrl.ram_load, clk)
        self.pc.write(ctrl.imm, ctrl.pc_inc, ctrl.pc_load, final_reset, clk)


# CONTROL INSTRUCTIONS
LDI: Final[BIT] = 0x80
LDA: Final[BIT] = 0x90
STA: Final[BIT] = 0xA0
MOV_AB: Final[BIT] = 0xB0
MOV_BA: Final[BIT] = 0xC0
JMP: Final[BIT] = 0xD0
JZ: Final[BIT] = 0xE0
HLT: Final[BIT] = 0xF0


# HELPER FUNCTIONS
def bits8(value: int) -> list[int]:
    return [(value >> i) & 1 for i in range(8)]


def program(*values: int) -> list[list[int]]:
    return [bits8(value) for value in values]


def load_program(cpu: Cpu8, instructions: list[list[int]]) -> None:
    for address, instruction in enumerate(instructions):
        cpu.ram.write(
            bits8(address),
            instruction,
            load=1,
            clk=0,
        )
        cpu.ram.write(
            bits8(address),
            instruction,
            load=1,
            clk=1,
        )


def run_cpu(
    cpu: Cpu8,
    cycles: int,
    reset: int = 0,
) -> None:
    for _ in range(cycles):
        cpu.tick(reset=reset, clk=0)
        cpu.tick(reset=reset, clk=1)


def word_to_int(word: list[int]) -> int:
    return sum(bit << i for i, bit in enumerate(word))


# TESTS
test_ldi: list[WORD] = program(
    LDI | 0x05,  # ldi a, 5
    HLT,  # HALT
)

test_mov_ba = program(
    LDI | 0x07,  # A = 7
    MOV_BA,  # B = A
    HLT,
)

test_mov_ab = program(
    LDI | 0x03,  # A = 3
    MOV_BA,  # B = 3
    LDI | 0x09,  # A = 9
    MOV_AB,  # A = B = 3
    HLT,
)

test_add = program(
    LDI | 0x05,  # A = 5
    MOV_BA,  # B = 5
    LDI | 0x03,  # A = 3
    # A = A + B
    0x00,  # ADD
    HLT,
)

test_alu = program(
    LDI | 0x0F,  # A = 15
    MOV_BA,  # B = 15
    0x00,  # ADD: A = 30
    0x10,  # SUB: A = 15
    0x20,  # AND: A = 15
    0x30,  # OR : A = 15
    0x40,  # XOR: A = 0
    0x50,  # NOT: A = 255
    0x60,  # SHL: A = 254
    0x70,  # SHR: A = 127
    HLT,
)

test_ram = program(
    # 1. Build the value 42 (15 + 15 + 12)
    LDI | 15,  # A = 15
    MOV_BA,  # B = 15
    LDI | 15,  # A = 15
    0x00,  # ADD: A = A + B (30)
    MOV_BA,  # B = 30
    LDI | 12,  # A = 12
    0x00,  # ADD: A = A + B (42)
    # 2. Execute your RAM test
    STA | 10,  # RAM[10] = A (Stores 42)
    LDI | 0,  # A = 0
    LDA | 10,  # A = RAM[10] (Loads 42)
    HLT,
)

test_jmp = program(
    LDI | 1,  # 0: A = 1
    JMP | 4,  # 1: jump to instruction 4
    LDI | 99,  # 2: should NOT execute
    LDI | 99,  # 3: should NOT execute
    LDI | 7,  # 4: A = 7
    HLT,  # 5
)

test_jz = program(
    LDI | 5,  # 0: A = 5
    MOV_BA,  # 1: B = 5
    0x10,  # 2: SUB: A = A - B = 0 (Opcode 001)
    JZ | 6,  # 3: jump because ALU zero flag is 1
    LDI | 15,  # 4: should be skipped (using valid 4-bit immediate)
    HLT,  # 5: skipped
    LDI | 7,  # 6: A = 7
    HLT,  # 7: Halt
)

test_jz_not_taken = program(
    LDI | 5,  # A = 5
    MOV_BA,  # B = 5
    LDI | 3,  # A = 3
    0x01,  # A = 3 - 5 = 254, zero = 0
    JZ | 7,  # should NOT jump
    LDI | 9,  # A = 9
    HLT,
)


# MAIN
def main() -> None:
    cpu: Cpu8 = Cpu8()

    load_program(cpu, test_jz)

    # Reset CPU.
    cpu.tick(reset=1, clk=0)
    cpu.tick(reset=1, clk=1)

    # Run.
    run_cpu(cpu, cycles=20)

    print("A =", word_to_int(cpu.regA.read()))
    print("B =", word_to_int(cpu.regB.read()))
    print("PC =", word_to_int(cpu.pc.read()))


if __name__ == "__main__":
    main()
