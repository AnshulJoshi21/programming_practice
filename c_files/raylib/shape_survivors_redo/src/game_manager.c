#include "game_manager.h"
#include "settings.h"
#include <assert.h>
#include <raymath.h>

void game_manager_init(GameManager* gm) {
    assert(gm);

    gm->current_state = GAME_STATE_RUNNING;
    player_init(&gm->player);
    enemy_manager_init(&gm->enemy_manager);
    gm->camera = (Camera2D){.offset   = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                            .target   = (Vector2){0, 0},
                            .rotation = 0.0f,
                            .zoom     = 1.0f};
}

static void update_camera(GameManager* gm) {
    assert(gm);

    const float half_w = SCREEN_WIDTH / 2.0f;
    const float half_h = SCREEN_HEIGHT / 2.0f;

    gm->camera.target.x = Clamp(gm->player.pos.x, half_w, MAP_SIZE - half_w);
    gm->camera.target.y = Clamp(gm->player.pos.y, half_h, MAP_SIZE - half_h);
}

static Vector2 get_player_target(GameManager* gm) {
    assert(gm);

    float   min_distance = MAP_SIZE * MAP_SIZE;
    Vector2 target_pos   = (Vector2){0, 0};

    for (int i = 0; i < gm->enemy_manager.enemies_size; i++) {
        const Enemy* enemy = &gm->enemy_manager.enemies[i];

        const float dx       = enemy->pos.x - gm->player.pos.x;
        const float dy       = enemy->pos.y - gm->player.pos.y;
        const float distance = sqrtf((dx * dx) + (dy * dy));
        if (distance < min_distance) {
            min_distance = distance;
            target_pos   = enemy->pos;
        }
    }
    return target_pos;
}

void game_manager_update(GameManager* gm, const float dt, const Vector2* world_mouse) {
    assert(gm);

    player_update(&gm->player, dt);
    enemy_manager_update(&gm->enemy_manager, dt, gm->player.pos);
    bullet_manager_update(&gm->bullet_manager, dt);
    update_camera(gm);

    // spawn bullets
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
