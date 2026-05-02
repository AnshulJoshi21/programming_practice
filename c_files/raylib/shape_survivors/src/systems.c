#include "settings.h"
#include "systems.h"
#include "utils.h"
#include <assert.h>
#include <math.h>

// XP + LEVELUPS
int system_get_xp_next(const LevelComponent *level) {
  assert(level);

  return (level->level * level->level * 2);
}

void system_add_xp(LevelComponent *level, XpComponent *xp, const int amount) {
  assert(level);
  assert(xp);

  xp->xp += amount;

  while (xp->xp >= xp->xp_next) {
    xp->xp -= xp->xp_next;
    xp->pending_levelups++;
    level->level++;
    xp->xp_next = system_get_xp_next(level);
  }
}

void system_consume_levelups(XpComponent *xp) {
  assert(xp);

  if (xp->pending_levelups > 0) {
    xp->pending_levelups--;
    return;
  }
}

// RENDER
void system_draw_background_grid(void) {
  const float thickness = 2.0f;
  const Color color = LIGHTGRAY;
  const float block_size = 400.0f;

  for (float x = 0; x < MAP_SIZE; x += block_size) {
    DrawLineEx((Vector2){x, 0}, (Vector2){x, MAP_SIZE}, thickness, color);
  }
  for (float y = 0; y < MAP_SIZE; y += block_size) {
    DrawLineEx((Vector2){0, y}, (Vector2){MAP_SIZE, y}, thickness, color);
  }
}

Rectangle system_get_dest_rect(const PositionComponent *position,
                               const RectComponent *rect) {
  assert(position);
  assert(rect);

  return (Rectangle){position->x, position->y, rect->width, rect->height};
}

void system_draw_rect(const PositionComponent *position,
                      const RectComponent *rect,
                      const RotationComponent *rotation,
                      const ColorComponent *color,
                      const AnimationComponent *animation) {
  assert(position);
  assert(rect);
  assert(rotation);
  assert(color);
  assert(animation);

  const Rectangle dest = system_get_dest_rect(position, rect);
  const Vector2 origin = (Vector2){dest.width / 2.0f, dest.height / 2.0f};

  const Color tint = (animation->hit_timer > 0) ? RED : color->tint;

  DrawRectanglePro(dest, origin, rotation->angle, tint);
}

void system_draw_circle(const PositionComponent *position,
                        const CircleComponent *circle,
                        const ColorComponent *color) {
  assert(position);
  assert(circle);
  assert(color);

  DrawCircleV((Vector2){position->x, position->y}, circle->radius, color->tint);
}

void system_draw_centered_text(const TextComponent *text,
                               const Rectangle bounds) {
  assert(text);

  center_and_draw_text(ORIGIN_CENTER, text->text, bounds, text->font_size,
                       text->spacing, text->tint);
}

// MOVEMENT
void system_set_direction(const PositionComponent *position,
                          MoveComponent *move, const Vector2 target_pos) {
  assert(position);
  assert(move);

  const float dx = target_pos.x - position->x;
  const float dy = target_pos.y - position->y;
  const float distance = sqrtf((dx * dx) + (dy * dy));
  if (distance > 0) {
    move->direction = (Vector2){dx / distance, dy / distance};
  }
}

void system_move(PositionComponent *position, const MoveComponent *move,
                 const float dt) {
  assert(position);
  assert(move);

  position->x += move->direction.x * move->speed * dt;
  position->y += move->direction.y * move->speed * dt;
}

void system_set_bounds(PositionComponent *position, const float half_w,
                       const float half_h, const Rectangle bounds) {
  assert(position);

  position->x =
      fmaxf(bounds.x + half_w, fminf(position->x, bounds.width - half_w));
  position->y =
      fmaxf(bounds.y + half_h, fminf(position->y, bounds.height - half_h));
}

// UPDATES
void system_update_lifetime(LifetimeComponent *lifetime, const float dt) {
  assert(lifetime);

  lifetime->remaining -= dt;
  if (lifetime->remaining <= 0.0f) {
    lifetime->remaining = 0.0f;
  }
}
void system_update_hit_timer(AnimationComponent *animation, const float dt) {
  assert(animation);

  animation->hit_timer -= dt;
  if (animation->hit_timer <= 0.0f) {
    animation->hit_timer = 0.0f;
  }
}
