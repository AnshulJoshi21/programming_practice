#include "collisions.h"
#include "game_manager.h"
#include "settings.h"
#include "systems.h"
#include "ui.h"
#include "utils.h"

#include <assert.h>
#include <math.h>

static void _set_state(GameManager *gm, const GameState state) {
    assert(gm);

    gm->current_state = state;
}

static void _reset(GameManager *gm) {
    assert(gm);
    _set_state(gm, GAME_STATE_COMBAT);

    bullet_manager_init(&gm->bullet_manager);
    player_init(&gm->player);
    enemy_manager_init(&gm->enemy_manager);
    drop_manager_init(&gm->drop_manager);
    particle_manager_init(&gm->particle_manager);
    upgrade_manager_init(&gm->upgrade_manager);

    gm->camera = (Camera2D){.offset = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                            .target = (Vector2){0, 0},
                            .rotation = 0.0f,
                            .zoom = 1.0f};
}

void game_manager_init(GameManager *gm) {
    assert(gm);

    _reset(gm);
}

static void _draw_background_grid(void) {
    const float thickness = 2.0f;
    const Color color = GRAY;
    const float block_size = 30.0f;

    for (float x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_SIZE}, thickness, color);
    }
    for (float y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_SIZE, y}, thickness, color);
    }
}

void game_manager_draw(GameManager *gm, const Vector2 mouse_pos) {
    assert(gm);

    switch (gm->current_state) {
        case GAME_STATE_TITLE:
            break;

        case GAME_STATE_COMBAT: {
            BeginMode2D(gm->camera);

            _draw_background_grid();

            drop_manager_draw(&gm->drop_manager);
            bullet_manager_draw(&gm->bullet_manager);
            enemy_manager_draw(&gm->enemy_manager);
            player_draw(&gm->player);
            particle_manager_draw(&gm->particle_manager);

            EndMode2D();

            // game ui
            ui_draw_player_xp_bar(&gm->player);

        } break;

        case GAME_STATE_UPGRADE: {
            upgrade_manager_draw(&gm->upgrade_manager, mouse_pos);

        } break;

        case GAME_STATE_EXIT: {
            const float width = 300.0f;
            const float height = 150.0f;
            const float x = (GetScreenWidth() - width) / 2.0f;
            const float y = (GetScreenHeight() - height) / 2.0f;

            DrawRectangleRec((Rectangle){x, y, width, height}, WHITE);

            center_and_draw_text(ORIGIN_TOP_LEFT, "GAME OVER", (Rectangle){x, y, width, height},
                                 30.0f, 2.0f, BLACK);
            center_and_draw_text(ORIGIN_TOP_LEFT, "press ENTER to restart",
                                 (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200},
                                 20.0f, 2.0f, BLACK);

            DrawRectangleLinesEx((Rectangle){x, y, width, height}, 5.0f, BLACK);
        } break;
    }
}

static void _camera_update(GameManager *gm) {
    assert(gm);

    const float half_w = SCREEN_WIDTH / 2.0f;
    const float half_h = SCREEN_HEIGHT / 2.0f;

    gm->camera.target.x = fmaxf(half_w, fminf(gm->player.position.x, MAP_SIZE - half_w));
    gm->camera.target.y = fmaxf(half_h, fminf(gm->player.position.y, MAP_SIZE - half_h));
}

static Vector2 _get_player_target(GameManager *gm) {
    assert(gm);

    float min_distance = MAP_SIZE;
    Vector2 pos = (Vector2){0};

    for (int i = 0; i < gm->enemy_manager.spawner.count; i++) {
        Enemy *enemy = &gm->enemy_manager.enemies[i];

        const float dx = enemy->position.x - gm->player.position.x;
        const float dy = enemy->position.y - gm->player.position.y;
        const float distance = sqrtf((dx * dx) + (dy * dy));
        if (distance < min_distance) {
            min_distance = distance;
            pos = (Vector2){enemy->position.x, enemy->position.y};
        }
    }

    return pos;
}

void game_manager_update(GameManager *gm, const float dt) {
    assert(gm);

    switch (gm->current_state) {
        case GAME_STATE_TITLE:
            break;
        case GAME_STATE_COMBAT:

        {  // update entities
            player_update(&gm->player, dt);

            const Vector2 player_pos = (Vector2){gm->player.position.x, gm->player.position.y};

            enemy_manager_update(&gm->enemy_manager, &gm->drop_manager, dt, player_pos);
            bullet_manager_update(&gm->bullet_manager, dt);
            drop_manager_update(&gm->drop_manager);
            particle_manager_update(&gm->particle_manager, dt);

            _camera_update(gm);

            // spawn bullet
            //
            // player bullet
            const Vector2 player_target = _get_player_target(gm);
            if (system_timer_tick(&gm->player.bullet_timer)) {
                bullet_manager_spawn(&gm->bullet_manager, BULLET_SINGLE, player_pos, player_target,
                                     gm->player.bullet_config);
            }

            // collisions
            player_collision_enemies(&gm->player, &gm->enemy_manager);
            bullet_collision_enemies(&gm->bullet_manager, &gm->enemy_manager,
                                     &gm->particle_manager);
            enemy_collision_enemies(&gm->enemy_manager);
            player_collision_drops(&gm->player, &gm->drop_manager);

            // player level up event
            if (gm->player.xp.pending_levelups > 0) {
                _set_state(gm, GAME_STATE_UPGRADE);
            }

            // game over
            if (gm->player.health.hp <= 0) {
                _set_state(gm, GAME_STATE_EXIT);
            }

        } break;

        case GAME_STATE_UPGRADE: {
            upgrade_manager_update(&gm->upgrade_manager, &gm->player);

            // handle multiple level ups
            if (gm->upgrade_manager.choices[0] == UPGRADE_NONE &&
                gm->upgrade_manager.current_choice == UPGRADE_NONE) {
                //
                system_consume_levelups(&gm->player.xp);
                if (gm->player.xp.pending_levelups <= 0) {
                    _set_state(gm, GAME_STATE_COMBAT);
                }
            }

        } break;

        case GAME_STATE_EXIT: {
            if (IsKeyPressed(KEY_ENTER)) {
                _reset(gm);
            }
        } break;
    }
}
