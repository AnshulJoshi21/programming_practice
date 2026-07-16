#include "components.hpp"
#include "settings.hpp"
#include "systems.hpp"
#include <cmath>

namespace Systems {

// LEVEL + XP
int get_xp_next(const Components::Level& level) {
    return 10 + ((level.current * level.current) * 2);
}

// RENDERING
void draw_background_grid(void) {
    const float thickness  = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = 100.0f;

    for (float x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx({x, 0}, {x, MAP_SIZE}, thickness, color);
    }

    for (float y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx({0, y}, {MAP_SIZE, y}, thickness, color);
    }
}

void draw_rect(const Components::Position&  position,
               const Components::Rotation&  rotation,
               const Components::Rect&      rect,
               const Components::Color_&    color,
               const Components::Animation& animation) {
    const Rectangle dest   = {position.x, position.y, rect.width, rect.height};
    const Vector2   origin = {dest.width / 2.0f, dest.height / 2.0f};

    const Color tint = (animation.hit_timer > 0) ? RED : color.tint;

    DrawRectanglePro(dest, origin, rotation.angle, tint);
}

void draw_circle(const Components::Position& position,
                 const Components::Circle&   circle,
                 const Components::Color_&   color) {
    DrawCircleV({position.x, position.y}, circle.radius, color.tint);
}

// MOVEMENT
void set_direction(const Components::Position& position,
                   Components::Movement&       movement,
                   const Vector2               target_pos) {
    const float dx       = target_pos.x - position.x;
    const float dy       = target_pos.y - position.y;
    const float distance = std::sqrt((dx * dx) + (dy * dy));

    if (distance > 0) {
        movement.direction = {dx / distance, dy / distance};
    }
}

void move(Components::Position& position, const Components::Movement& movement, const float dt) {
    position.x += movement.direction.x * movement.speed * dt;
    position.y += movement.direction.y * movement.speed * dt;
}

void set_bounds(Components::Position& position,
                const float           half_w,
                const float           half_h,
                const Rectangle       bounds) {
    position.x = std::max(bounds.x + half_w, std::min(position.x, bounds.width - half_w));
    position.y = std::max(bounds.y + half_h, std::min(position.y, bounds.height - half_h));
}

// UPDATES
void update_xp(Components::Level& level, Components::Xp& xp) {
    if (xp.current >= xp.next) {
        xp.current -= xp.next;
        level.current += 1;
        level.pending += 1;
        xp.next = get_xp_next(level);
    }
}

void update_lifetime(Components::Lifetime& lifetime, const float dt) {
    lifetime.current -= dt;
    if (lifetime.current <= 0) {
        lifetime.current = 0;
    }
}

void update_hit_timer(Components::Animation& animation, const float dt) {
    animation.hit_timer -= dt;
    if (animation.hit_timer <= 0) {
        animation.hit_timer = 0;
    }
}

void update_health(Components::Health& health) {
    health.current = std::max(0, std::min(health.current, health.max));
}

} // namespace Systems
