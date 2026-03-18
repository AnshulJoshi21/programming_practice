// armor_data.h

#ifndef ARMOR_DATA_H
#define ARMOR_DATA_H

#include <stdint.h>

/* ─────────────────────────────────────────────
   Armor Types
───────────────────────────────────────────── */
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

/* ─────────────────────────────────────────────
   Armor Slot
───────────────────────────────────────────── */
typedef enum ArmorSlot {
    SLOT_HEAD  = 0,
    SLOT_CHEST = 1,
    SLOT_LEGS  = 2,
    SLOT_HANDS = 3,
    SLOT_FEET  = 4,
    SLOT_MAX   = 5,
} ArmorSlot;

/* ─────────────────────────────────────────────
   Armor Class (tier)
───────────────────────────────────────────── */
typedef enum ArmorClass {
    CLASS_LIGHT  = 0,
    CLASS_MEDIUM = 1,
    CLASS_HEAVY  = 2,
} ArmorClass;

/* ─────────────────────────────────────────────
   Base Armor Definition
───────────────────────────────────────────── */
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

/* ─────────────────────────────────────────────
   Static Armor Table
   Access via: base_armor[ARMOR_LEATHER]
───────────────────────────────────────────── */
static const BaseArmor base_armor[ARMOR_MAX] = {

    [ARMOR_CLOTH] =
        {
            .type          = ARMOR_CLOTH,
            .name          = "Cloth",
            .armor_class   = CLASS_LIGHT,
            .slot          = SLOT_CHEST,
            .defense       = 2,
            .magic_resist  = 4,
            .dodge_penalty = 0.00f,
            .durability    = 40,
            .weight        = 300,
            .requires_str  = 0,
        },

    [ARMOR_LEATHER] =
        {
            .type          = ARMOR_LEATHER,
            .name          = "Leather",
            .armor_class   = CLASS_LIGHT,
            .slot          = SLOT_CHEST,
            .defense       = 8,
            .magic_resist  = 2,
            .dodge_penalty = 0.02f,
            .durability    = 60,
            .weight        = 800,
            .requires_str  = 5,
        },

    [ARMOR_HIDE] =
        {
            .type          = ARMOR_HIDE,
            .name          = "Hide",
            .armor_class   = CLASS_MEDIUM,
            .slot          = SLOT_CHEST,
            .defense       = 14,
            .magic_resist  = 3,
            .dodge_penalty = 0.05f,
            .durability    = 75,
            .weight        = 1400,
            .requires_str  = 10,
        },

    [ARMOR_CHAINMAIL] =
        {
            .type          = ARMOR_CHAINMAIL,
            .name          = "Chainmail",
            .armor_class   = CLASS_MEDIUM,
            .slot          = SLOT_CHEST,
            .defense       = 22,
            .magic_resist  = 5,
            .dodge_penalty = 0.10f,
            .durability    = 90,
            .weight        = 2500,
            .requires_str  = 15,
        },

    [ARMOR_SCALEMAIL] =
        {
            .type          = ARMOR_SCALEMAIL,
            .name          = "Scalemail",
            .armor_class   = CLASS_MEDIUM,
            .slot          = SLOT_CHEST,
            .defense       = 28,
            .magic_resist  = 8,
            .dodge_penalty = 0.12f,
            .durability    = 100,
            .weight        = 3200,
            .requires_str  = 18,
        },

    [ARMOR_PLATEMAIL] =
        {
            .type          = ARMOR_PLATEMAIL,
            .name          = "Platemail",
            .armor_class   = CLASS_HEAVY,
            .slot          = SLOT_CHEST,
            .defense       = 38,
            .magic_resist  = 6,
            .dodge_penalty = 0.20f,
            .durability    = 120,
            .weight        = 5000,
            .requires_str  = 22,
        },

    [ARMOR_FULLPLATE] =
        {
            .type          = ARMOR_FULLPLATE,
            .name          = "Full Plate",
            .armor_class   = CLASS_HEAVY,
            .slot          = SLOT_CHEST,
            .defense       = 50,
            .magic_resist  = 8,
            .dodge_penalty = 0.30f,
            .durability    = 150,
            .weight        = 7500,
            .requires_str  = 28,
        },

    [ARMOR_ROBE] =
        {
            .type          = ARMOR_ROBE,
            .name          = "Robe",
            .armor_class   = CLASS_LIGHT,
            .slot          = SLOT_CHEST,
            .defense       = 3,
            .magic_resist  = 20,
            .dodge_penalty = 0.00f,
            .durability    = 35,
            .weight        = 250,
            .requires_str  = 0,
        },

    [ARMOR_BRIGANDINE] =
        {
            .type          = ARMOR_BRIGANDINE,
            .name          = "Brigandine",
            .armor_class   = CLASS_MEDIUM,
            .slot          = SLOT_CHEST,
            .defense       = 32,
            .magic_resist  = 6,
            .dodge_penalty = 0.15f,
            .durability    = 110,
            .weight        = 4000,
            .requires_str  = 20,
        },

    [ARMOR_DRAGONSCALE] =
        {
            .type          = ARMOR_DRAGONSCALE,
            .name          = "Dragonscale",
            .armor_class   = CLASS_HEAVY,
            .slot          = SLOT_CHEST,
            .defense       = 65,
            .magic_resist  = 40,
            .dodge_penalty = 0.10f,
            .durability    = 200,
            .weight        = 4500,
            .requires_str  = 25,
        },
};

#endif /* ARMOR_DATA_H */
