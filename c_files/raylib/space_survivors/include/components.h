#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "sprite_data.h"

#include <raylib.h>

#define BIT(n) (1 << (n))

typedef enum ComponentMask {
    TAG_PLAYER     = BIT(0),
    COMP_TRANSFORM = BIT(1),
    COMP_ANIMATION = BIT(2),
    COMP_COLOR     = BIT(3),
    COMP_MOVE      = BIT(4),
    COMP_HEALTH    = BIT(5),
    COMP_DAMAGE    = BIT(6),
    COMP_TARGET    = BIT(7),
    COMP_LIFETIME  = BIT(8)

} ComponentMask;

typedef struct TransformComponent
{
    Vector2 pos;
    Vector2 scale;
    float rotation;

} TransformComponent;

typedef struct AnimationComponent
{
    SpriteData current_sprite;

} AnimationComponent;

typedef struct ColorComponent
{
    Color tint;

} ColorComponent;

typedef struct MoveComponent
{
    float speed;
    Vector2 direction;

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

typedef struct TargetComponent
{
    const Vector2 *pos;
    bool track_once;

} TargetComponent;

typedef struct LifetimeComponent
{
    float lifetime;

} LifetimeComponent;

#endif // COMPONENTS_H
