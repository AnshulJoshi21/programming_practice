#pragma once

#include "../components.hpp"
#include "drop_type.hpp"

class Drop {
  public:
    PositionComponent position;
    CircleComponent circle;
    ColorComponent color;
    TextComponent text;
    StateComponent state;
    DropComponent drop;

    Drop(const DropType type, const Vector2 start_pos);

    void draw(void) const;
};
