#include "animation.h"
#include "game_manager.h"
#include "settings.h"

#include <assert.h>
#include <math.h>
#include <memory.h>

void game_manager_init(GameManager *gm)
{
    assert(gm);

    texture_manager_init(&gm->texture_manager);
    texture_manager_check(&gm->texture_manager);

    memset(gm->animation_configs, 0, sizeof(gm->animation_configs));

    animation_config_init(gm->animation_configs, &gm->texture_manager);

    player_init(&gm->player, gm->animation_configs);

    gm->camera = (Camera2D){.offset
                            = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
                            .target   = (Vector2){0, 0},
                            .rotation = 0.0f,
                            .zoom     = 1.0f};
}

static void game_manager_update_camera(GameManager *gm)
{
    assert(gm);

    const float half_w = BASE_WIDTH / 2.0f;
    const float half_h = BASE_HEIGHT / 2.0f;

    gm->camera.target.x
            = fmaxf(half_w, fminf(gm->player.dest.x, MAP_WIDTH - half_w));
    gm->camera.target.y
            = fmaxf(half_h, fminf(gm->player.dest.y, MAP_HEIGHT - half_h));
}

void game_manager_update(GameManager *gm, const float dt)
{
    assert(gm);

    player_update(&gm->player, dt);

    game_manager_update_camera(gm);
}

static void draw_background_grid(void)
{
    const float thick        = 2.0f;
    const Color color        = LIGHTGRAY;
    const float block_width  = MAP_WIDTH / 2.0f;
    const float block_height = MAP_HEIGHT / 2.0f;

    for (float x = 0; x < MAP_WIDTH; x += block_width) {
        DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_HEIGHT}, thick, color);
    }
    for (float y = 0; y < MAP_HEIGHT; y += block_height) {
        DrawLineEx((Vector2){0, y}, (Vector2){MAP_WIDTH, y}, thick, color);
    }
}

void game_manager_draw(const GameManager *gm)
{
    assert(gm);

    BeginMode2D(gm->camera);

    draw_background_grid();

    player_draw(&gm->player);

    EndMode2D();
}

void game_manager_shutdown(GameManager *gm)
{
    assert(gm);

    texture_manager_shutdown(&gm->texture_manager);
}
