#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int   size;
} LinkedList;

static Node* create_node(const int data) {
    Node* new_node = malloc(sizeof(Node));
    assert(new_node);
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

static void ll_init(LinkedList* ll) {
    assert(ll);

    ll->head = NULL;
    ll->size = 0;
}

static void ll_print(const LinkedList* ll) {
    assert(ll);

    const Node* current = ll->head;

    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("None\n");
}

static void ll_prepend(LinkedList* ll, const int data) {
    assert(ll);

    Node* new_node = create_node(data);
    new_node->next = ll->head;
    ll->head       = new_node;

    ll->size++;
}

static void ll_append(LinkedList* ll, const int data) {
    assert(ll);

    Node* new_node = create_node(data);

    if (!ll->head) {
        ll->head = new_node;
        ll->size++;
        return;
    }

    Node* current = ll->head;
    while (current->next) {
        current = current->next;
    }

    current->next = new_node;
    ll->size++;
}

static void ll_pop(LinkedList* ll) {
    assert(ll);

    if (!ll->head) {
        return;
    }

    if (!ll->head->next) {
        ll->head = NULL;
        return;
    }

    Node* prev    = NULL;
    Node* current = ll->head;
    while (current->next) {
        prev    = current;
        current = current->next;
    }

    free(current);
    prev->next = NULL;
    ll->size--;
}

static void ll_pop_left(LinkedList* ll) {
    assert(ll);

    if (!ll->head) {
        return;
    }

    if (!ll->head->next) {
        ll->head = NULL;
        ll->size--;
        return;
    }

    Node* temp = ll->head;
    ll->head   = ll->head->next;
    free(temp);

    ll->size--;
}

static void ll_free(LinkedList* ll) {
    assert(ll);

    Node* current = ll->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    LinkedList ll;
    ll_init(&ll);

    ll_append(&ll, 1);
    ll_append(&ll, 2);
    ll_append(&ll, 3);
    ll_append(&ll, 4);
    ll_append(&ll, 5);
    ll_prepend(&ll, 0);

    ll_pop(&ll);
    ll_pop_left(&ll);

    ll_print(&ll);
    printf("Size: %d\n", ll.size);

    ll_free(&ll);

    return 0;
}
