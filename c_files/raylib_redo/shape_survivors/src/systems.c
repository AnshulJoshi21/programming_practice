#include "settings.h"
#include "systems.h"
#include "utils.h"
#include <assert.h>
#include <math.h>

// LEVEL + XP

int system_get_xp_next(const CLevel* level) {
    assert(level);

    return 10 + (level->level * level->level * 2);
}

void system_add_xp(CLevel* level, CXp* xp, const int amount) {
    assert(level);
    assert(xp);

    xp->xp += amount;
    while (xp->xp >= xp->xp_next) {
        xp->xp -= xp->xp_next;
        level->level++;
        xp->pending_levelups++;

        xp->xp_next = system_get_xp_next(level);
    }
}

void system_consume_xp(CXp* xp) {
    assert(xp);

    if (xp->pending_levelups > 0) {
        xp->pending_levelups--;
        return;
    }
}

// RENDER

void system_draw_rect(const CPosition*  position,
                      const CRect*      rect,
                      const CRotation*  rotation,
                      const CAnimation* animation,
                      const CColor*     color) {
    assert(position);
    assert(rect);
    assert(rotation);
    assert(animation);
    assert(color);

    const Rectangle dest   = (Rectangle){position->x, position->y, rect->width, rect->height};
    const Vector2   origin = (Vector2){dest.width / 2.0f, dest.height / 2.0f};
    const Color     tint   = (animation->hit_timer > 0) ? RED : color->tint;

    DrawRectanglePro(dest, origin, rotation->angle, tint);
}

void system_draw_circle(const CPosition* position, const CCircle* circle, const CColor* color) {
    assert(position);
    assert(circle);
    assert(color);

    DrawCircleV((Vector2){position->x, position->y}, circle->radius, color->tint);
}

void system_draw_centered_text(const CText* text, const Rectangle bounds) {
    assert(text);

    center_and_draw_text(ORIGIN_CENTER, text, bounds);
}

// MOVEMENT

void system_set_direction(const CPosition* position, CMove* move, const Vector2* target_pos) {
    const float dx = target_pos->x - position->x;
    const float dy = target_pos->y - position->y;

    const float distance = sqrtf(dx * dx + dy * dy);
    if (distance > 0) {
        move->direction = (Vector2){dx / distance, dy / distance};
    }
}

void system_move(CPosition* position, const CMove* move, const float dt) {
    assert(position);

    position->x += move->direction.x * move->speed * dt;
    position->y += move->direction.y * move->speed * dt;
}

void system_set_bounds(CPosition* position, CRect* rect, const Rectangle bounds) {
    const float half_w = rect->width / 2.0f;
    const float half_h = rect->height / 2.0f;

    position->x = fmaxf(bounds.x + half_w, fminf(position->x, MAP_SIZE - half_w));
    position->y = fmaxf(bounds.y + half_h, fminf(position->y, MAP_SIZE - half_h));
}

// UPDATES

void system_update_hit_timer(CAnimation* animation, const float dt) {
    assert(animation);

    animation->hit_timer -= dt;
    if (animation->hit_timer < 0) {
        animation->hit_timer = 0;
    }
}

void system_update_lifetime(CLifetime* lifetime, const float dt) {
    assert(lifetime);

    lifetime->life -= dt;
    if (lifetime->life < 0) {
        lifetime->life = 0;
    }
}
