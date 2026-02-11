#include "../../include/settings.h"
#include "../../include/systems/system_movement.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

void system_normalize_direction(MovementComponent *m)
{
    assert(m);

    m->direction = Vector2Normalize(m->direction);
}

void system_set_target_direction(TransformComponent *t, MovementComponent *m,
                                 Vector2 target_pos)
{
    assert(t && m);

    m->direction.x = target_pos.x - t->position.x;
    m->direction.y = target_pos.y - t->position.y;

    if (m->direction.x != 0 || m->direction.y != 0) {
        m->direction = Vector2Normalize(m->direction);
    }
}

void system_rotate_towards_target(TransformComponent *t, MovementComponent *m,
                                  Vector2 target_pos)
{
    assert(t && m);

    system_set_target_direction(t, m, target_pos);

    t->rotation =
        atan2f(m->direction.y, m->direction.x) * RAD2DEG + ROTATION_OFFSET;
}

void system_move(TransformComponent *t, MovementComponent *m, float dt)
{
    assert(t && m);

    t->position.x += m->direction.x * m->speed * dt;
    t->position.y += m->direction.y * m->speed * dt;
}
