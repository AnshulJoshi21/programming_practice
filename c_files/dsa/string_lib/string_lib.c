#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 2

// If you're aiming for a true MVP (10–15 functions)
// These would provide the best value:
// Create - done
// Destroy - done
// Length - done
// Copy/Assign - done
// Duplicate
// Append string
// Append character
// Compare
// Equals
// Substring
// Find substring
// Starts with
// Ends with
// Trim
// Get C string
//
// Nice additions later
// Replace
// Split/Join
// Case-insensitive operations
// UTF-8 support
// String formatting (similar to printf)
// Capacity management (reserve, shrink-to-fit)
// Hashing
// Iterator support
// Regex helpers (usually outside the core library)

typedef struct String {
    char*  arr;
    size_t size;
    size_t capacity;
} String;

void string_init(String* str) {
    assert(str);

    str->size     = 0;
    str->capacity = INITIAL_CAPACITY + 1;
    str->arr      = malloc(sizeof(*str->arr) * str->capacity);
    assert(str->arr);

    str->arr[str->size] = '\0';
}

void string_resize(String* str) {
    assert(str);

    size_t new_capacity = str->capacity;

    if ((str->size + 1) == str->capacity) {
        new_capacity *= GROWTH_FACTOR;
    } else if ((str->size + 1) < str->capacity / 4) {
        new_capacity /= SHRINK_FACTOR;
    } else
        return;

    new_capacity++;

    if (new_capacity < INITIAL_CAPACITY + 1) {
        new_capacity = INITIAL_CAPACITY + 1;
    }

    char* temp = realloc(str->arr, sizeof(*str->arr) * new_capacity);
    assert(temp);

    str->arr      = temp;
    str->capacity = new_capacity;
}

void string_grow_capacity(String* str) {
    assert(str);

    if (str->size < str->capacity)
        return;

    str->capacity *= GROWTH_FACTOR;
    str->arr = realloc(str->arr, sizeof(*str->arr) * str->capacity);
    assert(str->arr);
}

void string_shrink_capacity(String* str) {
    assert(str);

    if (str->size >= str->capacity / 4)
        return;

    str->capacity /= SHRINK_FACTOR;
    str->arr = realloc(str->arr, sizeof(*str->arr) * str->capacity);
    assert(str->arr);
}

size_t string_size(String* str) {
    assert(str);

    return str->size;
}

bool string_empty(String* str) {
    assert(str);

    return str->size == 0;
}

void string_clear(String* str) {
    assert(str);

    str->size     = 0;
    str->capacity = INITIAL_CAPACITY + 1;
    str->arr      = realloc(str->arr, sizeof(*str->arr) * str->capacity);
    assert(str->arr);

    str->arr[str->size] = '\0';
}

void string_copy(const String* src, String* dest) {
    assert(src);
    assert(dest);

    dest->capacity = src->capacity;
    dest->size     = src->size;
    dest->arr      = realloc(dest->arr, sizeof(*dest) * dest->capacity);
    assert(dest->arr);

    for (size_t i = 0; i < src->size; i++) {
        src->arr[i] = dest->arr[i];
    }
}

void string_append_c_string(String* str, const char* string) {
    assert(str);
    assert(string);

    size_t old_size = str->size;
    str->size += strlen(string);

    for (size_t i = old_size - 1; i < str->size; i++) {
        str->arr[i] = string[i];
    }
}

void string_free(String* str) {
    assert(str);

    if (str->arr) {
        free(str->arr);
        str->size     = 0;
        str->capacity = 0;
    }
}

int main(void) {
    return 0;
}
