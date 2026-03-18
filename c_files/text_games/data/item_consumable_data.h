// item_consumable_data.h

#ifndef ITEM_CONSUMABLE_DATA_H
#define ITEM_CONSUMABLE_DATA_H

#include <stdint.h>

/* ─────────────────────────────────────────────
   Consumable Types
───────────────────────────────────────────── */
typedef enum ConsumableType {
    CONSUMABLE_HEALTH_POTION     = 0,
    CONSUMABLE_MANA_POTION       = 1,
    CONSUMABLE_ANTIDOTE          = 2,
    CONSUMABLE_ELIXIR_STRENGTH   = 3,
    CONSUMABLE_ELIXIR_SWIFTNESS  = 4,
    CONSUMABLE_SCROLL_FIREBALL   = 5,
    CONSUMABLE_SCROLL_TELEPORT   = 6,
    CONSUMABLE_RATION            = 7,
    CONSUMABLE_SMOKE_BOMB        = 8,
    CONSUMABLE_RESURRECTION_HERB = 9,
    CONSUMABLE_MAX               = 10,
} ConsumableType;

/* ─────────────────────────────────────────────
   Consumable Effect Target
───────────────────────────────────────────── */
typedef enum ConsumableTarget {
    TARGET_SELF  = 0, // affects the user
    TARGET_ENEMY = 1, // affects a single enemy
    TARGET_AOE   = 2, // affects all enemies in range
    TARGET_ALLY  = 3, // affects a single ally
} ConsumableTarget;

/* ─────────────────────────────────────────────
   Base Consumable Definition
───────────────────────────────────────────── */
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

/* ─────────────────────────────────────────────
   Static Consumable Table
   Access via: base_consumable[CONSUMABLE_HEALTH_POTION]
───────────────────────────────────────────── */
static const BaseConsumable base_consumable[CONSUMABLE_MAX] = {

    [CONSUMABLE_HEALTH_POTION] =
        {
            .type         = CONSUMABLE_HEALTH_POTION,
            .name         = "Health Potion",
            .target       = TARGET_SELF,
            .effect_value = 80,
            .effect_turns = 0,
            .stack_max    = 10,
            .buy_price    = 50,
            .sell_price   = 20,
            .weight       = 1,
            .level_req    = 1,
        },

    [CONSUMABLE_MANA_POTION] =
        {
            .type         = CONSUMABLE_MANA_POTION,
            .name         = "Mana Potion",
            .target       = TARGET_SELF,
            .effect_value = 60,
            .effect_turns = 0,
            .stack_max    = 10,
            .buy_price    = 50,
            .sell_price   = 20,
            .weight       = 1,
            .level_req    = 1,
        },

    [CONSUMABLE_ANTIDOTE] =
        {
            .type         = CONSUMABLE_ANTIDOTE,
            .name         = "Antidote",
            .target       = TARGET_SELF,
            .effect_value = 0,
            .effect_turns = 0,
            .stack_max    = 10,
            .buy_price    = 30,
            .sell_price   = 10,
            .weight       = 1,
            .level_req    = 1,
        },

    [CONSUMABLE_ELIXIR_STRENGTH] =
        {
            .type         = CONSUMABLE_ELIXIR_STRENGTH,
            .name         = "Elixir of Strength",
            .target       = TARGET_SELF,
            .effect_value = 8, // +8 STR
            .effect_turns = 10,
            .stack_max    = 5,
            .buy_price    = 150,
            .sell_price   = 60,
            .weight       = 1,
            .level_req    = 5,
        },

    [CONSUMABLE_ELIXIR_SWIFTNESS] =
        {
            .type         = CONSUMABLE_ELIXIR_SWIFTNESS,
            .name         = "Elixir of Swiftness",
            .target       = TARGET_SELF,
            .effect_value = 8, // +8 DEX
            .effect_turns = 10,
            .stack_max    = 5,
            .buy_price    = 150,
            .sell_price   = 60,
            .weight       = 1,
            .level_req    = 5,
        },

    [CONSUMABLE_SCROLL_FIREBALL] =
        {
            .type         = CONSUMABLE_SCROLL_FIREBALL,
            .name         = "Scroll of Fireball",
            .target       = TARGET_AOE,
            .effect_value = 120, // fire damage
            .effect_turns = 0,
            .stack_max    = 5,
            .buy_price    = 200,
            .sell_price   = 80,
            .weight       = 0,
            .level_req    = 8,
        },

    [CONSUMABLE_SCROLL_TELEPORT] =
        {
            .type         = CONSUMABLE_SCROLL_TELEPORT,
            .name         = "Scroll of Teleport",
            .target       = TARGET_SELF,
            .effect_value = 0,
            .effect_turns = 0,
            .stack_max    = 3,
            .buy_price    = 300,
            .sell_price   = 120,
            .weight       = 0,
            .level_req    = 10,
        },

    [CONSUMABLE_RATION] =
        {
            .type         = CONSUMABLE_RATION,
            .name         = "Ration",
            .target       = TARGET_SELF,
            .effect_value = 20, // slow HP regen over turns
            .effect_turns = 5,
            .stack_max    = 20,
            .buy_price    = 10,
            .sell_price   = 3,
            .weight       = 2,
            .level_req    = 1,
        },

    [CONSUMABLE_SMOKE_BOMB] =
        {
            .type         = CONSUMABLE_SMOKE_BOMB,
            .name         = "Smoke Bomb",
            .target       = TARGET_AOE,
            .effect_value = 0, // blinds enemies for turns
            .effect_turns = 3,
            .stack_max    = 5,
            .buy_price    = 80,
            .sell_price   = 30,
            .weight       = 1,
            .level_req    = 3,
        },

    [CONSUMABLE_RESURRECTION_HERB] =
        {
            .type         = CONSUMABLE_RESURRECTION_HERB,
            .name         = "Resurrection Herb",
            .target       = TARGET_SELF,
            .effect_value = 50, // revive with 50 HP
            .effect_turns = 0,
            .stack_max    = 2,
            .buy_price    = 1000,
            .sell_price   = 400,
            .weight       = 1,
            .level_req    = 15,
        },
};

#endif /* ITEM_CONSUMABLE_DATA_H */
