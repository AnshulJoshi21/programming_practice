#include "bullet_manager.h"
#include <assert.h>

void bullet_manager_init(BulletManager* bm) {
    assert(bm);

    bm->projectile_size = 0;
    bm->orbital_size    = 0;
}

void bullet_manager_spawn_projectile(BulletManager*      bm,
                                     const EntityConfig* econfig,
                                     const Vector2       start_pos,
                                     const Vector2       target_pos) {
    assert(bm);
    assert(econfig);

    if (bm->projectile_size >= MAX_PROJECTILES)
        return;

    const ProjectileConfig config = (ProjectileConfig){
        .center = start_pos, .homing = econfig->homing, .target_pos = target_pos};

    projectile_init(&bm->projectiles[bm->projectile_size++], econfig, &config);
}

void bullet_manager_spawn_orbital(BulletManager*      bm,
                                  const EntityConfig* econfig,
                                  const Vector2*      origin) {
    assert(bm);
    assert(econfig);

    if (bm->orbital_size >= MAX_ORBITALS)
        return;

    for (int i = 0; i < bm->orbital_size; i++) {
        const OrbitalConfig config = (OrbitalConfig){
            .angle  = (2 * PI * i) / bm->orbital_size,
            .origin = origin,
        };

        orbital_init(&bm->orbitals[bm->orbital_size++], econfig, &config);
    }
}

void bullet_manager_update(BulletManager* bm, const float dt) {
    assert(bm);

    for (int i = 0; i < bm->projectile_size; i++) {
        ProjectileBullet* projectile = &bm->projectiles[i];

        projectile_update(projectile, dt);

        // despawn
        if (projectile->lifetime <= 0) {
            bm->projectiles[i] = bm->projectiles[--bm->projectile_size];
            i--;
        }
    }

    for (int i = 0; i < bm->orbital_size; i++) {
        OrbitalBullet* orbital = &bm->orbitals[i];
        orbital_update(orbital, dt);

        // despawn
        if (orbital->lifetime <= 0) {
            bm->orbitals[i] = bm->orbitals[--bm->orbital_size];
            i--;
        }
    }
}

void bullet_manager_draw(const BulletManager* bm) {
    assert(bm);

    for (int i = 0; i < bm->projectile_size; i++) {
        const ProjectileBullet* projectile = &bm->projectiles[i];
        const ProjectileDef*    def        = &projectile_db[projectile->type];
        DrawCircleV(projectile->center, def->radius, def->color);
    }
    for (int i = 0; i < bm->orbital_size; i++) {
        const OrbitalBullet* orbital = &bm->orbitals[i];
        const OrbitalDef*    def     = &orbital_db[orbital->type];
        DrawCircleV(orbital->center, def->radius, def->color);
    }
}
