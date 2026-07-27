#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

typedef enum OriginType {
    ORIGIN_TYPE_CENTER,
    ORIGIN_TYPE_TOP_LEFT,
} OriginType;

float utils_randf(const float min, const float max);

void utils_draw_centered_text(const OriginType type,
                              const char*      text,
                              const Rectangle  bounds,
                              const float      font_size,
                              const float      spacing,
                              const Color      tint);

#endif // UTILS_H
