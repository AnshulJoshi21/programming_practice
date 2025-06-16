#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

void
center_and_draw_text(const char* text, int font_size, Rectangle layout_rect, Color color);
void
center_and_draw_text_array(const char** text_array,
                           const int text_array_size,
                           int font_size,
                           int text_gap,
                           Rectangle layout_rect,
                           Color color);

#endif // UTILS_H;