// character_data.h

#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include "armor_data.h"
#include "weapon_data.h"

#include <stdint.h>

/* ─────────────────────────────────────────────
   Character Classes
───────────────────────────────────────────── */
typedef enum CharacterClass {
    CLASS_WARRIOR     = 0,
    CLASS_ROGUE       = 1,
    CLASS_MAGE        = 2,
    CLASS_PALADIN     = 3,
    CLASS_RANGER      = 4,
    CLASS_NECROMANCER = 5,
    CLASS_BERSERKER   = 6,
    CLASS_PRIEST      = 7,
    CLASS_ASSASSIN    = 8,
    CLASS_DRUID       = 9,
    CLASS_MAX         = 10,
} CharacterClass;

/* ─────────────────────────────────────────────
   Allowed Armor Class per Character Class
   Bitmask: bit0=LIGHT, bit1=MEDIUM, bit2=HEAVY
───────────────────────────────────────────── */
#define ALLOW_LIGHT (1 << CLASS_LIGHT)
#define ALLOW_MEDIUM (1 << CLASS_MEDIUM)
#define ALLOW_HEAVY (1 << CLASS_HEAVY)

/* ─────────────────────────────────────────────
   Base Character Stats Definition
───────────────────────────────────────────── */
typedef struct BaseCharacterData
{
    CharacterClass char_class; // enum ID
    const char *name;          // class display name
    uint16_t base_hp;          // starting hit points
    uint16_t base_mp;          // starting mana points
    uint8_t base_str;          // strength
    uint8_t base_dex;          // dexterity
    uint8_t base_int;          // intelligence
    uint8_t base_vit;          // vitality
    uint8_t armor_proficiency; // bitmask of allowed ArmorClass
    WeaponType primary_weapon; // default starting weapon
} BaseCharacterData;

/* ─────────────────────────────────────────────
   Static Character Data Table
   Access via: base_character[CLASS_WARRIOR]
───────────────────────────────────────────── */
static const BaseCharacterData base_character[CLASS_MAX] = {

    [CLASS_WARRIOR] =
        {
            .char_class        = CLASS_WARRIOR,
            .name              = "Warrior",
            .base_hp           = 200,
            .base_mp           = 30,
            .base_str          = 18,
            .base_dex          = 10,
            .base_int          = 6,
            .base_vit          = 16,
            .armor_proficiency = ALLOW_LIGHT | ALLOW_MEDIUM | ALLOW_HEAVY,
            .primary_weapon    = WEAPON_SWORD,
        },

    [CLASS_ROGUE] =
        {
            .char_class        = CLASS_ROGUE,
            .name              = "Rogue",
            .base_hp           = 140,
            .base_mp           = 50,
            .base_str          = 10,
            .base_dex          = 20,
            .base_int          = 10,
            .base_vit          = 10,
            .armor_proficiency = ALLOW_LIGHT | ALLOW_MEDIUM,
            .primary_weapon    = WEAPON_DAGGER,
        },

    [CLASS_MAGE] =
        {
            .char_class        = CLASS_MAGE,
            .name              = "Mage",
            .base_hp           = 90,
            .base_mp           = 200,
            .base_str          = 5,
            .base_dex          = 8,
            .base_int          = 24,
            .base_vit          = 7,
            .armor_proficiency = ALLOW_LIGHT,
            .primary_weapon    = WEAPON_STAFF,
        },

    [CLASS_PALADIN] =
        {
            .char_class        = CLASS_PALADIN,
            .name              = "Paladin",
            .base_hp           = 180,
            .base_mp           = 100,
            .base_str          = 16,
            .base_dex          = 8,
            .base_int          = 12,
            .base_vit          = 14,
            .armor_proficiency = ALLOW_LIGHT | ALLOW_MEDIUM | ALLOW_HEAVY,
            .primary_weapon    = WEAPON_MACE,
        },

    [CLASS_RANGER] =
        {
            .char_class        = CLASS_RANGER,
            .name              = "Ranger",
            .base_hp           = 150,
            .base_mp           = 60,
            .base_str          = 12,
            .base_dex          = 18,
            .base_int          = 10,
            .base_vit          = 10,
            .armor_proficiency = ALLOW_LIGHT | ALLOW_MEDIUM,
            .primary_weapon    = WEAPON_BOW,
        },

    [CLASS_NECROMANCER] =
        {
            .char_class        = CLASS_NECROMANCER,
            .name              = "Necromancer",
            .base_hp           = 100,
            .base_mp           = 180,
            .base_str          = 6,
            .base_dex          = 8,
            .base_int          = 22,
            .base_vit          = 8,
            .armor_proficiency = ALLOW_LIGHT,
            .primary_weapon    = WEAPON_SCYTHE,
        },

    [CLASS_BERSERKER] =
        {
            .char_class        = CLASS_BERSERKER,
            .name              = "Berserker",
            .base_hp           = 240,
            .base_mp           = 10,
            .base_str          = 22,
            .base_dex          = 12,
            .base_int          = 4,
            .base_vit          = 18,
            .armor_proficiency = ALLOW_LIGHT | ALLOW_MEDIUM,
            .primary_weapon    = WEAPON_AXE,
        },

    [CLASS_PRIEST] =
        {
            .char_class        = CLASS_PRIEST,
            .name              = "Priest",
            .base_hp           = 120,
            .base_mp           = 160,
            .base_str          = 8,
            .base_dex          = 8,
            .base_int          = 20,
            .base_vit          = 12,
            .armor_proficiency = ALLOW_LIGHT | ALLOW_MEDIUM,
            .primary_weapon    = WEAPON_WAND,
        },

    [CLASS_ASSASSIN] =
        {
            .char_class        = CLASS_ASSASSIN,
            .name              = "Assassin",
            .base_hp           = 130,
            .base_mp           = 70,
            .base_str          = 12,
            .base_dex          = 22,
            .base_int          = 12,
            .base_vit          = 8,
            .armor_proficiency = ALLOW_LIGHT,
            .primary_weapon    = WEAPON_CROSSBOW,
        },

    [CLASS_DRUID] =
        {
            .char_class        = CLASS_DRUID,
            .name              = "Druid",
            .base_hp           = 160,
            .base_mp           = 140,
            .base_str          = 10,
            .base_dex          = 12,
            .base_int          = 18,
            .base_vit          = 14,
            .armor_proficiency = ALLOW_LIGHT | ALLOW_MEDIUM,
            .primary_weapon    = WEAPON_SPEAR,
        },
};

#endif /* CHARACTER_DATA_H */
