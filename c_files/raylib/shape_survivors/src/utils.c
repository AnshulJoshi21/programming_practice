#include "utils.h"
#include <assert.h>
#include <stdlib.h>

float randf(const float min, const float max) {
    if (min == max)
        return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float) rand() / (float) RAND_MAX) * (maximum - minimum);
}

void center_and_draw_text(const OriginType type,
                          const char*      text,
                          const Rectangle  bounds,
                          const float      font_size,
                          const float      spacing,
                          const Color      tint) {
    assert(text);

    const Font    font      = GetFontDefault();
    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    Vector2       pos       = (Vector2){0, 0};

    if (type == ORIGIN_TYPE_CENTER)
        pos = (Vector2){
            bounds.x - (text_size.x / 2.0f),
            bounds.y - (text_size.y / 2.0f),
        };
    if (type == ORIGIN_TYPE_TOP_LEFT)
        pos = (Vector2){
            bounds.x + (bounds.width - text_size.x) / 2.0f,
            bounds.y + (bounds.height - text_size.y) / 2.0f,
        };

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}
