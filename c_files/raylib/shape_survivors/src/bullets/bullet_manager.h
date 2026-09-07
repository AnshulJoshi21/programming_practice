#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "bullet.h"

#define MAX_BULLETS 100

typedef struct {
    Bullet bullets[MAX_BULLETS];
    int    size;
} BulletManager;

void bullet_manager_init(BulletManager* em);
void bullet_manager_spawn(BulletManager* bm, const Vector2 start_pos, const Vector2 target_pos);
void bullet_manager_update(BulletManager* em, const float dt);
void bullet_manager_draw(const BulletManager* em);

#endif // BULLET_MANAGER_H
