#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "../timer.h"
#include "bullet_orbital.h"
#include "bullet_projectile.h"

#define MAX_PROJECTILES 1000
#define MAX_ORBITALS 8

typedef struct BulletManager {
    ProjectileBullet projectiles[MAX_PROJECTILES];
    int              projectile_size;
    IntervalTimer    projectile_timer;
    OrbitalBullet    orbitals[MAX_ORBITALS];
    int              orbital_size;
} BulletManager;

void bullet_manager_init(BulletManager* bm);

void bullet_manager_spawn_projectile(BulletManager*      bm,
                                     const EntityConfig* econfig,
                                     const Vector2       start_pos,
                                     const Vector2       target_pos);
void bullet_manager_spawn_orbital(BulletManager*      bm,
                                  const EntityConfig* econfig,
                                  const Vector2*      origin);

void bullet_manager_update(BulletManager* bm, const float dt);
void bullet_manager_draw(const BulletManager* bm);

#endif // BULLET_MANAGER_H
