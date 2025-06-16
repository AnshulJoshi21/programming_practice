pos: list[tuple] = []
row: int = 2
col: int = 5

count: int = 0

for i in range(8):
    if i != row:
        pos.append((i, col))
    if i != col:
        pos.append((row, i))

    


for i in range(8):
    for j in range(8):
        if (i, j) in pos:
            print(" P ", end=" ")
        elif (i, j) == (row, col):
            print(" Q ", end=" ")
        else:
            print(" _ ", end=" ")

    print()
    print()
