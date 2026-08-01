#include "bullet_projectile.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

const ProjectileDef projectile_db[PROJECTILE_TYPE_MAX] = {
    [PROJECTILE_TYPE_MAGIC_MISSILE] = {.name        = "Magic Missile",
                                       .pattern     = BULLET_PATTERN_PROJECTILE,
                                       .damage_mode = DAMAGE_MODE_INSTANT_HIT,
                                       .radius      = 5.0f,
                                       .color       = RED,
                                       .speed       = 300.0f,
                                       .damage      = 1.0f,
                                       .fire_rate   = 1.0f,
                                       .lifetime    = 1.0f},
};

void projectile_init(ProjectileBullet*       bullet,
                     const EntityConfig*     econfig,
                     const ProjectileConfig* config) {
    assert(bullet);
    assert(econfig);
    assert(config);

    const ProjectileDef* def = &projectile_db[econfig->type];

    bullet->type  = econfig->type;
    bullet->level = econfig->level;

    bullet->center     = config->center;
    bullet->lifetime   = def->lifetime;
    bullet->homing     = config->homing;
    bullet->target_pos = NULL;

    // set direction
    const float dx       = config->target_pos.x - config->center.x;
    const float dy       = config->target_pos.y - config->center.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) {
        bullet->direction = (Vector2){dx / distance, dy / distance};
    }

    if (bullet->homing)
        bullet->target_pos = &config->target_pos;
}

void projectile_update(ProjectileBullet* bullet, const float dt) {
    assert(bullet);

    const ProjectileDef* def = &projectile_db[bullet->type];

    if (bullet->homing && bullet->target_pos) {
        const float dx       = bullet->target_pos->x - bullet->center.x;
        const float dy       = bullet->target_pos->y - bullet->center.y;
        const float distance = sqrtf((dx * dx) + (dy * dy));
        if (distance > 0) {
            bullet->direction = (Vector2){dx / distance, dy / distance};
        }
    }

    // move
    bullet->center.x += bullet->direction.x * def->speed * dt;
    bullet->center.y += bullet->direction.y * def->speed * dt;

    // update lifetime
    bullet->lifetime -= dt;
    if (bullet->lifetime <= 0.0f) {
        bullet->lifetime = 0.0f;
    }
}
