#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

Node *create_node(const int data)
{
    Node *node = malloc(sizeof(Node));
    assert(node != NULL);

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void dll_init(DoublyLinkedList *list)
{
    assert(list);

    list->head = NULL;
    list->size = 0;
}

void dll_prepend(DoublyLinkedList *list, const int data)
{
    assert(list);

    Node *new_node = create_node(data);

    new_node->next = list->head;
    if (list->head) {
        list->head->prev = new_node;
    }

    list->head = new_node;
    list->size++;
}

void dll_append(DoublyLinkedList *list, const int data)
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

    new_node->prev = current;
    current->next  = new_node;
    list->size++;
}

void dll_remove_at(DoublyLinkedList *list, const int index)
{
    assert(list && list->head);
    assert(list->size > 0);
    assert(index >= 0 && index < list->size);

    Node *current = list->head;
    int   count   = 0;

    while (current) {
        if (count == index) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }

            if (current == list->head) {
                list->head = current->next;
            }

            free(current);
            list->size--;
            return;
        }

        current = current->next;
        count++;
    }
}

void dll_remove(DoublyLinkedList *list, const int data)
{
    assert(list && list->head);
    assert(list->size > 0);

    Node *current = list->head;

    while (current) {
        if (current->data == data) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }

            if (current == list->head) {
                list->head = current->next;
            }

            free(current);
            list->size--;
            return;
        }

        current = current->next;
    }

    printf("data not found\n");
}

void dll_reverse(DoublyLinkedList *list)
{
    assert(list && list->head);
    assert(list->size > 0);

    Node *current = list->head;
    Node *prev    = NULL;
    Node *temp    = NULL;

    while (current) {
        temp = current->next;

        current->prev = temp;
        current->next = prev;

        prev    = current;
        current = temp;
    }

    list->head = prev;
}

void dll_print(DoublyLinkedList *list)
{
    assert(list && list->head);

    if (list->size == 0) {
        printf("empty list\n");
        return;
    }

    printf("Next: null -> ");

    Node *current = list->head;
    while (current) {
        printf("%d -> ", current->data);

        current = current->next;
    }

    printf("null\n");

    //
    // find last node
    current = list->head;
    while (current->next) {
        current = current->next;
    }

    printf("Prev: null <- ");

    while (current) {
        printf("%d <- ", current->data);

        current = current->prev;
    }

    printf("null\n");
}

void dll_free(DoublyLinkedList *list)
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
