#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

Node*
create_new_node(int data)
{
    Node* new_node = ( Node* ) malloc(sizeof(Node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
    }
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

typedef struct LinkedList
{
    Node* head;

} LinkedList;

void
ll_init(LinkedList* ll)
{
    ll->head = NULL;
}

void
ll_prepend(LinkedList* ll, int data)
{
    Node* new_node = create_new_node(data);
    new_node->next = ll->head;
    ll->head = new_node;
}

void
ll_append(LinkedList* ll, int data)
{
    Node* new_node = create_new_node(data);

    if (!ll->head)
    {
        ll->head = new_node;
        return;
    }

    Node* current = ll->head;
    while (current->next)
    {
        current = current->next;
    }
    current->next = new_node;
}

void
ll_insert_at_index(LinkedList* ll, int index, int data)
{
    Node* new_node = create_new_node(data);

    if (!ll->head || index == 0)
    {
        new_node->next = ll->head;
        ll->head = new_node;
        return;
    }

    Node* prev = ll->head;
    int count = 0;
    while (prev && count < index - 1)
    {
        count++;
        prev = prev->next;
    }

    if (!prev)
    {
        fprintf(stderr, "Index out of bounds\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    new_node->next = prev->next;
    prev->next = new_node;
}

void
ll_print_list(LinkedList* ll)
{
    Node* current = ll->head;
    while (current)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("None\n");
}

void
ll_free(LinkedList* ll)
{
    Node* current = ll->head;
    while (current)
    {
        Node* tmp = current->next;
        free(current);
        current = tmp;
    }
}

int
main(void)
{
    LinkedList ll;
    ll_init(&ll);
    ll_append(&ll, 1);
    ll_append(&ll, 2);
    ll_append(&ll, 3);
    ll_prepend(&ll, 0);
    ll_insert_at_index(&ll, -1, 10);
    ll_print_list(&ll);

    ll_free(&ll);

    return 0;
}