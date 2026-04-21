#pragma once

#include "../components.hpp"
#include "../drops/drop_type.hpp"
#include "enemy.hpp"
#include <functional>
#include <vector>

class EnemyManager {
  private:
    void spawn(const Vector2 target_pos);
    void despawn(const size_t index);

  public:
    std::vector<Enemy> enemies;
    SpawnerComponent spawner;
    TimerComponent timer;

    EnemyManager();

    void draw(void) const;
    void
    update(const float dt, const Vector2 target_pos,
           std::function<void(const DropType type, const Vector2 start_pos)>
               spawn_drop);
};
