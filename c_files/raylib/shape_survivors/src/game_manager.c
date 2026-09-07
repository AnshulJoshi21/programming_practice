#include "game_manager.h"
#include "settings.h"
#include <assert.h>
#include <math.h>

void game_manager_init(GameManager* gm) {
    assert(gm);

    gm->current_state = GAME_STATE_RUNNING;

    player_init(&gm->player);
    enemy_manager_init(&gm->enemy_manager);
    bullet_manager_init(&gm->bullet_manager);

    gm->camera = (Camera2D){
        .offset   = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target   = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1.0f,
    };
}

static void camera_update(GameManager* gm) {
    assert(gm);

    const float half_w = GetScreenWidth() / 2.0f;
    const float half_h = GetScreenHeight() / 2.0f;

    gm->camera.target.x = fmaxf(half_w, fminf(gm->player.rect.x, MAP_SIZE - half_w));
    gm->camera.target.y = fmaxf(half_h, fminf(gm->player.rect.y, MAP_SIZE - half_h));
}

static Vector2 get_player_target(GameManager* gm) {
    assert(gm);

    Vector2 target       = (Vector2){0, 0};
    float   min_distance = MAP_SIZE * MAP_SIZE;

    const Player* player = &gm->player;

    // find closest enemy to player
    for (int i = 0; i < gm->enemy_manager.size; i++) {
        const Enemy* enemy = &gm->enemy_manager.enemies[i];

        const float dx       = enemy->rect.x - player->rect.x;
        const float dy       = enemy->rect.y - player->rect.y;
        const float distance = sqrtf((dx * dx) + (dy * dy));
        if (distance < min_distance) {
            min_distance = distance;
            target       = (Vector2){enemy->rect.x, enemy->rect.y};
        }
    }

    return target;
}

void game_manager_update(GameManager* gm, const float dt) {
    assert(gm);

    player_update(&gm->player, dt);
    enemy_manager_update(&gm->enemy_manager, dt, (Vector2){gm->player.rect.x, gm->player.rect.y});
    bullet_manager_update(&gm->bullet_manager, dt);

    camera_update(gm);

    // spawn bullet
    if (timer_tick(&gm->player.bullet_timer, dt)) {
        bullet_manager_spawn(&gm->bullet_manager,
                             (Vector2){gm->player.rect.x, gm->player.rect.y},
                             get_player_target(gm));
    }
}

static void draw_background_grid(void) {
    const float thickness  = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = 100.0f;

    for (float x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_SIZE}, thickness, color);
    }
    for (float y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_SIZE, y}, thickness, color);
    }
}

void game_manager_draw(const GameManager* gm) {
    assert(gm);

    BeginMode2D(gm->camera);

    draw_background_grid();

    bullet_manager_draw(&gm->bullet_manager);
    player_draw(&gm->player);
    enemy_manager_draw(&gm->enemy_manager);

    EndMode2D();
}
