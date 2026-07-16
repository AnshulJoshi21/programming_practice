#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <raylib.h>

typedef struct CLevel {
    int level;
} CLevel;

typedef struct CExp {
    int exp;
    int exp_next;
    int pending_levelups;
} CExp;

typedef struct CState {
    bool active;
} CState;

typedef struct CPosition {
    float x;
    float y;
} CPosition;

typedef struct CRect {
    float width;
    float height;
} CRect;

typedef struct CCircle {
    float radius;
} CCircle;

typedef struct CRotation {
    float angle;
} CRotation;

typedef struct CColor {
    Color tint;
} CColor;

typedef struct CText {
    const char* text;
    float       font_size;
    float       spacing;
    Color       tint;
} CText;

typedef struct CMovement {
    float   speed;
    Vector2 direction;
} CMovement;

typedef struct CHealth {
    int max;
    int current;
} CHealth;

typedef struct CDamage {
    int amount;
} CDamage;

typedef struct CLifetime {
    float max;
    float remaining;
} CLifetime;

typedef struct CAnimation {
    float hit_timer_max;
    float hit_timer;
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
