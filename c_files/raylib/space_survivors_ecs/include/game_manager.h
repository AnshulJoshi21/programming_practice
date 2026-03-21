#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "ecs.h"
#include "utils.h"

#include <raylib.h>

typedef struct GameManager
{
    World world;
    int player_id;
    int enemy_count;
    IntervalTimer enemy_spawn_timer;
    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_draw(const GameManager *gm, const Texture2D background,
                       const Texture2D spritesheet);
void game_manager_update(GameManager *gm, const float dt,
                         Vector2 mouse_pos_world);

#endif // GAME_MANAGER_H
