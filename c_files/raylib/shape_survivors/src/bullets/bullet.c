#include "bullet.h"

#include "../systems.h"

#include <assert.h>
#include <math.h>

void bullet_init(Bullet *bullet, const BulletType type, const Vector2 start_pos,
                 const Vector2 target_pos, const BulletConfig config) {
    assert(bullet);

    const float dx = target_pos.x - start_pos.x;
    const float dy = target_pos.y - start_pos.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));

    bullet->type = type;

    bullet->position.x = start_pos.x;
    bullet->position.y = start_pos.y;

    bullet->circle.radius = 5.0f;

    bullet->color.tint = RED;

    bullet->move.speed = config.speed;
    if (distance > 0)
        bullet->move.direction = (Vector2){dx / distance, dy / distance};

    bullet->damage.value = config.damage;

    bullet->lifetime.max = config.lifetime;
    bullet->lifetime.remaining = bullet->lifetime.max;
}

void bullet_draw(const Bullet *bullet) {
    assert(bullet);

    system_draw_circle(&bullet->position, &bullet->circle, &bullet->color);
}

void bullet_update(Bullet *bullet, const float dt) {
    assert(bullet);

    system_move(&bullet->position, &bullet->move, dt);
    system_update_lifetime(&bullet->lifetime, dt);
}
