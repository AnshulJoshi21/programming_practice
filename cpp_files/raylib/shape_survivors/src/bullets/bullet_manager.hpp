#pragma once

#include "../components.hpp"
#include "bullet.hpp"
#include <vector>

class BulletManager {
  public:
    std::vector<Bullet> bullets;
    Components::Spawner spawner;

    BulletManager();

    void spawn(const BulletConfig& config, const Vector2& start_pos, const Vector2& target_pos);
    void despawn(const int index);
    void update(const float dt);
    void draw(void) const;
};
