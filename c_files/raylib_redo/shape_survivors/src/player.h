#ifndef PLAYER_H
#define PLAYER_H

#include "components.h"

typedef struct Player {
    CLevel     level;
    CXp        xp;
    CPosition  position;
    CRotation  rotation;
    CRect      rect;
    CColor     color;
    CText      text;
    CMove      move;
    CHealth    health;
    CAnimation animation;
    CTimer     bullet_timer;
} Player;

void player_init(Player* player);
void player_draw(const Player* player);
void player_update(Player* player, const float dt);

#endif // PLAYER_H
