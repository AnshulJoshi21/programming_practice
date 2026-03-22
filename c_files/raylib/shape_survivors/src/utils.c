#include "../include/settings.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

float utils_random_uniform(const float min, const float max)
{
    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    if (min == max)
        return min;

    return minimum + ((float)rand() / (float)RAND_MAX) * (maximum - minimum);
}

void utils_draw_grid_background(void)
{
    float thickness        = 2.0f;
    Color color            = LIGHTGRAY;
    const float block_size = 30.0f;

    // vertical lines
    for (float x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_SIZE}, thickness, color);
    }
    // horizontal lines
    for (float y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_SIZE, y}, thickness, color);
    }
}

void utils_center_and_draw_text(const char *text, const Rectangle layout_rect,
                                const int font_size, const Color color)
{
    assert(text);

    const float text_width = MeasureText(text, font_size);
    const int x = layout_rect.x + (layout_rect.width - text_width) / 2.0f;
    const int y = layout_rect.y + (layout_rect.height - font_size) / 2.0f;

    DrawText(text, x, y, font_size, color);
}

void utils_interval_timer_init(IntervalTimer *it, const float duration)
{
    assert(it);

    it->duration  = duration;
    it->last_time = GetTime();
}

bool utils_interval_timer_update(IntervalTimer *it)
{
    assert(it);

    const float current_time = GetTime();
    if (current_time - it->last_time >= it->duration) {
        it->last_time = current_time;

        return true;
    }

    return false;
}
