#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "sprite_data.h"

#include <raylib.h>

#define MAX_ENEMIES 10

typedef struct Enemy
{
    SpriteData sprite_name;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;

    float max_hp;
    float hp;

} Enemy;

void enemy_init(Enemy *enemy, const Vector2 start_pos);

typedef struct EnemyManager
{
    Enemy enemy_list[MAX_ENEMIES];
    int size;

    float speed;

    float last_spawn_time;
    float spawn_interval;

} EnemyManager;

void enemy_manager_init(EnemyManager *em);
void enemy_manager_draw(const EnemyManager *em, const Texture2D spritesheet);
void enemy_manager_update(EnemyManager *em, const float dt,
                          const Vector2 target_pos);

#endif // ENEMY_MANAGER_H
