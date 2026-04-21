#include "bullet_manager.hpp"

BulletManager::BulletManager() : spawner({.max = 200}) {}

void BulletManager::draw(void) const
{
    for (const Bullet &bullet : bullets) {
        bullet.draw();
    }
}

void BulletManager::spawn(const BulletConfig bullet_config,
                          const Vector2 start_pos, const Vector2 target_pos)
{
    if (bullets.size() >= spawner.max)
        return;

    bullets.push_back(Bullet({bullet_config, start_pos, target_pos}));
}

void BulletManager::despawn(const size_t index)
{
    if (index >= bullets.size())
        return;

    bullets[index] = bullets.back();
    bullets.pop_back();
}

void BulletManager::update(const float dt)
{
    // update
    for (size_t i = 0; i < bullets.size(); i++) {
        Bullet &bullet = bullets[i];

        bullet.update(dt);

        if (bullet.lifetime.remaining <= 0) {
            despawn(i);
        }
    }
}
