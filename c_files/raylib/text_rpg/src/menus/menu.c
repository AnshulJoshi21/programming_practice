#define _GNU_SOURCE

#include "../../include/menus/menu.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
menu_init(Menu* menu,
          const char* const* arr,
          const int arr_size,
          int font_size,
          int text_gap,
          Rectangle layout_rect)
{
    menu->arr = malloc(arr_size * sizeof(const char*));
    if (menu->arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < arr_size; i++)
    {
        menu->arr[i] = strndup(arr[i], strlen(arr[i]) + 1);
        if (menu->arr[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    menu->arr_size = arr_size;
    menu->font_size = font_size;
    menu->text_gap = text_gap;
    menu->layout_rect = layout_rect;

    menu->selected = 0;
    menu->first_visible_element = 0;
    menu->text_height = font_size + text_gap;
    menu->max_visible_elements = (layout_rect.height - text_gap) / menu->text_height;
    menu->max_visible_text_height =
      (font_size * arr_size) + (text_gap * (arr_size - 1)); // last gap does not count
}

void
menu_draw(Menu* menu)
{
    int last_visible_element = menu->first_visible_element + menu->max_visible_elements;

    for (int i = menu->first_visible_element; i < menu->arr_size && i < last_visible_element; i++)
    {
        int text_width = MeasureText(menu->arr[i], menu->font_size);
        int text_x = menu->layout_rect.x + menu->layout_rect.width / 2 - text_width / 2;
        int text_y = menu->layout_rect.y + menu->layout_rect.height / 2 -
                     menu->max_visible_text_height / 2 +
                     (i - menu->first_visible_element) * menu->text_height;

        menu->color = (i == menu->selected) ? BLACK : GRAY;

        // draw menu items
        DrawText(menu->arr[i], text_x, text_y, menu->font_size, menu->color);

        if (i == menu->selected)
        {
            // draw selection arrow
            DrawText(">", text_x - 30, text_y, menu->font_size, menu->color);
        }
    }
}

void
menu_update(Menu* menu)
{
    if (IsKeyPressed(KEY_UP))
    {
        menu->selected--;
        if (menu->selected <= 0)
        {
            menu->selected = 0;
        }

        if (menu->selected <= menu->first_visible_element)
        {
            menu->first_visible_element = menu->selected;
        }
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        menu->selected++;
        if (menu->selected > menu->arr_size - 1)
        {
            menu->selected = menu->arr_size - 1;
        }

        if (menu->selected >= menu->first_visible_element + menu->max_visible_elements - 1)
        {
            menu->first_visible_element++;
        }
    }
}

void
menu_free(Menu* menu)
{
    for (int i = 0; i < menu->arr_size; i++)
    {
        free(menu->arr[i]);
        menu->arr[i] = NULL;
    }

    free(menu->arr);
    menu->arr = NULL;
}