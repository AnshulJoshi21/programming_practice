#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "animation_data.h"
#include <raylib.h>

typedef struct CLevel {
    int current;
} CLevel;

typedef struct CXp {
    int current;
    int next;
    int pending_levelups;
} CXp;

typedef struct CState {
    int  prev;
    int  current;
    bool active;
} CState;

typedef struct CTransform {
    Vector2 pos;
    Vector2 scale;
    float   rotation;
} CTransform;

typedef struct CRender {
    Texture2D texture;
    Rectangle source;
    Vector2   size;
    Vector2   origin;
    Color     tint;
} CRender;

typedef struct CText {
    const char* string;
    float       font_size;
    float       spacing;
    Color       tint;
} CText;

typedef struct CMovement {
    float   speed_x;
    float   speed_y;
    Vector2 direction;
} CMovement;

typedef struct CHealth {
    int max;
    int current;
} CHealth;

typedef struct CDamage {
    int current;
} CDamage;

typedef struct CLifetime {
    float max;
    float current;
} CLifetime;

typedef struct CAnimation {
    int   type;
    int   current;
    float timer;
    bool  is_finished;
} CAnimation;

typedef struct CSpawner {
    int max;
    int current;
} CSpawner;

typedef struct CTimer {
    float elapsed;
    float interval;
} CTimer;

#endif // COMPONENTS_H
