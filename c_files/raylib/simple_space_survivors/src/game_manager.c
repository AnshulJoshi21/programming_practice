#include "../include/game_manager.h"
#include "../include/settings.h"
#include "../include/starfield.h"

#include <assert.h>
#include <math.h>

void game_manager_init(GameManager *gm, const Texture2D spritesheet)
{
    assert(gm);

    player_init(&gm->player, spritesheet);

    gm->camera = (Camera2D){
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = (Vector2){gm->player.dest.x, gm->player.dest.y},
        .rotation = 0.0f,
        .zoom     = 1.0f};

    starfield_init(&gm->starfield);
}

void game_manager_draw(const GameManager *gm, const Texture2D spritesheet)
{
    assert(gm);

    BeginMode2D(gm->camera);

    starfield_draw(&gm->starfield, spritesheet, gm->camera);

    player_draw(&gm->player);

    EndMode2D();
}

void game_manager_update(GameManager *gm, const float dt)
{
    assert(gm);

    player_update(&gm->player, dt, GetMousePosition());

    // update camera target
    float half_w = GetScreenWidth() / 2.0f;
    float half_h = GetScreenHeight() / 2.0f;

    gm->camera.target.x =
        fmaxf(half_w, fminf(gm->player.dest.x, MAP_SIZE - half_w));
    gm->camera.target.y =
        fmaxf(half_h, fminf(gm->player.dest.y, MAP_SIZE - half_h));
}
