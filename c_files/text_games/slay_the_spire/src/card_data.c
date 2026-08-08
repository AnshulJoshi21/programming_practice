#include "card_data.h"

const CardDef card_db[CARD_ID_MAX] = {
    [CARD_ID_STRIKE] = {.name   = "Strike",
                        .type   = CARD_TYPE_ATTACK,
                        .owner  = CHARACTER_NONE,
                        .rarity = CARD_RARITY_BASIC,
                        .cost   = 1},

    [CARD_ID_DEFEND] = {.name   = "Defend",
                        .type   = CARD_TYPE_SKILL,
                        .owner  = CHARACTER_NONE,
                        .rarity = CARD_RARITY_BASIC,
                        .cost   = 1},

    [CARD_ID_BASH] = {.name   = "Bash",
                      .type   = CARD_TYPE_ATTACK,
                      .owner  = CHARACTER_NONE,
                      .rarity = CARD_RARITY_BASIC,
                      .cost   = 2},

    [CARD_ID_NEUTRALIZE] = {.name   = "Neutralize",
                            .type   = CARD_TYPE_ATTACK,
                            .owner  = CHARACTER_NONE,
                            .rarity = CARD_RARITY_BASIC,
                            .cost   = 0},

    [CARD_ID_SURVIVOR] = {.name   = "Survivor",
                          .type   = CARD_TYPE_SKILL,
                          .owner  = CHARACTER_NONE,
                          .rarity = CARD_RARITY_BASIC,
                          .cost   = 1},

    [CARD_ID_DUALCAST] = {.name   = "Dual Cast",
                          .type   = CARD_TYPE_SKILL,
                          .owner  = CHARACTER_NONE,
                          .rarity = CARD_RARITY_BASIC,
                          .cost   = 1},

    [CARD_ID_ZAP] = {.name   = "Zap",
                     .type   = CARD_TYPE_SKILL,
                     .owner  = CHARACTER_NONE,
                     .rarity = CARD_RARITY_BASIC,
                     .cost   = 1},

    [CARD_ID_ERUPTION] = {.name   = "Eruption",
                          .type   = CARD_TYPE_ATTACK,
                          .owner  = CHARACTER_NONE,
                          .rarity = CARD_RARITY_BASIC,
                          .cost   = 2},

    [CARD_ID_VIGILANCE] = {.name   = "Vigilance",
                           .type   = CARD_TYPE_SKILL,
                           .owner  = CHARACTER_NONE,
                           .rarity = CARD_RARITY_BASIC,
                           .cost   = 2},
};
