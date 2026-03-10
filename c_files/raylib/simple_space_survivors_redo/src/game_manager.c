#include "../include/game_manager.h"
#include "../include/settings.h"

#include <assert.h>
#include <math.h>

void game_manager_init(GameManager *gm)
{
    assert(gm);

    starfield_init(&gm->starfield);

    player_init(&gm->player);
    enemy_manager_init(&gm->enemy_manager);

    gm->camera = (Camera2D){
        .offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        .target = (Vector2){0, 0},
        .rotation = 0.0f,
        .zoom     = 1.0f};
}

void game_manager_draw(const GameManager *gm, const Texture2D spritesheet)
{
    assert(gm);

    BeginMode2D(gm->camera);

    BeginBlendMode(BLEND_ALPHA);

    starfield_draw(&gm->starfield, spritesheet, gm->camera);

    player_draw(&gm->player, spritesheet);
    enemy_manager_draw(&gm->enemy_manager, spritesheet);

    EndBlendMode();

    EndMode2D();
}

void game_manager_update(GameManager *gm, const float dt)
{
    assert(gm);

    // find closest enemy to player
    Vector2 closest_enemy_pos = {0};
    float min_distance        = MAP_SIZE;

    for (int i = 0; i < gm->enemy_manager.size; i++) {
        const Enemy *e = &gm->enemy_manager.enemy_list[i];

        float dx       = e->dest.x - gm->player.dest.x;
        float dy       = e->dest.y - gm->player.dest.y;
        float distance = sqrtf(dx * dx + dy * dy);
        if (distance < min_distance) {
            closest_enemy_pos = (Vector2){e->dest.x, e->dest.y};
            min_distance      = distance;
        }
    }

    player_update(&gm->player, dt, closest_enemy_pos);
    const Vector2 start_pos = (Vector2){gm->player.dest.x, gm->player.dest.y};
    enemy_manager_update(&gm->enemy_manager, dt, start_pos);

    // update camera target
    const float half_w = GetScreenWidth() / 2.0f;
    const float half_h = GetScreenHeight() / 2.0f;

    gm->camera.target.x =
        fmaxf(half_w, fminf(gm->player.dest.x, MAP_SIZE - half_w));
    gm->camera.target.y =
        fmaxf(half_h, fminf(gm->player.dest.y, MAP_SIZE - half_h));
}
