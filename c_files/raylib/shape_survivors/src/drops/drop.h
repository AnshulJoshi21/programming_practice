#pragma once

#include "../components.h"

typedef struct {
    StateComponent    state;
    PositionComponent position;
    CircleComponent   circle;
    ColorComponent    color;
    TextComponent     text;
    DropComponent     drop;
} Drop;

void drop_init(Drop* drop, const DropType type, const Vector2 start_pos);
void drop_draw(const Drop* drop);
