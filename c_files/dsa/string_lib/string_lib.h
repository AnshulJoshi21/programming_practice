#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char*  data;
    size_t size;
    size_t capacity;
} String;

/* Lifecycle */
String string_new(const char* text);
String string_copy(const String* string);
void   string_free(String* string);

/* Properties */
size_t string_size(const String* string);
size_t string_capacity(const String* string);
bool   string_empty(const String* string);

/* Memory */
bool string_reserve(String* string, size_t capacity);
bool string_resize(String* string, size_t size);
void string_clear(String* string);

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

#endif
