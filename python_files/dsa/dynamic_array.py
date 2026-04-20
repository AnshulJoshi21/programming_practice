INITIAL_CAPACITY: int = 4


class DynamicArray:
    def __init__(self) -> None:
        self.size: int = 0
        self.capacity: int = INITIAL_CAPACITY
        self.arr: list[int | None] = [None] * INITIAL_CAPACITY

    def resize(self) -> None:
        new_arr: list[int | None] = [None] * self.capacity
        for i in range(self.size):
            new_arr[i] = self.arr[i]

        self.arr = new_arr

    def grow(self) -> None:
        if self.size >= self.capacity:
            self.capacity *= 2

            self.resize()

    def shrink(self) -> None:
        if self.size <= self.capacity // 4:
            self.capacity //= 2

            self.capacity = max(self.capacity, INITIAL_CAPACITY)

            self.resize()

    def prepend(self, data: int) -> None:
        self.grow()

        for i in range(self.size, 0, -1):
            self.arr[i] = self.arr[i - 1]

        self.arr[0] = data
        self.size += 1

    def append(self, data: int) -> None:
        self.grow()

        self.arr[self.size] = data
        self.size += 1

    def remove_at(self, index: int) -> None:
        if not self.arr or self.size <= 0:
            return

        for i in range(index, self.size - 1):
            self.arr[i] = self.arr[i + 1]

        self.size += 1

    def remove(self, data: int) -> None:
        if not self.arr or self.size <= 0:
            return

        for i in range(self.size):
            if self.arr[i] == data:
                for j in range(i, self.size - 1):
                    self.arr[j] = self.arr[j + 1]

                self.size += 1
                return

    def reverse(self) -> None:
        if not self.arr or self.size <= 0:
            return

        for i in range(self.size // 2):
            temp: int | None = self.arr[i]
            self.arr[i] = self.arr[self.size - 1 - i]
            self.arr[self.size - 1 - i] = temp

    def print(self) -> None:
        if not self.arr or self.size <= 0:
            return

        for i in range(self.size):
            print(self.arr[i], end=" -> ")

        print("none")


def main() -> None:
    arr: DynamicArray = DynamicArray()
    print("Append: 1...9")
    for i in range(1, 10):
        arr.append(i)
    arr.print()
    print(f"size: {arr.size}")

    print("Prepend: 0")
    arr.prepend(0)
    arr.print()
    print(f"size: {arr.size}")

    print("Remove at: 4")
    arr.remove_at(4)
    arr.print()
    print(f"size: {arr.size}")

    print("Remove: 8")
    arr.remove(8)
    arr.print()
    print(f"size: {arr.size}")

    print("Reverse:")
    arr.reverse()
    arr.print()
    print(f"size: {arr.size}")


if __name__ == "__main__":
    main()
