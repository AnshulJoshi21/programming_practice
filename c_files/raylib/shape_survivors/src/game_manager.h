#pragma once

#include "bullets/bullet_manager.h"
#include "collision_manager.h"
#include "components.h"
#include "drops/drop_manager.h"
#include "enemies/enemy_manager.h"
#include "player.h"
#include <raylib.h>

typedef struct {
    int current_wave;

    Player        player;
    EnemyManager  enemy_manager;
    BulletManager bullet_manager;
    DropManager   drop_manager;

    CollisionManager collision_manager;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager* gm);
void game_manager_update(GameManager* gm, const float dt);
void game_manager_draw(const GameManager* gm);
