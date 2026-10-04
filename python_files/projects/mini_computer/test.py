from dataclasses import dataclass


# LOGIC GATES
def nand_gate(a: int, b: int) -> int:
    return 1 if (a == 1 and b == 1) else 0


def not_gate(a: int) -> int:
    return nand_gate(a, a)


def and_gate(a: int, b: int) -> int:
    return not_gate(nand_gate(a, b))


def or_gate(a: int, b: int) -> int:
    return nand_gate(not_gate(a), not_gate(b))


def xor_gate(a: int, b: int) -> int:
    return or_gate(and_gate(not_gate(a), b), and_gate(a, not_gate(b)))


# ADDERS
@dataclass(slots=True)
class AdderResult:
    sum: int
    cout: int


def half_adder(a: int, b: int) -> AdderResult:
    sum: int = xor_gate(a, b)
    cout: int = and_gate(a, b)
    return AdderResult(sum, cout)


def full_adder(a: int, b: int, cin: int) -> AdderResult:
    r1: AdderResult = half_adder(a, b)
    r2: AdderResult = half_adder(r1.sum, cin)
    return AdderResult(sum=r2.sum, cout=or_gate(r1.cout, r2.cout))


# Muxes
@dataclass(slots=True)
class Mux2x1Input:
    a: int
    b: int


def mux_2x1(sel: int, data: Mux2x1Input) -> int:
    return or_gate(and_gate(not_gate(sel), data.a), and_gate(sel, data.b))


@dataclass(slots=True)
class Mux4x1Input:
    a: int
    b: int
    c: int
    d: int


# sel = 2bits
def mux_4x1(sel: list[int], data: Mux4x1Input) -> int:
    r1: int = mux_2x1(sel[0], Mux2x1Input(data.a, data.b))
    r2: int = mux_2x1(sel[0], Mux2x1Input(data.c, data.d))
    return mux_2x1(sel[1], Mux2x1Input(r1, r2))


@dataclass(slots=True)
class Mux8x1Input:
    a: int
    b: int
    c: int
    d: int
    e: int
    f: int
    g: int
    h: int


# sel = 3bits
def mux_8x1(sel: list[int], data: Mux8x1Input) -> int:
    r1: int = mux_4x1([sel[0], sel[1]], Mux4x1Input(data.a, data.b, data.c, data.d))
    r2: int = mux_4x1([sel[0], sel[1]], Mux4x1Input(data.e, data.f, data.g, data.h))
    return mux_2x1(sel[2], Mux2x1Input(r1, r2))


# DMUXES
@dataclass(slots=True)
class Dmux1x2Output:
    a: int
    b: int


def dmux_1x2(sel: int, data: int) -> Dmux1x2Output:
    a: int = and_gate(not_gate(sel), data)
    b: int = and_gate(sel, data)
    return Dmux1x2Output(a, b)


@dataclass(slots=True)
class Dmux1x4Output:
    a: int
    b: int
    c: int
    d: int


# sel = 2bits
def dmux_1x4(sel: list[int], data: int) -> Dmux1x4Output:
    r1: Dmux1x2Output = dmux_1x2(sel[1], data)
    r2: Dmux1x2Output = dmux_1x2(sel[0], r1.a)
    r3: Dmux1x2Output = dmux_1x2(sel[0], r1.b)
    return Dmux1x4Output(r2.a, r2.b, r3.a, r3.b)


@dataclass(slots=True)
class Dmux1x8Output:
    a: int
    b: int
    c: int
    d: int
    e: int
    f: int
    g: int
    h: int


# sel = 3bits
def dmux_1x8(sel: list[int], data: int) -> Dmux1x8Output:
    r1: Dmux1x2Output = dmux_1x2(sel[2], data)
    r2: Dmux1x4Output = dmux_1x4([sel[0], sel[1]], r1.a)
    r3: Dmux1x4Output = dmux_1x4([sel[0], sel[1]], r1.b)
    return Dmux1x8Output(r2.a, r2.b, r2.c, r2.d, r3.a, r3.b, r3.c, r3.d)


# LACHES + DFLIPFLOPS
class DLatch:
    def __init__(self) -> None:
        self.q: int = 0
        self.q_bar: int = not_gate(self.q)

    def update(self, data: int, enable: int) -> None:
        set_bar: int = nand_gate(data, enable)
        reset_bar: int = nand_gate(not_gate(data), enable)

        for _ in range(2):
            self.q = nand_gate(set_bar, self.q_bar)
            self.q_bar = nand_gate(reset_bar, self.q)


