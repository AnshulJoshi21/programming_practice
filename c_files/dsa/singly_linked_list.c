#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node* next;

} Node;

Node*
create_node(char data)
{
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;
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

int
ll_length(LinkedList* ll)
{
    if (!ll)
    {
        fprintf(stderr, "List not initialized\n");
        exit(EXIT_FAILURE);
    }

    Node* current = ll->head;
    int count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }

    return count;
}

void
ll_prepend(LinkedList* ll, char data)
{
    if (!ll)
    {
        fprintf(stderr, "List not initialized\n");
        exit(EXIT_FAILURE);
    }

    Node* new_node = create_node(data);
    new_node->next = ll->head;
    ll->head = new_node;
    return;
}

void
ll_append(LinkedList* ll, char data)
{
    if (!ll)
    {
        fprintf(stderr, "List not initialized\n");
        exit(EXIT_FAILURE);
    }

    Node* new_node = create_node(data);

    if (!ll->head)
    {
        new_node->next = ll->head;
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
ll_insert_at_index(LinkedList* ll, int index, char character)
{
    if (!ll)
    {
        fprintf(stderr, "List not initialized\n");
        exit(EXIT_FAILURE);
    }

    if (index < 0)
    {
        fprintf(stderr, "Index %d invalid\n", index);
        return;
    }

    Node* new_node = create_node(character);

    if (index == 0)
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
        fprintf(stderr, "Index %d out of bounds\n", index);
        free(new_node);
        return;
    }

    new_node->next = prev->next;
    prev->next = new_node;
}

void
ll_print_list(LinkedList* ll)
{
    if (!ll)
    {
        fprintf(stderr, "List not initialized\n");
        exit(EXIT_FAILURE);
    }

    Node* current = ll->head;
    while (current)
    {
        printf("%c -> ", current->data);
        current = current->next;
    }
    printf("None\n");
}

void
ll_free(LinkedList* ll)
{
    if (!ll)
    {
        fprintf(stderr, "List not initialized\n");
        exit(EXIT_FAILURE);
    }

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
    ll_append(&ll, 'b');
    ll_append(&ll, 'c');
    ll_append(&ll, 'd');
    ll_prepend(&ll, 'a');
    ll_print_list(&ll);
    printf("Length: %d\n", ll_length(&ll));
    ll_insert_at_index(&ll, 2, 'f');
    ll_print_list(&ll);
    printf("Length: %d\n", ll_length(&ll));

    ll_free(&ll);

    return 0;
}