#ifndef ENEMY_DATA_H
#define ENEMY_DATA_H

#include "armor_data.h"
#include "weapon_data.h"

#include <stdint.h>

typedef enum EnemyType {
    ENEMY_GOBLIN = 0,
    ENEMY_SKELETON,
    ENEMY_ORC,
    ENEMY_TROLL,
    ENEMY_VAMPIRE,
    ENEMY_WEREWOLF,
    ENEMY_DEMON,
    ENEMY_GOLEM,
    ENEMY_DRAGON,
    ENEMY_LICH,

    ENEMY_MAX,
} EnemyType;

typedef enum EnemyTier {
    TIER_COMMON = 0, // early game trash
    TIER_UNCOMMON,   // mid game threat
    TIER_ELITE,      // dangerous encounter
    TIER_BOSS,       // dungeon boss
} EnemyTier;

typedef enum EnemyBehaviour {
    AI_AGGRESSIVE = 0, // always charges player
    AI_DEFENSIVE,      // holds position, counterattacks
    AI_RANGED,         // keeps distance, kites
    AI_SUPPORT,        // heals/buffs nearby enemies
    AI_AMBUSH,         // waits hidden, burst damage
} EnemyBehaviour;

typedef struct BaseEnemy
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
} BaseEnemy;

extern const BaseEnemy base_enemy_db[ENEMY_MAX];

#endif
