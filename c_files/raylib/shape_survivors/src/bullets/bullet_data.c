#include "bullet_data.h"

const BulletData bullet_db[BULLET_BEHAVIOUR_MAX][BULLET_TYPE_MAX] = {
    [BULLET_BEHAVIOUR_PROJECTILE]
    = {[BULLET_TYPE_MAGIC_MISSILE] = {.behaviour     = BULLET_BEHAVIOUR_PROJECTILE,
                                      .type          = BULLET_TYPE_MAGIC_MISSILE,
                                      .name          = "Magic Missile",
                                      .base_radius   = 5.0f,
                                      .base_damage   = 10,
                                      .base_lifetime = 1.5f,

                                      .bullet.projectile = {.base_speed = 350.0f}}},

    [BULLET_BEHAVIOUR_ORBITAL]
    = {[BULLET_TYPE_ORBITAL_ORBS]
       = {.behaviour     = BULLET_BEHAVIOUR_ORBITAL,
          .type          = BULLET_TYPE_ORBITAL_ORBS,
          .name          = "Orbital Orbs",
          .base_radius   = 10.0f,
          .base_damage   = 30,
          .base_lifetime = 10.0f,

          .bullet.orbital
          = {.base_orbital_radius = 150.0f, .base_orbital_count = 4, .base_orbital_speed = 1.0f}}}};
