#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include "../components.h"

typedef struct Player
{
    TransformComponent transform;
    RenderComponent render;
    MovementComponent movement;

} Player;

void player_init(Player *player, const Texture2D spritesheet);
void player_draw(const Player *player);
void player_update(Player *player, float dt, Vector2 mouse_pos_world);

#endif // ENTITY_PLAYER_H
