#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

typedef enum {
    ORIGIN_TYPE_CENTER,
    ORIGIN_TYPE_TOP_LEFT,
} OriginType;

float randf(const float min, const float max);

void draw_centered_text(const OriginType type,
                        const char*      text,
                        const Rectangle  bounds,
                        const float      font_size,
                        const float      spacing,
                        const Color      tint);

#endif // UTILS_H
