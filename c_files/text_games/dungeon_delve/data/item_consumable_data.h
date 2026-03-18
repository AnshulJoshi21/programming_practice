#ifndef ITEM_CONSUMABLE_DATA_H
#define ITEM_CONSUMABLE_DATA_H

#include <stdint.h>

typedef enum ConsumableType {
    CONSUMABLE_HEALTH_POTION = 0,
    CONSUMABLE_MANA_POTION,
    CONSUMABLE_ANTIDOTE,
    CONSUMABLE_ELIXIR_STRENGTH,
    CONSUMABLE_ELIXIR_SWIFTNESS,
    CONSUMABLE_SCROLL_FIREBALL,
    CONSUMABLE_SCROLL_TELEPORT,
    CONSUMABLE_RATION,
    CONSUMABLE_SMOKE_BOMB,
    CONSUMABLE_RESURRECTION_HERB,

    CONSUMABLE_MAX,
} ConsumableType;

typedef enum ConsumableTarget {
    TARGET_SELF = 0, // affects the user
    TARGET_ENEMY,    // affects a single enemy
    TARGET_AOE,      // affects all enemies in range
    TARGET_ALLY,     // affects a single ally
} ConsumableTarget;

typedef struct BaseConsumable
{
    ConsumableType type;     // enum ID
    const char *name;        // display name
    ConsumableTarget target; // who it affects
    uint16_t effect_value;   // HP/MP restored or damage dealt
    uint8_t effect_turns;    // 0 = instant, >0 = duration in turns
    uint8_t stack_max;       // max stack size in inventory
    uint16_t buy_price;      // shop purchase cost
    uint16_t sell_price;     // vendor sell value
    uint8_t weight;          // carry weight cost
    uint8_t level_req;       // minimum player level to use

} BaseConsumable;

extern const BaseConsumable base_consumable_db[CONSUMABLE_MAX];

#endif
