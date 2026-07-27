#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "../timer.h"
#include "enemy.h"

#define MAX_ENEMIES 50

static const int ENEMY_SPAWN_INTERVAL = 2.0f;

typedef struct EnemyManager {
    Enemy         enemies[MAX_ENEMIES];
    int           enemies_max;
    int           enemies_size;
    IntervalTimer timer;
} EnemyManager;

void enemy_manager_init(EnemyManager* em);
void enemy_manager_spawn(EnemyManager* em, const Vector2 target_pos);
void enemy_manager_despawn(EnemyManager* em, const int index);
void enemy_manager_update(EnemyManager* em, const float dt, const Vector2 target_pos);
void enemy_manager_draw(const EnemyManager* em);

#endif // ENEMY_MANAGER_H
