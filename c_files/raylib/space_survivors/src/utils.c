#include "../include/settings.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

float random_uniform(const float min, const float max)
{
    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    if (min == max)
        return min;

    return minimum + ((float)rand() / (float)RAND_MAX) * (maximum - minimum);
}

void utils_draw_tiled_background(const Texture2D background)
{
    for (uint16_t y = 0; y < MAP_SIZE; y += background.height) {
        for (uint16_t x = 0; x < MAP_SIZE; x += background.width) {
            DrawTexture(background, x, y, WHITE);
        }
    }
}

Rectangle utils_get_dest_rect(const Vector2 pos, const Vector2 scale,
                              const Rectangle source)
{
    return (Rectangle){pos.x, pos.y, source.width * scale.x,
                       source.height * scale.y};
}
