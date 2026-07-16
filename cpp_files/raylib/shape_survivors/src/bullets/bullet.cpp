#include "../systems.hpp"
#include "bullet.hpp"

static const float BULLET_RADIUS = 4.0f;

Bullet::Bullet(const BulletConfig& config, const Vector2& start_pos, const Vector2& target_pos)
    : position({start_pos.x, start_pos.y}),

      circle({.radius = BULLET_RADIUS}),

      color({.tint = RED}),

      movement({.speed = config.speed, .direction = {0, 0}}),

      damage({.current = config.damage}),

      lifetime({.max = config.lifetime, .current = config.lifetime}) {
    //
    Systems::set_direction(position, movement, target_pos);
}

void Bullet::update(const float dt) {
    Systems::move(position, movement, dt);
    Systems::update_lifetime(lifetime, dt);
}

void Bullet::draw(void) const {
    Systems::draw_circle(position, circle, color);
}
