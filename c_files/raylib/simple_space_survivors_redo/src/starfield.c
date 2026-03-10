#include "../include/settings.h"
#include "../include/starfield.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>

static const float parallax_table[] = {
    [SPRITE_STAR_MEDIUM] = 0.8f,
    [SPRITE_STAR_SMALL]  = 0.5f,
    [SPRITE_STAR_TINY]   = 0.2f,
};

static inline float wrapf(const float value, const float max)
{
    float tmp = fmodf(value, max);
    if (tmp < 0)
        tmp += max;

    return tmp;
}

void starfield_init(Starfield *sf)
{
    assert(sf);

    for (int i = 0; i < MAX_STARS; i++) {
        Star *s = &sf->star_list[i];

        s->sprite_name = GetRandomValue(SPRITE_STAR_MEDIUM, SPRITE_STAR_TINY);

        s->pos.x = random_uniform(0, MAP_SIZE);
        s->pos.y = random_uniform(0, MAP_SIZE);

        s->parallax = parallax_table[s->sprite_name];

        s->phase_offset = random_uniform(0, 2 * PI);

        unsigned char brightness = GetRandomValue(150, 255);

        s->color = (Color){brightness, brightness, brightness, 255};
    }
}

void starfield_draw(const Starfield *sf, const Texture2D spritesheet,
                    const Camera2D camera)
{
    assert(sf);

    for (int i = 0; i < MAX_STARS; i++) {
        const Star *s = &sf->star_list[i];

        const Rectangle source = sprite_db[s->sprite_name];

        Vector2 draw_pos = (Vector2){
            s->pos.x - (camera.target.x * s->parallax),
            s->pos.y - (camera.target.y * s->parallax),
        };

        draw_pos.x = wrapf(draw_pos.x, MAP_SIZE);
        draw_pos.y = wrapf(draw_pos.y, MAP_SIZE);

        const float time = GetTime();

        // base + amplitude * sin(time * 2.0f + phase)
        const float base      = 0.4f;
        const float amplitude = 0.3f;
        const float twinkle =
            base + amplitude * sinf(time * 2.0f + s->phase_offset);

        Color color = s->color;
        color.a     = (unsigned char)(twinkle * 255);

        DrawTextureRec(spritesheet, source, draw_pos, color);
    }
}
