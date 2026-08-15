#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

float randf(const float min, const float max);

typedef enum OriginType {
    ORIGIN_CENTER,
    ORIGIN_TOP_LEFT,
} OriginType;

void draw_centered_text(const OriginType origin,
                        const Font       font,
                        const char*      text,
                        const Rectangle  bounds,
                        const float      font_size,
                        const float      spacing,
                        const Color      tint);

#endif // UTILS_H
