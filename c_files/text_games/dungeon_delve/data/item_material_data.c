#include "item_material_data.h"

const BaseMaterial base_material_db[MATERIAL_MAX] = {

    [MATERIAL_IRON_ORE] =
        {
            .type        = MATERIAL_IRON_ORE,
            .name        = "Iron Ore",
            .category    = MATCAT_ORE,
            .rarity      = 1,
            .stack_max   = 30,
            .craft_value = 10,
            .buy_price   = 20,
            .sell_price  = 5,
            .weight      = 3,
            .level_drop  = 1,
        },

    [MATERIAL_DARKSTEEL_ORE] =
        {
            .type        = MATERIAL_DARKSTEEL_ORE,
            .name        = "Darksteel Ore",
            .category    = MATCAT_ORE,
            .rarity      = 3,
            .stack_max   = 20,
            .craft_value = 40,
            .buy_price   = 150,
            .sell_price  = 50,
            .weight      = 4,
            .level_drop  = 15,
        },

    [MATERIAL_LEATHER_SCRAP] =
        {
            .type        = MATERIAL_LEATHER_SCRAP,
            .name        = "Leather Scrap",
            .category    = MATCAT_HIDE,
            .rarity      = 1,
            .stack_max   = 30,
            .craft_value = 8,
            .buy_price   = 15,
            .sell_price  = 4,
            .weight      = 1,
            .level_drop  = 1,
        },

    [MATERIAL_DRAGON_HIDE] =
        {
            .type        = MATERIAL_DRAGON_HIDE,
            .name        = "Dragon Hide",
            .category    = MATCAT_HIDE,
            .rarity      = 5,
            .stack_max   = 5,
            .craft_value = 100,
            .buy_price   = 0, // not sold in shops
            .sell_price  = 500,
            .weight      = 6,
            .level_drop  = 40,
        },

    [MATERIAL_MAGIC_CRYSTAL] =
        {
            .type        = MATERIAL_MAGIC_CRYSTAL,
            .name        = "Magic Crystal",
            .category    = MATCAT_CRYSTAL,
            .rarity      = 3,
            .stack_max   = 20,
            .craft_value = 50,
            .buy_price   = 200,
            .sell_price  = 70,
            .weight      = 1,
            .level_drop  = 12,
        },

    [MATERIAL_BONE_FRAGMENT] =
        {
            .type        = MATERIAL_BONE_FRAGMENT,
            .name        = "Bone Fragment",
            .category    = MATCAT_BONE,
            .rarity      = 1,
            .stack_max   = 30,
            .craft_value = 12,
            .buy_price   = 10,
            .sell_price  = 3,
            .weight      = 1,
            .level_drop  = 2,
        },

    [MATERIAL_WOOD_LOG] =
        {
            .type        = MATERIAL_WOOD_LOG,
            .name        = "Wood Log",
            .category    = MATCAT_WOOD,
            .rarity      = 1,
            .stack_max   = 30,
            .craft_value = 8,
            .buy_price   = 10,
            .sell_price  = 2,
            .weight      = 4,
            .level_drop  = 1,
        },

    [MATERIAL_SHADOWWOOD] =
        {
            .type        = MATERIAL_SHADOWWOOD,
            .name        = "Shadowwood",
            .category    = MATCAT_WOOD,
            .rarity      = 4,
            .stack_max   = 10,
            .craft_value = 70,
            .buy_price   = 0, // not sold in shops
            .sell_price  = 200,
            .weight      = 3,
            .level_drop  = 25,
        },

    [MATERIAL_RUBY_GEM] =
        {
            .type        = MATERIAL_RUBY_GEM,
            .name        = "Ruby Gem",
            .category    = MATCAT_GEM,
            .rarity      = 3,
            .stack_max   = 10,
            .craft_value = 60,
            .buy_price   = 300,
            .sell_price  = 120,
            .weight      = 1,
            .level_drop  = 20,
        },

    [MATERIAL_VOID_SHARD] =
        {
            .type        = MATERIAL_VOID_SHARD,
            .name        = "Void Shard",
            .category    = MATCAT_CRYSTAL,
            .rarity      = 5,
            .stack_max   = 5,
            .craft_value = 120,
            .buy_price   = 0, // not sold in shops
            .sell_price  = 800,
            .weight      = 1,
            .level_drop  = 45,
        },
};
