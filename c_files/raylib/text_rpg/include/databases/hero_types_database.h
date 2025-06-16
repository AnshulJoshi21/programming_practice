#ifndef Hero_TYPES_DATABASE_H
#define Hero_TYPES_DATABASE_H

typedef struct BaseHero
{
    const char* const type;
    const float health;
    const float damage;
    const float defense;
    const float health_growth;
    const float damage_growth;
    const float defense_growth;

} BaseHero;

extern const BaseHero hero_types[];
extern const int hero_types_size;

#endif // Hero_TYPES_DATABASE_H