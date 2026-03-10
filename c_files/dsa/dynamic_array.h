#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

#define da_append_val(da, type, value) da_append(da, &(type){value})

typedef struct DynamicArray
{
    void *arr;
    size_t size;
    size_t capacity;
    size_t elem_size;

} DynamicArray;

void da_init(DynamicArray *da, size_t elem_size);
size_t da_size(const DynamicArray *da);
size_t da_capacity(const DynamicArray *da);
void da_adjust_capacity(DynamicArray *da);
void da_append(DynamicArray *da, void *data);
void da_free(DynamicArray *da);

#endif // DYNAMIC_ARRAY_H
