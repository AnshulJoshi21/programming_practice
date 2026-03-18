#include "../include/settings.h"
#include "../include/utils.h"

#include <assert.h>

void utils_draw_background_grid(void)
{
    const float thickness  = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = 30.0f;

    // vertical lines
    for (int x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_SIZE}, thickness, color);
    }

    // horizontal lines
    for (int y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_SIZE, y}, thickness, color);
    }
}

void center_and_draw_text(const char *text, const Rectangle layout_rect,
                          const float font_size, const float spacing,
                          const Color tint)
{
    assert(text);

    const Font font = GetFontDefault();

    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    const Vector2 pos       = (Vector2){
        layout_rect.x + (layout_rect.width - text_size.x) / 2.0f,
        layout_rect.y + (layout_rect.height - text_size.y) / 2.0f,
    };

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}
