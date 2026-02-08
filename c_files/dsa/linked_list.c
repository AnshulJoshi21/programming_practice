// TODO: init, is_empty, size, print_list, append, prepend, pop, insert, remove,
// search, reverse, free

#include <stdbool.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;

} Node;

typedef struct SinglyLinkedList
{
    Node *head;

} SinglyLinkedList;

static void sll_init(SinglyLinkedList *sll);
static bool sll_is_empty(SinglyLinkedList *sll);
static void sll_size(SinglyLinkedList *sll);
static void sll_print_list(SinglyLinkedList *sll);
static void sll_append(SinglyLinkedList *sll);
static void sll_prepend(SinglyLinkedList *sll);
static void sll_pop(SinglyLinkedList *sll);
static void sll_insert(SinglyLinkedList *sll);
static void sll_remove(SinglyLinkedList *sll);
static void sll_search(SinglyLinkedList *sll);
static void sll_reverse(SinglyLinkedList *sll);
static void sll_free(SinglyLinkedList *sll);
