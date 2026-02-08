#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

void center_and_draw_text(const char *text, float font_size, float text_spacing,
                          Rectangle layout_rect, Color color);

void scrollable_menu(const char **text_list, const int list_size,
                     float font_size, float text_spacing, float line_gap,
                     Rectangle layout_rect, Color color);

typedef struct Timer
{
    float start_time;
    float interval_duration;

} Timer;

void interval_timer_init(Timer *timer, float interval_duration);
bool interval_timer_update(Timer *timer);

#endif // UTILS_H
