#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

#define SCREEN_BACKGROUND RAYWHITE

#define MAX_ENTITIES 2000

extern const uint16_t SCREEN_WIDTH;
extern const uint16_t SCREEN_HEIGHT;
extern const char SCREEN_TITLE[];

extern const uint16_t MAP_SIZE;

#define MAX_ENEMIES 200

extern const uint16_t ENEMY_MIN_SPAWN_DISTANCE;
extern const uint16_t ENEMY_MAX_SPAWN_DISTANCE;
extern const float ENEMY_SPAWN_RATE;

#define MAX_BULLETS 200

extern const float BULLET_SPAWN_RATE;
extern const float BULLET_MAX_LIFETIME;

#endif // SETTINGS_H
