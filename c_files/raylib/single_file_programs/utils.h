#ifndef UTILS_H
#define UTILS_H

#include <assert.h>
#include <raylib.h>
#include <stdlib.h>

// -- CENTERED TEXT ------------------------//
//
static inline void center_and_draw_text(const char *text, float font_size,
                                        float text_spacing,
                                        Rectangle layout_rect, Color color)
{
    assert(text);

    Font font         = GetFontDefault();
    Vector2 text_size = MeasureTextEx(font, text, font_size, text_spacing);
    Vector2 position  = (Vector2){
        layout_rect.x + layout_rect.width / 2.0f - text_size.x / 2.0f,
        layout_rect.y + layout_rect.height / 2.0f - text_size.y / 2.0f,
    };

    DrawTextEx(font, text, position, font_size, text_spacing, color);
}

// -- SCROLLABLE MENU WITH CENTERED TEXT ------------------------//
//
static inline void scrollable_menu(const char **text_list, const int list_size,
                                   float font_size, float text_spacing,
                                   Rectangle layout_rect, Color color)
{
    assert(text_list);
}

// -- RANDOM FLOATING POINT NUMBER GENERATOR ------------------------//
//
static inline float random_uniform(float min, float max)
{
    return (min + ((float)rand() / RAND_MAX * (max - min)));
}

//-- INTERVAL TIMER ------------------------//
//
typedef struct Timer
{
    float start_time;
    float interval_duration;

} Timer;

static inline void interval_timer_init(Timer *timer, float interval_duration)
{
    assert(timer);
    assert(interval_duration >= 0.0f);

    timer->start_time        = GetTime();
    timer->interval_duration = interval_duration;
}

static inline bool interval_timer_update(Timer *timer)
{
    assert(timer);

    float current_time = GetTime();

    if (current_time - timer->start_time >= timer->interval_duration) {
        timer->start_time = current_time;

        return true;
    }

    return false;
}

#endif // UTILS_H
