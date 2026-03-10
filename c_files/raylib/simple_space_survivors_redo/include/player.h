#ifndef PLAYER_H
#define PLAYER_H

#include "../include/sprite_data.h"

typedef struct Player
{
    SpriteData sprite_name;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;

    float speed;
    Vector2 direction;

    float max_hp;
    float hp;

} Player;

void player_init(Player *player);
void player_draw(const Player *player, const Texture2D spritesheet);
void player_update(Player *player, const float dt, const Vector2 target_pos);

#endif // PLAYER_H
