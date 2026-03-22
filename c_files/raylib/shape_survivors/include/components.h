#include <raylib.h>

#define BIT(n) (1 << (n))

typedef enum ComponentMask {

    COMP_POSITION = BIT(0),
    COMP_SIZE     = BIT(1),
    COMP_RADIUS   = BIT(2),
    COMP_COLOR    = BIT(3),
    COMP_MOVE     = BIT(4),
    COMP_HEALTH   = BIT(5),
    COMP_DAMAGE   = BIT(6),
    COMP_LIFETIME = BIT(7),
    COMP_TARGET   = BIT(8),

    TAG_PLAYER = BIT(9),
    TAG_ENEMY  = BIT(10),
    TAG_BULLET = BIT(11)

} ComponentMask;

typedef struct PositionComponent
{
    Vector2 pos;

} PositionComponent;

typedef struct SizeComponent
{
    float size;

} SizeComponent;

typedef struct RadiusComponent
{
    float radius;

} RadiusComponent;

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
    int dmg;

} DamageComponent;

typedef struct LifetimeComponent
{
    float life;

} LifetimeComponent;

typedef struct TargetComponent
{
    const Vector2 *pos;
    bool track_once;

} TargetComponent;