class DFlipFlop:
    def __init__(self) -> None:
        self.master: DLatch = DLatch()
        self.slave: DLatch = DLatch()

    def update(self, data: int, clk: int) -> None:
        self.master.update(data, not_gate(clk))
        self.slave.update(self.master.q, clk)


# REGISTERS + RAMS
class Register8:
    def __init__(self) -> None:
        self.bits: list[DFlipFlop] = [DFlipFlop() for _ in range(8)]

    def read(self) -> list[int]:
        return [bit.slave.q for bit in self.bits]

    def write(self, data: list[int], load: int, clk: int) -> None:
        current: list[int] = [bit.slave.q for bit in self.bits]

        for i in range(8):
            next_bit = mux_2x1(load, Mux2x1Input(current[i], data[i]))

            self.bits[i].update(next_bit, clk)


class Ram8:
    def __init__(self) -> None:
        self.regs: list[Register8] = [Register8() for _ in range(8)]

    # addr = 3bits
    def read(self, addr: list[int]) -> list[int]:
        regs: list[list[int]] = [reg.read() for reg in self.regs]

        result: list[int] = [0] * 8

        for i in range(8):
            result[i] = mux_8x1(
                addr,
                Mux8x1Input(
                    regs[0][i],
                    regs[1][i],
                    regs[2][i],
                    regs[3][i],
                    regs[4][i],
                    regs[5][i],
                    regs[6][i],
                    regs[7][i],
                ),
            )

        return result

    # addr = 3bits
    def write(self, addr: list[int], data: list[int], load: int, clk: int) -> None:
        load_signals: Dmux1x8Output = dmux_1x8(addr, load)
        self.regs[0].write(data, load_signals.a, clk)
        self.regs[1].write(data, load_signals.b, clk)
        self.regs[2].write(data, load_signals.c, clk)
        self.regs[3].write(data, load_signals.d, clk)
        self.regs[4].write(data, load_signals.e, clk)
        self.regs[5].write(data, load_signals.f, clk)
        self.regs[6].write(data, load_signals.g, clk)
        self.regs[7].write(data, load_signals.h, clk)


class Ram64:
    def __init__(self) -> None:
        self.rams: list[Ram8] = [Ram8() for _ in range(8)]

    # addr = 6bits
    def read(self, addr: list[int]) -> list[int]:
        top_addr: list[int] = [addr[3], addr[4], addr[5]]
        bottom_addr: list[int] = [addr[0], addr[1], addr[2]]

        rams: list[list[int]] = [ram.read(top_addr) for ram in self.rams]
        result: list[int] = [0] * 8
        for i in range(8):
            result[i] = mux_8x1(
                bottom_addr,
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
    def write(self, addr: list[int], data: list[int], load: int, clk: int) -> None:
        top_addr: list[int] = [addr[3], addr[4], addr[5]]
        bottom_addr: list[int] = [addr[0], addr[1], addr[2]]

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
    def read(self, addr: list[int]) -> list[int]:
        top_addr: list[int] = [addr[6], addr[7]]
        bottom_addr: list[int] = [
            addr[0],
            addr[1],
            addr[2],
            addr[3],
            addr[4],
            addr[5],
            addr[6],
        ]

        rams: list[list[int]] = [ram.read(bottom_addr) for ram in self.rams]
        result: list[int] = [0] * 8

        for i in range(8):
            result[i] = mux_4x1(
                top_addr,
                Mux4x1Input(
                    rams[0][i],
                    rams[1][i],
                    rams[2][i],
                    rams[3][i],
                ),
            )

        return result

    # addr = 8bits
    def write(self, addr: list[int], data: list[int], load: int, clk: int) -> None:
        top_addr: list[int] = [addr[6], addr[7]]
        bottom_addr: list[int] = [
            addr[0],
            addr[1],
            addr[2],
            addr[3],
            addr[4],
            addr[5],
            addr[6],
        ]

        load_signals: Dmux1x4Output = dmux_1x4(top_addr, load)
        self.rams[0].write(bottom_addr, data, load_signals.a, clk)
        self.rams[1].write(bottom_addr, data, load_signals.b, clk)
        self.rams[2].write(bottom_addr, data, load_signals.c, clk)
        self.rams[3].write(bottom_addr, data, load_signals.d, clk)


class ProgramCounter:
    def __init__(self) -> None:
        self.reg: Register8 = Register8()

    def read(self) -> list[int]:
        pass
