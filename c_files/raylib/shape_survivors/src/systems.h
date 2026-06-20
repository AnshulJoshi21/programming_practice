#pragma once

#include "components.h"
#include "systems.h"
#include <assert.h>
#include <math.h>

// LEVEL + XP
int  system_get_xp_next(const LevelComponent* level);
void system_add_xp(LevelComponent* level, XpComponent* xp, const int amount);
void system_consume_pending_levelups(XpComponent* xp);

// RENDER
Rectangle system_get_dest_rect(const PositionComponent* position, const RectComponent* rect);
Vector2   system_get_origin(const Rectangle* dest);

void system_draw_rect(const PositionComponent*  position,
                      const RectComponent*      rect,
                      const RotationComponent*  rotation,
                      const ColorComponent*     color,
                      const AnimationComponent* animation);

void system_draw_circle(const PositionComponent* position,
                        const CircleComponent*   circle,
                        const ColorComponent*    color);

void system_draw_centered_text(const PositionComponent* position,
                               const float              half_w,
                               const float              half_h,
                               const TextComponent*     text);

// MOVEMENT
void system_set_direction(const PositionComponent* position,
                          MoveComponent*           move,
                          const Vector2            target_pos);
void system_move(PositionComponent* position, const MoveComponent* move, const float dt);
void system_set_bounds(PositionComponent*   position,
                       const RectComponent* rect,
                       const Rectangle      bounds);

// UPDATE
void system_update_lifetime(LifetimeComponent* lifetime, const float dt);
void system_update_hit_timer(AnimationComponent* animation, const float dt);

bool system_timer_tick(TimerComponent* timer);
