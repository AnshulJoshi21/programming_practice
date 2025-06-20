class Node:
    def __init__(self, data: int) -> None:
        self.data: int = data
        self.next: Node | None = None


class LinkedList:
    def __init__(self) -> None:
        self.head: Node | None = None

    def insert_at_beginning(self, data: int) -> None:
        new_node: Node = Node(data)
        new_node.next = self.head
        self.head = new_node

    def insert_at_end(self, data: int) -> None:
        new_node: Node = Node(data)

        if self.head is None:
            self.head = new_node
            return

        current: Node = self.head
        while current.next:
            current = current.next
        current.next = new_node

    def insert_at_index(self, index: int, data: int) -> None:
        new_node: Node = Node(data)

        if index == 0:
            new_node.next = self.head
            self.head = new_node
            return

        current: Node | None = self.head
        current_index: int = 0
        while current:
            current_index += 1
            if current_index == index:
                if current.next is None:
                    current.next = new_node
                    return
                else:
                    prev: Node | None = current
                    new_node.next = current.next
                    prev.next = new_node

            current = current.next

        if index > current_index:
            raise ValueError("Index out of bounds")

    def delete_by_value(self, data: int) -> None:
        if self.head is None:
            print("List is empty")
            return
        elif self.head.data == data:
            self.head = self.head.next
            return

        prev: Node | None = self.head
        while prev:
            current: Node | None = prev.next
            if current is not None and current.data == data:
                prev.next = current.next
                return

            prev = prev.next

    def delete_by_index(self, index: int) -> None:
        if self.head is None:
            print("List is empty")
            return
        elif index == 0:
            self.head = self.head.next
            return

        prev: Node | None = self.head
        current_index: int = 0
        while prev:
            current_index += 1
            current: Node | None = prev.next
            if current is not None and index == current_index:
                prev.next = current.next
                return

            prev = prev.next

    def print(self) -> None:
        if self.head is None:
            print("List is empty")
            return

        current: Node | None = self.head
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("None")

    def length(self) -> int:
        count: int = 0
        current: Node | None = self.head
        while current:
            count += 1
            current = current.next

        return count


ll: LinkedList = LinkedList()
ll.insert_at_end(1)
ll.insert_at_end(2)
ll.insert_at_end(3)
ll.insert_at_beginning(0)
ll.print()
ll.insert_at_index(0, 2)
ll.print()
