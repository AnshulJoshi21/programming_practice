#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

typedef struct Node {
    int          data;
    struct Node *prev;
    struct Node *next;

} Node;

typedef struct CircularLinkedList {
    Node *head;
    Node *tail;
    int   size;

} CircularLinkedList;

Node *create_node(const int data);

void cll_init(CircularLinkedList *list);
void cll_prepend(CircularLinkedList *list, const int data);
void cll_append(CircularLinkedList *list, const int data);
void cll_remove_at(CircularLinkedList *list, const int index);
void cll_remove(CircularLinkedList *list, const int data);
void cll_reverse(CircularLinkedList *list);
void cll_print(CircularLinkedList *list);
void cll_free(CircularLinkedList *list);

#endif  // CIRCULAR_LINKED_LIST_H
