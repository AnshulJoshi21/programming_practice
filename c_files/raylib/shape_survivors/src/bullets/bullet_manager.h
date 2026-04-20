#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "bullet.h"

#include "../components.h"

#define MAX_BULLETS 1000

typedef struct BulletManager {
    Bullet bullets[MAX_BULLETS];

    SpawnerComponent spawner;

} BulletManager;

void bullet_manager_init(BulletManager* em);
void bullet_manager_draw(const BulletManager* em);
void bullet_manager_update(BulletManager* bm, const float dt);

void bullet_manager_spawn(BulletManager* bm, const BulletType type, const Vector2 start_pos,
                          const Vector2 target_pos, BulletConfig owner_config);
void bullet_manager_despawn(BulletManager* bm, const int index);

#endif  // BULLET_MANAGER_H
