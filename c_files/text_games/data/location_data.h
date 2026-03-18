// location_data.h

#ifndef LOCATION_DATA_H
#define LOCATION_DATA_H

#include <stdint.h>
#include "town_data.h"

/* ─────────────────────────────────────────────
   Location Types
───────────────────────────────────────────── */
typedef enum LocationType {
    LOC_ASHVEIL_CEMETERY        = 0,    // TOWN_ASHVEIL
    LOC_GRIMHOLT_INQUISITORY    = 1,    // TOWN_GRIMHOLT
    LOC_WRAITHFEN_APOTHECARY    = 2,    // TOWN_WRAITHFEN
    LOC_DUSKMERE_CASTLE         = 3,    // TOWN_DUSKMERE
    LOC_IRONSPIRE_FOUNDRY       = 4,    // TOWN_IRONSPIRE
    LOC_SALTMOOR_DOCKYARDS      = 5,    // TOWN_SALTMOOR
    LOC_CRESTFALL_THRONE_ROOM   = 6,    // TOWN_CRESTFALL
    LOC_THORNWICK_WITCHWOOD     = 7,    // TOWN_THORNWICK
    LOC_VORRATHGARD_DEEP_MINES  = 8,    // TOWN_VORRATHGARD
    LOC_OBSIDIAN_GATE_WARCAMP   = 9,    // TOWN_OBSIDIAN_GATE
    LOC_MAX                     = 10,
} LocationType;

/* ─────────────────────────────────────────────
   Location Category
───────────────────────────────────────────── */
typedef enum LocationCategory {
    LOCCAT_DUNGEON      = 0,    // combat zone, enemies spawn
    LOCCAT_SOCIAL       = 1,    // NPC hub, quests & trade
    LOCCAT_WILDERNESS   = 2,    // open exploration area
    LOCCAT_LANDMARK     = 3,    // story-critical, one-time event
} LocationCategory;

/* ─────────────────────────────────────────────
   Base Location Definition
───────────────────────────────────────────── */
typedef struct BaseLocation {
    LocationType        type;               // enum ID
    const char         *name;               // display name
    const char         *description;        // flavour / map tooltip
    TownType            town_id;            // parent town (FK → base_town)
    LocationCategory    category;           // functional category
    uint8_t             is_interior;        // 1 = indoors / underground
    uint8_t             is_locked;          // 1 = requires key or quest flag
    uint8_t             danger_level;       // 1 (safe) – 10 (deadly)
    uint8_t             level_req;          // min player level to enter
    uint16_t            discovery_exp;      // EXP on first visit
} BaseLocation;

