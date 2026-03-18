// enemy_data.h

#ifndef ENEMY_DATA_H
#define ENEMY_DATA_H

#include "armor_data.h"
#include "weapon_data.h"

#include <stdint.h>

/* ─────────────────────────────────────────────
   Enemy Types
───────────────────────────────────────────── */
typedef enum EnemyType {
    ENEMY_GOBLIN   = 0,
    ENEMY_SKELETON = 1,
    ENEMY_ORC      = 2,
    ENEMY_TROLL    = 3,
    ENEMY_VAMPIRE  = 4,
    ENEMY_WEREWOLF = 5,
    ENEMY_DEMON    = 6,
    ENEMY_GOLEM    = 7,
    ENEMY_DRAGON   = 8,
    ENEMY_LICH     = 9,
    ENEMY_MAX      = 10,
} EnemyType;

/* ─────────────────────────────────────────────
   Enemy Tier (difficulty band)
───────────────────────────────────────────── */
typedef enum EnemyTier {
    TIER_COMMON   = 0, // early game trash
    TIER_UNCOMMON = 1, // mid game threat
    TIER_ELITE    = 2, // dangerous encounter
    TIER_BOSS     = 3, // dungeon boss
} EnemyTier;

/* ─────────────────────────────────────────────
   Enemy Behaviour AI Hint
───────────────────────────────────────────── */
typedef enum EnemyBehaviour {
    AI_AGGRESSIVE = 0, // always charges player
    AI_DEFENSIVE  = 1, // holds position, counterattacks
    AI_RANGED     = 2, // keeps distance, kites
    AI_SUPPORT    = 3, // heals/buffs nearby enemies
    AI_AMBUSH     = 4, // waits hidden, burst damage
} EnemyBehaviour;

/* ─────────────────────────────────────────────
   Base Enemy Definition
───────────────────────────────────────────── */
typedef struct BaseEnemyData
{
    EnemyType type;            // enum ID
    const char *name;          // display name
    EnemyTier tier;            // difficulty band
    EnemyBehaviour behaviour;  // AI pattern hint
    uint16_t base_hp;          // hit points
    uint8_t base_defense;      // flat damage reduction
    uint8_t base_magic_resist; // magic damage reduction
    WeaponType weapon;         // attack style (maps to weapon table)
    uint16_t damage_bonus;     // flat bonus on top of weapon damage
    uint8_t move_speed;        // tiles per turn (1–10)
    uint16_t exp_reward;       // experience granted on kill
    uint16_t gold_reward;      // gold dropped on kill
} BaseEnemyData;

