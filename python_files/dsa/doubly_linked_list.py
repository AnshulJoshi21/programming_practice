class Node:
    def __init__(self, data: int) -> None:
        self.data: int = data
        self.prev: Node | None = None
        self.next: Node | None = None


class DoublyLinkedList:
    def __init__(self) -> None:
        self.size: int = 0
        self.head: Node | None = None

    def prepend(self, data: int) -> None:
        new_node: Node = Node(data)

        if self.head:
            self.head.prev = new_node
        new_node.next = self.head

        self.head = new_node
        self.size += 1

    def append(self, data: int) -> None:
        new_node: Node = Node(data)

        if not self.head:
            self.head = new_node
            self.size += 1
            return

        current: Node | None = self.head
        while current.next:
            current = current.next

        new_node.prev = current
        current.next = new_node
        self.size += 1

    def remove_at(self, index: int) -> None:
        assert self.head
        assert self.size > 0
        assert 0 <= index < self.size

        current: Node | None = self.head
        count: int = 0

        while current:
            if count == index:
                if current.prev:
                    current.prev.next = current.next
                if current.next:
                    current.next.prev = current.prev

                if current == self.head:
                    self.head = current.next

                self.size -= 1
                return

            current = current.next
            count += 1

    def remove(self, data: int) -> None:
        assert self.head
        assert self.size > 0

        current: Node | None = self.head

        while current:
            if current.data == data:
                if current.prev:
                    current.prev.next = current.next
                if current.next:
                    current.next.prev = current.prev

                if current == self.head:
                    self.head = current.next

                self.size -= 1
                return

            current = current.next

        print("data not found")

    def reverse(self) -> None:
        assert self.head
        assert self.size > 0

        current: Node | None = self.head
        prev: Node | None = None
        next: Node | None = None

        while current:
            next = current.next

            current.prev = next
            current.next = prev

            prev = current
            current = next

        self.head = prev

    def print(self) -> None:
        assert self.head
        assert self.size > 0

        print("Next: none -> ", end="")
        current: Node | None = self.head

        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("none")

        print("Prev: none <- ", end="")
        # find last node
        current = self.head
        while current.next:
            current = current.next

        while current:
            print(current.data, end=" <- ")
            current = current.prev
        print("none")


def main() -> None:
    arr: DoublyLinkedList = DoublyLinkedList()
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