/* ─────────────────────────────────────────────
   Static Location Table
   Access via: base_location[LOC_ASHVEIL_CEMETERY]
───────────────────────────────────────────── */
static const BaseLocation base_location[LOC_MAX] = {

    [LOC_ASHVEIL_CEMETERY] = {
        .type           = LOC_ASHVEIL_CEMETERY,
        .name           = "Ashveil Cemetery",
        .description    = "Headstones jut from the fog like broken teeth. Something moves between them after dark.",
        .town_id        = TOWN_ASHVEIL,
        .category       = LOCCAT_DUNGEON,
        .is_interior    = 0,
        .is_locked      = 0,
        .danger_level   = 3,
        .level_req      = 1,
        .discovery_exp  = 40,
    },

    [LOC_GRIMHOLT_INQUISITORY] = {
        .type           = LOC_GRIMHOLT_INQUISITORY,
        .name           = "The Inquisitory",
        .description    = "Stone walls stained by decades of confession. The screaming never quite stops.",
        .town_id        = TOWN_GRIMHOLT,
        .category       = LOCCAT_LANDMARK,
        .is_interior    = 1,
        .is_locked      = 1,
        .danger_level   = 6,
        .level_req      = 10,
        .discovery_exp  = 120,
    },

    [LOC_WRAITHFEN_APOTHECARY] = {
        .type           = LOC_WRAITHFEN_APOTHECARY,
        .name           = "Murk's Apothecary",
        .description    = "Jars of things better left unnamed line every shelf. The proprietor smells of formaldehyde.",
        .town_id        = TOWN_WRAITHFEN,
        .category       = LOCCAT_SOCIAL,
        .is_interior    = 1,
        .is_locked      = 0,
        .danger_level   = 1,
        .level_req      = 1,
        .discovery_exp  = 30,
    },

    [LOC_DUSKMERE_CASTLE] = {
        .type           = LOC_DUSKMERE_CASTLE,
        .name           = "Castle Duskmere",
        .description    = "The Count's ancestral seat. Its towers cast shadows that point the wrong direction.",
        .town_id        = TOWN_DUSKMERE,
        .category       = LOCCAT_DUNGEON,
        .is_interior    = 1,
        .is_locked      = 1,
        .danger_level   = 8,
        .level_req      = 18,
        .discovery_exp  = 200,
    },

    [LOC_IRONSPIRE_FOUNDRY] = {
        .type           = LOC_IRONSPIRE_FOUNDRY,
        .name           = "The Ashen Foundry",
        .description    = "Molten iron flows through channels carved by slave labour. The foremen wear iron masks.",
        .town_id        = TOWN_IRONSPIRE,
        .category       = LOCCAT_DUNGEON,
        .is_interior    = 1,
        .is_locked      = 0,
        .danger_level   = 6,
        .level_req      = 12,
        .discovery_exp  = 100,
    },

    [LOC_SALTMOOR_DOCKYARDS] = {
        .type           = LOC_SALTMOOR_DOCKYARDS,
        .name           = "Saltmoor Dockyards",
        .description    = "Fog-wrapped piers stacked with crates that move on their own when no one is watching.",
        .town_id        = TOWN_SALTMOOR,
        .category       = LOCCAT_SOCIAL,
        .is_interior    = 0,
        .is_locked      = 0,
        .danger_level   = 5,
        .level_req      = 8,
        .discovery_exp  = 70,
    },

    [LOC_CRESTFALL_THRONE_ROOM] = {
        .type           = LOC_CRESTFALL_THRONE_ROOM,
        .name           = "The Shattered Throne",
        .description    = "The old king's seat, cracked down the middle. Something has been nesting in the rafters.",
        .town_id        = TOWN_CRESTFALL,
        .category       = LOCCAT_LANDMARK,
        .is_interior    = 1,
        .is_locked      = 0,
        .danger_level   = 8,
        .level_req      = 20,
        .discovery_exp  = 250,
    },

    [LOC_THORNWICK_WITCHWOOD] = {
        .type           = LOC_THORNWICK_WITCHWOOD,
        .name           = "Thornwick Witchwood",
        .description    = "The trees grow inward here. Villagers leave bread at the treeline and never look inside.",
        .town_id        = TOWN_THORNWICK,
        .category       = LOCCAT_WILDERNESS,
        .is_interior    = 0,
        .is_locked      = 0,
        .danger_level   = 5,
        .level_req      = 6,
        .discovery_exp  = 60,
    },

    [LOC_VORRATHGARD_DEEP_MINES] = {
        .type           = LOC_VORRATHGARD_DEEP_MINES,
        .name           = "The Deep Mines",
        .description    = "Sealed by order of the Elder Council. The seals are cracking from the inside.",
        .town_id        = TOWN_VORRATHGARD,
        .category       = LOCCAT_DUNGEON,
        .is_interior    = 1,
        .is_locked      = 1,
        .danger_level   = 9,
        .level_req      = 25,
        .discovery_exp  = 300,
    },

    [LOC_OBSIDIAN_GATE_WARCAMP] = {
        .type           = LOC_OBSIDIAN_GATE_WARCAMP,
        .name           = "The Warcamp",
        .description    = "A desperate staging ground. Soldiers sharpen blades and write letters they know won't be sent.",
        .town_id        = TOWN_OBSIDIAN_GATE,
        .category       = LOCCAT_SOCIAL,
        .is_interior    = 0,
        .is_locked      = 0,
        .danger_level   = 4,
        .level_req      = 1,
        .discovery_exp  = 80,
    },
};

#endif /* LOCATION_DATA_H */
