#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "bullet.h"

#define MAX_BULLETS 200

typedef struct BulletManager {
    Bullet   bullets[MAX_BULLETS];
    CSpawner spawner;
} BulletManager;

void bullet_manager_init(BulletManager* bm);
void bullet_manager_spawn(BulletManager*     bm,
                          const BulletConfig config,
                          const Vector2      start_pos,
                          const Vector2      target_pos);
void bullet_manager_despawn(BulletManager* bm, const int index);
void bullet_manager_update(BulletManager* bm, const float dt);
void bullet_manager_draw(const BulletManager* bm);

#endif // BULLET_MANAGER_H
