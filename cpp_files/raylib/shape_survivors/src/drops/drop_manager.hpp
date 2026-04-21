#pragma once

#include "drop.hpp"
#include <vector>

class DropManager {
  private:
    void despawn(const size_t index);

  public:
    std::vector<Drop> drops;

    DropManager();

    void draw(void) const;
    void spawn(const DropType type, const Vector2 start_pos);
    void update(void);
};
