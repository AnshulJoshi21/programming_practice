#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H

#include "../components.h"

void system_set_move_direction(TransformComponent *t, MovementComponent *m,
                               Vector2 target_pos);
void system_rotate_towards_target(TransformComponent *t, MovementComponent *m,
                                  Vector2 target_pos);
void system_move(TransformComponent *t, MovementComponent *m, float dt);

void system_set_bounds(TransformComponent *t, RenderComponent *r,
                       Rectangle bounds_rect);

#endif // SYSTEM_MOVEMENT_H
