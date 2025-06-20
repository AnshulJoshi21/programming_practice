class Node:
    def __init__(self, data: int) -> None:
        self.data: int = data
        self.next: Node | None = None


class LinkedList:
    def __init__(self) -> None:
        self.head: Node | None = None

    def length(self) -> int:
        current: Node | None = self.head
        length: int = 0
        while current:
            length += 1
            current = current.next

        return length

    def prepend(self, data: int) -> None:
        new_node: Node | None = Node(data)
        new_node.next = self.head
        self.head = new_node

    def append(self, data: int) -> None:
        new_node: Node | None = Node(data)

        if not self.head:
            self.head = new_node
            return

        current: Node | None = self.head
        while current.next:
            current = current.next

        current.next = new_node

    def insert_at_index(self, index: int, data: int) -> None:
        new_node: Node | None = Node(data)

        if not self.head or index == 0:
            new_node.next = self.head
            self.head = new_node
            return

        prev: Node | None = self.head
        count: int = 1
        while prev:
            if prev.next and count == index:
                new_node.next = prev.next
                prev.next = new_node
                return

            count += 1
            prev = prev.next

        raise ValueError("Index out of bounds")

    def delete_by_value(self, value: int) -> None:
        if not self.head:
            raise ValueError("List is empty")

        if self.head and self.head.data == value:
            self.head = self.head.next
            return

        current: Node | None = self.head
        while current:
            next: Node | None = current.next
            if next and next.data == value:
                current.next = next.next
                return

            current = current.next

        raise ValueError(f"{value} not in list")

    def delete_by_index(self, index: int) -> None:
        if not self.head:
            raise ValueError("List is empty")

        if self.head and index == 0:
            self.head = self.head.next
            return

        current: Node | None = self.head
        count: int = 1
        while current:
            next: Node | None = current.next
            if next and count == index:
                current.next = next.next
                return

            count += 1
            current = current.next

        raise ValueError("Index out of bounds")

    def index_from_value(self, value: int) -> int:
        if not self.head:
            raise ValueError("List is empty")

        count: int = 0
        current: Node | None = self.head
        while current:
            if current.data == value:
                return count

            count += 1
            current = current.next

        raise ValueError(f"{value} not in list")

    def value_from_index(self, index: int) -> int:
        if not self.head:
            raise ValueError("List is empty")

        count: int = 0
        current: Node | None = self.head
        while current:
            if count == index:
                return current.data

            count += 1
            current = current.next

        raise ValueError("Index out of bounds")

    def reverse(self) -> None:
        prev: Node | None = None
        current: Node | None = self.head
        while current:
            next_node: Node | None = current.next
            current.next = prev
            prev = current
            current = next_node

        self.head = prev

    def __str__(self) -> str:
        current: Node | None = self.head
        nodes: list[str] = []

        while current:
            nodes.append(str(current.data))
            current = current.next

        return " -> ".join(nodes) + " -> None"

    def __repr__(self) -> str:
        current: Node | None = self.head
        nodes: list[str] = []

        while current:
            nodes.append(str(current.data))
            current = current.next

        return " -> ".join(nodes) + " -> None"


ll: LinkedList = LinkedList()
ll.append(10)
ll.append(20)
ll.append(30)
ll.append(40)
ll.prepend(00)
print(ll.__str__())
print(ll.reverse())
print(ll.__str__())
