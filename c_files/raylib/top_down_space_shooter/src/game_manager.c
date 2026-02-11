#include "../include/game_manager.h"
#include "../include/settings.h"

#include <assert.h>

void gm_init(GameManager *gm, const Texture2D spritesheet)
{
    assert(gm);

    gm->camera = (Camera2D){
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1.0f};
}

void gm_draw(const GameManager *gm, const Texture2D background_texture)
{
    assert(gm);

    // draw game map background
    Rectangle background_source =
        (Rectangle){0, 0, background_texture.width, background_source.height};
    Rectangle background_dest = (Rectangle){0, 0, MAP_SIZE, MAP_SIZE};
    Vector2 background_origin = (Vector2){0, 0};

    DrawTexturePro(background_texture, background_source, background_dest,
                   background_origin, 0.0f, WHITE);
}

void gm_update(GameManager *gm, float dt, Vector2 mouse_pos_world)
{
    assert(gm);
}
