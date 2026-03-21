#include "../include/entities.h"
#include "../include/game_manager.h"
#include "../include/systems.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>

void game_manager_init(GameManager *gm)
{
    assert(gm);

    gm->world     = (World){0};
    gm->player_id = create_player(&gm->world);
    gm->camera    = (Camera2D){
           .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
           .target = (Vector2){0, 0},
           .rotation = 0.0f,
           .zoom     = 1.0f};
}

void game_manager_draw(const GameManager *gm, const Texture2D background,
                       const Texture2D spritesheet)
{
    assert(gm);

    BeginMode2D(gm->camera);

    utils_draw_tiled_background(background);
    system_draw(&gm->world, spritesheet);

    EndMode2D();
}

void game_manager_update(GameManager *gm, const float dt,
                         const Vector2 mouse_pos_world)
{
    assert(gm);

    const Vector2 *player_pos = &gm->world.transform_list[gm->player_id].pos;
    // set player target
    TargetComponent *player_target = &gm->world.target_list[gm->player_id];
    player_target->pos             = &mouse_pos_world;

    system_handle_input(&gm->world);
    system_set_direction(&gm->world);
    system_rotate(&gm->world);
    system_move(&gm->world, dt);
    system_set_bounds(&gm->world);

    // update camera target
    const float half_w = GetScreenWidth() / 2.0f;
    const float half_h = GetScreenHeight() / 2.0f;

    gm->camera.target.x = fmaxf(half_w, fminf(player_pos->x, half_w));
    gm->camera.target.y = fmaxf(half_h, fminf(player_pos->y, half_h));
}
