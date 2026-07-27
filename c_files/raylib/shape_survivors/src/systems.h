#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include <raylib.h>

#// LEVEL + XP
int system_get_xp_next(const CLevel* level);

// RENDER
void system_draw_background_grid(void);
void system_draw_rect(const CPosition*  position,
                      const CRect*      rect,
                      const CRotation*  rotation,
                      const CColor*     color,
                      const CAnimation* animation);
void system_draw_circle(const CPosition* position, const CCircle* circle, const CColor* color);
void system_draw_centered_text(const CPosition* position,
                               const float      width,
                               const float      height,
                               const CText*     text);

// MOVEMENT
void system_set_direction(const CPosition* position, CMovement* movement, const Vector2 target_pos);
void system_move(CPosition* position, const CMovement* movement, const float dt);
void system_set_bounds(CPosition*      position,
                       const float     half_w,
                       const float     half_h,
                       const Rectangle bounds);

// UPDATE
void system_update_xp(CLevel* level, CXp* xp);
void system_update_hit_timer(CAnimation* animation, const float dt);
void system_update_lifetime(CLifetime* lifetime, const float dt);
void system_update_health(CHealth* health);
bool system_timer_tick(CTimer* timer);

#endif // SYSTEMS_H
