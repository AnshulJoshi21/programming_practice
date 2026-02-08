import numpy as np

INITIAL_CAPACITY: int = 4
GROWTH_FACTOR: int = 2
SHRINK_FACTOR: int = 4


class DynamicArray:
    def __init__(self) -> None:
        self.size: int = 0
        self.capacity: int = INITIAL_CAPACITY
        self.arr: np.array[int] = np.empty(self.size, dtype=int)

    def size(self) -> int:
        return self.size

    def get(self, index: int) -> None:
        assert index < self.size

        return self.arr[index]

    def set(self, index: int, data: int) -> None:
        assert index < self.size

        self.arr[index] = data

    def adjust_capacity(self) -> None:
        # grow
        if self.size == self.capacity:
            self.capacity *= GROWTH_FACTOR
        # shrink
        elif self.size * SHRINK_FACTOR < self.capacity:
            self.capacity = self.capacity // GROWTH_FACTOR

            if self.capacity < INITIAL_CAPACITY:
                self.capacity = INITIAL_CAPACITY
        # do nothing
        else:
            return
