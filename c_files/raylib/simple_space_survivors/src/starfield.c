#include "../include/settings.h"
#include "../include/sprite_data.h"
#include "../include/starfield.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>

void starfield_init(Starfield *sf)
{
    assert(sf);

    for (int i = 0; i < MAX_STARS; i++) {
        sf->star_list[i].name =
            GetRandomValue(SPRITE_STAR_MEDIUM, SPRITE_STAR_TINY);

        if (sf->star_list[i].name == SPRITE_STAR_TINY)
            sf->star_list[i].parallax = 0.2f;
        else if (sf->star_list[i].name == SPRITE_STAR_SMALL)
            sf->star_list[i].parallax = 0.5f;
        else
            sf->star_list[i].parallax = 0.7f;

        sf->star_list[i].pos.x = random_uniform(0, MAP_SIZE);
        sf->star_list[i].pos.y = random_uniform(0, MAP_SIZE);

        sf->star_list[i].phase = random_uniform(0, 2 * PI);

        int brightness         = GetRandomValue(150, 255);
        sf->star_list[i].color = (Color){brightness, brightness, brightness,
                                         GetRandomValue(100, 255)};
    }
}

void starfield_draw(const Starfield *sf, const Texture2D spritesheet,
                    const Camera2D camera)
{
    assert(sf);

    for (int i = 0; i < MAX_STARS; i++) {
        const Star *star = &sf->star_list[i];

        const Rectangle source = sprite_db[star->name];

        Vector2 draw_pos = (Vector2){
            star->pos.x - (camera.target.x * star->parallax),
            star->pos.y - (camera.target.y * star->parallax),
        };

        // screen wrapping
        draw_pos.x = fmodf(draw_pos.x, MAP_SIZE);
        if (draw_pos.x < 0)
            draw_pos.x += MAP_SIZE;

        draw_pos.y = fmodf(draw_pos.y, MAP_SIZE);
        if (draw_pos.y < 0)
            draw_pos.y += MAP_SIZE;

        // draw
        DrawTextureRec(spritesheet, source, draw_pos, star->color);
    }
}
