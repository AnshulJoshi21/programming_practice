#include "game_manager.h"
#include "settings.h"
#include <assert.h>

void game_manager_init(GameManager* gm) {
    assert(gm);
    gm->camera = (Camera2D){
        .offset   = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
        .target   = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1,
    };
}

void game_manager_update(GameManager* gm, const float dt) {
    assert(gm);
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

    EndMode2D();
}
