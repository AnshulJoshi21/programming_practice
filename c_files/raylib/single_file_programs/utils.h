#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

static inline void center_and_draw_text(const char *text, float font_size, float text_spacing,
                                        Rectangle layout_rect, Color color)
{
    if (!text)
        return;

    Font font         = GetFontDefault();
    Vector2 text_size = MeasureTextEx(font, text, font_size, text_spacing);
    Vector2 position  = (Vector2){
        layout_rect.x + layout_rect.width / 2.0f - text_size.x / 2.0f,
        layout_rect.y + layout_rect.height / 2.0f - text_size.y / 2.0f,
    };

    DrawTextEx(font, text, position, font_size, text_spacing, color);
}

#endif // UTILS_H
