#ifndef PLAYER_H
#define PLAYER_H

#include "bullets/bullet.h"
#include "components.h"
#include <raylib.h>

typedef struct Player {
    CLevel     level;
    CXp        xp;
    CPosition  position;
    CRect      rect;
    CRotation  rotation;
    CColor     color;
    CText      text;
    CMovement  movement;
    CHealth    health;
    CAnimation animation;
    CTimer     bullet_timer;

    BulletConfig bullet_config;
} Player;

void player_init(Player* player);
void player_update(Player* player, const float dt);
void player_draw(const Player* player);

#endif // PLAYER_H
