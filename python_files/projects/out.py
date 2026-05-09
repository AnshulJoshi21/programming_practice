def decimal_to_bits(num: int) -> list[int]:
    out: list[int] = []
    temp: int = num

    while temp > 0:
        out.append(temp % 2)
        temp //= 2

    out.reverse()
    return out


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
my_game_rom = [
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],  # LDI R1, 5
    [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1],  # LDI R2, 3
    [0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0],  # ADD R3, R1, R2
]

str_rom: list[str] = ["LDI R1, 5", "LDI R2, 3", "ADD R3, R1, R2"]
bin_rom: list[list[int]] = decode_rom(str_rom)

# assert bin_rom == my_game_rom

for i in range(3):
    print(my_game_rom[i])
    print(bin_rom[i])
    print()
