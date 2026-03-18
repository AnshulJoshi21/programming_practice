#ifndef ARMOR_DATA_H
#define ARMOR_DATA_H

#include <stdint.h>

typedef enum ArmorType {
    ARMOR_CLOTH       = 0,
    ARMOR_LEATHER     = 1,
    ARMOR_HIDE        = 2,
    ARMOR_CHAINMAIL   = 3,
    ARMOR_SCALEMAIL   = 4,
    ARMOR_PLATEMAIL   = 5,
    ARMOR_FULLPLATE   = 6,
    ARMOR_ROBE        = 7,
    ARMOR_BRIGANDINE  = 8,
    ARMOR_DRAGONSCALE = 9,
    ARMOR_MAX         = 10,
} ArmorType;

typedef enum ArmorSlot {
    SLOT_HEAD  = 0,
    SLOT_CHEST = 1,
    SLOT_LEGS  = 2,
    SLOT_HANDS = 3,
    SLOT_FEET  = 4,
    SLOT_MAX   = 5,
} ArmorSlot;

typedef enum ArmorClass {
    CLASS_LIGHT  = 0,
    CLASS_MEDIUM = 1,
    CLASS_HEAVY  = 2,
} ArmorClass;

typedef struct BaseArmor
{
    ArmorType type;         // enum ID
    const char *name;       // display name
    ArmorClass armor_class; // light / medium / heavy
    ArmorSlot slot;         // equipment slot
    uint16_t defense;       // flat damage reduction
    uint16_t magic_resist;  // magic damage reduction
    float dodge_penalty;    // % dodge chance reduction (0.0 – 1.0)
    uint8_t durability;     // max durability (0–255)
    uint16_t weight;        // carry weight cost (grams or units)
    uint8_t requires_str;   // minimum strength to equip
} BaseArmor;

extern const BaseArmor base_armor[ARMOR_MAX];

#endif
