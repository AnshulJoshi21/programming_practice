#include "../systems.h"
#include "bullet.h"
#include <assert.h>

void bullet_init(Bullet*             bullet,
                 const BulletConfig* config,
                 const Vector2       start_pos,
                 const Vector2       target_pos) {
    assert(bullet);

    bullet->position.x = start_pos.x;
    bullet->position.y = start_pos.y;

    bullet->circle.radius = 4.0f;

    bullet->color.tint = RED;

    bullet->move.speed     = config->speed;
    bullet->move.direction = (Vector2){0, 0};

    bullet->damage.value = config->damage;

    bullet->lifetime.max       = config->lifetime;
    bullet->lifetime.remaining = config->lifetime;

    system_set_direction(&bullet->position, &bullet->move, target_pos);
}

void bullet_update(Bullet* bullet, const float dt) {
    assert(bullet);

    system_move(&bullet->position, &bullet->move, dt);
    system_update_lifetime(&bullet->lifetime, dt);
}

void bullet_draw(const Bullet* bullet) {
    assert(bullet);

    system_draw_circle(&bullet->position, &bullet->circle, &bullet->color);
}
