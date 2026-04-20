#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

typedef enum OriginType {
    ORIGIN_CENTER,
    ORIGIN_TOP_LEFT,

} OriginType;

float random_float(const float min, const float max);

void center_and_draw_text(const OriginType type, const char* text, const Rectangle layout_rect,
                          const float font_size, const float spacing, const Color tint);

void draw_progress_bar(const int maxValue, int currentValue, const Rectangle bounds,
                       const float borderThickness, const Color backgroundColor,
                       const Color borderColor, const Color fillColor);

#endif  // UTILS_H
