#include "utils.h"
#include <assert.h>
#include <stdlib.h>

float utils_randf(const float min, const float max) {
    if (min == max)
        return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float) rand() / (float) RAND_MAX) * (maximum - minimum);
}

void utils_draw_centered_text(const OriginType type,
                              const char*      text,
                              const Rectangle  bounds,
                              const float      font_size,
                              const float      spacing,
                              const Color      tint) {
    assert(text);

    const Font    font      = GetFontDefault();
    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    Vector2       pos;

    switch (type) {
        case ORIGIN_TYPE_CENTER:
            pos = (Vector2){
                bounds.x - text_size.x / 2.0f,
                bounds.y - text_size.y / 2.0f,
            };
            break;

        case ORIGIN_TYPE_TOP_LEFT:
            pos = (Vector2){
                bounds.x + (bounds.width - text_size.x) / 2.0f,
                bounds.y + (bounds.height - text_size.y) / 2.0f,
            };
            break;

        default:
            return;
    }

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}
