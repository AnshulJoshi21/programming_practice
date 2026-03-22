#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

float utils_random_uniform(const float min, const float max);

void utils_draw_grid_background(void);

void utils_center_and_draw_text(const char *text, const Rectangle layout_rect,
                                const int font_size, const Color color);

typedef struct IntervalTimer
{
    float duration;
    float last_time;

} IntervalTimer;

void utils_interval_timer_init(IntervalTimer *it, const float duration);
bool utils_interval_timer_update(IntervalTimer *it);

#endif // UTILS_H
