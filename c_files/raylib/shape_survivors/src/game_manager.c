#include "game_manager.h"
#include "settings.h"
#include "systems.h"
#include <assert.h>
#include <math.h>

void game_manager_init(GameManager* gm) {
    assert(gm);
    gm->current_state = GAME_STATE_RUNNING;

    player_init(&gm->player);
    enemy_manager_init(&gm->enemy_manager);
    bullet_manager_init(&gm->bullet_manager);
    drop_manager_init(&gm->drop_manager);

    collision_manager_init(&gm->collision_manager,
                           &gm->player,
                           &gm->enemy_manager,
                           &gm->bullet_manager,
                           &gm->drop_manager);

    ui_manager_init(&gm->ui_manager, &gm->player, &gm->enemy_manager);
    upgrade_manager_init(&gm->upgrade_manager, &gm->player);

    gm->camera = (Camera2D){
        .offset   = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
        .target   = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1.0f,
    };
}

static void update_camera(GameManager* gm) {
    assert(gm);

    const float half_w = BASE_WIDTH / 2.0f;
    const float half_h = BASE_HEIGHT / 2.0f;

    gm->camera.target.x = fmaxf(half_w, fminf(gm->player.position.x, MAP_SIZE - half_w));
    gm->camera.target.y = fmaxf(half_h, fminf(gm->player.position.y, MAP_SIZE - half_h));
}

static Vector2 get_player_target(const GameManager* gm) {
    assert(gm);

    float   min_distance = MAP_SIZE * MAP_SIZE;
    Vector2 target       = (Vector2){0, 0};
    for (int i = 0; i < gm->enemy_manager.spawner.current; i++) {
        const Enemy* enemy = &gm->enemy_manager.enemies[i];

        const float dx       = enemy->position.x - gm->player.position.x;
        const float dy       = enemy->position.y - gm->player.position.y;
        const float distance = sqrtf((dx * dx) + (dy * dy));
        if (distance < min_distance) {
            min_distance = distance;
            target       = (Vector2){enemy->position.x, enemy->position.y};
        }
    }

    return target;
}

void game_manager_update(GameManager* gm, const float dt) {
    assert(gm);

    switch (gm->current_state) {
        case GAME_STATE_TITLE:
            break;

        case GAME_STATE_RUNNING: {
            player_update(&gm->player, dt);
            enemy_manager_update(&gm->enemy_manager,
                                 dt,
                                 (Vector2){gm->player.position.x, gm->player.position.y},
                                 &gm->drop_manager);
            bullet_manager_update(&gm->bullet_manager, dt);
            drop_manager_update(&gm->drop_manager);

            update_camera(gm);

            // spawn
            if (system_timer_tick(&gm->player.bullet_timer)) {
                bullet_manager_spawn(&gm->bullet_manager,
                                     gm->player.bullet_config,
                                     (Vector2){gm->player.position.x, gm->player.position.y},
                                     get_player_target(gm));
            }

            // collisions
            collision_manager_player_vs_enemy(&gm->collision_manager);
            collision_manager_player_vs_drop(&gm->collision_manager);
            collision_manager_bullet_vs_enemy(&gm->collision_manager);
            collision_manager_enemy_vs_enemy(&gm->collision_manager);

            // upgrade state change
            if (gm->player.level.pending > 0) {
                gm->player.level.pending--;
                upgrade_manager_fill_choices(&gm->upgrade_manager);
                gm->current_state = GAME_STATE_UPGRADE;
            }

        } break;

        case GAME_STATE_UPGRADE: {
            upgrade_manager_apply_upgrade(&gm->upgrade_manager);

            if (upgrade_manager_is_choices_empty(&gm->upgrade_manager)
                && gm->upgrade_manager.selected_upgrade == UPGRADE_TYPE_NONE)
                gm->current_state = GAME_STATE_RUNNING;
        } break;

        case GAME_STATE_EXIT:
            break;
    }
}

void game_manager_draw(GameManager* gm, const Vector2 world_mouse) {
    assert(gm);

    switch (gm->current_state) {
        case GAME_STATE_TITLE:
            break;

        case GAME_STATE_RUNNING: {
            BeginMode2D(gm->camera);

            system_draw_background_grid();

            drop_manager_draw(&gm->drop_manager);
            bullet_manager_draw(&gm->bullet_manager);
            player_draw(&gm->player);
            enemy_manager_draw(&gm->enemy_manager);

            ui_manager_enemy_health_bar(&gm->ui_manager);
            ui_manager_player_health_bar(&gm->ui_manager);

            EndMode2D();

            // ui
            ui_manager_player_xp_bar(&gm->ui_manager);

        } break;

        case GAME_STATE_UPGRADE: {
            upgrade_manager_draw(&gm->upgrade_manager, world_mouse);

        } break;

        case GAME_STATE_EXIT:
            break;
    }
}
