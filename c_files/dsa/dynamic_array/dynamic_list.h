#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

typedef struct DynamicArray {
    int *arr;
    int  size;
    int  capacity;

} DynamicArray;

void da_init(DynamicArray *da);
void da_resize(DynamicArray *da);
void da_grow(DynamicArray *da);
void da_shrink(DynamicArray *da);
void da_prepend(DynamicArray *da, const int value);
void da_append(DynamicArray *da, const int value);
void da_remove_at(DynamicArray *da, const int index);
void da_remove(DynamicArray *da, const int value);
void da_reverse(DynamicArray *da);
void da_print(DynamicArray *da);
void da_free(DynamicArray *da);

#endif  // DYNAMIC_LIST_H
