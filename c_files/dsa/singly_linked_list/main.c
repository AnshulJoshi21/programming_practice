#include <stdio.h>

#include "singly_linked_list.h"

int main(void)
{
    SinglyLinkedList arr;
    sll_init(&arr);

    printf("\nAppend: 1...9\n");
    for (int i = 1; i < 10; i++) {
        sll_append(&arr, i);
    }
    sll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nPrepend: 0\n");
    sll_prepend(&arr, 0);
    sll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove at: 4\n");
    sll_remove_at(&arr, 4);
    sll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove: 8\n");
    sll_remove(&arr, 8);
    sll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nReverse:\n");
    sll_reverse(&arr);
    sll_print(&arr);
    printf("size: %d\n", arr.size);

    sll_free(&arr);

    return 0;
}
