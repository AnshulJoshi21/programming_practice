#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_list.h"

static const int INITIAL_CAPACITY = 4;

void da_init(DynamicArray *da)
{
    assert(da);

    da->size     = 0;
    da->capacity = INITIAL_CAPACITY;
    da->arr      = malloc(INITIAL_CAPACITY * sizeof(int));
    assert(da->arr != NULL);
}

void da_resize(DynamicArray *da)
{
    assert(da);

    int *temp = realloc(da->arr, da->capacity * sizeof(int));
    assert(temp != NULL);

    da->arr = temp;
}

void da_grow(DynamicArray *da)
{
    assert(da);

    if (da->size >= da->capacity) {
        da->capacity *= 2;

        da_resize(da);
    }
}

void da_shrink(DynamicArray *da)
{
    assert(da);

    if (da->size <= da->capacity / 4) {
        da->capacity /= 4;

        if (da->capacity < INITIAL_CAPACITY) {
            da->capacity = INITIAL_CAPACITY;
        }

        da_resize(da);
    }
}

void da_prepend(DynamicArray *da, const int value)
{
    assert(da);

    da_grow(da);

    for (int i = da->size; i > 0; i--) {
        da->arr[i] = da->arr[i - 1];
    }

    da->arr[0] = value;
    da->size++;
}

void da_append(DynamicArray *da, const int value)
{
    assert(da);

    da_grow(da);

    da->arr[da->size++] = value;
}

void da_remove_at(DynamicArray *da, const int index)
{
    assert(da);
    assert(da->size > 0);
    assert(index >= 0 && index < da->size);

    for (int i = index; i < da->size - 1; i++) {
        da->arr[i] = da->arr[i + 1];
    }

    da->size--;
    da_shrink(da);
}

void da_remove(DynamicArray *da, const int value)
{
    assert(da);
    assert(da->size > 0);

    for (int i = 0; i < da->size; i++) {
        if (da->arr[i] == value) {
            for (int j = i; j < da->size - 1; j++) {
                da->arr[j] = da->arr[j + 1];
            }

            da->size--;
            da_shrink(da);
            return;
        }
    }

    printf("data not found\n");
}

void da_reverse(DynamicArray *da)
{
    assert(da);
    assert(da->size > 0);

    for (int i = 0; i < da->size / 2; i++) {
        int temp                  = da->arr[i];
        da->arr[i]                = da->arr[da->size - 1 - i];
        da->arr[da->size - 1 - i] = temp;
    }
}

void da_print(DynamicArray *da)
{
    assert(da);

    if (da->size == 0) {
        printf("empty list\n");
        return;
    }

    for (int i = 0; i < da->size; i++) {
        printf("%d -> ", da->arr[i]);
    }

    printf("null\n");
}

void da_free(DynamicArray *da)
{
    if (da && da->arr) {
        free(da->arr);
        da->arr  = NULL;
        da->size = 0;
    }
}
