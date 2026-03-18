#include "../include/entities.h"
#include "../include/game_manager.h"
#include "../include/settings.h"
#include "../include/systems.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>

void game_manager_init(GameManager *gm)
{
    assert(gm);

    gm->world = (World){0};

    gm->player_id = create_player(&gm->world);

    gm->camera = (Camera2D){
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1.0f};
}

void game_manager_draw(const GameManager *gm)
{
    assert(gm);

    BeginMode2D(gm->camera);

    utils_draw_background_grid();

    system_draw(&gm->world);

    EndMode2D();
}

void game_manager_update(GameManager *gm, const float dt)
{
    assert(gm);

    system_handle_update(&gm->world);
    system_move(&gm->world, dt);
    system_set_bounds(&gm->world);

    // update camera target
    const Vector2 *player_pos = &gm->world.pos_list[gm->player_id].pos;
    const float half_w        = GetScreenWidth() / 2.0f;
    const float half_h        = GetScreenHeight() / 2.0f;

    gm->camera.target.x =
        fmaxf(half_w, fminf(player_pos->x, MAP_SIZE - half_w));
    gm->camera.target.y =
        fmaxf(half_h, fminf(player_pos->y, MAP_SIZE - half_h));
}
