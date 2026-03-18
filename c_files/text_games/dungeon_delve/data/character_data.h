#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

#include "armor_data.h"
#include "weapon_data.h"

#include <stdint.h>

typedef enum CharacterClass {
    CLASS_WARRIOR = 0,
    CLASS_ROGUE,
    CLASS_MAGE,
    CLASS_PALADIN,
    CLASS_RANGER,
    CLASS_NECROMANCER,
    CLASS_BERSERKER,
    CLASS_PRIEST,
    CLASS_ASSASSIN,
    CLASS_DRUID,

    CLASS_MAX,
} CharacterClass;

/* ─────────────────────────────────────────────
   Allowed Armor Class per Character Class
   Bitmask: bit0=LIGHT, bit1=MEDIUM, bit2=HEAVY
───────────────────────────────────────────── */
#define ALLOW_LIGHT (1 << CLASS_LIGHT)
#define ALLOW_MEDIUM (1 << CLASS_MEDIUM)
#define ALLOW_HEAVY (1 << CLASS_HEAVY)

typedef struct BaseCharacter
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

} BaseCharacter;

extern const BaseCharacter base_character_db[CLASS_MAX];

#endif /* CHARACTER_DATA_H */
