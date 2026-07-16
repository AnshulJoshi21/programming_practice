#pragma once

#include "../components.hpp"
#include "../drops/drop_manager.hpp"
#include "enemy.hpp"
#include <vector>

class EnemyManager {
  public:
    std::vector<Enemy>  enemies;
    Components::Spawner spawner;
    Components::Timer   timer;

    EnemyManager();

    void spawn(const Vector2& target_pos);
    void despawn(const int index);
    void update(const float dt, const Vector2& target_pos, DropManager& drop_manager);
    void draw(void) const;
};
