#include "bullet_data.h"

const BulletDef bullet_db[BULLET_TYPE_MAX] = {
    [BULLET_TYPE_MAGIC_MISSILES] = {.type            = BULLET_TYPE_MAGIC_MISSILES,
                                    .pattern         = BULLET_PATTERN_PROJECTILE,
                                    .name            = "MagicMissiles",
                                    .description     = "",
                                    .radius          = 5.0f,
                                    .color           = RED,
                                    .damage          = 1.0f,
                                    .lifetime        = 1.0f,
                                    .max_count       = 500,
                                    .data.projectile = {.fire_rate = 1.0f, .speed = 300.0f}},

    [BULLET_TYPE_ORBITING_ORBS]
    = {.type         = BULLET_TYPE_ORBITING_ORBS,
       .pattern      = BULLET_PATTERN_ORBITAL,
       .name         = "Orbiting Orbs",
       .description  = "",
       .radius       = 10.0f,
       .color        = BLUE,
       .damage       = 5.0f,
       .lifetime     = 5.0f,
       .max_count    = 10,
       .data.orbital = {.orbital_radius = 100.0f, .orbital_speed = 1.0f}},
};
