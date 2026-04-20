#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "enemy.h"

#include "../components.h"
#include "../drops/drop_manager.h"

#define MAX_ENEMIES 1000

typedef struct EnemyManager {
    Enemy enemies[MAX_ENEMIES];

    SpawnerComponent spawner;
    TimerComponent timer;

} EnemyManager;

void enemy_manager_init(EnemyManager* em);
void enemy_manager_draw(const EnemyManager* em);
void enemy_manager_update(EnemyManager* em, DropManager* dm, const float dt,
                          const Vector2 target_pos);

void enemy_manager_spawn(EnemyManager* em, const EnemyType type, const Vector2 target_pos);
void enemy_manager_despawn(EnemyManager* em, const int index);

#endif  // ENEMY_MANAGER_H
