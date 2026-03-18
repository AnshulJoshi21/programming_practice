// npc_data.h

#ifndef NPC_DATA_H
#define NPC_DATA_H

#include "location_data.h"
#include "town_data.h"

#include <stdint.h>

/* ─────────────────────────────────────────────
   NPC Types
───────────────────────────────────────────── */
typedef enum NpcType {
    NPC_ELARA_GRAVEDIGGER = 0, // LOC_ASHVEIL_CEMETERY
    NPC_PRIOR_MALTHEUS    = 1, // LOC_GRIMHOLT_INQUISITORY
    NPC_MURK_APOTHECARY   = 2, // LOC_WRAITHFEN_APOTHECARY
    NPC_COUNT_VALDRIS     = 3, // LOC_DUSKMERE_CASTLE
    NPC_FOREMAN_GRETH     = 4, // LOC_IRONSPIRE_FOUNDRY
    NPC_SILAS_SMUGGLER    = 5, // LOC_SALTMOOR_DOCKYARDS
    NPC_ARCHIVIST_VOSS    = 6, // LOC_CRESTFALL_THRONE_ROOM
    NPC_WREN_HERBALIST    = 7, // LOC_THORNWICK_WITCHWOOD
    NPC_ELDER_DURAK       = 8, // LOC_VORRATHGARD_DEEP_MINES
    NPC_COMMANDER_SERATH  = 9, // LOC_OBSIDIAN_GATE_WARCAMP
    NPC_MAX               = 10,
} NpcType;

/* ─────────────────────────────────────────────
   NPC Role
───────────────────────────────────────────── */
typedef enum NpcRole {
    ROLE_MERCHANT   = 0, // buys/sells items
    ROLE_QUESTGIVER = 1, // issues quests
    ROLE_BLACKSMITH = 2, // repairs & crafts gear
    ROLE_INNKEEPER  = 3, // rest & rumours
    ROLE_HEALER     = 4, // restores HP/MP for gold
    ROLE_TRAINER    = 5, // sells skill upgrades
    ROLE_LOREKEEPER = 6, // exposition & world info
    ROLE_ENEMY_NPC  = 7, // hostile, becomes combat
} NpcRole;

/* ─────────────────────────────────────────────
   NPC Disposition
───────────────────────────────────────────── */
typedef enum NpcDisposition {
    DISP_FRIENDLY   = 0,
    DISP_NEUTRAL    = 1,
    DISP_SUSPICIOUS = 2,
    DISP_HOSTILE    = 3,
} NpcDisposition;

/* ─────────────────────────────────────────────
   Base NPC Definition
───────────────────────────────────────────── */
typedef struct BaseNpc
{
    NpcType type;               // enum ID
    const char *name;           // display name
    const char *title;          // subtitle shown under name
    const char *greeting;       // first dialogue line
    NpcRole role;               // functional role
    NpcDisposition disposition; // default attitude to player
    LocationType location_id;   // where they stand (FK → base_location)
    TownType town_id;           // parent town  (FK → base_town)
    uint8_t is_essential;       // 1 = cannot be killed
    uint8_t level_req;          // min player level to interact
} BaseNpc;

