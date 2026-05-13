# NOTE: num = msb -> lsb, msb = num[0] and lsb = num[15]
#
from dataclasses import dataclass

MAX_BITS: int = 16
MAX_REGISTERS: int = 8


def bits_to_int(bits: list[int]) -> int:
    result: int = 0

    count: int = 0
    for i in range(len(bits) - 1, -1, -1):
        result |= bits[i] << count
        count += 1

    return result


def decimal_to_bits(num: int) -> list[int]:
    out: list[int] = []
    temp: int = num

    while temp > 0:
        out.append(temp % 2)
        temp //= 2

    out.reverse()
    return out


# LOGIC GATES
def nand_(a: int, b: int) -> int:
    return 1 if (a == 0 or b == 0) else 0


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
    r1: AddResult = half_adder(a, b)
    r2: AddResult = half_adder(r1.sum, cin)

    return AddResult(r2.sum, or_(r1.carry, r2.carry))


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


# sel = 3bits
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
    carry: int = 1

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

    result[15] = 0

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


# opcode = 3bits
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
    msb_r: int = sign

    overflow_add: int = and_(xnor_(msb_a, msb_b), xor_(msb_a, msb_r))
    overflow_sub: int = and_(xor_(msb_a, msb_b), xor_(msb_a, msb_r))
    overflow: int = mux(overflow_add, overflow_sub, op0)

    is_arith: int = and_(not_(op2), not_(op1))
    overflow = and_(is_arith, overflow)

    return AluResult(result, Flag(carry, zero, sign, overflow))


# Latches and flip flops
class Dlatch:
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
        self.master: Dlatch = Dlatch()
        self.slave: Dlatch = Dlatch()

    def update(self, data: int, clk: int) -> int:
        master_q: int = self.master.update(data, not_(clk))
        slave_q: int = self.slave.update(master_q, clk)

        return slave_q


# registers
class Register16:
    def __init__(self) -> None:
        self.bits: list[DFlipFlop] = [DFlipFlop() for _ in range(MAX_BITS)]
        self.out: list[int] = [0] * MAX_BITS

    def update(self, data: list[int], load: int, clk: int) -> list[int]:
        d_in: list[int] = mux16(self.out, data, load)

        new_out: list[int] = [0] * MAX_BITS
        for i in range(MAX_BITS - 1, -1, -1):
            new_out[i] = self.bits[i].update(d_in[i], clk)

        if clk:
            self.out = new_out

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
        write_data: list[int],
        write_addr: list[int],
        load: int,
        read_addr_a: list[int],
        read_addr_b: list[int],
        clk: int,
    ) -> RegisterFileResult:
        load_signals: Dmux8Result = dmux8way(load, write_addr)
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

        return RegisterFileResult(out_a, out_b)


