class Node:
    def __init__(self, data: int) -> None:
        self.data: int = data
        self.prev: Node | None = None
        self.next: Node | None = None


class CircularLinkedList:
    def __init__(self) -> None:
        self.size: int = 0
        self.head: Node | None = None
        self.tail: Node | None = None

    def prepend(self, data: int) -> None:
        new_node: Node = Node(data)

        if not self.head:
            new_node.next = new_node
            new_node.prev = new_node

            self.head = new_node
            self.tail = new_node

            self.size += 1
            return

        new_node.next = self.head
        new_node.prev = self.tail

        self.head.prev = new_node
        if self.tail:
            self.tail.next = new_node

        self.head = new_node

        self.size += 1

    def append(self, data: int) -> None:
        new_node: Node = Node(data)

        if not self.head:
            new_node.next = new_node
            new_node.prev = new_node

            self.head = new_node
            self.tail = new_node

            self.size += 1
            return

        new_node.next = self.head
        new_node.prev = self.tail

        self.head.prev = new_node
        if self.tail:
            self.tail.next = new_node

        self.tail = new_node

        self.size += 1

    def remove_at(self, index: int) -> None:
        assert self.head
        assert self.tail
        assert self.size > 0
        assert 0 <= index < self.size

        current: Node | None = self.head
        count: int = 0

        while current:
            if count == index:
                if self.size == 1:
                    self.head = self.tail = None
                    self.size -= 1
                    return

                if current.prev:
                    current.prev.next = current.next
                if current.next:
                    current.next.prev = current.prev

                if current == self.head:
                    self.head = current.next
                if current == self.tail:
                    self.tail = current.prev

                self.size -= 1
                return

            current = current.next
            count += 1

            if current == self.head:
                break

    def remove(self, data: int) -> None:
        assert self.head
        assert self.tail
        assert self.size > 0

        current: Node | None = self.head

        while current:
            if current.data == data:
                if self.size == 1:
                    self.head = self.tail = None
                    self.size -= 1
                    return

                if current.prev:
                    current.prev.next = current.next
                if current.next:
                    current.next.prev = current.prev

                if current == self.head:
                    self.head = current.next
                if current == self.tail:
                    self.tail = current.prev

                self.size -= 1
                return

            current = current.next

            if current == self.head:
                break

        print("data not found")

    def reverse(self) -> None:
        assert self.head
        assert self.tail
        assert self.size > 0

        current: Node | None = self.head
        prev: Node | None = self.tail
        next: Node | None = None

        while current:
            next = current.next

            current.prev = next
            current.next = prev

            prev = current
            current = next

            if current == self.head:
                break

        self.head = current
        self.tail = prev

    def print(self) -> None:
        assert self.head
        assert self.tail
        assert self.size > 0

        print("Next: tail -> ", end="")
        current: Node | None = self.head

        while current:
            print(current.data, end=" -> ")
            current = current.next

            if current == self.head:
                break

        print("head")

        print("Prev: head <- ", end="")
        current = self.tail

        while current:
            print(current.data, end=" <- ")
            current = current.prev

            if current == self.tail:
                break

        print("tail")


def main() -> None:
    arr: CircularLinkedList = CircularLinkedList()
    print()
    print("Append: 1...9")
    for i in range(1, 10):
        arr.append(i)
    arr.print()
    print(f"size: {arr.size}")

    print()
    print("Prepend: 0")
    arr.prepend(0)
    arr.print()
    print(f"size: {arr.size}")

    print()
    print("Remove at: 4")
    arr.remove_at(4)
    arr.print()
    print(f"size: {arr.size}")

    print()
    print("Remove: 8")
    arr.remove(8)
    arr.print()
    print(f"size: {arr.size}")

    print()
    print("Reverse:")
    arr.reverse()
    arr.print()
    print(f"size: {arr.size}")


if __name__ == "__main__":
    main()
