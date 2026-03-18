#include "enemy_data.h"

const BaseEnemy base_enemy_db[ENEMY_MAX] = {

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
