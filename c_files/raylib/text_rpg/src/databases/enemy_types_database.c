#include "../../include/databases/enemy_types_database.h"

const BaseEnemy enemy_types[] = {
    { "Zombie", 50, 5, 1.10f, 1.05f, 4, 1.05f },    { "Goblin", 40, 7, 1.08f, 1.06f, 2, 1.03f },
    { "Skeleton", 45, 6, 1.09f, 1.05f, 3, 1.04f },  { "Orc", 70, 10, 1.12f, 1.08f, 6, 1.07f },
    { "Troll", 100, 8, 1.15f, 1.04f, 8, 1.06f },    { "Vampire", 65, 12, 1.10f, 1.10f, 5, 1.08f },
    { "Werewolf", 80, 11, 1.12f, 1.09f, 6, 1.07f }, { "Demon", 90, 14, 1.13f, 1.12f, 7, 1.09f },
    { "Dragon", 150, 20, 1.18f, 1.15f, 10, 1.10f }, { "Bandit", 55, 9, 1.09f, 1.07f, 3, 1.05f },
    { "Witch", 60, 13, 1.08f, 1.13f, 4, 1.06f }
};

const int enemy_types_size = sizeof(enemy_types) / sizeof(enemy_types[0]);