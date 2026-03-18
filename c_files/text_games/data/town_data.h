// town_data.h

#ifndef TOWN_DATA_H
#define TOWN_DATA_H

#include <stdint.h>

/* ─────────────────────────────────────────────
   Town Types
───────────────────────────────────────────── */
typedef enum TownType {
    TOWN_ASHVEIL       = 0, // fog-choked starting village
    TOWN_GRIMHOLT      = 1, // fortified inquisitor stronghold
    TOWN_WRAITHFEN     = 2, // swamp settlement, plague-ridden
    TOWN_DUSKMERE      = 3, // lakeside town, vampire-controlled
    TOWN_IRONSPIRE     = 4, // industrial mining city
    TOWN_SALTMOOR      = 5, // coastal, smugglers & cultists
    TOWN_CRESTFALL     = 6, // ruined capital, partially reclaimed
    TOWN_THORNWICK     = 7, // isolated forest hamlet
    TOWN_VORRATHGARD   = 8, // underground dwarven refuge
    TOWN_OBSIDIAN_GATE = 9, // gateway city to the Blighted Wastes
    TOWN_MAX           = 10,
} TownType;

/* ─────────────────────────────────────────────
   Town Size
───────────────────────────────────────────── */
typedef enum TownSize {
    SIZE_HAMLET  = 0, // <100 residents
    SIZE_VILLAGE = 1, // 100–500
    SIZE_TOWN    = 2, // 500–5000
    SIZE_CITY    = 3, // 5000+
} TownSize;

/* ─────────────────────────────────────────────
   Town Allegiance
───────────────────────────────────────────── */
typedef enum TownAllegiance {
    ALLEGIANCE_NEUTRAL     = 0,
    ALLEGIANCE_INQUISITION = 1,
    ALLEGIANCE_UNDEAD      = 2,
    ALLEGIANCE_CULTIST     = 3,
    ALLEGIANCE_INDEPENDENT = 4,
} TownAllegiance;

/* ─────────────────────────────────────────────
   Base Town Definition
───────────────────────────────────────────── */
typedef struct BaseTown
{
    TownType type;             // enum ID
    const char *name;          // display name
    const char *description;   // flavour / map tooltip
    TownSize size;             // population band
    TownAllegiance allegiance; // controlling faction
    uint8_t has_shop;          // 1 = merchant available
    uint8_t has_inn;           // 1 = rest/save point
    uint8_t has_blacksmith;    // 1 = weapon/armor repair & craft
    uint8_t danger_level;      // 1 (safe) – 10 (deadly)
    uint16_t discovery_exp;    // EXP granted on first visit
} BaseTown;

