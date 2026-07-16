#include "systems.h"
#include "utils.h"
#include <assert.h>
#include <math.h>

// LEVEL + EXP
int system_get_exp_next(const CLevel* level) {
    assert(level);

    return 10 + ((level->level * level->level) * 2);
}

void system_add_exp(CLevel* level, CExp* exp, const int amount) {
    assert(level);
    assert(exp);

    exp->exp += amount;

    while (exp->exp >= exp->exp_next) {
        exp->exp -= exp->exp_next;
        level->level++;
        exp->pending_levelups++;

        exp->exp_next = system_get_exp_next(level);
    }
}

void system_consume_pending_levelups(CExp* exp) {
    assert(exp);

    if (exp->pending_levelups > 0) {
        exp->pending_levelups--;
        return;
    }
}

// RENDER
void system_draw_rect(const CPosition*  position,
                      const CRect*      rect,
                      const CRotation*  rotation,
                      const CColor*     color,
                      const CAnimation* animation) {
    assert(position);
    assert(rect);
    assert(rotation);
    assert(color);
    assert(animation);

    const Rectangle dest   = (Rectangle){position->x, position->y, rect->width, rect->height};
    const Vector2   origin = (Vector2){dest.width / 2.0f, dest.height / 2.0f};

    const Color tint = (animation->hit_timer > 0) ? RED : color->tint;

    DrawRectanglePro(dest, origin, rotation->angle, tint);
}

void system_draw_circle(const CPosition* position, const CCircle* circle, const CColor* color) {
    assert(position);
    assert(circle);
    assert(color);

    const Vector2 center = (Vector2){position->x, position->y};
    DrawCircleV(center, circle->radius, color->tint);
}

void system_draw_centered_text(const CPosition* position,
                               const float      width,
                               const float      height,
                               const CText*     text) {
    assert(position);
    assert(text);

    const Rectangle bounds = (Rectangle){position->x, position->y, width, height};
    utils_center_and_draw_text(
        ORIGIN_CENTER, text->text, bounds, text->font_size, text->spacing, text->tint);
}

// MOVEMENT
void system_set_direction(const CPosition* position,
                          CMovement*       movement,
                          const Vector2    target_pos) {
    assert(position);
    assert(movement);

    const float dx       = target_pos.x - position->x;
    const float dy       = target_pos.y - position->y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) {
        movement->direction = (Vector2){dx / distance, dy / distance};
    }
}

void system_move(CPosition* position, const CMovement* movement, const float dt) {
    assert(position);
    assert(movement);

    position->x += movement->direction.x * movement->speed * dt;
    position->y += movement->direction.y * movement->speed * dt;
}

void system_set_bounds(CPosition*      position,
                       const float     half_w,
                       const float     half_h,
                       const Rectangle bounds) {
    assert(position);

    position->x = fmaxf(bounds.x + half_w, fminf(position->x, bounds.width - half_w));
    position->y = fmaxf(bounds.y + half_h, fminf(position->y, bounds.height - half_h));
}

// UPDATE
void system_update_lifetime(CLifetime* lifetime, const float dt) {
    assert(lifetime);

    lifetime->remaining -= dt;
    if (lifetime->remaining <= 0) {
        lifetime->remaining = 0;
    }
}

void system_update_hit_timer(CAnimation* animation, const float dt) {
    assert(animation);

    animation->hit_timer -= dt;
    if (animation->hit_timer <= 0) {
        animation->hit_timer = 0;
    }
}

void system_update_health(CHealth* health) {
    assert(health);

    health->current = utils_max_int(0, utils_min_int(health->current, health->max));
}

bool system_timer_tick(CTimer* timer) {
    assert(timer);

    const float current_time = GetTime();
    if (current_time - timer->elapsed >= timer->interval) {
        timer->elapsed = current_time;
        return true;
    }
    return false;
}
