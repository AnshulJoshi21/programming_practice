#ifndef GAME_STATES_H
#define GAME_STATES_H

typedef enum GameState
{
    STATE_MAIN_MENU = 0,
    STATE_PLAYER_SELECTION_MENU = 1,
    STATE_TOWN_MENU = 2,
    STATE_MAP_MENU = 3,
    STATE_QUEST_MENU = 4,
    STATE_SHOP_MENU = 5,

    STATE_QUIT = 6,

} GameState;

#endif // GAME_STATES_H