#include "enemy_data.h"

const EnemyData enemy_db[ENEMY_TYPE_MAX] = {{"Bat", {24, 24}, 100.0f, 20, 5},
                                            {"Zombie", {32, 32}, 60.0f, 40, 10},
                                            {"Ghost", {24, 24}, 80.0f, 25, 7},
                                            {"Vampire", {28, 28}, 70.0f, 50, 12},
                                            {"Demon", {36, 36}, 50.0f, 80, 15}};
