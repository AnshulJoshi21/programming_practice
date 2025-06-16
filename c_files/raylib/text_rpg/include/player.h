#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct Player
{
    const char * const type;
    const float max_health;
    float health;
    float damage;
    float defense;
    const float health_growth;
    const float damage_growth;
    const float defense_growth;

}Player;

Player player_init(int selected);
bool player_is_alive(Player * player);
void player_draw(Player *player);
void Player_update(Player *player);

#endif // PLAYER_H;