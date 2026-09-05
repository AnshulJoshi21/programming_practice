#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const int INITIAL_CAPACITY = 4;
static const int GROWTH_FACTOR    = 2;
static const int SHRINK_FACTOR    = 2;

typedef struct {
    int* arr;
    int  size;
    int  capacity;
} DynamicArray;

static void da_init(DynamicArray* da) {
    assert(da);

    da->size     = 0;
    da->capacity = INITIAL_CAPACITY;
    da->arr      = malloc(sizeof(int) * da->capacity);
    assert(da->arr);
}

static void da_resize(DynamicArray* da) {
    assert(da);

    da->arr = realloc(da->arr, da->capacity * sizeof(int));
    assert(da->arr);
}

static void da_print(const DynamicArray* da) {
    assert(da);

    for (int i = 0; i < da->size; i++) {
        printf("%d -> ", da->arr[i]);
    }

    printf("none\n");
}

static void da_prepend(DynamicArray* da, const int data) {
    assert(da);

    if (da->size == da->capacity) {
        da->capacity *= GROWTH_FACTOR;
        da_resize(da);
    }

    da->size++;
    for (int i = da->size; i > 0; i--) {
        da->arr[i] = da->arr[i - 1];
    }
    da->arr[0] = data;
}

static void da_append(DynamicArray* da, const int data) {
    assert(da);

    if (da->size == da->capacity) {
        da->capacity *= GROWTH_FACTOR;
        da_resize(da);
    }

    da->arr[da->size++] = data;
}

static void da_insert(DynamicArray* da, const int index, const int data) {
    assert(da);
    assert(index >= 0 && index < da->size);

    if (da->size == da->capacity) {
        da->capacity *= GROWTH_FACTOR;
        da_resize(da);
    }

    da->size++;
    for (int i = da->size; i > index; i--) {
        da->arr[i] = da->arr[i - 1];
    }
    da->arr[index] = data;
}

static void da_pop(DynamicArray* da) {
    assert(da);

    da->size--;
    if (da->size < da->capacity / 4) {
        da->capacity /= SHRINK_FACTOR;
        da->capacity = (da->capacity > INITIAL_CAPACITY) ? da->capacity : INITIAL_CAPACITY;
        da_resize(da);
    }
}

static void da_remove_at(DynamicArray* da, const int index) {
    assert(da);
    assert(index >= 0 && index < da->size);

    for (int i = index; i < da->size - 1; i++) {
        da->arr[i] = da->arr[i + 1];
    }
    da->size--;
    if (da->size < da->capacity / 4) {
        da->capacity /= SHRINK_FACTOR;
        da->capacity = (da->capacity > INITIAL_CAPACITY) ? da->capacity : INITIAL_CAPACITY;
        da_resize(da);
    }
}

static void da_remove(DynamicArray* da, const int data) {
    assert(da);

    for (int i = 0; i < da->size; i++) {
        if (da->arr[i] == data) {
            for (int j = i; j < da->size - 1; j++) {
                da->arr[j] = da->arr[j + 1];
            }
            da->size--;
            if (da->size < da->capacity / 4) {
                da->capacity /= SHRINK_FACTOR;
                da->capacity = (da->capacity > INITIAL_CAPACITY) ? da->capacity : INITIAL_CAPACITY;
                da_resize(da);
            }
            return;
        }
    }

    printf("Data not in array\n");
}

static void da_free(DynamicArray* da) {
    assert(da);
    if (da->arr) {
        free(da->arr);
        da->size     = 0;
        da->capacity = 0;
    }
}

int main(void) {
    DynamicArray arr;
    da_init(&arr);

    da_append(&arr, 1);
    da_append(&arr, 2);
    da_append(&arr, 3);
    da_append(&arr, 4);
    da_append(&arr, 5);
    da_prepend(&arr, 0);
    da_insert(&arr, 3, 10);
    da_pop(&arr);
    da_remove_at(&arr, 1);
    da_remove(&arr, 10);

    da_print(&arr);

    da_free(&arr);

    return 0;
}
