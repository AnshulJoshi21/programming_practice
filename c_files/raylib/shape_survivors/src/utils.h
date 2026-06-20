#pragma once

#include <raylib.h>

float randf(const float min, const float max);

typedef enum {
    ORIGIN_TYPE_CENTER,
    ORIGIN_TYPE_TOP_LEFT,
} OriginType;

void center_and_draw_text(const OriginType type,
                          const char*      text,
                          const Rectangle  bounds,
                          const float      font_size,
                          const float      spacing,
                          const Color      tint);
