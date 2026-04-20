#include "bullet_manager.h"

#include <assert.h>

void bullet_manager_init(BulletManager* bm) {
    assert(bm);

    bm->spawner.max = MAX_BULLETS;
    bm->spawner.count = 0;
}

void bullet_manager_draw(const BulletManager* bm) {
    assert(bm);

    for (int i = 0; i < bm->spawner.count; i++) {
        bullet_draw(&bm->bullets[i]);
    }
}

void bullet_manager_spawn(BulletManager* bm, const BulletType type, const Vector2 start_pos,
                          const Vector2 target_pos, BulletConfig owner_config) {
    assert(bm);

    if (bm->spawner.count >= bm->spawner.max) {
        return;
    }

    bullet_init(&bm->bullets[bm->spawner.count], type, start_pos, target_pos, owner_config);
    bm->spawner.count++;
}

void bullet_manager_despawn(BulletManager* bm, const int index) {
    assert(bm);
    assert(index >= 0 && index < bm->spawner.count);

    bm->bullets[index] = bm->bullets[bm->spawner.count - 1];
    bm->spawner.count--;
}

void bullet_manager_update(BulletManager* bm, const float dt) {
    assert(bm);

    // update
    for (int i = 0; i < bm->spawner.count; i++) {
        Bullet* bullet = &bm->bullets[i];

        bullet_update(bullet, dt);

        if (bullet->lifetime.remaining <= 0) {
            bullet_manager_despawn(bm, i);
            i--;
        }
    }
}
