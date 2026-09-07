#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "../timer.h"
#include "enemy.h"

#define MAX_ENEMIES 100

typedef struct {
    Enemy enemies[MAX_ENEMIES];
    int   size;
    Timer timer;
} EnemyManager;

void enemy_manager_init(EnemyManager* em);
void enemy_manager_spawn(EnemyManager* em, const float dt, const Vector2 target_pos);
void enemy_manager_update(EnemyManager* em, const float dt, const Vector2 target_pos);
void enemy_manager_draw(const EnemyManager* em);

#endif // ENEMY_MANAGER_H