# RAMS
class Ram8:
    def __init__(self) -> None:
        self.registers: list[Register16] = [Register16() for _ in range(MAX_REGISTERS)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
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


# 6bit addr
class Ram64:
    def __init__(self) -> None:
        self.rams: list[Ram8] = [Ram8() for _ in range(MAX_REGISTERS)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
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


# 9bit addr
class Ram512:
    def __init__(self) -> None:
        self.rams: list[Ram64] = [Ram64() for _ in range(MAX_REGISTERS)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
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


# 12bit addr
class Ram4k:
    def __init__(self) -> None:
        self.rams: list[Ram512] = [Ram512() for _ in range(MAX_REGISTERS)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
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


# 14bit addr
class Ram16k:
    def __init__(self) -> None:
        self.rams: list[Ram4k] = [Ram4k() for _ in range(4)]

    def update(
        self, data: list[int], addr: list[int], load: int, clk: int
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


# control unit
@dataclass(slots=True)
class ControlSignals:
    alu_opcode: list[int]
    reg_write: int
    mem_write: int
    mem2reg: int
    alu_src: int
    pc_load: int

    reg_dst: list[int]
    reg_src_a: list[int]
    reg_src_b: list[int]
    immediate: list[int]


def decode_instruction(instruction: list[int], zero_flag: int) -> ControlSignals:
    opcode: list[int] = instruction[0:4]
    reg_dst: list[int] = instruction[4:7]
    reg_src_a: list[int] = instruction[7:10]
    reg_src_b: list[int] = instruction[10:13]
    immediate: list[int] = [0] * 7 + instruction[7:16]

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

    alu_opcode: list[int] = [opcode[1], opcode[2], opcode[3]]
    reg_write: int = or_(is_alu_op, or_(is_ldi, is_ldr))
    mem_write: int = is_str
    mem2reg: int = is_ldr
    alu_src: int = is_ldi
    pc_load: int = or_(is_jmp, and_(zero_flag, is_jeq))

    return ControlSignals(
        alu_opcode,
        reg_write,
        mem_write,
        mem2reg,
        alu_src,
        pc_load,
        reg_dst,
        reg_src_a,
        reg_src_b,
        immediate,
    )


# program counter
class ProgramCounter:
    def __init__(self) -> None:
        self.register: Register16 = Register16()
        self.out: list[int] = [0] * MAX_BITS

    def update(
        self, data: list[int], inc: int, load: int, reset: int, clk: int
    ) -> list[int]:
        one16: list[int] = [0] * (MAX_BITS - 1) + [1]
        inc_val: list[int] = add16(self.out, one16).result

        r0: list[int] = mux16(self.out, inc_val, inc)
        r1: list[int] = mux16(r0, data, load)

        zero16: list[int] = [0] * MAX_BITS
        r2: list[int] = mux16(r1, zero16, reset)

        new_out: list[int] = self.register.update(r2, 1, clk)

        if clk:
            self.out = new_out

        return self.out


# cpu
@dataclass(slots=True)
class CpuResult:
    out_m: list[int]
    write_m: int
    addr_m: list[int]
    pc_out: list[int]


class Cpu:
    def __init__(self) -> None:
        self.pc: ProgramCounter = ProgramCounter()
        self.registers: RegisterFile = RegisterFile()

        self.current_zero: int = 0
        self.zero_flag_dff: DFlipFlop = DFlipFlop()

    def update(
        self, instruction: list[int], in_m: list[int], reset: int, clk: int
    ) -> CpuResult:
        ctrl: ControlSignals = decode_instruction(instruction, self.current_zero)

        reg_out_a: list[int] = self.registers.registers[bits_to_int(ctrl.reg_src_a)].out
        reg_out_b: list[int] = self.registers.registers[bits_to_int(ctrl.reg_src_b)].out

        alu_in_b: list[int] = mux16(reg_out_b, ctrl.immediate, ctrl.alu_src)
        alu_out: AluResult = alu16(reg_out_a, alu_in_b, ctrl.alu_opcode)

        reg_write_data: list[int] = mux16(alu_out.result, in_m, ctrl.mem2reg)

        self.registers.update(
            reg_write_data,
            ctrl.reg_dst,
            ctrl.reg_write,
            ctrl.reg_src_a,
            ctrl.reg_src_b,
            clk,
        )

        self.current_zero = self.zero_flag_dff.update(alu_out.flag.zero, clk)

        pc_inc: int = not_(ctrl.pc_load)
        pc_next: list[int] = self.pc.update(reg_out_b, pc_inc, ctrl.pc_load, reset, clk)

        return CpuResult(reg_out_b, ctrl.mem_write, reg_out_a, pc_next)


# computer


class Computer:
    def __init__(self, rom: list[list[int]]) -> None:
        self.cpu: Cpu = Cpu()
        self.ram: Ram16k = Ram16k()

        self.rom: list[list[int]] = rom
        self.reset: int = 0
        self.clock_state: int = 0

    def tick(self) -> None:
        pc_addr: int = bits_to_int(self.cpu.pc.out)
        instruction: list[int]
        if pc_addr < len(self.rom):
            instruction = self.rom[pc_addr]
        else:
            instruction = [0] * MAX_BITS

        current_ram_out: list[int] = self.ram.update(
            [0] * MAX_BITS, self.cpu.registers.registers[0].out[2:16], 0, 0
        )
        self.clock_state = 0
        self.cpu.update(instruction, current_ram_out, self.reset, self.clock_state)

        self.clock_state = 1

        cpu_out: CpuResult = self.cpu.update(
            instruction, current_ram_out, self.reset, self.clock_state
        )

        self.ram.update(
            cpu_out.out_m, cpu_out.addr_m, cpu_out.write_m, self.clock_state
        )


opcode_dict: dict[str, list[int]] = {
    "ADD": [0, 0, 0, 0],
    "SUB": [0, 0, 0, 1],
    "AND": [0, 0, 1, 0],
    "OR": [0, 0, 1, 1],
    "XOR": [0, 1, 0, 0],
    "NOT": [0, 1, 0, 1],
    "SHL": [0, 1, 1, 0],
    "SHR": [0, 1, 1, 1],
    "LDI": [1, 0, 0, 0],
    "LDR": [1, 0, 0, 1],
    "STR": [1, 0, 1, 0],
    "JMP": [1, 0, 1, 1],
    "JEQ": [1, 1, 0, 0],
}

register_dict: dict[str, list[int]] = {
    "R0": [0, 0, 0],
    "R1": [0, 0, 1],
    "R2": [0, 1, 0],
    "R3": [0, 1, 1],
    "R4": [1, 0, 0],
    "R5": [1, 0, 1],
    "R6": [1, 1, 0],
    "R7": [1, 1, 1],
}


def decode_rom(rom: list[str]) -> list[list[int]]:
    out: list[list[int]] = []

    for inst in rom:
        instruction: list[str] = inst.replace(",", "").split()
        temp: list[int] = []

        temp += opcode_dict[instruction[0]]

        if instruction[0] == "LDI":
            temp += register_dict[instruction[1]]

            # pad with 0 from reg to decimal num
            dec_bits: list[int] = decimal_to_bits(int(instruction[2]))
            temp += [0] * (16 - (len(temp) + len(dec_bits)))
            temp += dec_bits
        else:
            for inst in instruction[1:]:
                temp += register_dict[inst]

            # pad the rest with 0 till 16bits
            temp += [0] * (16 - len(temp))

        out.append(temp)

    return out


# compiled program

str_rom: list[str] = ["LDI R1, 5", "LDI R2, 3", "ADD R3, R1, R2"]
# str_rom = ["LDI R1, 5", "ADD R1, R1, R1"]  # R1 = R1 + R1, expect 10
my_game_rom: list[list[int]] = decode_rom(str_rom)

# Plug in the game cartridge and turn on the power!
my_computer = Computer(rom=my_game_rom)

# Run the computer for 3 clock cycles
print("Booting up...")
for cycle in range(3):
    my_computer.tick()

# Let's check Register 3!
r3_binary = my_computer.cpu.registers.registers[3].out
print(f"Result in R3: {r3_binary} (Decimal: {bits_to_int(r3_binary)})")
