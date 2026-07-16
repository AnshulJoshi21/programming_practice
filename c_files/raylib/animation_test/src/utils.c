#include "utils.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

int utils_min_int(const int a, const int b) {
    return (a < b) ? a : b;
}

int utils_max_int(const int a, const int b) {
    return (a > b) ? a : b;
}

float utils_randf(const float min, const float max) {
    if (min == max)
        return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float) rand() / (float) RAND_MAX) * (maximum - minimum);
}

void utils_center_and_draw_text(const OriginType type,
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
        case ORIGIN_CENTER:
            pos = (Vector2){
                bounds.x - text_size.x / 2.0f,
                bounds.y - text_size.y / 2.0f,
            };
            break;
        case ORIGIN_TOP_LEFT:
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

void utils_draw_progress_bar(const int       min,
                             const int       max,
                             const Rectangle bounds,
                             const float     line_thickness,
                             const Color     line_color,
                             const Color     bg_color,
                             const Color     fill_color) {
    // background rect
    DrawRectangleRec(bounds, bg_color);

    // progress rect
    float progress_width = ((float) min / (float) max) * bounds.width;
    progress_width       = fmaxf(0, fminf(progress_width, bounds.width));

    const Rectangle progress_rect = (Rectangle){bounds.x, bounds.y, progress_width, bounds.height};
    DrawRectangleRec(progress_rect, fill_color);

    // outline rect
    DrawRectangleLinesEx(bounds, line_thickness, line_color);
}
