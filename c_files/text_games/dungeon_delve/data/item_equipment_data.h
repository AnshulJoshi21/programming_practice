#ifndef ITEM_EQUIPMENT_DATA_H
#define ITEM_EQUIPMENT_DATA_H

#include <stdint.h>

typedef enum EquipmentType {
    EQUIP_RING_VITALITY = 0,
    EQUIP_RING_POWER,
    EQUIP_AMULET_GUARDIAN,
    EQUIP_AMULET_WISDOM,
    EQUIP_BELT_WARRIOR,
    EQUIP_BELT_SHADOW,
    EQUIP_CLOAK_SWIFTNESS,
    EQUIP_CLOAK_ARCANE,
    EQUIP_BOOTS_TRAVELLER,
    EQUIP_BOOTS_IRON,

    EQUIP_MAX,
} EquipmentType;

typedef enum EquipmentSlot {
    ESLOT_RING = 0,
    ESLOT_AMULET,
    ESLOT_BELT,
    ESLOT_CLOAK,
    ESLOT_BOOTS,

    ESLOT_MAX,
} EquipmentSlot;

typedef struct BaseEquipment
{
    EquipmentType type;  // enum ID
    const char *name;    // display name
    EquipmentSlot slot;  // where it is equipped
    int8_t bonus_str;    // STR modifier (can be negative)
    int8_t bonus_dex;    // DEX modifier
    int8_t bonus_int;    // INT modifier
    int8_t bonus_vit;    // VIT modifier
    uint16_t bonus_hp;   // flat HP bonus
    uint16_t bonus_mp;   // flat MP bonus
    uint16_t buy_price;  // shop purchase cost
    uint16_t sell_price; // vendor sell value

} BaseEquipment;

extern const BaseEquipment base_equipment_db[EQUIP_MAX];

#endif
