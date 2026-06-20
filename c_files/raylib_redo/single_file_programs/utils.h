#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

float randf(const float min, const float max);

typedef enum OriginType {
    ORIGIN_CENTER,
    ORIGIN_TOP_LEFT,

} OriginType;

void center_and_draw_text(const OriginType type,
                          const Rectangle  bounds,
                          const char*      text,
                          const float      font_size,
                          const float      spacing,
                          const Color      tint);

#endif // UTILS_H
