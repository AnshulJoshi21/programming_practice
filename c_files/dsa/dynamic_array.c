// TODO: init, size, capacity, get, set, adjust_capacity, append, pop, insert,
// remove, clear, free

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4
#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 4

typedef struct IntArray
{
    size_t size;
    size_t capacity;
    int *data;

} IntArray;

static void int_array_init(IntArray *arr)
{
    assert(arr);

    arr->size     = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->data     = (int *)malloc(arr->capacity * sizeof(int));
    assert(arr->data);
}

static size_t int_array_size(IntArray *arr)
{
    assert(arr);

    return arr->size;
}

static size_t int_array_capacity(IntArray *arr)
{
    assert(arr);

    return arr->capacity;
}

static int int_array_get(IntArray *arr, size_t index)
{
    assert(arr);
    assert(index < arr->size);

    return arr->data[index];
}

static void int_array_set(IntArray *arr, size_t index, int value)
{
    assert(arr);
    assert(index < arr->size);

    arr->data[index] = value;
}

static void int_array_adjust_capacity(IntArray *arr)
{
    assert(arr);

    size_t new_capacity;

    // grow
    if (arr->size == arr->capacity) {
        new_capacity = arr->capacity * GROWTH_FACTOR;
        // shrink
    } else if (arr->size * SHRINK_FACTOR < arr->capacity) {
        new_capacity = arr->capacity / GROWTH_FACTOR;

        // should always be greater than minimum size
        if (new_capacity < INITIAL_CAPACITY) {
            new_capacity = INITIAL_CAPACITY;
        }

        // return as it is
    } else
        return;

    int *temp = (int *)realloc(arr->data, new_capacity * sizeof(int));
    assert(temp);

    arr->data     = temp;
    arr->capacity = new_capacity;
}

static void int_array_append(IntArray *arr, int value)
{
    assert(arr);

    arr->size++;
    int_array_adjust_capacity(arr);
    arr->data[arr->size - 1] = value;
}

static void int_array_pop(IntArray *arr)
{
    assert(arr);
    assert(arr->size > 0);

    arr->size--;
    int_array_adjust_capacity(arr);
}

static void int_array_insert(IntArray *arr, size_t index, int value)
{
    assert(arr);
    assert(index <= arr->size);

    arr->size++;
    int_array_adjust_capacity(arr);

    for (size_t i = arr->size - 1; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[index] = value;
}

static void int_array_remove(IntArray *arr, size_t index)
{
    assert(arr);
    assert(index < arr->size);

    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
    int_array_adjust_capacity(arr);
}

static void int_array_clear(IntArray *arr)
{
    assert(arr);

    arr->size = 0;
    int_array_adjust_capacity(arr);
}

static void int_array_free(IntArray *arr)
{
    assert(arr);
    assert(arr->data);

    free(arr->data);
    arr->data     = NULL;
    arr->size     = 0;
    arr->capacity = 0;
}

// == UNIT TEST ===========================

// TODO: init, size, capacity, get, set, adjust_capacity, append, pop, insert,
// remove, clear, free

static void test_int_array(void)
{
    IntArray arr;
    int_array_init(&arr);

    assert(int_array_capacity(&arr) == INITIAL_CAPACITY); // capacity working
    assert(int_array_size(&arr) == 0);                    // size working

    // arr.data = {1, 2, 3};
    for (size_t i = 1; i <= 3; i++) {
        int_array_append(&arr, i);
    }

    size_t size = int_array_size(&arr);
    assert(size == 3); // append working

    for (size_t i = 0; i < size; i++) {
        int value = int_array_get(&arr, i);
        assert(value == 1 + i); // get working
    }

    int_array_set(&arr, 0, 5);
    assert(int_array_get(&arr, 0) == 5); // set working

    int_array_pop(&arr);
    size = int_array_size(&arr);
    assert(size == 2); // pop working

    int_array_insert(&arr, 0, 10);
    assert(int_array_get(&arr, 0) == 10);
    assert(int_array_size(&arr) == 3); // insert working

    int_array_remove(&arr, 0);
    assert(int_array_get(&arr, 0) != 10);
    assert(int_array_size(&arr) == 2); // remove working

    int_array_clear(&arr);
    size = int_array_size(&arr);
    assert(size == 0); // clear working

    int_array_free(&arr);
}

// == MAIN ===========================
int main(void)
{
    test_int_array();

    printf("All checks passed\n");

    return 0;
}
