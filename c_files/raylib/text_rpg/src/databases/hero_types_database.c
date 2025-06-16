#include "../../include/databases/hero_types_database.h"

const BaseHero hero_types[] = { { "WARRIOR", 90, 8, 8, 1.12f, 1.06f, 1.08f },
                                { "RANGER", 60, 11, 4, 1.08f, 1.12f, 1.06f },
                                { "MAGE", 50, 14, 3, 1.05f, 1.15f, 1.04f },
                                { "CLERIC", 65, 6, 6, 1.10f, 1.04f, 1.07f },
                                { "ROGUE", 55, 13, 3, 1.07f, 1.14f, 1.05f },
                                { "PALADIN", 80, 9, 7, 1.11f, 1.08f, 1.09f },
                                { "BERSERKER", 70, 12, 5, 1.10f, 1.13f, 1.06f },
                                { "NECROMANCER", 50, 10, 3, 1.06f, 1.10f, 1.04f },
                                { "DRUID", 65, 9, 5, 1.10f, 1.09f, 1.07f },
                                { "MONK", 60, 10, 5, 1.09f, 1.10f, 1.08f } };

const int hero_types_size = sizeof(hero_types) / sizeof(hero_types[0]);
