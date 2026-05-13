from dataclasses import dataclass, field

MEMORY_SIZE: int = 4096


def sign_extend(value: int, bits: int) -> int:
    sign_bit: int = 1 << (bits - 1)
    return (value & (sign_bit - 1)) - (value & sign_bit)


def get_bits(value: int, start: int, length: int) -> int:
    mask: int = (1 << length) - 1
    return (value >> start) & mask


@dataclass
class RV32I:
    regs: list[int] = field(default_factory=lambda: [0] * 32)
    pc: int = 0
    memory: bytearray = field(default_factory=lambda: bytearray(MEMORY_SIZE))

    def load_word(self, addr: int) -> int:
        return (
            self.memory[addr]
            | (self.memory[addr + 1] << 8)
            | (self.memory[addr + 2] << 16)
            | (self.memory[addr + 3] << 24)
        )

    def store_word(self, addr: int, value: int) -> None:
        self.memory[addr] = value & 0xFF
        self.memory[addr + 1] = (value >> 8) & 0xFF
        self.memory[addr + 2] = (value >> 16) & 0xFF
        self.memory[addr + 3] = (value >> 24) & 0xFF

    def fetch(self) -> int:
        return self.load_word(self.pc)

    def step(self) -> None:
        instr: int = self.fetch()

        opcode: int = get_bits(instr, 0, 7)

        old_pc: int = self.pc

        self.pc += 4

        rd: int
        funct3: int
        rs1: int
        rs2: int
        funct7: int
        imm: int

        # r type instruction
        if opcode == 0b0110011:
            rd = get_bits(instr, 7, 5)
            funct3 = get_bits(instr, 12, 3)
            rs1 = get_bits(instr, 15, 5)
            rs2 = get_bits(instr, 20, 5)
            funct7 = get_bits(instr, 25, 7)

            # add
            if funct3 == 0b000 and funct7 == 0b0000000:
                self.regs[rd] = (self.regs[rs1] + self.regs[rs2]) & 0xFFFFFFFF

            # sub
            elif funct3 == 0b000 and funct7 == 0b0100000:
                self.regs[rd] = (self.regs[rs1] - self.regs[rs2]) & 0xFFFFFFFF
            else:
                raise Exception("Unknown R-type instruction")

        # i type arithmetic
        elif opcode == 0b0010011:
            rd = get_bits(instr, 7, 5)
            funct3 = get_bits(instr, 12, 3)
            rs1 = get_bits(instr, 15, 5)

            imm = sign_extend(get_bits(instr, 20, 12), 12)

            # addi
            if funct3 == 0b000:
                self.regs[rd] = (self.regs[rs1] + imm) & 0xFFFFFFFF

            else:
                raise Exception("Unkonwn I-type instruction")

        # load instruction
        elif opcode == 0b0000011:
            rd = get_bits(instr, 7, 5)
            funct3 = get_bits(instr, 12, 3)
            rs1 = get_bits(instr, 15, 5)

            imm = sign_extend(get_bits(instr, 20, 12), 12)

            addr = (self.regs[rs1] + imm) & 0xFFFFFFFF

            # lw = load word
            if funct3 == 0b010:
                self.regs[rd] = self.load_word(addr)

            else:
                raise Exception("Unknown load instruction")

        # store instruction
        elif opcode == 0b0100011:
            funct3 = get_bits(instr, 12, 3)
            rs1 = get_bits(instr, 15, 5)
            rs2 = get_bits(instr, 20, 5)

            imm_low: int = get_bits(instr, 7, 5)
            imm_high: int = get_bits(instr, 25, 7)

            imm = sign_extend(imm_low | imm_high << 5, 12)

            addr = (self.regs[rs1] + imm) & 0xFFFFFFFF

            # sw = store word
            if funct3 == 0b010:
                self.store_word(addr, self.regs[rs2])

            else:
                raise Exception("Unknown store instruction")

        # branch instruction
        elif opcode == 0b1100011:
            funct3 = get_bits(instr, 12, 3)
            rs1 = get_bits(instr, 15, 5)
            rs2 = get_bits(instr, 20, 5)

            imm = (
                (get_bits(instr, 31, 1) << 12)
                | (get_bits(instr, 7, 1) << 11)
                | (get_bits(instr, 25, 6) << 5)
                | (get_bits(instr, 8, 4) << 1)
            )

            imm = sign_extend(imm, 12)

            # beq
            if funct3 == 0b000:
                if self.regs[rs1] == self.regs[rs2]:
                    self.pc = old_pc + imm

            # bne
            elif funct3 == 0b001:
                if self.regs[rs1] != self.regs[rs2]:
                    self.pc = old_pc + imm

            else:
                raise Exception("Unknown branch instruction")

        # jal (jump and link)
        elif opcode == 0b1101111:
            rd = get_bits(instr, 7, 5)

            imm = (
                (get_bits(instr, 31, 1) << 20)
                | (get_bits(instr, 12, 8) << 12)
                | (get_bits(instr, 20, 1) << 11)
                | (get_bits(instr, 21, 10) << 1)
            )

            imm = sign_extend(imm, 21)

            # save return addr
            self.regs[rd] = self.pc

            # jump
            self.pc = old_pc + imm

        # lui (load upper immediate)
        elif opcode == 0b0110111:
            rd = get_bits(instr, 7, 5)
            imm = get_bits(instr, 12, 20) << 12

            self.regs[rd] = imm

        # unknown instruction
        else:
            raise Exception(f"Unknown opcode: {opcode: 07b}")

        # reg[0] is hardcoded to 0 in riscV
        self.regs[0] = 0

    def load_program(self, instructions: list[int], start_addr=0) -> None:
        self.pc = start_addr

        for i, instr in enumerate(instructions):
            addr: int = start_addr + (i * 4)
            self.store_word(addr, instr)

    def run(self, steps: int = 100) -> None:
        for _ in range(steps):
            self.step()


if __name__ == "__main__":
    cpu: RV32I = RV32I()

    # Small demo program:
    #
    # addi x1, x0, 10
    # addi x2, x0, 20
    # add  x3, x1, x2
    #
    # x3 should become 30

    program: list[int] = [
        # addi x1, x0, 10
        0x00A00093,
        # addi x2, x0, 20
        0x01400113,
        # add x3, x1, x2
        0x002081B3,
    ]

    cpu.load_program(program)
    cpu.run(steps=3)

    print(f"x1 = {cpu.regs[1]}")
    print(f"x2 = {cpu.regs[2]}")
    print(f"x3 = {cpu.regs[3]}")
