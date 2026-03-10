#ifndef STARFIELD_H
#define STARFIELD_H

#include <raylib.h>

#define MAX_STARS 100

typedef struct Star
{
    int name;
    Vector2 pos;
    float parallax; // near(0.1f) and far(1.0f)
    float phase;    // random offset for twinkling
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
