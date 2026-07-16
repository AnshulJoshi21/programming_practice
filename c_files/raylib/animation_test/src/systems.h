#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include <raylib.h>

#// LEVEL + XP
int system_get_xp_next(const CLevel* level);

// RENDER
void system_render_texture(const CTransform* transform, const CRender* render);

// MOVEMENT
void system_set_direction(const CTransform* transform,
                          CMovement*        movement,
                          const Vector2     target_pos);
void system_move_x(CTransform* transform, const CMovement* movement, const float dt);
void system_set_bounds(CTransform* transform, CRender* render, const Rectangle bounds);

// UPDATE
void system_update_xp(CLevel* level, CXp* xp);
void system_update_lifetime(CLifetime* lifetime, const float dt);
void system_update_health(CHealth* health);
bool system_timer_tick(CTimer* timer);
void system_animate(const Entity entity, CAnimation* animation, const float dt);
void system_update_dimenions(const Entity      entity,
                             const CTransform* transform,
                             CRender*          render,
                             const CAnimation* animation);

#endif // SYSTEMS_H
