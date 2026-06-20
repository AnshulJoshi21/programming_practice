#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"

// LEVEL + XP
int  system_get_xp_next(const CLevel* level);
void system_add_xp(CLevel* level, CXp* xp, const int amount);
void system_consume_xp(CXp* xp);

// RENDER
void system_draw_rect(const CPosition*  position,
                      const CRect*      rect,
                      const CRotation*  rotation,
                      const CAnimation* animation,
                      const CColor*     color);
void system_draw_circle(const CPosition* position, const CCircle* circle, const CColor* color);
void system_draw_centered_text(const CText* text, const Rectangle bounds);

// MOVEMENT
void system_set_direction(const CPosition* position, CMove* move, const Vector2* target_pos);
void system_move(CPosition* position, const CMove* move, const float dt);
void system_set_bounds(CPosition* position, CRect* rect, const Rectangle bounds);

// UPDATES
void system_update_hit_timer(CAnimation* animation, const float dt);
void system_update_lifetime(CLifetime* lifetime, const float dt);

#endif // SYSTEMS_H
