#pragma once

#include "../components.h"
#include "../drops/drop_manager.h"
#include "enemy.h"

#define MAX_ENEMIES 1000

typedef struct {
    int dead_enemy_count;

    Enemy            enemies[MAX_ENEMIES];
    SpawnerComponent spawner;
    TimerComponent   timer;
} EnemyManager;

void enemy_manager_init(EnemyManager* em);
void enemy_manager_spawn(EnemyManager* em, const int current_wave, const Vector2 target_pos);
void enemy_manager_despawn(EnemyManager* em, const int index);
void enemy_manager_update(EnemyManager* em,
                          const float   dt,
                          const int     current_wave,
                          const Vector2 target_pos,
                          DropManager*  dm);
void enemy_manager_draw(const EnemyManager* em);
