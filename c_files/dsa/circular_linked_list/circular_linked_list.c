#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "circular_linked_list.h"

Node *create_node(const int data)
{
    Node *node = malloc(sizeof(Node));
    assert(node != NULL);

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void cll_init(CircularLinkedList *list)
{
    assert(list);

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void cll_prepend(CircularLinkedList *list, const int data)
{
    assert(list);

    Node *new_node = create_node(data);

    if (!list->head) {
        new_node->next = new_node;
        new_node->prev = new_node;

        list->head = new_node;
        list->tail = new_node;

        list->size++;
        return;
    }

    new_node->next = list->head;
    new_node->prev = list->tail;

    list->head->prev = new_node;
    list->tail->next = new_node;

    list->head = new_node;

    list->size++;
}

void cll_append(CircularLinkedList *list, const int data)
{
    assert(list);

    Node *new_node = create_node(data);

    if (!list->head) {
        new_node->next = new_node;
        new_node->prev = new_node;

        list->head = new_node;
        list->tail = new_node;

        list->size++;
        return;
    }

    new_node->next = list->head;
    new_node->prev = list->tail;

    list->head->prev = new_node;
    list->tail->next = new_node;

    list->tail = new_node;

    list->size++;
}

void cll_remove_at(CircularLinkedList *list, const int index)
{
    assert(list && list->head && list->tail);
    assert(list->size > 0);
    assert(index >= 0 && index < list->size);

    Node *current = list->head;
    int   count   = 0;

    while (1) {
        if (count == index) {
            if (list->size == 1) {
                list->head = list->tail = NULL;
                list->size--;
                return;
            }

            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }

            if (current == list->head) {
                list->head = current->next;
            }

            if (current == list->tail) {
                list->tail = current->prev;
            }

            free(current);
            list->size--;
            return;
        }

        current = current->next;
        count++;

        if (current == list->head) {
            break;
        }
    }
}

void cll_remove(CircularLinkedList *list, const int data)
{
    assert(list && list->head && list->tail);
    assert(list->size > 0);

    Node *current = list->head;

    while (1) {
        if (current->data == data) {
            if (list->size == 1) {
                list->head = list->tail = NULL;
                list->size--;
                return;
            }

            if (current->prev) {
                current->prev->next = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }

            if (current == list->head) {
                list->head = current->next;
            }

            if (current == list->tail) {
                list->tail = current->prev;
            }

            free(current);
            list->size--;
            return;
        }

        current = current->next;

        if (current == list->head) {
            break;
        }
    }

    printf("data not found\n");
}

void cll_reverse(CircularLinkedList *list)
{
    assert(list && list->head && list->tail);
    assert(list->size > 0);

    Node *current = list->head;
    Node *prev    = NULL;
    Node *temp    = NULL;

    while (1) {
        temp = current->next;

        current->prev = temp;
        current->next = prev;

        prev    = current;
        current = temp;

        if (current == list->head) {
            break;
        }
    }

    list->head = current;
    list->tail = current->prev;
}

void cll_print(CircularLinkedList *list)
{
    assert(list && list->head && list->tail);

    if (list->size == 0) {
        printf("empty list\n");
        return;
    }

    printf("Next: tail -> ");

    Node *current = list->head;
    while (1) {
        printf("%d -> ", current->data);

        current = current->next;

        if (current == list->head) {
            break;
        }
    }

    printf("head\n");

    //
    printf("Prev: tail <- ");

    current = list->tail;
    while (1) {
        printf("%d <- ", current->data);

        current = current->prev;

        if (current == list->tail) {
            break;
        }
    }

    printf("head\n");
}

void cll_free(CircularLinkedList *list)
{
    assert(list && list->head && list->tail);
    assert(list->size > 0);

    Node *current = list->head;
    while (1) {
        Node *temp = current;
        current    = current->next;
        free(temp);

        if (current == list->head) {
            break;
        }
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
