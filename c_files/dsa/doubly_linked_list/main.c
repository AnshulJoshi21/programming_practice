#include <stdio.h>

#include "doubly_linked_list.h"

int main(void)
{
    DoublyLinkedList arr;
    dll_init(&arr);

    printf("\nAppend: 1...9\n");
    for (int i = 1; i < 10; i++) {
        dll_append(&arr, i);
    }
    dll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nPrepend: 0\n");
    dll_prepend(&arr, 0);
    dll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove at: 4\n");
    dll_remove_at(&arr, 4);
    dll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove: 8\n");
    dll_remove(&arr, 8);
    dll_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nReverse:\n");
    dll_reverse(&arr);
    dll_print(&arr);
    printf("size: %d\n", arr.size);

    dll_free(&arr);

    return 0;
}
