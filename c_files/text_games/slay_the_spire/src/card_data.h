#ifndef CARD_DATA_H
#define CARD_DATA_H

#include "character_data.h"

typedef enum {
    CARD_RARITY_BASIC,
    CARD_RARITY_COMMON,
    CARD_RARITY_UNCOMMON,
    CARD_RARITY_RARE,
    CARD_RARITY_MAX,
} CardRarity;

typedef enum {
    CARD_TYPE_ATTACK,
    CARD_TYPE_SKILL,
    CARD_TYPE_POWER,
    CARD_TYPE_MAX,
} CardType;

typedef enum {
    CARD_ID_STRIKE,
    CARD_ID_DEFEND,
    CARD_ID_BASH,
    CARD_ID_NEUTRALIZE,
    CARD_ID_SURVIVOR,
    CARD_ID_DUALCAST,
    CARD_ID_ZAP,
    CARD_ID_ERUPTION,
    CARD_ID_VIGILANCE,
    CARD_ID_MAX,
} CardId;

typedef struct {
    const char*   name;
    CardType      type;
    CharacterType owner;
    CardRarity    rarity;
    int           cost;
} CardDef;

extern const CardDef card_db[CARD_ID_MAX];

#endif // CARD_DATA_H
