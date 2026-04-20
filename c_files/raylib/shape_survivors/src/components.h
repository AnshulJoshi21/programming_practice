#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <raylib.h>

typedef struct XpComponent {
    int level;
    int xp;
    int xp_next;
    int pending_levelups;

} XpComponent;

typedef struct StateComponent {
    bool active;

} StateComponent;

typedef struct PositionComponent {
    float x;
    float y;

} PositionComponent;

typedef struct RectComponent {
    float width;
    float height;

} RectComponent;

typedef struct CircleComponent {
    float radius;

} CircleComponent;

typedef struct RotationComponent {
    float value;

} RotationComponent;

typedef struct TextComponent {
    const char *text;

} TextComponent;

typedef struct ColorComponent {
    Color tint;

} ColorComponent;

typedef struct MoveComponent {
    float speed;
    Vector2 direction;

} MoveComponent;

typedef struct HealthComponent {
    int max_hp;
    int hp;

} HealthComponent;

typedef struct DamageComponent {
    int value;

} DamageComponent;

typedef struct LifetimeComponent {
    float max;
    float remaining;

} LifetimeComponent;

typedef struct AnimationComponent {
    float hit_timer;

} AnimationComponent;

typedef struct SpawnerComponent {
    int max;
    int count;

} SpawnerComponent;

typedef struct TimerComponent {
    float elapsed;
    float interval;

} TimerComponent;

typedef struct DropComponent {
    int type;
    int amount;

} DropComponent;

typedef struct ParticleComponent {
    int type;

} ParticleComponent;

#endif  // COMPONENTS_H
