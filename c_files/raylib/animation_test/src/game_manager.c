#include "game_manager.h"
#include "settings.h"
#include <assert.h>

void game_manager_init(GameManager* gm) {
    assert(gm);

    texture_manager_load(&gm->texture_manager);

    gm->camera = (Camera2D){.offset   = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
                            .target   = (Vector2){0, 0},
                            .rotation = 0.0f,
                            .zoom     = 1.0f};
}

static void gm_camera_update(GameManager* gm) {
    assert(gm);
}

void game_manager_update(GameManager* gm, const float dt) {
    assert(gm);

    gm_camera_update(gm);
}

static void draw_background_grid(void) {
    const float thick        = 2.0f;
    const Color color        = LIGHTGRAY;
    const float block_width  = MAP_WIDTH / 4.0f;
    const float block_height = MAP_HEIGHT / 4.0f;

    for (int x = 0; x < MAP_WIDTH; x += block_width) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_HEIGHT}, thick, color);
    }

    for (int y = 0; y < MAP_HEIGHT; y += block_height) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_WIDTH, y}, thick, color);
    }
}
void game_manager_draw(const GameManager* gm) {
    assert(gm);

    BeginMode2D(gm->camera);

    draw_background_grid();

    EndMode2D();
}

void game_manager_shutdown(GameManager* gm) {
    assert(gm);

    texture_manager_unload(&gm->texture_manager);
}
