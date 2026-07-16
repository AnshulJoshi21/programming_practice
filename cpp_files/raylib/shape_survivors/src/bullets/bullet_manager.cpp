#include "bullet_manager.hpp"

static const int BULLETS_MAX = 200;

BulletManager::BulletManager() : spawner({.max = BULLETS_MAX}) {}

void BulletManager::spawn(const BulletConfig& config,
                          const Vector2&      start_pos,
                          const Vector2&      target_pos) {
    const int bullets_size = static_cast<int>(bullets.size());

    if (bullets_size >= BULLETS_MAX)
        return;

    bullets.push_back(Bullet(config, start_pos, target_pos));
}

void BulletManager::despawn(const int index) {
    const int bullets_size = static_cast<int>(bullets.size());

    if (index < 0 || index >= bullets_size)
        return;

    bullets[index] = bullets[bullets_size - 1];
    bullets.pop_back();
}

void BulletManager::update(const float dt) {
    const int bullets_size = static_cast<int>(bullets.size());
    for (int i = 0; i < bullets_size; i++) {
        Bullet& bullet = bullets[i];

        bullet.update(dt);

        if (bullet.lifetime.current <= 0) {
            despawn(i);
            i--;
        }
    }
}

void BulletManager::draw(void) const {
    for (const Bullet& bullet : bullets)
        bullet.draw();
}
