#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

typedef struct Node {
    int          data;
    struct Node *next;

} Node;

typedef struct SinglyLinkedList {
    Node *head;
    int   size;

} SinglyLinkedList;

Node *create_node(const int data);

void sll_init(SinglyLinkedList *list);
void sll_prepend(SinglyLinkedList *list, const int data);
void sll_append(SinglyLinkedList *list, const int data);
void sll_remove_at(SinglyLinkedList *list, const int index);
void sll_remove(SinglyLinkedList *list, const int data);
void sll_reverse(SinglyLinkedList *list);
void sll_print(SinglyLinkedList *list);
void sll_free(SinglyLinkedList *list);

#endif  // SINGLY_LINKED_LIST_H
