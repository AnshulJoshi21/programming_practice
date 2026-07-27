#include "bullet_data.h"

const SkillDef skill_db[SKILL_MAX] = {
    [SKILL_MAGIC_MISSILE] = {
    .skill_type = SKILL_MAGIC_MISSILE,
    .bullet_type = BULLET_PROJECTILE,
    .name = "Magic Missile",
    .radius = 10.0f,
    .color = RED,
    {.projectile = {
            .speed = 300.0f,
            .damage = 1,
            .lifetime = 1.0f,
}}},
   
    [SKILL_ORBITING_ORBS] = {
    .skill_type = SKILL_ORBITING_ORBS,
    .bullet_type = BULLET_ORBITER,
    .name = "Orbiting Orbs",
    .radius = 10.0f,
    .color = RED,
    {.orbiter = {
    .angular_radius = 100.0f,
    .damage = 1,
}}},
};
