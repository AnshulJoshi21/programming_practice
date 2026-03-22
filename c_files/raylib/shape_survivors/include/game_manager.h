#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "ecs.h"
#include "utils.h"

#include <raylib.h>
#include <stdint.h>

typedef struct GameManager
{
    World world;
    uint32_t player_id;
    uint32_t enemy_count;
    IntervalTimer enemy_interval_timer;
    uint32_t bullet_count;
    IntervalTimer bullet_interval_timer;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_draw(const GameManager *gm);
void game_manager_update(GameManager *gm, const float dt);

#endif // GAME_MANAGER_H
