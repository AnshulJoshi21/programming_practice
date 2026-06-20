#include "game_manager.h"
#include "settings.h"
#include "systems.h"
#include <assert.h>
#include <math.h>

void game_manager_init(GameManager* gm) {
    assert(gm);

    gm->current_wave = 1;

    player_init(&gm->player);
    enemy_manager_init(&gm->enemy_manager);
    bullet_manager_init(&gm->bullet_manager);
    drop_manager_init(&gm->drop_manager);

    collision_manager_init(&gm->collision_manager,
                           &gm->player,
                           &gm->enemy_manager,
                           &gm->bullet_manager,
                           &gm->drop_manager);

    gm->camera = (Camera2D){
        .offset   = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
        .target   = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1,
    };
}

static void update_camera(GameManager* gm) {
    assert(gm);

    const float half_w = BASE_WIDTH / 2.0f;
    const float half_h = BASE_HEIGHT / 2.0f;

    gm->camera.target.x = fmaxf(half_w, fminf(gm->player.position.x, MAP_SIZE - half_w));
    gm->camera.target.y = fmaxf(half_h, fminf(gm->player.position.y, MAP_SIZE - half_h));
}

static Vector2 get_player_target_pos(GameManager* gm) {
    assert(gm);

    Vector2 target       = (Vector2){0, 0};
    float   min_distance = MAP_SIZE * MAP_SIZE;

    for (int i = 0; i < gm->enemy_manager.spawner.current; i++) {
        Enemy* enemy = &gm->enemy_manager.enemies[i];

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

    // update wave
    if (gm->enemy_manager.dead_enemy_count >= ENEMIES_PER_WAVE) {
        gm->enemy_manager.dead_enemy_count = 0;
        gm->current_wave++;
    }

    // update entities
    player_update(&gm->player, dt);
    enemy_manager_update(&gm->enemy_manager,
                         dt,
                         gm->current_wave,
                         (Vector2){gm->player.position.x, gm->player.position.y},
                         &gm->drop_manager);
    bullet_manager_update(&gm->bullet_manager, dt);
    drop_manager_update(&gm->drop_manager);
    update_camera(gm);

    // spawn entities
    // bullet
    if (system_timer_tick(&gm->player.bullet_timer)) {
        bullet_manager_spawn(&gm->bullet_manager,
                             &gm->player.bullet_config,
                             (Vector2){gm->player.position.x, gm->player.position.y},
                             get_player_target_pos(gm));
    }

    // collisions
    collision_manager_update(&gm->collision_manager);
}

static void draw_background_grid(void) {
    const float thick      = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = MAP_SIZE / 4.0f;

    for (int x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_SIZE}, thick, color);
    }

    for (int y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_SIZE, y}, thick, color);
    }
}

void game_manager_draw(const GameManager* gm) {
    assert(gm);
    BeginMode2D(gm->camera);

    draw_background_grid();

    drop_manager_draw(&gm->drop_manager);
    bullet_manager_draw(&gm->bullet_manager);
    player_draw(&gm->player);
    enemy_manager_draw(&gm->enemy_manager);

    EndMode2D();
}
