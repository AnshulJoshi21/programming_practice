#include "../include/player.h"
#include "../include/databases/hero_types_database.h"
#include <stdio.h>
#include <stdlib.h>

Player
player_init(int selected)
{
    if (selected < 0 || selected >= hero_types_size)
    {
        fprintf(stderr, "Parameter 'selected' out of bounds\n");
        exit(EXIT_FAILURE);
    }

    return (Player){
        .type = hero_types[selected].type,
        .max_health = hero_types[selected].health,
        .health = hero_types[selected].health,
        .damage = hero_types[selected].damage,
        .defense = hero_types[selected].defense,
        .health_growth = hero_types[selected].health_growth,
        .damage_growth = hero_types[selected].damage_growth,
        .defense_growth = hero_types[selected].defense_growth,
    };
}

bool
player_is_alive(Player* player)
{
    return player->health > 0;
}