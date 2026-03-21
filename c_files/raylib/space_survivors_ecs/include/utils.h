#ifndef UTILS_H
#define UTILS_H

#include "ecs.h"

#include <raylib.h>

Rectangle get_source_rect(const World *world, const int id);
Rectangle get_dest_rect(const World *world, const int id);
Vector2 get_origin_vector(const World *world, const int id);

float random_uniform(const float min, const float max);

void utils_draw_background(const Texture2D background);

typedef struct IntervalTimer
{
    float last_time;
    float interval_duration;

} IntervalTimer;

void interval_timer_init(IntervalTimer *timer, const int interval_duration);
bool interval_timer_update(IntervalTimer *timer);

#endif // UTILS_H
