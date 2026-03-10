#include "dynamic_array.h"

#include <assert.h>
#include <string.h>

static const size_t INITIAL_CAPACITY = 4;
static const size_t GROWTH_FACTOR    = 2;
static const size_t SHRINK_FACTOR    = 4;

void da_init(DynamicArray *da, size_t elem_size)
{
    assert(da);

    da->size      = 0;
    da->capacity  = INITIAL_CAPACITY;
    da->elem_size = elem_size;

    da->arr = malloc(da->capacity * da->elem_size);
    assert(da->arr);
}

size_t da_size(const DynamicArray *da)
{
    assert(da);
    return da->size;
}

size_t da_capacity(const DynamicArray *da)
{
    assert(da);
    return da->capacity;
}

void da_adjust_capacity(DynamicArray *da)
{
    assert(da);

    size_t new_capacity;

    // growth
    if (da->size >= da->capacity) {
        new_capacity = da->capacity * GROWTH_FACTOR;
    }
    // shrink
    else if (da->size * SHRINK_FACTOR < da->capacity) {
        new_capacity = da->capacity / GROWTH_FACTOR;

        if (new_capacity < INITIAL_CAPACITY) {
            new_capacity = INITIAL_CAPACITY;
        }
    }
    // do nothing
    else
        return;

    void *temp = realloc(da->arr, new_capacity * da->elem_size);
    assert(temp);

    da->arr      = temp;
    da->capacity = new_capacity;
}

void da_append(DynamicArray *da, void *data)
{
    assert(da);
    assert(data);

    da_adjust_capacity(da);

    char *destination = (char *)da->arr + (da->size * da->elem_size);
    memcpy(destination, data, da->elem_size);

    da->size++;
}

void da_free(DynamicArray *da)
{
    if (da->arr) {
        free(da->arr);
        da->arr = NULL;

        da->size = da->capacity = 0;
    }
}
