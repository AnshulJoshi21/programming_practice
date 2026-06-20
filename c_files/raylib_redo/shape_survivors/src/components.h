#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <raylib.h>

typedef struct CLevel {
    int level;
} CLevel;

typedef struct CXp {
    int xp;
    int xp_next;
    int pending_levelups;
} CXp;

typedef struct CPosition {
    float x;
    float y;
} CPosition;

typedef struct CRotation {
    float angle;
} CRotation;

typedef struct CRect {
    float width;
    float height;
} CRect;

typedef struct CCircle {
    float radius;
} CCircle;

typedef struct CColor {
    Color tint;

} CColor;

typedef struct CText {
    const char* text;
    float       font_size;
    float       spacing;
    Color       tint;
} CText;

typedef struct CMove {
    float   speed;
    Vector2 direction;
} CMove;

typedef struct CHealth {
    int hp;
    int max;
} CHealth;

typedef struct CDamage {
    int dmg;
} CDamage;

typedef struct CAnimation {
    float hit_timer;
    float hit_timer_max;
} CAnimation;

typedef struct CLifetime {
    float life;
    float max;
} CLifetime;

typedef struct CSpawner {
    int current;
    int max;
} CSpawner;

typedef struct CTimer {
    float elapsed;
    float duration;
} CTimer;

#endif // COMPONENTS_H
