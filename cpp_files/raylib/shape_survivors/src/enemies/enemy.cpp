#include "../settings.hpp"
#include "../utils.hpp"
#include "enemy.hpp"
#include <raymath.h>

Enemy::Enemy(const EnemyType type, const Vector2& target_pos) {
    const float random_angle = utils::randf(0, 2 * PI);
    const float random_distance
        = utils::randf(GetScreenWidth() / 2.0f, GetScreenWidth() / 2.0f + 100.0f);

    const Vector2 pos = {
        cosf(random_angle) * random_distance + target_pos.x,
        sinf(random_angle) * random_distance + target_pos.y,
    };

    const EnemyDef& def = enemy_db[static_cast<std::size_t>(type)];

    rect      = {pos.x, pos.y, def.width, def.height};
    origin    = {rect.width / 2.0f, rect.height / 2.0f};
    rotation  = 0.0f;
    color     = def.color;
    speed     = def.speed;
    direction = {0, 0};
    damage    = def.damage;
    hp        = def.hp;
    hit_timer = 0.0f;
}

void Enemy::update(const float dt, const Vector2& target_pos) {
    // set direction
    const float dx       = target_pos.x - rect.x;
    const float dy       = target_pos.y - rect.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) { // move
        direction = {dx / distance, dy / distance};

        rect.x += direction.x * speed * dt;
        rect.y += direction.y * speed * dt;

        // set bounds
        const float half_w = rect.width / 2.0f;
        const float half_h = rect.height / 2.0f;

        rect.x = Clamp(rect.x, half_w, MAP_SIZE - half_w);
        rect.y = Clamp(rect.y, half_h, MAP_SIZE - half_h);
    }
}

void Enemy::draw(void) const {
    DrawRectanglePro(rect, origin, rotation, color);
}
