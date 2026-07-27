#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <raylib.h>

typedef struct CLevel {
    int current;
    int pending;
} CLevel;

typedef struct CXp {
    int current;
    int next;
} CXp;

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

typedef struct COrbit {
    float angle;
    float angular_speed;
    float orbit_radius;
} COrbit;

typedef struct CColor {
    Color tint;
} CColor;

typedef struct CText {
    const char* string;
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
    int current;
} CDamage;

typedef struct CLifetime {
    float max;
    float current;
} CLifetime;

typedef struct CAnimation {
    float hit_timer_max;
    float hit_timer_current;
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
