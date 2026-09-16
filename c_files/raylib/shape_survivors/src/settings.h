#ifndef SETTINGS_H
#define SETTINGS_H

#include <raylib.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int MAP_SIZE;

#define MAX_BULLETS 10
#define MAX_ORBITALS 10

typedef struct {
    Color dark;
    Color purple;
    Color beige;
    Color white;
} Palette;

extern const Palette palette;

#endif // SETTINGS_H
