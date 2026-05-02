#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

typedef enum {
  ORIGIN_CENTER,
  ORIGIN_TOP_LEFT,

} OriginType;

float random_float(const float min, const float max);

void center_and_draw_text(const OriginType type, const char *text,
                          const Rectangle bounds, const float font_size,
                          const float spacing, const Color tint);

void draw_progress_bar(const int min, const int max, const Rectangle bounds,
                       const float border_thickness, const Color bg_color,
                       const Color fill_color, const Color border_color);

#endif // UTILS_H
