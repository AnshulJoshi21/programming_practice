#include "utils.h"

#include <assert.h>
#include <stdlib.h>

float random_float(const float min, const float max) {
    if (min == max) {
        return min;
    }

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float) rand() / (float) RAND_MAX) * (maximum - minimum);
}

void center_and_draw_text(const OriginType type, const char* text, const Rectangle layout_rect,
                          const float font_size, const float spacing, const Color tint) {
    assert(text);

    const Font font = GetFontDefault();
    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    Vector2 pos;

    if (type == ORIGIN_CENTER) {
        pos = (Vector2){
            layout_rect.x - (text_size.x / 2.0f),
            layout_rect.y - (text_size.y / 2.0f),
        };
    } else if (type == ORIGIN_TOP_LEFT) {
        pos = (Vector2){
            layout_rect.x + (layout_rect.width - text_size.x) / 2.0f,
            layout_rect.y + (layout_rect.height - text_size.y) / 2.0f,
        };
    }

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}

void draw_progress_bar(const int maxValue, int currentValue, const Rectangle bounds,
                       const float borderThickness, const Color backgroundColor,
                       const Color borderColor, const Color fillColor) {
    // Draw background
    DrawRectangleRec(bounds, backgroundColor);

    // Calculate filled width based on progress
    float filledWidth = ((float) currentValue / (float) maxValue) * bounds.width;

    Rectangle fillRect = {bounds.x, bounds.y, filledWidth, bounds.height};

    // Draw progress fill
    DrawRectangleRec(fillRect, fillColor);

    // Draw border
    DrawRectangleLinesEx(bounds, borderThickness, borderColor);
}
