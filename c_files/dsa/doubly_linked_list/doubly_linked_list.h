#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct Node {
    int          data;
    struct Node *prev;
    struct Node *next;

} Node;

typedef struct DoublyLinkedList {
    Node *head;
    int   size;

} DoublyLinkedList;

Node *create_node(const int data);

void dll_init(DoublyLinkedList *list);
void dll_prepend(DoublyLinkedList *list, const int data);
void dll_append(DoublyLinkedList *list, const int data);
void dll_remove_at(DoublyLinkedList *list, const int index);
void dll_remove(DoublyLinkedList *list, const int data);
void dll_reverse(DoublyLinkedList *list);
void dll_print(DoublyLinkedList *list);
void dll_free(DoublyLinkedList *list);

#endif  // DOUBLY_LINKED_LIST_H
