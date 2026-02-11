#ifndef SYSTEM_MOVEMENT_H
#define SYSTEM_MOVEMENT_H

#include "../components.h"

void system_normalize_direction(MovementComponent *m);
void system_set_target_direction(TransformComponent *t, MovementComponent *m,
                                 Vector2 target_pos);
void system_rotate_towards_target(TransformComponent *t, MovementComponent *m,
                                  Vector2 target_pos);
void system_move(TransformComponent *t, MovementComponent *m, float dt);

#endif // SYSTEM_MOVEMENT_H
