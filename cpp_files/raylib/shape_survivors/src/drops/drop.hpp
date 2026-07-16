#pragma once

#include "../components.hpp"

enum class DropType {
    NONE,
    XP,
    HP,
};

class Drop {
  public:
    Components::State    state;
    Components::Position position;
    Components::Circle   circle;
    Components::Color_   color;
    Components::Text     text;
    DropType             type;
    int                  amount;

    Drop(const DropType drop_type, const Vector2& start_pos);

    void draw(void) const;
};
