#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

typedef enum OriginType {
    ORIGIN_CENTER,
    ORIGIN_TOP_LEFT,

} OriginType;

int utils_min_int(const int a, const int b);
int utils_max_int(const int a, const int b);

float utils_randf(const float min, const float max);

void utils_center_and_draw_text(const OriginType type,
                                const char*      text,
                                const Rectangle  rect,
                                const float      font_size,
                                const float      spacing,
                                const Color      tint);

void utils_draw_progress_bar(const int       min,
                             const int       max,
                             const Rectangle bounds,
                             const float     line_thickness,
                             const Color     line_color,
                             const Color     bg_color,
                             const Color     fill_color);

#endif // UTILS_H
