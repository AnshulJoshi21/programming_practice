#pragma once

#include "drop.hpp"
#include <vector>

class DropManager {
  public:
    std::vector<Drop> drops;

    DropManager();

    DropType get_random_drop_type(void);
    void     spawn(const DropType type, const Vector2& start_pos);
    void     despawn(const int index);
    void     update(void);
    void     draw(void) const;
};
