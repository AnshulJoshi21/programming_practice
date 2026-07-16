#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "../drops/drop_manager.h"
#include "enemy.h"

#define MAX_ENEMIES 200

typedef struct EnemyManager {
    Enemy    enemies[MAX_ENEMIES];
    CSpawner spawner;
    CTimer   timer;
} EnemyManager;

void enemy_manager_init(EnemyManager* em);
void enemy_manager_spawn(EnemyManager* em, const Vector2 target_pos);
void enemy_manager_despawn(EnemyManager* em, const int index);
void enemy_manager_update(EnemyManager* em,
                          const float   dt,
                          const Vector2 target_pos,
                          DropManager*  dm);
void enemy_manager_draw(const EnemyManager* em);

#endif // ENEMY_MANAGER_H
