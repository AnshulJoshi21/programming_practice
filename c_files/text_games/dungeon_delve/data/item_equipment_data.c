#include "item_equipment_data.h"

const BaseEquipment base_equipment_db[EQUIP_MAX] = {

    [EQUIP_RING_VITALITY] =
        {
            .type       = EQUIP_RING_VITALITY,
            .name       = "Ring of Vitality",
            .slot       = ESLOT_RING,
            .bonus_str  = 0,
            .bonus_dex  = 0,
            .bonus_int  = 0,
            .bonus_vit  = 5,
            .bonus_hp   = 40,
            .bonus_mp   = 0,
            .buy_price  = 300,
            .sell_price = 100,
        },

    [EQUIP_RING_POWER] =
        {
            .type       = EQUIP_RING_POWER,
            .name       = "Ring of Power",
            .slot       = ESLOT_RING,
            .bonus_str  = 6,
            .bonus_dex  = 0,
            .bonus_int  = 0,
            .bonus_vit  = 0,
            .bonus_hp   = 0,
            .bonus_mp   = 0,
            .buy_price  = 350,
            .sell_price = 120,
        },

    [EQUIP_AMULET_GUARDIAN] =
        {
            .type       = EQUIP_AMULET_GUARDIAN,
            .name       = "Amulet of the Guardian",
            .slot       = ESLOT_AMULET,
            .bonus_str  = 3,
            .bonus_dex  = 0,
            .bonus_int  = 0,
            .bonus_vit  = 6,
            .bonus_hp   = 60,
            .bonus_mp   = 0,
            .buy_price  = 500,
            .sell_price = 180,
        },

    [EQUIP_AMULET_WISDOM] =
        {
            .type       = EQUIP_AMULET_WISDOM,
            .name       = "Amulet of Wisdom",
            .slot       = ESLOT_AMULET,
            .bonus_str  = 0,
            .bonus_dex  = 0,
            .bonus_int  = 8,
            .bonus_vit  = 0,
            .bonus_hp   = 0,
            .bonus_mp   = 80,
            .buy_price  = 500,
            .sell_price = 180,
        },

    [EQUIP_BELT_WARRIOR] =
        {
            .type       = EQUIP_BELT_WARRIOR,
            .name       = "Warrior's Belt",
            .slot       = ESLOT_BELT,
            .bonus_str  = 4,
            .bonus_dex  = 0,
            .bonus_int  = 0,
            .bonus_vit  = 4,
            .bonus_hp   = 30,
            .bonus_mp   = 0,
            .buy_price  = 250,
            .sell_price = 80,
        },

    [EQUIP_BELT_SHADOW] =
        {
            .type       = EQUIP_BELT_SHADOW,
            .name       = "Shadow Belt",
            .slot       = ESLOT_BELT,
            .bonus_str  = 0,
            .bonus_dex  = 6,
            .bonus_int  = 2,
            .bonus_vit  = 0,
            .bonus_hp   = 0,
            .bonus_mp   = 20,
            .buy_price  = 280,
            .sell_price = 90,
        },

    [EQUIP_CLOAK_SWIFTNESS] =
        {
            .type       = EQUIP_CLOAK_SWIFTNESS,
            .name       = "Cloak of Swiftness",
            .slot       = ESLOT_CLOAK,
            .bonus_str  = 0,
            .bonus_dex  = 8,
            .bonus_int  = 0,
            .bonus_vit  = 0,
            .bonus_hp   = 0,
            .bonus_mp   = 0,
            .buy_price  = 400,
            .sell_price = 140,
        },

    [EQUIP_CLOAK_ARCANE] =
        {
            .type       = EQUIP_CLOAK_ARCANE,
            .name       = "Arcane Cloak",
            .slot       = ESLOT_CLOAK,
            .bonus_str  = 0,
            .bonus_dex  = 0,
            .bonus_int  = 10,
            .bonus_vit  = 0,
            .bonus_hp   = 0,
            .bonus_mp   = 100,
            .buy_price  = 600,
            .sell_price = 220,
        },

    [EQUIP_BOOTS_TRAVELLER] =
        {
            .type       = EQUIP_BOOTS_TRAVELLER,
            .name       = "Traveller's Boots",
            .slot       = ESLOT_BOOTS,
            .bonus_str  = 0,
            .bonus_dex  = 4,
            .bonus_int  = 0,
            .bonus_vit  = 2,
            .bonus_hp   = 20,
            .bonus_mp   = 0,
            .buy_price  = 180,
            .sell_price = 60,
        },

    [EQUIP_BOOTS_IRON] =
        {
            .type       = EQUIP_BOOTS_IRON,
            .name       = "Iron Boots",
            .slot       = ESLOT_BOOTS,
            .bonus_str  = 2,
            .bonus_dex  = -2, // heavy, reduces agility
            .bonus_int  = 0,
            .bonus_vit  = 6,
            .bonus_hp   = 50,
            .bonus_mp   = 0,
            .buy_price  = 220,
            .sell_price = 75,
        },
};
