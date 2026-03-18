#ifndef ITEM_MATERIAL_DATA_H
#define ITEM_MATERIAL_DATA_H

#include <stdint.h>

typedef enum MaterialType {
    MATERIAL_IRON_ORE = 0,
    MATERIAL_DARKSTEEL_ORE,
    MATERIAL_LEATHER_SCRAP,
    MATERIAL_DRAGON_HIDE,
    MATERIAL_MAGIC_CRYSTAL,
    MATERIAL_BONE_FRAGMENT,
    MATERIAL_WOOD_LOG,
    MATERIAL_SHADOWWOOD,
    MATERIAL_RUBY_GEM,
    MATERIAL_VOID_SHARD,

    MATERIAL_MAX,
} MaterialType;

typedef enum MaterialCategory {
    MATCAT_ORE = 0, // smelted into ingots
    MATCAT_HIDE,    // tanned into leather
    MATCAT_CRYSTAL, // used in magic crafting
    MATCAT_BONE,    // used in dark crafting
    MATCAT_WOOD,    // used in weapon/bow crafting
    MATCAT_GEM,     // socketed or sold

} MaterialCategory;

typedef struct BaseMaterial
{
    MaterialType type;         // enum ID
    const char *name;          // display name
    MaterialCategory category; // crafting category
    uint8_t rarity;            // 1=common … 5=legendary
    uint8_t stack_max;         // max stack in inventory
    uint8_t craft_value;       // potency in crafting recipes
    uint16_t buy_price;        // shop purchase cost (0 = not sold)
    uint16_t sell_price;       // vendor sell value
    uint8_t weight;            // carry weight cost per unit
    uint8_t level_drop;        // min enemy level to drop this

} BaseMaterial;

extern const BaseMaterial base_material_db[MATERIAL_MAX];

#endif
