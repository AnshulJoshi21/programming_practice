#include "systems.h"
#include "utils.h"

#include <assert.h>
#include <raymath.h>

Rectangle system_get_dest_rect(const PositionComponent *position, const RectComponent *rect) {
    assert(position);
    assert(rect);

    return (Rectangle){position->x, position->y, rect->width, rect->height};
}

void system_draw_rect(const PositionComponent *position, const RectComponent *rect,
                      const RotationComponent *rotation, const ColorComponent *color,
                      const TextComponent *text, const AnimationComponent *animation) {
    assert(position);
    assert(rect);
    assert(rotation);
    assert(color);
    assert(text);
    assert(animation);

    const Rectangle dest = system_get_dest_rect(position, rect);
    const Vector2 origin = (Vector2){dest.width / 2, dest.height / 2};

    const Color tint = (animation->hit_timer > 0) ? RED : color->tint;

    // rect
    DrawRectanglePro(dest, origin, rotation->value, tint);

    // text
    center_and_draw_text(ORIGIN_CENTER, text->text, dest, 20.0f, 0.0f, WHITE);

    // outline rect
    const Rectangle outline_rect =
        (Rectangle){dest.x - origin.x, dest.y - origin.y, rect->width, rect->height};

    DrawRectangleLinesEx(outline_rect, 4.0f, BLACK);
}

void system_draw_circle(const PositionComponent *position, const CircleComponent *circle,
                        const ColorComponent *color) {
    assert(position);
    assert(circle);
    assert(color);

    DrawCircleV((Vector2){position->x, position->y}, circle->radius, color->tint);
}

void system_draw_hp_bar(const OriginType type, const PositionComponent *position,
                        const RectComponent *rect, const HealthComponent *hp) {
    assert(position);
    assert(rect);

    const float width = rect->width + 10.0f;
    const float height = 10.0f;

    float x;
    float y;

    switch (type) {
        case ORIGIN_CENTER: {
            x = position->x - rect->width / 2.0f - (width - rect->width) / 2.0f;
            y = position->y - rect->height / 2.0f - height * 1.5f;
        } break;

        case ORIGIN_TOP_LEFT: {
            x = position->x - (width - rect->width) / 2.0f;
            y = position->y - height * 1.5f;
        } break;
    }

    const Rectangle bounds = (Rectangle){x, y, width, height};
    const float border_thickness = 1.0f;

    const Color background_color = WHITE;
    const Color border_color = BLACK;
    const Color fill_color = RED;

    draw_progress_bar(hp->max_hp, hp->hp, bounds, border_thickness, background_color, border_color,
                      fill_color);
}

void system_set_direction(const PositionComponent *position, MoveComponent *move,
                          const Vector2 target_pos) {
    assert(position);
    assert(move);

    const float dx = target_pos.x - position->x;
    const float dy = target_pos.y - position->y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) {
        move->direction = (Vector2){dx / distance, dy / distance};
    }
}

void system_move(PositionComponent *position, const MoveComponent *move, const float dt) {
    assert(position);
    assert(move);

    position->x += move->direction.x * move->speed * dt;
    position->y += move->direction.y * move->speed * dt;
}

void system_set_bounds_rect(PositionComponent *position, const RectComponent *rect,
                            const Rectangle bounds_rect) {
    assert(position);
    assert(rect);

    const float half_w = rect->width / 2.0f;
    const float half_h = rect->height / 2.0f;

    position->x = fmaxf(bounds_rect.x + half_w, fminf(position->x, bounds_rect.width - half_w));
    position->y = fmaxf(bounds_rect.y + half_h, fminf(position->y, bounds_rect.height - half_h));
}

void system_update_hit_timer(AnimationComponent *animation, const float dt) {
    assert(animation);

    animation->hit_timer -= dt;
    if (animation->hit_timer <= 0) {
        animation->hit_timer = 0.0f;
    }
}

void system_update_lifetime(LifetimeComponent *lifetime, const float dt) {
    assert(lifetime);

    lifetime->remaining -= dt;
    if (lifetime->remaining <= 0) {
        lifetime->remaining = 0.0f;
    }
}

bool system_timer_tick(TimerComponent *timer) {
    assert(timer);

    const float current = GetTime();
    if (current - timer->elapsed >= timer->interval) {
        timer->elapsed = current;

        return true;
    }

    return false;
}

int system_xp_to_next_level(XpComponent *xp) {
    assert(xp);

    return 10 + (xp->level * xp->level * 2);
}

void system_add_xp(XpComponent *xp, const DropComponent *drop) {
    assert(xp);

    xp->xp += drop->amount;

    while (xp->xp >= xp->xp_next) {
        xp->xp -= xp->xp_next;
        xp->level++;
        xp->xp_next = system_xp_to_next_level(xp);
        xp->pending_levelups++;
    }
}

void system_consume_levelups(XpComponent *xp) {
    assert(xp);

    if (xp->pending_levelups > 0) {
        xp->pending_levelups--;
        return;
    }
}
