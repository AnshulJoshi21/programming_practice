#ifndef ENEMY_TYPES_DATABASE_H
#define ENEMY_TYPES_DATABASE_H

typedef struct BaseEnemy
{
    const char* const type;
    const float health;
    const float damage;
    const float defense;
    const float health_growth;
    const float damage_growth;
    const float defense_growth;

} BaseEnemy;

extern const BaseEnemy enemy_types[];
extern const int enemy_types_size;

#endif // ENEMY_TYPES_DATABASE_H