#pragma once

#include "../components.hpp"
#include "bullet.hpp"
#include <vector>

class BulletManager {
  private:
    void despawn(const size_t index);

  public:
    std::vector<Bullet> bullets;
    SpawnerComponent spawner;

    BulletManager();

    void draw(void) const;
    void spawn(const BulletConfig bullet_config, const Vector2 start_pos,
               const Vector2 target_pos);
    void update(const float dt);
};
