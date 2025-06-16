#include "../include/utils.h"

void
center_and_draw_text(const char* text, int font_size, Rectangle layout_rect, Color color)
{
    int text_width = MeasureText(text, font_size);
    int text_x = ( int ) (layout_rect.x + layout_rect.width / 2 - text_width / 2);
    int text_y = ( int ) (layout_rect.y + layout_rect.height / 2 - font_size / 2);

    DrawText(text, text_x, text_y, font_size, color);
}

void
center_and_draw_text_array(const char** text_array,
                           const int text_array_size,
                           int font_size,
                           int text_gap,
                           Rectangle layout_rect,
                           Color color)

{
    int text_height = font_size + text_gap;
    int max_visible_elements_height =
      (font_size * text_array_size) + (text_gap * (text_array_size - 1));

    for (int i = 0; i < text_array_size; i++)
    {
        int text_width = MeasureText(text_array[i], font_size);
        int text_x = ( int ) (layout_rect.x + layout_rect.width / 2 - text_width / 2);
        int text_y = ( int ) (layout_rect.y + layout_rect.height / 2 -
                              max_visible_elements_height / 2 + (i * text_height));

        DrawText(text_array[i], text_x, text_y, font_size, color);
    }
}
