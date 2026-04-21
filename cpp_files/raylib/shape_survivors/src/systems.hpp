#pragma once

#include "components.hpp"
#include <raylib.h>

// level and xp updates
int system_get_xp_next(const LevelComponent &level);
void system_add_xp(LevelComponent &level, XpComponent &xp, const int amount);
void system_consume_levelup(LevelComponent &level);

// render
Rectangle system_get_dest_rect(const PositionComponent &position,
                               const RectComponent &rect);
void system_draw_rect(const PositionComponent &position,
                      const RectComponent &rect,
                      const RotationComponent &rotation,
                      const ColorComponent &color,
                      const AnimationComponent &animation);
void system_draw_circle(const PositionComponent &position,
                        const CircleComponent &circle,
                        const ColorComponent &color);
void system_draw_centered_text(const PositionComponent &position,
                               const float width, const float height,
                               const TextComponent &text);

// movement
void system_set_direction(const PositionComponent &position,
                          MoveComponent &move, const Vector2 target_pos);
void system_move(PositionComponent &position, const MoveComponent &move,
                 const float dt);
void system_set_bounds(PositionComponent &position, const float half_w,
                       const float half_h, const Rectangle bounds);

// updates
void system_update_lifetime(LifetimeComponent &lifetime, const float dt);
void system_update_hit_timer(AnimationComponent &animation, const float dt);
