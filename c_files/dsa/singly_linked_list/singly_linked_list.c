#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"

Node *create_node(const int data)
{
    Node *node = malloc(sizeof(Node));
    assert(node != NULL);

    node->data = data;
    node->next = NULL;

    return node;
}

void sll_init(SinglyLinkedList *list)
{
    assert(list);

    list->head = NULL;
    list->size = 0;
}

void sll_prepend(SinglyLinkedList *list, const int data)
{
    assert(list);

    Node *new_node = create_node(data);
    new_node->next = list->head;
    list->head     = new_node;
    list->size++;
}

void sll_append(SinglyLinkedList *list, const int data)
{
    assert(list);

    Node *new_node = create_node(data);

    if (!list->head) {
        list->head = new_node;
        list->size++;
        return;
    }

    Node *current = list->head;

    while (current->next) {
        current = current->next;
    }

    current->next = new_node;
    list->size++;
}

void sll_remove_at(SinglyLinkedList *list, const int index)
{
    assert(list && list->head);
    assert(list->size > 0);
    assert(index >= 0 && index < list->size);

    Node *current = list->head;
    Node *prev    = NULL;
    int   count   = 0;

    while (current) {
        if (count == index) {
            if (prev) {
                prev->next = current->next;
            }

            if (current == list->head) {
                list->head = current->next;
            }

            free(current);
            list->size--;
            return;
        }

        prev    = current;
        current = current->next;
        count++;
    }
}

void sll_remove(SinglyLinkedList *list, const int data)
{
    assert(list && list->head);
    assert(list->size > 0);

    Node *current = list->head;
    Node *prev    = NULL;

    while (current) {
        if (current->data == data) {
            if (prev) {
                prev->next = current->next;
            }

            if (current == list->head) {
                list->head = current->next;
            }

            free(current);
            list->size--;
            return;
        }

        prev    = current;
        current = current->next;
    }

    printf("data not found\n");
}

void sll_reverse(SinglyLinkedList *list)
{
    assert(list && list->head);
    assert(list->size > 0);

    Node *current = list->head;
    Node *prev    = NULL;
    Node *temp    = NULL;

    while (current) {
        temp          = current->next;
        current->next = prev;
        prev          = current;
        current       = temp;
    }

    list->head = prev;
}

void sll_print(SinglyLinkedList *list)
{
    assert(list && list->head);

    if (list->size == 0) {
        printf("empty list\n");
        return;
    }

    Node *current = list->head;
    while (current) {
        printf("%d -> ", current->data);

        current = current->next;
    }

    printf("null\n");
}

void sll_free(SinglyLinkedList *list)
{
    assert(list && list->head);
    assert(list->size > 0);

    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current    = current->next;
        free(temp);
    }

    list->head = NULL;
    list->size = 0;
}
