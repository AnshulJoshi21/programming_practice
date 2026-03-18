#ifndef WEAPON_DATA_H
#define WEAPON_DATA_H

#include <stdint.h>

typedef enum WeaponType {
    WEAPON_SWORD = 0,
    WEAPON_AXE,
    WEAPON_BOW,
    WEAPON_DAGGER,
    WEAPON_STAFF,
    WEAPON_SPEAR,
    WEAPON_MACE,
    WEAPON_CROSSBOW,
    WEAPON_SCYTHE,
    WEAPON_WAND,

    WEAPON_MAX,
} WeaponType;

typedef enum DamageType {
    DMG_PHYSICAL = 0,
    DMG_PIERCE,
    DMG_MAGIC,
    DMG_FIRE,
    DMG_ICE,
} DamageType;

typedef struct BaseWeapon
{
    WeaponType type;        // enum ID
    const char *name;       // display name
    DamageType damage_type; // physical / magic / elemental
    uint16_t damage_min;    // minimum damage roll
    uint16_t damage_max;    // maximum damage roll
    float attack_speed;     // attacks per second
    uint8_t range;          // 1 = melee, >1 = ranged (tiles)
    uint16_t stamina_cost;  // stamina consumed per swing
    uint16_t weight;        // affects carry load (grams or units)
    uint8_t two_handed;     // 0 = one-handed, 1 = two-handed

} BaseWeapon;

extern const BaseWeapon base_weapon_db[WEAPON_MAX];

#endif
