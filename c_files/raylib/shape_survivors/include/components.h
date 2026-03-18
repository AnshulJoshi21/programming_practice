#include <raylib.h>

typedef enum ComponentMask {
    COMP_POSITION  = 1 << 0,
    COMP_COLOR     = 1 << 1,
    COMP_MOVE      = 1 << 2,
    COMP_HEALTH    = 1 << 3,
    COMP_DAMAGE    = 1 << 4,
    COMP_ANIMATION = 1 << 5,

    TAG_PLAYER = 1 << 6,
    TAG_ENEMY  = 1 << 7,
    TAG_BULLET = 1 << 8

} ComponentMask;

typedef struct PositionComponent
{
    Vector2 pos;

} PositionComponent;

typedef struct ColorComponent
{
    Color color;

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

typedef struct AnimationComponent
{
    float hit_timer;

} AnimationComponent;
