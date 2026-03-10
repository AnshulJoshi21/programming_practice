#include "dynamic_array.h"

#include <stdio.h>

int main(void)
{
    DynamicArray int_arr;
    da_init(&int_arr, sizeof(int));

    printf("Size: %lu\n", da_size(&int_arr));
    printf("Capacity: %lu\n", da_capacity(&int_arr));

    da_append_val(&int_arr, int, 2);

    da_free(&int_arr);

    return 0;
}
