#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 4
#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 2

typedef struct DynamicArray {
    int*   arr;
    size_t size;
    size_t capacity;
} DynamicArray;

void da_init(DynamicArray* da) {
    assert(da);

    da->size     = 0;
    da->capacity = INITIAL_CAPACITY;

    da->arr = malloc(sizeof(*da->arr) * da->capacity);
    assert(da->arr != NULL);
}

void da_resize(DynamicArray* da, size_t new_capacity) {
    assert(da);

    if (new_capacity < INITIAL_CAPACITY)
        new_capacity = INITIAL_CAPACITY;

    int* temp = realloc(da->arr, sizeof(*temp) * da->capacity);
    assert(temp != NULL);

    da->arr      = temp;
    da->capacity = new_capacity;
}

void da_print(DynamicArray* da) {
    assert(da);

    printf("[");
    for (size_t i = 0; i < da->size; i++) {
        printf("%d", da->arr[i]);

        if (i < (da->size - 1)) {
            printf(",");
        }
    }

    printf("]\n");
}

void da_prepend(DynamicArray* da, const int value) {
    assert(da);

    if (da->size == da->capacity)
        da_resize(da, da->capacity * GROWTH_FACTOR);

    for (size_t i = da->size; i > 0; i--) {
        da->arr[i] = da->arr[i - 1];
    }
    da->arr[0] = value;
    da->size++;
}

void da_append(DynamicArray* da, const int value) {
    assert(da);

    if (da->size == da->capacity)
        da_resize(da, da->capacity * GROWTH_FACTOR);

    da->arr[da->size] = value;
    da->size++;
}

void da_pop(DynamicArray* da) {
    assert(da);

    da->size--;
    if (da->size < da->capacity / 4)
        da_resize(da, da->capacity / SHRINK_FACTOR);
}

void da_remove_index(DynamicArray* da, const size_t index) {
    assert(da);
    assert(index < da->size);

    for (size_t i = 0; i < da->size; i++) {
        if (i == index) {
            for (size_t j = i; j < da->size - 1; j++) {
                da->arr[j] = da->arr[j + 1];
            }

            da->size--;
            if (da->size < da->capacity / 4)
                da_resize(da, da->capacity / SHRINK_FACTOR);
            return;
        }
    }

    printf("Index: %zu, not found in array\n", index);
}

void da_remove_value(DynamicArray* da, const int value) {
    assert(da);

    for (int i = 0; i < da->size; i++) {
        if (da->arr[i] == value) {
            for (size_t j = i; j < da->size - 1; j++) {
                da->arr[j] = da->arr[j + 1];
            }

            da->size--;
            if (da->size < da->capacity / 4)
                da_resize(da, da->capacity / SHRINK_FACTOR);
            return;
        }
    }

    printf("Value: %d, not found in array\n", value);
}

void da_free(DynamicArray* da) {
    if (da && da->arr) {
        free(da->arr);
        da->arr      = NULL;
        da->size     = 0;
        da->capacity = 0;
    }
}

int main(void) {
    DynamicArray da;
    da_init(&da);

    da_print(&da);

    da_append(&da, 2);
    da_append(&da, 3);
    da_append(&da, 4);
    da_append(&da, 5);
    da_append(&da, 6);
    da_append(&da, 7);
    da_append(&da, 8);
    da_prepend(&da, 1);
    da_print(&da);

    da_pop(&da);
    da_print(&da);

    da_remove_index(&da, 2);
    da_print(&da);

    da_remove_value(&da, 5);
    da_print(&da);

    da_free(&da);

    return 0;
}
