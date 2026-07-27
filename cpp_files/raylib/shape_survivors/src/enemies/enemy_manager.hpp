#pragma once

#include "../utils.hpp"
#include "enemy.hpp"
#include <vector>

class EnemyManager {
  public:
    std::vector<Enemy> enemies;
    IntervalTimer      timer;

    EnemyManager(void);
    void spawn(const Vector2& target_pos);
    void despawn(const std::size_t index);
    void update(const float dt, const Vector2& target_pos);
    void draw(void) const;
};
