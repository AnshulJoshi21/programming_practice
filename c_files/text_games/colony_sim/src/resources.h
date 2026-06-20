#pragma once
#include <stdint.h>
#include <stdio.h>

// NOTE: RAW/UNPROCESSED RESOURCES ONLY.

#define BIT(n) (1 << (n))

#define NAME_SIZE 128

typedef enum ResourceType {
    RESOURCE_TYPE_UNKNOWN,
    RESOURCE_TYPE_CONSUMABLE,
    RESOURCE_TYPE_NON_CONSUMABLE,
} ResourceType;

typedef enum ResourceTag {
    RESOURCE_TAG_PLANT   = BIT(0),
    RESOURCE_TAG_ANIMAL  = BIT(1),
    RESOURCE_TAG_MINERAL = BIT(2),

    RESOURCE_TAG_WOOD      = BIT(3),
    RESOURCE_TAG_STONE     = BIT(4),
    RESOURCE_TAG_METAL_ORE = BIT(5),

    RESOURCE_TAG_EDIBLE     = BIT(6),
    RESOURCE_TAG_PERISHABLE = BIT(7),

    RESOURCE_TAG_FUEL = BIT(8),

    RESOURCE_TAG_COMMON = BIT(9),
    RESOURCE_TAG_RARE   = BIT(10),
} ResourceTag;

typedef enum ResourceId {
    /* Plants */
    RESOURCE_BERRY,
    RESOURCE_MUSHROOM,
    RESOURCE_HERBS,
    RESOURCE_FIBER_PLANT,

    /* Crops */
    RESOURCE_WHEAT,
    RESOURCE_POTATO,
    RESOURCE_CORN,

    /* Wood */
    RESOURCE_LOG,

    /* Stone & Earth */
    RESOURCE_STONE,
    RESOURCE_CLAY,
    RESOURCE_SAND,

    /* Ores */
    RESOURCE_COPPER_ORE,
    RESOURCE_IRON_ORE,
    RESOURCE_COAL,

    /* Animal */
    RESOURCE_HIDE,
    RESOURCE_WOOL,
    RESOURCE_RAW_MEAT,
    RESOURCE_FISH,

    /* Luxury */
    RESOURCE_GEMS,

    RESOURCE_MAX,
} ResourceId;

typedef struct Resource {
    ResourceType type;
    uint32_t     tags;
    ResourceId   id;
    char         name[NAME_SIZE];
} Resource;

extern const Resource resources_db[RESOURCE_MAX];
extern const size_t   resources_size;
