// item_quest_data.h

#ifndef ITEM_QUEST_DATA_H
#define ITEM_QUEST_DATA_H

#include <stdint.h>

/* ─────────────────────────────────────────────
   Quest Item Types
───────────────────────────────────────────── */
typedef enum QuestItemType {
    QUEST_DUNGEON_KEY          = 0,
    QUEST_ANCIENT_TOME         = 1,
    QUEST_ROYAL_SEAL           = 2,
    QUEST_BROKEN_AMULET        = 3,
    QUEST_DRAGON_EGG           = 4,
    QUEST_LICH_PHYLACTERY      = 5,
    QUEST_VILLAGE_PENDANT      = 6,
    QUEST_STOLEN_MANIFEST      = 7,
    QUEST_BLOOD_CRYSTAL        = 8,
    QUEST_WORLD_STONE_FRAGMENT = 9,

    QUEST_MAX = 10,
} QuestItemType;

/* ─────────────────────────────────────────────
   Quest Item Category
───────────────────────────────────────────── */
typedef enum QuestItemCategory {
    QCAT_KEY      = 0, // unlocks a door / area
    QCAT_DOCUMENT = 1, // readable, triggers dialogue
    QCAT_ARTIFACT = 2, // story-critical object
    QCAT_DELIVERY = 3, // hand-in to an NPC
    QCAT_TROPHY   = 4, // proof of kill / achievement
} QuestItemCategory;

/* ─────────────────────────────────────────────
   Base Quest Item Definition
───────────────────────────────────────────── */
typedef struct BaseQuestItem
{
    QuestItemType type;         // enum ID
    const char *name;           // display name
    const char *description;    // flavour / journal text
    QuestItemCategory category; // functional category
    uint16_t quest_id;          // associated quest ID (0 = none)
    uint8_t is_unique;          // 1 = only one can exist in world
    uint8_t is_droppable;       // 0 = locked to inventory
    uint8_t is_readable;        // 1 = player can inspect text
    uint16_t sell_price;        // 0 = cannot be sold
    uint8_t weight;             // carry weight cost
} BaseQuestItem;

/* ─────────────────────────────────────────────
   Static Quest Item Table
   Access via: base_quest_item[QUEST_DUNGEON_KEY]
───────────────────────────────────────────── */
static const BaseQuestItem base_quest_item[QUEST_MAX] = {

    [QUEST_DUNGEON_KEY] =
        {
            .type = QUEST_DUNGEON_KEY,
            .name = "Dungeon Key",
            .description =
                "A rusted iron key. It must open something deep below.",
            .category     = QCAT_KEY,
            .quest_id     = 101,
            .is_unique    = 1,
            .is_droppable = 0,
            .is_readable  = 0,
            .sell_price   = 0,
            .weight       = 0,
        },

    [QUEST_ANCIENT_TOME] =
        {
            .type        = QUEST_ANCIENT_TOME,
            .name        = "Ancient Tome",
            .description = "Pages filled with forgotten scripture. The scholar "
                           "in town seeks this.",
            .category    = QCAT_DOCUMENT,
            .quest_id    = 102,
            .is_unique   = 1,
            .is_droppable = 0,
            .is_readable  = 1,
            .sell_price   = 0,
            .weight       = 2,
        },

    [QUEST_ROYAL_SEAL] =
        {
            .type = QUEST_ROYAL_SEAL,
            .name = "Royal Seal",
            .description =
                "The king's official seal. Return it to the palace at once.",
            .category     = QCAT_DELIVERY,
            .quest_id     = 103,
            .is_unique    = 1,
            .is_droppable = 0,
            .is_readable  = 0,
            .sell_price   = 0,
            .weight       = 1,
        },

    [QUEST_BROKEN_AMULET] =
        {
            .type = QUEST_BROKEN_AMULET,
            .name = "Broken Amulet",
            .description =
                "One half of a family heirloom. Someone is searching for this.",
            .category     = QCAT_DELIVERY,
            .quest_id     = 104,
            .is_unique    = 1,
            .is_droppable = 0,
            .is_readable  = 0,
            .sell_price   = 0,
            .weight       = 0,
        },

    [QUEST_DRAGON_EGG] =
        {
            .type        = QUEST_DRAGON_EGG,
            .name        = "Dragon Egg",
            .description = "Warm to the touch. It pulses faintly — something "
                           "stirs within.",
            .category    = QCAT_ARTIFACT,
            .quest_id    = 105,
            .is_unique   = 1,
            .is_droppable = 0,
            .is_readable  = 0,
            .sell_price   = 0,
            .weight       = 8,
        },

    [QUEST_LICH_PHYLACTERY] =
        {
            .type = QUEST_LICH_PHYLACTERY,
            .name = "Lich's Phylactery",
            .description =
                "A soul vessel. The Lich cannot die while this survives.",
            .category     = QCAT_TROPHY,
            .quest_id     = 106,
            .is_unique    = 1,
            .is_droppable = 0,
            .is_readable  = 0,
            .sell_price   = 0,
            .weight       = 2,
        },

    [QUEST_VILLAGE_PENDANT] =
        {
            .type         = QUEST_VILLAGE_PENDANT,
            .name         = "Village Pendant",
            .description  = "A child's keepsake, lost during the raid. Her "
                            "father still waits.",
            .category     = QCAT_DELIVERY,
            .quest_id     = 107,
            .is_unique    = 0,
            .is_droppable = 1,
            .is_readable  = 0,
            .sell_price   = 0,
            .weight       = 0,
        },

    [QUEST_STOLEN_MANIFEST] =
        {
            .type = QUEST_STOLEN_MANIFEST,
            .name = "Stolen Manifest",
            .description =
                "A merchant's cargo list. It details a suspicious shipment.",
            .category     = QCAT_DOCUMENT,
            .quest_id     = 108,
            .is_unique    = 1,
            .is_droppable = 0,
            .is_readable  = 1,
            .sell_price   = 0,
            .weight       = 0,
        },

    [QUEST_BLOOD_CRYSTAL] =
        {
            .type         = QUEST_BLOOD_CRYSTAL,
            .name         = "Blood Crystal",
            .description  = "Crystallised vampire essence. The hunters need "
                            "proof of the kill.",
            .category     = QCAT_TROPHY,
            .quest_id     = 109,
            .is_unique    = 0,
            .is_droppable = 1,
            .is_readable  = 0,
            .sell_price   = 50,
            .weight       = 1,
        },

    [QUEST_WORLD_STONE_FRAGMENT] =
        {
            .type         = QUEST_WORLD_STONE_FRAGMENT,
            .name         = "World Stone Fragment",
            .description  = "A shard of something ancient and vast. The ground "
                            "hums beneath it.",
            .category     = QCAT_ARTIFACT,
            .quest_id     = 110,
            .is_unique    = 1,
            .is_droppable = 0,
            .is_readable  = 0,
            .sell_price   = 0,
            .weight       = 5,
        },
};

#endif /* ITEM_QUEST_DATA_H */
