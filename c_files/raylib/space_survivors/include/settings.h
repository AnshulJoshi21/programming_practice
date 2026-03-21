#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

#define SCREEN_BACKGROUND RAYWHITE
#define MAX_ENTITIES 2000

extern const uint16_t SCREEN_WIDTH;
extern const uint16_t SCREEN_HEIGHT;
extern const char SCREEN_TITLE[];
extern const uint16_t MAP_SIZE;
extern const float ROTATION_OFFSET;
extern const float PLAYER_SCALE;
extern const float ENEMY_SCALE;
extern const float LASER_SCALE;
extern const float MAX_LASER_LIFETIME;
extern const float ENEMY_MIN_SPAWN_DISTANCE;
extern const float ENEMY_MAX_SPAWN_DISTANCE;

#endif // SETTINGS_H
