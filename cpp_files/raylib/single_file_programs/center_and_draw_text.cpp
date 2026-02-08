#include "center_and_draw_text.h"

#include <cassert>

void center_and_draw_text(const char *text, Rectangle layout_rect, Font font,
                          float font_size, float spacing, Color color)
{
    assert(text);

    Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    Vector2 pos       = (Vector2){
        layout_rect.x + layout_rect.width / 2.0f - text_size.x / 2.0f,
        layout_rect.y + layout_rect.height / 2.0f - text_size.y / 2.0f,
    };

    DrawTextEx(font, text, pos, font_size, spacing, color);
}
