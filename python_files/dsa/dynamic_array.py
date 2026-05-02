INITIAL_CAPACITY: int = 4


class DynamicArray:
    def __init__(self) -> None:
        self.size: int = 0
        self.capacity: int = INITIAL_CAPACITY
        self.arr: list[int] = []
