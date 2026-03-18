#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "ecs.h"

void system_draw(const World *world);
void system_handle_update(World *world);
void system_move(World *world, const float dt);
void system_set_bounds(World *world);

#endif // SYSTEMS_H
