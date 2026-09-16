#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "../settings.h"
#include "bullet.h"

typedef struct {
    Bullet bullets[MAX_BULLETS];
    int    size;
} BulletManager;

void bullet_manager_init(BulletManager* bm);
void bullet_manager_spawn(BulletManager* bm, const BulletInitConfig config);
void bullet_manager_update(BulletManager* bm, const float dt);
void bullet_manager_draw(const BulletManager* bm);

#endif // BULLET_MANAGER_H
