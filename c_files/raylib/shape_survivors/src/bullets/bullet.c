#include "bullet.h"
#include <assert.h>
#include <raymath.h>

void bullet_init(Bullet* bullet, const Vector2 start_pos, const Vector2 target_pos) {
    assert(bullet);

    const float dx       = target_pos.x - start_pos.x;
    const float dy       = target_pos.y - start_pos.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    bullet->direction    = (Vector2){0, 0};
    if (distance > 0) {
        bullet->direction = (Vector2){dx / distance, dy / distance};
    }

    bullet->center       = start_pos;
    bullet->radius       = 7.0f;
    bullet->color        = RED;
    bullet->speed        = 400.0f;
    bullet->damage       = 1;
    bullet->max_lifetime = 1.0f;
    bullet->lifetime     = bullet->max_lifetime;
}

void bullet_update(Bullet* bullet, const float dt) {
    assert(bullet);

    // move
    bullet->center.x += bullet->direction.x * bullet->speed * dt;
    bullet->center.y += bullet->direction.y * bullet->speed * dt;

    // update lifetime
    bullet->lifetime -= dt;
    if (bullet->lifetime <= 0.0f) {
        bullet->lifetime = 0.0f;
    }
}

void bullet_draw(const Bullet* bullet) {
    assert(bullet);

    DrawCircleV(bullet->center, bullet->radius, bullet->color);
}
