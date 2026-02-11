#include "../include/game_manager.h"
#include "../include/settings.h"

#include <assert.h>
#include <math.h>

void gm_init(GameManager *gm, const Texture2D spritesheet,
             const Texture2D background_texture)
{
    assert(gm);

    background_init(&gm->background, background_texture);

    player_init(&gm->player, spritesheet);

    gm->camera = (Camera2D){
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = (Vector2){gm->player.transform.position.x,
                            gm->player.transform.position.y},
        .rotation = 0.0f,
        .zoom     = 1.0f};
}

void gm_draw(const GameManager *gm)
{
    assert(gm);

    BeginMode2D(gm->camera);

    background_draw(&gm->background);

    player_draw(&gm->player);

    EndMode2D();
}

void gm_update(GameManager *gm, float dt, Vector2 mouse_pos_world)
{
    assert(gm);

    player_update(&gm->player, dt, mouse_pos_world);

    // update camera target
    float half_w = GetScreenWidth() / 2.0f;
    float half_h = GetScreenHeight() / 2.0f;

    gm->camera.target.x = fmaxf(
        half_w, fminf(gm->player.transform.position.x, MAP_SIZE - half_w));
    gm->camera.target.y = fmaxf(
        half_h, fminf(gm->player.transform.position.y, MAP_SIZE - half_h));
}
