#ifndef PLAYER_H
#define PLAYER_H

#include "asset_manager.h"
#include "components.h"
#include <raylib.h>

typedef enum PlayerState {
    PLAYER_STATE_NONE,

    PLAYER_STATE_IDLE,
    PLAYER_STATE_RUN,
    PLAYER_STATE_JUMP,
    PLAYER_STATE_ATTACK,
    PLAYER_STATE_HURT,
    PLAYER_STATE_DASH,
    PLAYER_STATE_SLIDE,
    PLAYER_STATE_CROUCH,
    PLAYER_STATE_LEDGE_HANG,
    PLAYER_STATE_WALL_SLIDE,
    PLAYER_STATE_LADDER,
    PLAYER_STATE_DEATH,

    PLAYER_STATE_MAX

} PlayerState;

typedef struct Player {
    CState     state;
    CLevel     level;
    CXp        xp;
    CTransform transform;
    CRender    render;
    CMovement  movement;
    CHealth    health;
    CAnimation animation;
} Player;

void player_init(Player* player, const AssetManager* asset_manager);
void player_update(Player* player, const float dt);
void player_draw(const Player* player);

#endif // PLAYER_H
