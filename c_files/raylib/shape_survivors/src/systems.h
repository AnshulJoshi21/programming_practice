#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "components.h"
#include "utils.h"

Rectangle system_get_dest_rect(const PositionComponent *position, const RectComponent *rect);

void system_draw_rect(const PositionComponent *position, const RectComponent *rect,
                      const RotationComponent *rotation, const ColorComponent *color,
                      const TextComponent *text, const AnimationComponent *animation);

void system_draw_circle(const PositionComponent *position, const CircleComponent *circle,
                        const ColorComponent *color);

void system_draw_hp_bar(const OriginType type, const PositionComponent *position,
                        const RectComponent *rect, const HealthComponent *hp);

void system_set_direction(const PositionComponent *position, MoveComponent *move,
                          const Vector2 target_pos);

void system_move(PositionComponent *position, const MoveComponent *move, const float dt);

void system_set_bounds_rect(PositionComponent *position, const RectComponent *rect,
                            const Rectangle bounds_rect);

void system_update_hit_timer(AnimationComponent *animation, const float dt);
void system_update_lifetime(LifetimeComponent *lifetime, const float dt);

bool system_timer_tick(TimerComponent *timer);

int system_xp_to_next_level(XpComponent *xp);
void system_add_xp(XpComponent *xp, const DropComponent *drop);
void system_consume_levelups(XpComponent *xp);

#endif  // SYSTEMS_H
