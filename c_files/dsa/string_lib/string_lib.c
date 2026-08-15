// NOTE: size + 1 <= capacity;
// NOTE: data[size] = '\0';

#include "string_lib.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const size_t INITIAL_CAPACITY = 10;
static const size_t GROWTH_FACTOR    = 2;
static const size_t SHRINK_FACTOR    = 2;

/* Lifecycle */

String string_new(const char* text) {
    assert(text);

    size_t text_size = 0;
    while (text[text_size] != '\0') {
        text_size++;
    }

    String string;
    string.size     = text_size;
    string.capacity = INITIAL_CAPACITY;

    while (string.size + 1 >= string.capacity)
        string.capacity *= GROWTH_FACTOR;

    string.data = malloc(string.capacity);
    assert(string.data);

    for (size_t i = 0; i < text_size; i++) {
        string.data[i] = text[i];
    }
    string.data[string.size] = '\0';

    return string;
}

String string_copy(const String* string) {
    assert(string);

    String new_string;
    new_string.size     = string->size;
    new_string.capacity = string->capacity;
    new_string.data     = malloc(new_string.capacity);
    assert(new_string.data);

    for (size_t i = 0; i < new_string.size; i++) {
        new_string.data[i] = string->data[i];
    }
    new_string.data[new_string.size] = '\0';

    return new_string;
}

void string_free(String* string) {
    assert(string);

    free(string->data);

    string->data     = NULL;
    string->size     = 0;
    string->capacity = 0;
}

/* Properties */
size_t string_size(const String* string) {
    assert(string);
    return string->size;
}

size_t string_capacity(const String* string) {
    assert(string);
    return string->capacity;
}

bool string_empty(const String* string) {
    assert(string);
    return string->size == 0;
}

/* Memory */
bool string_reserve(String* string, size_t capacity) {
    if (capacity <= string->capacity)
        return true;

    char* temp = realloc(string->data, capacity);
    if (temp == NULL)
        return false;

    string->capacity = capacity;
    string->data     = temp;

    return true;
}

bool string_resize(String* string, size_t size) {
    assert(string);

    size_t new_capacity = string->capacity;
    while (size + 1 >= new_capacity) {
        new_capacity *= GROWTH_FACTOR;
    }

    if (new_capacity != string->capacity) {
        char* temp = realloc(string->data, new_capacity);
        if (temp == NULL)
            return false;

        string->capacity = new_capacity;
        string->data     = temp;
    }

    string->size               = size;
    string->data[string->size] = '\0';

    return true;
}

void string_clear(String* string) {
    assert(string);

    string->size               = 0;
    string->data[string->size] = '\0';
}

/* Append / insert / remove */
bool string_append(String* string, const String* other);
bool string_append_cstr(String* string, const char* text);
bool string_push(String* string, char c);

bool string_insert(String* string, size_t index, const String* other);
bool string_insert_cstr(String* string, size_t index, const char* text);

bool string_remove(String* string, size_t index, size_t count);
bool string_pop(String* string, char* out);

/* Access */
char*       string_at(String* string, size_t index);
const char* string_cstr(const String* string);

/* Comparison */
int  string_compare(const String* a, const String* b);
bool string_equal(const String* a, const String* b);
bool string_startswith(const String* string, const String* prefix);
bool string_endswith(const String* string, const String* suffix);

/* Search */
size_t string_find(const String* string, const String* substring);
size_t string_rfind(const String* string, const String* substring);
bool   string_contains(const String* string, const String* substring);
size_t string_count(const String* string, const String* substring);

/* Modification */
bool string_replace(String* string, const String* old_str, const String* new_str);

void string_reverse(String* string);

/* Case */
void string_lower(String* string);
void string_upper(String* string);
void string_swapcase(String* string);

/* Whitespace */
void string_strip(String* string);
void string_lstrip(String* string);
void string_rstrip(String* string);

/* Split / join */
String* string_split(const String* string, const String* separator, size_t* count);

String string_join(const String* separator, const String* strings, size_t count);

/* Character classification */
bool string_isalpha(const String* string);
bool string_isdigit(const String* string);
bool string_isalnum(const String* string);
bool string_isspace(const String* string);
bool string_islower(const String* string);
bool string_isupper(const String* string);

/* Conversion */
String string_from_int(long value);
String string_from_double(double value);

long   string_to_int(const String* string, bool* success);
double string_to_double(const String* string, bool* success);
