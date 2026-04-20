#ifndef ENEMY_H
#define ENEMY_H

#include "../components.h"

typedef enum EnemyType {
    ENEMY_BASIC,
    ENEMY_FAST,
    ENEMY_TANK,
    ENEMY_RANGED,
    ENEMY_MAX

} EnemyType;

typedef struct Enemy {
    EnemyType type;
    PositionComponent position;
    RectComponent rect;
    RotationComponent rotation;
    ColorComponent color;
    TextComponent text;
    MoveComponent move;
    HealthComponent health;
    DamageComponent damage;
    AnimationComponent animation;

} Enemy;

void enemy_init(Enemy *enemy, const EnemyType type, const Vector2 target_pos);
void enemy_draw(const Enemy *enemy);
void enemy_update(Enemy *enemy, const float dt, const Vector2 target_pos);

#endif  // ENEMY_H
