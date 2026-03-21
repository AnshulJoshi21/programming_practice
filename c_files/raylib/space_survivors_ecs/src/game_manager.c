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
    interval_timer_init(&gm->enemy_spawn_timer, ENEMY_SPAWN_RATE);

    gm->camera = (Camera2D){
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

    utils_draw_background(background);
    system_draw(&gm->world, spritesheet);

    EndMode2D();
}

static void set_player_target(GameManager *gm, Vector2 mouse_pos_world)
{
    assert(gm);

    TargetComponent *player_target  = &gm->world.target_list[gm->player_id];
    player_target->pos              = &mouse_pos_world;
    player_target->continous_update = true;
}

static void update_camera_target(GameManager *gm, const Vector2 player_pos)
{
    assert(gm);

    const float half_w = GetScreenWidth() / 2.0f;
    const float half_h = GetScreenHeight() / 2.0f;

    gm->camera.target.x = fmaxf(half_w, fminf(player_pos.x, MAP_SIZE - half_w));
    gm->camera.target.y = fmaxf(half_h, fminf(player_pos.y, MAP_SIZE - half_h));
}

void game_manager_update(GameManager *gm, const float dt,
                         const Vector2 mouse_pos_world)
{
    assert(gm);

    const Vector2 player_pos = gm->world.transform_list[gm->player_id].pos;

    // spawn enemies
    if (gm->enemy_count < MAX_ENEMIES) {

        for (int id = 0; id < gm->world.enttity_count; id++) {

            if (gm->enemy_count <= 0 ||
                interval_timer_update(&gm->enemy_spawn_timer)) {

                create_enemy(&gm->world, player_pos);
                gm->enemy_count++;
            }
        }
    }

    set_player_target(gm, mouse_pos_world);

    system_handle_input(&gm->world);
    system_set_direction(&gm->world);
    system_rotate(&gm->world);
    system_move(&gm->world, dt);
    system_set_bounds(&gm->world);

    update_camera_target(gm, player_pos);
}
