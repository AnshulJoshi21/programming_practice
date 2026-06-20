#include "game_manager.h"
#include "settings.h"
#include <assert.h>
#include <math.h>

void game_manager_init(GameManager* gm) {
    assert(gm);

    player_init(&gm->player);

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

void game_manager_update(GameManager* gm, const float dt) {
    assert(gm);

    player_update(&gm->player, dt);
    update_camera(gm);
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

    player_draw(&gm->player);

    EndMode2D();
}
