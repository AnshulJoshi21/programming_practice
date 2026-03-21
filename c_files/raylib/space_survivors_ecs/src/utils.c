#include "../include/settings.h"
#include "../include/sprite_data.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

Rectangle get_source_rect(const World *world, const int id)
{
    assert(world);
    assert(id >= 0 && id < world->enttity_count);

    return sprite_db[world->sprite_list[id].current_sprite];
}

Rectangle get_dest_rect(const World *world, const int id)
{
    assert(world);
    assert(id >= 0 && id < world->enttity_count);

    const Rectangle source              = get_source_rect(world, id);
    const TransformComponent *transform = &world->transform_list[id];

    return (Rectangle){transform->pos.x, transform->pos.y,
                       source.width * transform->scale.x,
                       source.height * transform->scale.y};
}

Vector2 get_origin_vector(const World *world, const int id)
{
    assert(world);
    assert(id >= 0 && id < world->enttity_count);

    const Rectangle dest = get_dest_rect(world, id);

    return (Vector2){dest.width / 2.0f, dest.height / 2.0f};
}

float random_uniform(const float min, const float max)
{
    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    if (min == max)
        return min;

    return minimum + ((float)rand() / (float)RAND_MAX) * (maximum - minimum);
}

void utils_draw_background(const Texture2D background)
{
    for (int y = 0; y < MAP_SIZE; y += background.height) {
        for (int x = 0; x < MAP_SIZE; x += background.width) {

            DrawTexture(background, x, y, WHITE);
        }
    }
}

// INTERVAL TIMERS
//
void interval_timer_init(IntervalTimer *timer, const int interval_duration)
{
    assert(timer);

    timer->last_time         = GetTime();
    timer->interval_duration = interval_duration;
}

bool interval_timer_update(IntervalTimer *timer)
{
    assert(timer);

    const float current_time = GetTime();
    if (current_time - timer->last_time >= timer->interval_duration) {
        timer->last_time = current_time;

        return true;
    }

    return false;
}
