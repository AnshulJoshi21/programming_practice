#include <raylib.h>

void
center_and_draw_text(const char* text, int font_size, Rectangle layout_rect, Color color = BLACK)
{
    int text_width = MeasureText(text, font_size);
    int text_x = layout_rect.x + layout_rect.width / 2 - text_width / 2;
    int text_y = layout_rect.y + layout_rect.height / 2 - font_size / 2;

    DrawText(text, text_x, text_y, font_size, color);
}