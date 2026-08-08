#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const size_t INITIAL_CAPACITY = 4;
static const size_t GROWTH_FACTOR    = 2;
static const size_t SHRINK_FACTOR    = 2;

typedef struct {
    int*   arr;
    size_t size;
    size_t capacity;
} DynamicArray;

void da_init(DynamicArray* da) {
    assert(da);

    da->capacity = INITIAL_CAPACITY;
    da->size     = 0;
    da->arr      = malloc(da->capacity * sizeof(int));
    assert(da->arr);
}

void da_print(DynamicArray* da) {
    assert(da);

    for (size_t i = 0; i < da->size; i++) {
        printf("%d -> ", da->arr[i]);
    }

    printf("None\n");
}

void da_grow(DynamicArray* da) {
    assert(da);
    if (da->size >= da->capacity) {
        size_t new_capacity = da->capacity;
        new_capacity *= GROWTH_FACTOR;

        int* temp = realloc(da->arr, new_capacity * sizeof(int));
        assert(temp);

        da->capacity = new_capacity;
        da->arr      = temp;
    }
}

void da_shrink(DynamicArray* da) {
    assert(da);
    if (da->size > da->capacity / 4)
        return;

    size_t new_capacity = da->capacity;
    new_capacity /= SHRINK_FACTOR;

    if (new_capacity < INITIAL_CAPACITY)
        new_capacity = INITIAL_CAPACITY;

    int* temp = realloc(da->arr, new_capacity * sizeof(int));
    assert(temp);

    da->capacity = new_capacity;
    da->arr      = temp;
}

void da_prepend(DynamicArray* da, const int value) {
    assert(da);

    da->size++;
    da_grow(da);

    for (size_t i = da->size; i > 0; i--) {
        da->arr[i] = da->arr[i - 1];
    }
    da->arr[0] = value;
}

void da_append(DynamicArray* da, const int value) {
    assert(da);

    da->size++;
    da_grow(da);

    da->arr[da->size - 1] = value;
}

void da_insert(DynamicArray* da, const size_t index, const int value) {
    assert(da);
    assert(index < da->size);

    da->size++;
    da_grow(da);

    for (size_t i = da->size; i > index; i--) {
        da->arr[i] = da->arr[i - 1];
    }
    da->arr[index] = value;
}

void da_replace(DynamicArray* da, const size_t index, const int value) {
    assert(da);
    assert(index < da->size);

    da->arr[index] = value;
}

void da_remove_index(DynamicArray* da, const size_t index) {
    assert(da);
    assert(index < da->size);

    for (size_t i = index; i < da->size - 1; i++) {
        da->arr[i] = da->arr[i + 1];
    }
    da->size--;
    da_shrink(da);
}

void da_remove_value(DynamicArray* da, const int value) {
    assert(da);

    for (size_t i = 0; i < da->size - 1; i++) {
        if (da->arr[i] == value) {
            for (size_t j = i; j < da->size; j++) {
                da->arr[j] = da->arr[j + 1];
            }
            da->size--;
            da_shrink(da);
            return;
        }
    }

    printf("Value not found\n");
}

void da_free(DynamicArray* da) {
    assert(da);

    if (da->arr) {
        free(da->arr);
        da->capacity = 0;
        da->size     = 0;
    }
}

int main(void) {
    DynamicArray dynamic_array;
    da_init(&dynamic_array);

    da_append(&dynamic_array, 10);
    da_append(&dynamic_array, 20);
    da_append(&dynamic_array, 30);
    da_append(&dynamic_array, 40);
    da_append(&dynamic_array, 50);
    da_prepend(&dynamic_array, 00);
    da_print(&dynamic_array);

    da_insert(&dynamic_array, 2, 190);
    da_print(&dynamic_array);

    da_replace(&dynamic_array, 2, 20);
    da_print(&dynamic_array);

    da_remove_index(&dynamic_array, 2);
    da_print(&dynamic_array);

    da_remove_value(&dynamic_array, 40);
    da_print(&dynamic_array);

    da_free(&dynamic_array);

    return 0;
}
