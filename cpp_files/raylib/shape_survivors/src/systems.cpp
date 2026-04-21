#include "systems.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>

int system_get_xp_next(const LevelComponent &level)
{
    return 10 + (level.current * level.current * 2);
}

void system_add_xp(LevelComponent &level, XpComponent &xp, const int amount)
{
    xp.xp += amount;

    while (xp.xp >= xp.xp_next) {
        xp.xp -= xp.xp_next;
        level.current++;
        level.pending_levelups++;

        xp.xp_next = system_get_xp_next(level);
    }
}

void system_consume_levelup(LevelComponent &level)
{
    if (level.pending_levelups > 0) {
        level.pending_levelups--;
        return;
    }
}

Rectangle system_get_dest_rect(const PositionComponent &position,
                               const RectComponent &rect)
{
    return {position.x, position.y, rect.width, rect.height};
}

void system_draw_rect(const PositionComponent &position,
                      const RectComponent &rect,
                      const RotationComponent &rotation,
                      const ColorComponent &color,
                      const AnimationComponent &animation)
{
    const Rectangle dest = system_get_dest_rect(position, rect);
    const Vector2 origin = {dest.width / 2.0f, dest.height / 2.0f};
    const Color tint = (animation.hit_timer > 0) ? RED : color.tint;

    DrawRectanglePro(dest, origin, rotation.angle, tint);
}

void system_draw_circle(const PositionComponent &position,
                        const CircleComponent &circle,
                        const ColorComponent &color)
{
    DrawCircleV({position.x, position.y}, circle.radius, color.tint);
}

void system_draw_centered_text(const PositionComponent &position,
                               const float width, const float height,
                               const TextComponent &text)
{
    const Rectangle bounds = {position.x, position.y, width, height};
    center_and_draw_text(OriginType::center, text.text, bounds);
}

void system_set_direction(const PositionComponent &position,
                          MoveComponent &move, const Vector2 target_pos)
{
    const float dx = target_pos.x - position.x;
    const float dy = target_pos.y - position.y;

    const float distance = std::sqrt((dx * dx) + (dy * dy));
    if (distance > 0) {
        move.direction = {dx / distance, dy / distance};
    }
}

void system_move(PositionComponent &position, const MoveComponent &move,
                 const float dt)
{
    position.x += move.direction.x * move.speed * dt;
    position.y += move.direction.y * move.speed * dt;
}

void system_set_bounds(PositionComponent &position, const float half_w,
                       const float half_h, const Rectangle bounds)
{
    position.x = std::max(bounds.x + half_w,
                          std::min(position.x, bounds.width - half_w));
    position.y = std::max(bounds.y + half_h,
                          std::min(position.y, bounds.height - half_h));
}

void system_update_lifetime(LifetimeComponent &lifetime, const float dt)
{
    lifetime.remaining -= dt;
    if (lifetime.remaining <= 0) {
        lifetime.remaining = 0;
    }
}

void system_update_hit_timer(AnimationComponent &animation, const float dt)
{
    animation.hit_timer -= dt;
    if (animation.hit_timer <= 0) {
        animation.hit_timer = 0;
    }
}
