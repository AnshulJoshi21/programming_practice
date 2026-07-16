#pragma once

#include "components.hpp"

namespace Systems {

// LEVEL + XP
int get_xp_next(const Components::Level& level);

// RENDERING
void draw_background_grid(void);
void draw_rect(const Components::Position&  position,
               const Components::Rotation&  rotation,
               const Components::Rect&      rect,
               const Components::Color_&    color,
               const Components::Animation& animation);
void draw_circle(const Components::Position& position,
                 const Components::Circle&   circle,
                 const Components::Color_&   color);

// MOVEMENT
void set_direction(const Components::Position& position,
                   Components::Movement&       movement,
                   const Vector2               target_pos);
void move(Components::Position& position, const Components::Movement& movement, const float dt);
void set_bounds(Components::Position& position,
                const float           half_w,
                const float           half_h,
                const Rectangle       bounds);

// UPDATES
void update_xp(Components::Level& level, Components::Xp& xp);
void update_lifetime(Components::Lifetime& lifetime, const float dt);
void update_hit_timer(Components::Animation& animation, const float dt);
void update_health(Components::Health& health);

} // namespace Systems
