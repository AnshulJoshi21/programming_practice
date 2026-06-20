#pragma once

#include "../components.h"
#include "bullet.h"

#define MAX_BULLETS 1000

typedef struct {
    Bullet           bullets[MAX_BULLETS];
    SpawnerComponent spawner;
} BulletManager;

void bullet_manager_init(BulletManager* em);
void bullet_manager_spawn(BulletManager*      em,
                          const BulletConfig* config,
                          const Vector2       start_pos,
                          const Vector2       target_pos);
void bullet_manager_despawn(BulletManager* em, const int index);
void bullet_manager_update(BulletManager* em, const float dt);
void bullet_manager_draw(const BulletManager* em);
