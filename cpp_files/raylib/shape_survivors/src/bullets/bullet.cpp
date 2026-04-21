#include "../systems.hpp"
#include "bullet.hpp"
#include <cmath>
#include <raymath.h>

Bullet::Bullet(const BulletConfig bullet_config, const Vector2 start_pos,
               const Vector2 target_pos)
    : position({.x = start_pos.x, .y = start_pos.y}), circle({.radius = 4.0f}),
      color({.tint = RED}),
      move({.speed = bullet_config.speed, .direction = {0, 0}}),
      damage({.amount = bullet_config.damage}),
      lifetime(
          {.max = bullet_config.lifetime, .remaining = bullet_config.lifetime})
{
    system_set_direction(position, move, target_pos);
}

void Bullet::draw(void) const { system_draw_circle(position, circle, color); }

void Bullet::update(const float dt)
{
    system_move(position, move, dt);
    system_update_lifetime(lifetime, dt);
}
