#include "systems.h"
#include "utils.h"
#include <assert.h>
#include <math.h>

// LEVEL + XP
int system_get_xp_next(const LevelComponent* level) {
    assert(level);

    return 10 + (level->current * level->current * 2);
}

void system_add_xp(LevelComponent* level, XpComponent* xp, const int amount) {
    assert(level);
    assert(xp);

    xp->current += amount;
    while (xp->current >= xp->next) {
        xp->current -= xp->next;
        level->current++;
        xp->pending_levelups++;

        xp->next = system_get_xp_next(level);
    }
}

void system_consume_pending_levelups(XpComponent* xp) {
    assert(xp);

    if (xp->pending_levelups > 0) {
        xp->pending_levelups--;
        return;
    }
}

// RENDER
Rectangle system_get_dest_rect(const PositionComponent* position, const RectComponent* rect) {
    assert(position);
    assert(rect);

    return (Rectangle){position->x, position->y, rect->width, rect->height};
}

Vector2 system_get_origin(const Rectangle* dest) {
    assert(dest);

    return (Vector2){dest->width / 2.0f, dest->height / 2.0f};
}

void system_draw_rect(const PositionComponent*  position,
                      const RectComponent*      rect,
                      const RotationComponent*  rotation,
                      const ColorComponent*     color,
                      const AnimationComponent* animation) {
    assert(position);
    assert(rect);
    assert(rotation);
    assert(color);
    assert(animation);

    const Rectangle dest   = system_get_dest_rect(position, rect);
    const Vector2   origin = system_get_origin(&dest);
    const Color     tint   = (animation->hit_timer > 0) ? RED : color->tint;

    DrawRectanglePro(dest, origin, rotation->angle, tint);
}

void system_draw_circle(const PositionComponent* position,
                        const CircleComponent*   circle,
                        const ColorComponent*    color) {
    assert(position);
    assert(circle);
    assert(color);

    DrawCircleV((Vector2){position->x, position->y}, circle->radius, color->tint);
}

void system_draw_centered_text(const PositionComponent* position,
                               const float              half_w,
                               const float              half_h,
                               const TextComponent*     text) {
    assert(position);
    assert(text);

    const Rectangle dest = (Rectangle){position->x, position->y, half_w * 2, half_h * 2};

    center_and_draw_text(
        ORIGIN_TYPE_CENTER, text->text, dest, text->font_size, text->spacing, text->tint);
}

// MOVEMENT
void system_set_direction(const PositionComponent* position,
                          MoveComponent*           move,
                          const Vector2            target_pos) {
    assert(position);
    assert(move);

    const float dx       = target_pos.x - position->x;
    const float dy       = target_pos.y - position->y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) {
        move->direction = (Vector2){dx / distance, dy / distance};
    }
}

void system_move(PositionComponent* position, const MoveComponent* move, const float dt) {
    assert(position);
    assert(move);

    position->x += move->direction.x * move->speed * dt;
    position->y += move->direction.y * move->speed * dt;
}

void system_set_bounds(PositionComponent*   position,
                       const RectComponent* rect,
                       const Rectangle      bounds) {
    assert(position);
    assert(rect);

    const Rectangle dest   = system_get_dest_rect(position, rect);
    const Vector2   origin = system_get_origin(&dest);

    position->x = fmaxf(bounds.x + origin.x, fminf(position->x, bounds.width - origin.x));
    position->y = fmaxf(bounds.y + origin.y, fminf(position->y, bounds.height - origin.y));
}

// UPDATE
void system_update_lifetime(LifetimeComponent* lifetime, const float dt) {
    assert(lifetime);

    lifetime->remaining -= dt;
    if (lifetime->remaining <= 0) {
        lifetime->remaining = 0;
    }
}

void system_update_hit_timer(AnimationComponent* animation, const float dt) {
    assert(animation);

    animation->hit_timer -= dt;
    if (animation->hit_timer <= 0) {
        animation->hit_timer = 0;
    }
}

bool system_timer_tick(TimerComponent* timer) {
    assert(timer);

    float current = GetTime();
    if (current - timer->elapsed >= timer->interval) {
        timer->elapsed = current;

        return true;
    }
    return false;
}
