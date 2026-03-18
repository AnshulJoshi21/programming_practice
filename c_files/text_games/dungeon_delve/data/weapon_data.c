#include "weapon_data.h"

const BaseWeapon base_weapon_db[WEAPON_MAX] = {

    [WEAPON_SWORD] =
        {
            .type         = WEAPON_SWORD,
            .name         = "Sword",
            .damage_type  = DMG_PHYSICAL,
            .damage_min   = 10,
            .damage_max   = 18,
            .attack_speed = 1.2f,
            .range        = 1,
            .stamina_cost = 10,
            .weight       = 1500,
            .two_handed   = 0,
        },

    [WEAPON_AXE] =
        {
            .type         = WEAPON_AXE,
            .name         = "Axe",
            .damage_type  = DMG_PHYSICAL,
            .damage_min   = 14,
            .damage_max   = 24,
            .attack_speed = 0.9f,
            .range        = 1,
            .stamina_cost = 15,
            .weight       = 2200,
            .two_handed   = 0,
        },

    [WEAPON_BOW] =
        {
            .type         = WEAPON_BOW,
            .name         = "Bow",
            .damage_type  = DMG_PIERCE,
            .damage_min   = 8,
            .damage_max   = 20,
            .attack_speed = 0.8f,
            .range        = 8,
            .stamina_cost = 12,
            .weight       = 1000,
            .two_handed   = 1,
        },

    [WEAPON_DAGGER] =
        {
            .type         = WEAPON_DAGGER,
            .name         = "Dagger",
            .damage_type  = DMG_PIERCE,
            .damage_min   = 5,
            .damage_max   = 12,
            .attack_speed = 2.0f,
            .range        = 1,
            .stamina_cost = 6,
            .weight       = 400,
            .two_handed   = 0,
        },

    [WEAPON_STAFF] =
        {
            .type         = WEAPON_STAFF,
            .name         = "Staff",
            .damage_type  = DMG_MAGIC,
            .damage_min   = 12,
            .damage_max   = 28,
            .attack_speed = 0.7f,
            .range        = 1,
            .stamina_cost = 8,
            .weight       = 1800,
            .two_handed   = 1,
        },

    [WEAPON_SPEAR] =
        {
            .type         = WEAPON_SPEAR,
            .name         = "Spear",
            .damage_type  = DMG_PIERCE,
            .damage_min   = 12,
            .damage_max   = 22,
            .attack_speed = 1.0f,
            .range        = 2,
            .stamina_cost = 13,
            .weight       = 2000,
            .two_handed   = 1,
        },

    [WEAPON_MACE] =
        {
            .type         = WEAPON_MACE,
            .name         = "Mace",
            .damage_type  = DMG_PHYSICAL,
            .damage_min   = 16,
            .damage_max   = 26,
            .attack_speed = 0.75f,
            .range        = 1,
            .stamina_cost = 18,
            .weight       = 2800,
            .two_handed   = 0,
        },

    [WEAPON_CROSSBOW] =
        {
            .type         = WEAPON_CROSSBOW,
            .name         = "Crossbow",
            .damage_type  = DMG_PIERCE,
            .damage_min   = 18,
            .damage_max   = 30,
            .attack_speed = 0.5f,
            .range        = 10,
            .stamina_cost = 10,
            .weight       = 3500,
            .two_handed   = 1,
        },

    [WEAPON_SCYTHE] =
        {
            .type         = WEAPON_SCYTHE,
            .name         = "Scythe",
            .damage_type  = DMG_PHYSICAL,
            .damage_min   = 20,
            .damage_max   = 35,
            .attack_speed = 0.6f,
            .range        = 2,
            .stamina_cost = 22,
            .weight       = 4000,
            .two_handed   = 1,
        },

    [WEAPON_WAND] =
        {
            .type         = WEAPON_WAND,
            .name         = "Wand",
            .damage_type  = DMG_MAGIC,
            .damage_min   = 15,
            .damage_max   = 32,
            .attack_speed = 1.4f,
            .range        = 6,
            .stamina_cost = 5,
            .weight       = 300,
            .two_handed   = 0,
        },
};
