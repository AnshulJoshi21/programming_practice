#ifndef PLAYER_H
#define PLAYER_H

#include "../include/sprite_data.h"

typedef struct Player
{
    Texture2D texture;
    SpriteData current_sprite;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;

    float speed;

    Vector2 look_direction;
    Vector2 move_direction;

    float max_hp;
    float hp;

} Player;

void player_init(Player *player, const Texture2D spritesheet);
void player_draw(const Player *player);
void player_update(Player *player, const float dt,
                   const Vector2 closest_target);

#endif // PLAYER_H
