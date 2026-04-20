#include <stdio.h>

#include "circular_linked_list.h"

int main(void)
{
    CircularLinkedList arr;
    cll_init(&arr);

    printf("\nAppend: 1...9\n");
    for (int i = 1; i < 10; i++) {
        cll_append(&arr, i);
    }
    cll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nPrepend: 0\n");
    cll_prepend(&arr, 0);
    cll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove at: 4\n");
    cll_remove_at(&arr, 4);
    cll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove: 8\n");
    cll_remove(&arr, 8);
    cll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nReverse:\n");
    cll_reverse(&arr);
    cll_print(&arr);
    printf("size: %d\n", arr.size);

    cll_free(&arr);

    return 0;
}
