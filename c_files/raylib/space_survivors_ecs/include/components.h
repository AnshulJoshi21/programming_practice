#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "sprite_data.h"

#include <raylib.h>

#define BIT(x) (1 << x)

typedef enum ComponentMask {
    TAG_PLAYER     = BIT(0),
    COMP_TRANSFORM = BIT(1),
    COMP_SPRITE    = BIT(2),
    COMP_MOVE      = BIT(3),
    COMP_HEALTH    = BIT(4),
    COMP_DAMAGE    = BIT(5),
    COMP_LIFETIME  = BIT(6),
    COMP_TARGET    = BIT(7),

} ComponentMask;

typedef struct TransformComponent
{
    Vector2 pos;
    Vector2 scale;
    float rotation;

} TransformComponent;

typedef struct SpriteComponent
{
    SpriteData current_sprite;
    Color tint;

} SpriteComponent;

typedef struct MoveComponent
{
    Vector2 direction;
    float speed;

} MoveComponent;

typedef struct HealthComponent
{
    int max_hp;
    int hp;

} HealthComponent;

typedef struct DamageComponent
{
    int damage;

} DamageComponent;

typedef struct LifetimeComponent
{
    float life;

} LifetimeComponent;

typedef struct TargetComponent
{
    Vector2 *pos;
    bool continous_update;

} TargetComponent;

#endif // COMPONENTS_H
