#ifndef STARFIELD_H
#define STARFIELD_H

#include "sprite_data.h"

#define MAX_STARS 150

typedef struct Star
{
    SpriteData sprite_name;
    Vector2 pos;
    float parallax;
    float phase_offset;
    Color color;

} Star;

typedef struct Starfield
{
    Star star_list[MAX_STARS];

} Starfield;

void starfield_init(Starfield *sf);
void starfield_draw(const Starfield *sf, const Texture2D spritesheet,
                    const Camera2D camera);

#endif // STARFIELD_H
