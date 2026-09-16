#include "bullet_manager.h"
#include <assert.h>

void bullet_manager_init(BulletManager* bm) {
    assert(bm);

    bm->size = 0;
}

void bullet_manager_spawn(BulletManager* bm, const BulletInitConfig config) {
    assert(bm);

    if (bm->size >= MAX_BULLETS) return;

    bullet_init(&bm->bullets[bm->size++], config);
}

void bullet_manager_update(BulletManager* bm, const float dt) {
    assert(bm);

    for (int i = 0; i < bm->size; i++) {
        Bullet* bullet = &bm->bullets[i];

        bullet_update(bullet, dt);

        // despawn
        if (bullet->lifetime <= 0) {
            bm->bullets[i] = bm->bullets[--bm->size];
            i--;
        }
    }
}

void bullet_manager_draw(const BulletManager* bm) {
    assert(bm);

    for (int i = 0; i < bm->size; i++) {
        bullet_draw(&bm->bullets[i]);
    }
}
