#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef struct Menu
{
    char** arr;
    int arr_size;
    int selected;
    int first_visible_element;
    int max_visible_elements;
    int max_visible_text_height;
    int font_size;
    int text_gap;
    int text_height;
    Rectangle layout_rect;
    Color color;

} Menu;

void
menu_init(Menu* menu,
          const char* const* arr,
          const int arr_size,
          int font_size,
          int text_gap,
          Rectangle layout_rect);
void
menu_draw(Menu* menu);
void
menu_update(Menu* menu);
void
menu_free(Menu* menu);

#endif // MENU_H;