#include "bullet_manager.h"
#include <assert.h>

void bullet_manager_init(BulletManager* bm) {
    assert(bm);

    bm->spawner.max     = MAX_BULLETS;
    bm->spawner.current = 0;
}

void bullet_manager_spawn(BulletManager*     bm,
                          const BulletConfig config,
                          const Vector2      start_pos,
                          const Vector2      target_pos) {
    assert(bm);

    if (bm->spawner.current >= bm->spawner.max)
        return;

    bullet_init(&bm->bullets[bm->spawner.current], config, start_pos, target_pos);
    bm->spawner.current++;
}

void bullet_manager_despawn(BulletManager* bm, const int index) {
    assert(bm);

    if (index < 0 || index >= bm->spawner.current)
        return;

    bm->bullets[index] = bm->bullets[bm->spawner.current - 1];
    bm->spawner.current--;
}

void bullet_manager_update(BulletManager* bm, const float dt) {
    assert(bm);

    for (int i = 0; i < bm->spawner.current; i++) {
        Bullet* bullet = &bm->bullets[i];

        bullet_update(bullet, dt);

        if (bullet->lifetime.remaining <= 0) {
            bullet_manager_despawn(bm, i);
            i--;
        }
    }
}

void bullet_manager_draw(const BulletManager* bm) {
    assert(bm);

    for (int i = 0; i < bm->spawner.current; i++) {
        bullet_draw(&bm->bullets[i]);
    }
}
