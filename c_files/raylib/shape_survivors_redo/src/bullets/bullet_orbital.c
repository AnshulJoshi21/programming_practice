#include "bullet_orbital.h"
#include <assert.h>
#include <math.h>

const OrbitalDef orbital_db[ORBITAL_TYPE_MAX] = {
    [ORBITAL_TYPE_ORBITING_ORBS] = {
    .name = "Orbiting Orbs",
    .pattern = BULLET_PATTERN_ORBITAL,
    .damage_mode = DAMAGE_MODE_TICK,
    .radius = 10.0f,
    .color = BLACK,
    .damage = 5.0f,
    .orbital_radius = 100.0f,
    .orbital_speed = 1.0f,
    .lifetime = 20.0f,
},
};

void orbital_init(OrbitalBullet* bullet, const EntityConfig* econfig, const OrbitalConfig* config) {
    assert(bullet);
    assert(econfig);
    assert(config);
    assert(config->origin);

    const OrbitalDef* def = &orbital_db[econfig->type];

    bullet->type   = econfig->type;
    bullet->level  = econfig->level;
    bullet->origin = config->origin;
    bullet->angle  = config->angle;
    bullet->center = (Vector2){
        config->origin->x + cosf(config->angle) * def->orbital_radius,
        config->origin->y + sinf(config->angle) * def->orbital_radius,
    };
}

void orbital_update(OrbitalBullet* bullet, const float dt) {
    assert(bullet);

    const OrbitalDef* def = &orbital_db[bullet->type];

    bullet->angle += def->orbital_speed * dt;

    bullet->center = (Vector2){
        bullet->origin->x + cosf(bullet->angle) * def->orbital_radius,
        bullet->origin->y + sinf(bullet->angle) * def->orbital_radius,
    };

    // update lifetime
    bullet->lifetime -= dt;
    if (bullet->lifetime <= 0.0f) {
        bullet->lifetime = 0.0f;
    }
}