/* ─────────────────────────────────────────────
   Static NPC Table
   Access via: base_npc[NPC_ELARA_GRAVEDIGGER]
───────────────────────────────────────────── */
static const BaseNpc base_npc[NPC_MAX] = {

    [NPC_ELARA_GRAVEDIGGER] =
        {
            .type  = NPC_ELARA_GRAVEDIGGER,
            .name  = "Elara",
            .title = "The Gravedigger",
            .greeting =
                "Dig enough graves and the dead start to feel like neighbours.",
            .role         = ROLE_QUESTGIVER,
            .disposition  = DISP_NEUTRAL,
            .location_id  = LOC_ASHVEIL_CEMETERY,
            .town_id      = TOWN_ASHVEIL,
            .is_essential = 1,
            .level_req    = 1,
        },

    [NPC_PRIOR_MALTHEUS] =
        {
            .type     = NPC_PRIOR_MALTHEUS,
            .name     = "Prior Maltheus",
            .title    = "Hand of the Silver Inquisition",
            .greeting = "Confess willingly and the fire is quick. Resist and "
                        "it is not.",
            .role     = ROLE_ENEMY_NPC,
            .disposition  = DISP_HOSTILE,
            .location_id  = LOC_GRIMHOLT_INQUISITORY,
            .town_id      = TOWN_GRIMHOLT,
            .is_essential = 0,
            .level_req    = 10,
        },

    [NPC_MURK_APOTHECARY] =
        {
            .type         = NPC_MURK_APOTHECARY,
            .name         = "Murk",
            .title        = "Apothecary & Curiosities",
            .greeting     = "I don't ask where you've been. You shouldn't ask "
                            "what's in the jar.",
            .role         = ROLE_MERCHANT,
            .disposition  = DISP_NEUTRAL,
            .location_id  = LOC_WRAITHFEN_APOTHECARY,
            .town_id      = TOWN_WRAITHFEN,
            .is_essential = 1,
            .level_req    = 1,
        },

    [NPC_COUNT_VALDRIS] =
        {
            .type         = NPC_COUNT_VALDRIS,
            .name         = "Count Valdris",
            .title        = "Lord of Duskmere, Eternal",
            .greeting     = "You've survived the road to my castle. That alone "
                            "earns you five minutes.",
            .role         = ROLE_QUESTGIVER,
            .disposition  = DISP_SUSPICIOUS,
            .location_id  = LOC_DUSKMERE_CASTLE,
            .town_id      = TOWN_DUSKMERE,
            .is_essential = 0,
            .level_req    = 18,
        },

    [NPC_FOREMAN_GRETH] =
        {
            .type  = NPC_FOREMAN_GRETH,
            .name  = "Foreman Greth",
            .title = "Overseer of the Ashen Foundry",
            .greeting =
                "You look strong. The deep shift pays double. Don't ask why.",
            .role         = ROLE_QUESTGIVER,
            .disposition  = DISP_NEUTRAL,
            .location_id  = LOC_IRONSPIRE_FOUNDRY,
            .town_id      = TOWN_IRONSPIRE,
            .is_essential = 1,
            .level_req    = 12,
        },

    [NPC_SILAS_SMUGGLER] =
        {
            .type  = NPC_SILAS_SMUGGLER,
            .name  = "Silas",
            .title = "Dockmaster & Purveyor of Discretion",
            .greeting =
                "I move cargo, not questions. You want something moved?",
            .role         = ROLE_MERCHANT,
            .disposition  = DISP_SUSPICIOUS,
            .location_id  = LOC_SALTMOOR_DOCKYARDS,
            .town_id      = TOWN_SALTMOOR,
            .is_essential = 1,
            .level_req    = 1,
        },

    [NPC_ARCHIVIST_VOSS] =
        {
            .type     = NPC_ARCHIVIST_VOSS,
            .name     = "Archivist Voss",
            .title    = "Last Keeper of the Crown Records",
            .greeting = "I have catalogued the fall of kingdoms. Yours will be "
                        "entry four thousand and nine.",
            .role     = ROLE_LOREKEEPER,
            .disposition  = DISP_FRIENDLY,
            .location_id  = LOC_CRESTFALL_THRONE_ROOM,
            .town_id      = TOWN_CRESTFALL,
            .is_essential = 1,
            .level_req    = 20,
        },

    [NPC_WREN_HERBALIST] =
        {
            .type     = NPC_WREN_HERBALIST,
            .name     = "Wren",
            .title    = "Herbalist of the Thornwood",
            .greeting = "The wood told me you were coming. It rarely bothers "
                        "unless something is wrong.",
            .role     = ROLE_HEALER,
            .disposition  = DISP_FRIENDLY,
            .location_id  = LOC_THORNWICK_WITCHWOOD,
            .town_id      = TOWN_THORNWICK,
            .is_essential = 1,
            .level_req    = 1,
        },

    [NPC_ELDER_DURAK] =
        {
            .type     = NPC_ELDER_DURAK,
            .name     = "Elder Durak",
            .title    = "Stone-Warden of Vorrathgard",
            .greeting = "We sealed the deep tunnels in my grandfather's time. "
                        "Whatever you heard down there, ignore it.",
            .role     = ROLE_QUESTGIVER,
            .disposition  = DISP_NEUTRAL,
            .location_id  = LOC_VORRATHGARD_DEEP_MINES,
            .town_id      = TOWN_VORRATHGARD,
            .is_essential = 1,
            .level_req    = 25,
        },

    [NPC_COMMANDER_SERATH] =
        {
            .type         = NPC_COMMANDER_SERATH,
            .name         = "Commander Serath",
            .title        = "Warden of the Obsidian Gate",
            .greeting     = "Every soldier here volunteered. That tells you "
                            "everything about what waits beyond the gate.",
            .role         = ROLE_TRAINER,
            .disposition  = DISP_FRIENDLY,
            .location_id  = LOC_OBSIDIAN_GATE_WARCAMP,
            .town_id      = TOWN_OBSIDIAN_GATE,
            .is_essential = 1,
            .level_req    = 1,
        },
};

#endif /* NPC_DATA_H */
