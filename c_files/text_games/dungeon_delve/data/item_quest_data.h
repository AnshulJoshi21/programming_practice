#ifndef ITEM_QUEST_DATA_H
#define ITEM_QUEST_DATA_H

#include <stdint.h>

/* ─────────────────────────────────────────────
   Quest Item Types
───────────────────────────────────────────── */
typedef enum QuestItemType {
    QUEST_DUNGEON_KEY = 0,
    QUEST_ANCIENT_TOME,
    QUEST_ROYAL_SEAL,
    QUEST_BROKEN_AMULET,
    QUEST_DRAGON_EGG,
    QUEST_LICH_PHYLACTERY,
    QUEST_VILLAGE_PENDANT,
    QUEST_STOLEN_MANIFEST,
    QUEST_BLOOD_CRYSTAL,
    QUEST_WORLD_STONE_FRAGMENT,

    QUEST_MAX,
} QuestItemType;

typedef enum QuestItemCategory {
    QCAT_KEY = 0,  // unlocks a door / area
    QCAT_DOCUMENT, // readable, triggers dialogue
    QCAT_ARTIFACT, // story-critical object
    QCAT_DELIVERY, // hand-in to an NPC
    QCAT_TROPHY,   // proof of kill / achievement

} QuestItemCategory;

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

extern const BaseQuestItem base_quest_item_db[QUEST_MAX];

#endif
