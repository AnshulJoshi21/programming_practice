#ifndef SETTINGS_H
#define SETTINGS_H

#include <raylib.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const char SCREEN_TITLE[];

#define SCREEN_BACKGROUND RAYWHITE
#define HIT_COLOR RED

#define MAX_ENTITIES 2000

extern const int MAP_SIZE;
extern const float MAX_HIT_TIMER;

extern const float PLAYER_SIZE;
extern const float PLAYER_ROTATION;

extern const float ENEMY_SIZE;
extern const float ENEMY_ROTATION;

#endif // SETTINGS_H