/* ─────────────────────────────────────────────
   Static Town Table
   Access via: base_town[TOWN_ASHVEIL]
───────────────────────────────────────────── */
static const BaseTown base_town[TOWN_MAX] = {

    [TOWN_ASHVEIL] =
        {
            .type        = TOWN_ASHVEIL,
            .name        = "Ashveil",
            .description = "A dying village swallowed by eternal fog. The dead "
                           "do not always stay buried here.",
            .size        = SIZE_VILLAGE,
            .allegiance  = ALLEGIANCE_NEUTRAL,
            .has_shop    = 1,
            .has_inn     = 1,
            .has_blacksmith = 0,
            .danger_level   = 2,
            .discovery_exp  = 50,
        },

    [TOWN_GRIMHOLT] =
        {
            .type = TOWN_GRIMHOLT,
            .name = "Grimholt",
            .description =
                "Seat of the Silver Inquisition. Its pyres burn day and night.",
            .size           = SIZE_CITY,
            .allegiance     = ALLEGIANCE_INQUISITION,
            .has_shop       = 1,
            .has_inn        = 1,
            .has_blacksmith = 1,
            .danger_level   = 4,
            .discovery_exp  = 120,
        },

    [TOWN_WRAITHFEN] =
        {
            .type           = TOWN_WRAITHFEN,
            .name           = "Wraithfen",
            .description    = "Built on stilts above a cursed swamp. Half the "
                              "population carries the rot.",
            .size           = SIZE_VILLAGE,
            .allegiance     = ALLEGIANCE_NEUTRAL,
            .has_shop       = 1,
            .has_inn        = 0,
            .has_blacksmith = 0,
            .danger_level   = 5,
            .discovery_exp  = 80,
        },

    [TOWN_DUSKMERE] =
        {
            .type = TOWN_DUSKMERE,
            .name = "Duskmere",
            .description =
                "An elegant lakeside town frozen in eternal dusk. The Count "
                "does not tolerate visitors who ask questions.",
            .size           = SIZE_TOWN,
            .allegiance     = ALLEGIANCE_UNDEAD,
            .has_shop       = 1,
            .has_inn        = 1,
            .has_blacksmith = 1,
            .danger_level   = 7,
            .discovery_exp  = 150,
        },

    [TOWN_IRONSPIRE] =
        {
            .type = TOWN_IRONSPIRE,
            .name = "Ironspire",
            .description =
                "A city of black smoke and grinding gears. Workers disappear "
                "into the deep mines and are not seen again.",
            .size           = SIZE_CITY,
            .allegiance     = ALLEGIANCE_INDEPENDENT,
            .has_shop       = 1,
            .has_inn        = 1,
            .has_blacksmith = 1,
            .danger_level   = 5,
            .discovery_exp  = 130,
        },

    [TOWN_SALTMOOR] =
        {
            .type        = TOWN_SALTMOOR,
            .name        = "Saltmoor",
            .description = "A rotting port where every cargo manifest hides a "
                           "second truth.",
            .size        = SIZE_TOWN,
            .allegiance  = ALLEGIANCE_CULTIST,
            .has_shop    = 1,
            .has_inn     = 1,
            .has_blacksmith = 0,
            .danger_level   = 6,
            .discovery_exp  = 100,
        },

    [TOWN_CRESTFALL] =
        {
            .type = TOWN_CRESTFALL,
            .name = "Crestfall",
            .description =
                "The old capital, shattered by the Sundering. Survivors cling "
                "to the western quarter like barnacles.",
            .size           = SIZE_TOWN,
            .allegiance     = ALLEGIANCE_NEUTRAL,
            .has_shop       = 1,
            .has_inn        = 1,
            .has_blacksmith = 1,
            .danger_level   = 7,
            .discovery_exp  = 180,
        },

    [TOWN_THORNWICK] =
        {
            .type        = TOWN_THORNWICK,
            .name        = "Thornwick",
            .description = "A hamlet ringed by blackthorn. Villagers nail iron "
                           "horseshoes above every door.",
            .size        = SIZE_HAMLET,
            .allegiance  = ALLEGIANCE_NEUTRAL,
            .has_shop    = 0,
            .has_inn     = 1,
            .has_blacksmith = 0,
            .danger_level   = 3,
            .discovery_exp  = 40,
        },

    [TOWN_VORRATHGARD] =
        {
            .type        = TOWN_VORRATHGARD,
            .name        = "Vorrathgard",
            .description = "Carved into the root of the Ashpeak mountains. The "
                           "dwarves sealed the lower tunnels for a reason.",
            .size        = SIZE_TOWN,
            .allegiance  = ALLEGIANCE_INDEPENDENT,
            .has_shop    = 1,
            .has_inn     = 1,
            .has_blacksmith = 1,
            .danger_level   = 6,
            .discovery_exp  = 160,
        },

    [TOWN_OBSIDIAN_GATE] =
        {
            .type           = TOWN_OBSIDIAN_GATE,
            .name           = "Obsidian Gate",
            .description    = "The last city before the Blighted Wastes. Every "
                              "soul here is either desperate or damned.",
            .size           = SIZE_TOWN,
            .allegiance     = ALLEGIANCE_NEUTRAL,
            .has_shop       = 1,
            .has_inn        = 1,
            .has_blacksmith = 1,
            .danger_level   = 8,
            .discovery_exp  = 250,
        },
};

#endif /* TOWN_DATA_H */
