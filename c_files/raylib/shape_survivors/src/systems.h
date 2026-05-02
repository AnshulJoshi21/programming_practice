#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include <raylib.h>

// XP + LEVELUPS
int system_get_xp_next(const LevelComponent *level);
void system_add_xp(LevelComponent *level, XpComponent *xp, const int amount);
void system_consume_levelups(XpComponent *xp);

// RENDER
void system_draw_background_grid(void);
Rectangle system_get_dest_rect(const PositionComponent *position,
                               const RectComponent *rect);
void system_draw_rect(const PositionComponent *position,
                      const RectComponent *rect,
                      const RotationComponent *rotation,
                      const ColorComponent *color,
                      const AnimationComponent *animation);
void system_draw_circle(const PositionComponent *position,
                        const CircleComponent *circle,
                        const ColorComponent *color);
void system_draw_centered_text(const TextComponent *text,
                               const Rectangle bounds);

// MOVEMENT
void system_set_direction(const PositionComponent *position,
                          MoveComponent *move, const Vector2 target_pos);
void system_move(PositionComponent *position, const MoveComponent *move,
                 const float dt);
void system_set_bounds(PositionComponent *position, const float half_w,
                       const float half_h, const Rectangle bounds);

// UPDATES
void system_update_lifetime(LifetimeComponent *lifetime, const float dt);
void system_update_hit_timer(AnimationComponent *animation, const float dt);

#endif // SYSTEMS_H
