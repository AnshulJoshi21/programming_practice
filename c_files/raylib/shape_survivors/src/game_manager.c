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

    gm->world       = (World){0};
    gm->player_id   = create_player(&gm->world);
    gm->enemy_count = 0;
    utils_interval_timer_init(&gm->enemy_interval_timer, ENEMY_SPAWN_RATE);
    gm->bullet_count = 0;
    utils_interval_timer_init(&gm->bullet_interval_timer, BULLET_SPAWN_RATE);

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

    utils_draw_grid_background();
    system_draw(&gm->world);

    EndMode2D();
}

void game_manager_update(GameManager *gm, const float dt)
{
    assert(gm);

    const Vector2 *player_pos = &gm->world.position_list[gm->player_id].pos;

    // spawn enemy
    if (gm->enemy_count < 0)
        gm->enemy_count = 0;

    if (gm->enemy_count < MAX_ENEMIES) {

        if (gm->enemy_count == 0 ||
            utils_interval_timer_update(&gm->enemy_interval_timer)) {

            create_enemy(&gm->world, player_pos);
            gm->enemy_count++;
        }
    }

    // spawn bullet
    if (gm->bullet_count < 0)
        gm->bullet_count = 0;

    const Vector2 mouse_pos = GetMousePosition();

    if (gm->bullet_count < MAX_BULLETS) {

        if (utils_interval_timer_update(&gm->bullet_interval_timer)) {

            create_bullet(&gm->world, *player_pos, &mouse_pos);
            gm->bullet_count++;
        }
    }

    system_handle_input(&gm->world);
    system_set_direction(&gm->world);
    system_move(&gm->world, dt);
    system_set_bounds(&gm->world);
    system_despawner(&gm->world, &gm->enemy_count);

    // update camera target
    const float half_w = GetScreenWidth() / 2.0f;
    const float half_h = GetScreenHeight() / 2.0f;

    gm->camera.target.x =
        fmaxf(half_w, fminf(player_pos->x, MAP_SIZE - half_w));
    gm->camera.target.y =
        fmaxf(half_h, fminf(player_pos->y, MAP_SIZE - half_h));
}