/* ─────────────────────────────────────────────
   Static Enemy Table
   Access via: base_enemy[ENEMY_GOBLIN]
───────────────────────────────────────────── */
static const BaseEnemyData base_enemy[ENEMY_MAX] = {

    [ENEMY_GOBLIN] =
        {
            .type              = ENEMY_GOBLIN,
            .name              = "Goblin",
            .tier              = TIER_COMMON,
            .behaviour         = AI_AGGRESSIVE,
            .base_hp           = 40,
            .base_defense      = 3,
            .base_magic_resist = 2,
            .weapon            = WEAPON_DAGGER,
            .damage_bonus      = 2,
            .move_speed        = 6,
            .exp_reward        = 20,
            .gold_reward       = 8,
        },

    [ENEMY_SKELETON] =
        {
            .type              = ENEMY_SKELETON,
            .name              = "Skeleton",
            .tier              = TIER_COMMON,
            .behaviour         = AI_AGGRESSIVE,
            .base_hp           = 55,
            .base_defense      = 8,
            .base_magic_resist = 0,
            .weapon            = WEAPON_SWORD,
            .damage_bonus      = 3,
            .move_speed        = 4,
            .exp_reward        = 30,
            .gold_reward       = 5,
        },

    [ENEMY_ORC] =
        {
            .type              = ENEMY_ORC,
            .name              = "Orc",
            .tier              = TIER_UNCOMMON,
            .behaviour         = AI_AGGRESSIVE,
            .base_hp           = 120,
            .base_defense      = 14,
            .base_magic_resist = 4,
            .weapon            = WEAPON_AXE,
            .damage_bonus      = 8,
            .move_speed        = 4,
            .exp_reward        = 75,
            .gold_reward       = 25,
        },

    [ENEMY_TROLL] =
        {
            .type              = ENEMY_TROLL,
            .name              = "Troll",
            .tier              = TIER_UNCOMMON,
            .behaviour         = AI_DEFENSIVE,
            .base_hp           = 200,
            .base_defense      = 20,
            .base_magic_resist = 6,
            .weapon            = WEAPON_MACE,
            .damage_bonus      = 12,
            .move_speed        = 3,
            .exp_reward        = 120,
            .gold_reward       = 40,
        },

    [ENEMY_VAMPIRE] =
        {
            .type              = ENEMY_VAMPIRE,
            .name              = "Vampire",
            .tier              = TIER_ELITE,
            .behaviour         = AI_AMBUSH,
            .base_hp           = 180,
            .base_defense      = 16,
            .base_magic_resist = 22,
            .weapon            = WEAPON_DAGGER,
            .damage_bonus      = 18,
            .move_speed        = 8,
            .exp_reward        = 200,
            .gold_reward       = 80,
        },

    [ENEMY_WEREWOLF] =
        {
            .type              = ENEMY_WEREWOLF,
            .name              = "Werewolf",
            .tier              = TIER_ELITE,
            .behaviour         = AI_AGGRESSIVE,
            .base_hp           = 220,
            .base_defense      = 18,
            .base_magic_resist = 10,
            .weapon            = WEAPON_SPEAR, // claws mapped to spear reach
            .damage_bonus      = 22,
            .move_speed        = 9,
            .exp_reward        = 240,
            .gold_reward       = 60,
        },

    [ENEMY_DEMON] =
        {
            .type              = ENEMY_DEMON,
            .name              = "Demon",
            .tier              = TIER_ELITE,
            .behaviour         = AI_AGGRESSIVE,
            .base_hp           = 280,
            .base_defense      = 24,
            .base_magic_resist = 30,
            .weapon            = WEAPON_SCYTHE,
            .damage_bonus      = 28,
            .move_speed        = 6,
            .exp_reward        = 320,
            .gold_reward       = 120,
        },

    [ENEMY_GOLEM] =
        {
            .type              = ENEMY_GOLEM,
            .name              = "Golem",
            .tier              = TIER_ELITE,
            .behaviour         = AI_DEFENSIVE,
            .base_hp           = 400,
            .base_defense      = 40,
            .base_magic_resist = 35,
            .weapon            = WEAPON_MACE,
            .damage_bonus      = 30,
            .move_speed        = 2,
            .exp_reward        = 380,
            .gold_reward       = 100,
        },

    [ENEMY_DRAGON] =
        {
            .type              = ENEMY_DRAGON,
            .name              = "Dragon",
            .tier              = TIER_BOSS,
            .behaviour         = AI_AGGRESSIVE,
            .base_hp           = 800,
            .base_defense      = 55,
            .base_magic_resist = 50,
            .weapon       = WEAPON_CROSSBOW, // breath mapped to crossbow range
            .damage_bonus = 60,
            .move_speed   = 7,
            .exp_reward   = 1000,
            .gold_reward  = 500,
        },

    [ENEMY_LICH] =
        {
            .type              = ENEMY_LICH,
            .name              = "Lich",
            .tier              = TIER_BOSS,
            .behaviour         = AI_RANGED,
            .base_hp           = 600,
            .base_defense      = 30,
            .base_magic_resist = 80,
            .weapon            = WEAPON_STAFF,
            .damage_bonus      = 70,
            .move_speed        = 4,
            .exp_reward        = 1200,
            .gold_reward       = 650,
        },
};

#endif /* ENEMY_DATA_H */
