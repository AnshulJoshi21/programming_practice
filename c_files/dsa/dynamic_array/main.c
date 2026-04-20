#include <stdio.h>

#include "dynamic_list.h"

int main(void)
{
    DynamicArray arr;
    da_init(&arr);

    printf("\nAppend: 1...9\n");
    for (int i = 1; i < 10; i++) {
        da_append(&arr, i);
    }
    da_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nPrepend: 0\n");
    da_prepend(&arr, 0);
    da_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove at: 4\n");
    da_remove_at(&arr, 4);
    da_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nRemove: 8\n");
    da_remove(&arr, 8);
    da_print(&arr);
    printf("size: %d\n", arr.size);

    printf("\nReverse:\n");
    da_reverse(&arr);
    da_print(&arr);
    printf("size: %d\n", arr.size);

    da_free(&arr);

    return 0;
}
