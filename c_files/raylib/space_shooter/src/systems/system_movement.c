#include "../../include/settings.h"
#include "../../include/systems/system_movement.h"
#include "../../include/systems/system_render.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

void system_set_move_direction(TransformComponent *t, MovementComponent *m,
                               Vector2 target_pos)
{
    assert(t && m);

    m->move_direction.x = target_pos.x - t->position.x;
    m->move_direction.y = target_pos.y - t->position.y;

    if (m->move_direction.x != 0 || m->move_direction.y != 0) {
        m->move_direction = Vector2Normalize(m->move_direction);
    }
}

void system_rotate_towards_target(TransformComponent *t, MovementComponent *m,
                                  Vector2 target_pos)
{
    assert(t && m);

    m->look_direction.x = target_pos.x - t->position.x;
    m->look_direction.y = target_pos.y - t->position.y;
    t->rotation = atan2f(m->look_direction.y, m->look_direction.x) * RAD2DEG +
                  ROTATION_OFFSET;
}

void system_move(TransformComponent *t, MovementComponent *m, float dt)
{
    assert(t && m);

    t->position.x += m->move_direction.x * m->speed * dt;
    t->position.y += m->move_direction.y * m->speed * dt;
}

void system_set_bounds(TransformComponent *t, RenderComponent *r,
                       Rectangle bounds_rect)
{
    assert(t && r);

    Rectangle dest = system_get_dest_rect(t, r);

    // origin centered rectangle
    t->position.x =
        fmaxf(bounds_rect.x + dest.width / 2.0f,
              fminf(t->position.x,
                    bounds_rect.x + bounds_rect.width - dest.width / 2.0f));

    t->position.y =
        fmaxf(bounds_rect.y + dest.height / 2.0f,
              fminf(t->position.y,
                    bounds_rect.x + bounds_rect.height - dest.height / 2.0f));
}
