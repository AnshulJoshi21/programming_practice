#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>
#include <stdint.h>

float random_uniform(const float min, const float max);

void utils_draw_tiled_background(const Texture2D background);

Rectangle utils_get_dest_rect(const Vector2 pos, const Vector2 scale,
                              const Rectangle source);

#endif // UTILS_H
