#include "../include/bullet_manager.h"
#include "../include/settings.h"

#include <assert.h>
#include <math.h>

static const float BULLET_SCALE_OFFSET = 0.5f;
static const float MAX_LIFETIME        = 5.0f;

// ----- BULLET ----------------------
void bullet_init(Bullet *bullet, const Vector2 start_pos,
                 const Vector2 target_pos)
{
    assert(bullet);

    bullet->sprite_name    = SPRITE_EFFECT_PURPLE;
    const Rectangle source = sprite_db[bullet->sprite_name];
    bullet->dest           = (Rectangle){start_pos.x, start_pos.y,
                                         source.width * BULLET_SCALE_OFFSET,
                                         source.height * BULLET_SCALE_OFFSET};
    bullet->origin =
        (Vector2){bullet->dest.width / 2.0f, bullet->dest.height / 2.0f};

    // rotate towards target
    float dx         = target_pos.x - bullet->dest.x;
    float dy         = target_pos.y - bullet->dest.y;
    bullet->rotation = atan2f(dy, dx) * RAD2DEG + ROTATION_OFFSET;

    // set direction towards target
    float distance = sqrtf(dx * dx + dy * dy);
    if (distance > 0) {
        bullet->direction.x = dx / distance;
        bullet->direction.y = dy / distance;
    }

    bullet->tint = WHITE;

    bullet->speed  = 400.0f;
    bullet->damage = 1.0f;

    bullet->lifetime = MAX_LIFETIME;
}

// ----- BULLET MANAGER ----------------------
void bullet_manager_init(BulletManager *bullet_manager)
{
    assert(bullet_manager);
}

void bullet_manager_draw(const BulletManager *bullet_manager)
{
    assert(bullet_manager);
}

void bullet_manager_update(BulletManager *bullet_manager, const float dt)
{
    assert(bullet_manager);
}
