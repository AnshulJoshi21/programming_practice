#include "../systems.hpp"
#include "drop.hpp"
#include <cmath>
#include <raymath.h>

Drop::Drop(const DropType type, const Vector2 start_pos)
    : position({.x = start_pos.x, .y = start_pos.y}), circle({.radius = 20.0f}),
      color({.tint = GRAY}), state({.active = true}),
      drop({.type = type, .amount = 0})
{
    switch (type) {
    case DropType::xp:
        text.text = "XP";
        drop.amount = 10;
        break;
    case DropType::hp:
        text.text = "HP";
        drop.amount = 10;
        break;
    }
}

void Drop::draw(void) const
{
    if (state.active) {
        system_draw_circle(position, circle, color);
        system_draw_centered_text(position, circle.radius * 2,
                                  circle.radius * 2, text);
    }
}
