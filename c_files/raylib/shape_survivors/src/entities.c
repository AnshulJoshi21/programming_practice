#include "../include/entities.h"
#include "../include/settings.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

uint32_t create_player(World *world)
{
    assert(world);

    const uint32_t id = create_entity(world);

    world->mask_list[id] = TAG_PLAYER | COMP_POSITION | COMP_SIZE | COMP_COLOR |
                           COMP_MOVE | COMP_HEALTH | COMP_TARGET;

    PositionComponent *position_c = &world->position_list[id];
    SizeComponent *size_c         = &world->size_list[id];
    ColorComponent *color_c       = &world->color_list[id];
    MoveComponent *move_c         = &world->move_list[id];
    HealthComponent *health_c     = &world->health_list[id];
    TargetComponent *target_c     = &world->target_list[id];

    position_c->pos = (Vector2){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f};

    size_c->size = 40.0f;

    color_c->color = GRAY;

    move_c->speed     = 300.0f;
    move_c->direction = (Vector2){0, 0};

    health_c->max_hp = 100;
    health_c->hp     = health_c->max_hp;

    target_c->pos        = NULL;
    target_c->track_once = false;

    return id;
}

uint32_t create_enemy(World *world, const Vector2 *target_pos)
{
    assert(world);

    const uint32_t id = create_entity(world);

    world->mask_list[id] = TAG_ENEMY | COMP_POSITION | COMP_SIZE | COMP_COLOR |
                           COMP_MOVE | COMP_HEALTH | COMP_DAMAGE | COMP_TARGET;

    PositionComponent *position_c = &world->position_list[id];
    SizeComponent *size_c         = &world->size_list[id];
    ColorComponent *color_c       = &world->color_list[id];
    MoveComponent *move_c         = &world->move_list[id];
    HealthComponent *health_c     = &world->health_list[id];
    DamageComponent *damage_c     = &world->damage_list[id];
    TargetComponent *target_c     = &world->target_list[id];

    const float random_angle   = utils_random_uniform(0, 2 * PI);
    const float random_distace = utils_random_uniform(ENEMY_MIN_SPAWN_DISTANCE,
                                                      ENEMY_MAX_SPAWN_DISTANCE);
    const Vector2 start_pos    = (Vector2){
        cosf(random_angle) * random_distace + target_pos->x,
        cosf(random_angle) * random_distace + target_pos->y,
    };

    position_c->pos = start_pos;

    size_c->size = 50.0f;

    const uint8_t random_choice = GetRandomValue(0, 4);
    switch (random_choice) {
    case 0:
        color_c->color = DARKBLUE;
        break;
    case 1:
        color_c->color = DARKBROWN;
        break;
    case 2:
        color_c->color = DARKGRAY;
        break;
    case 3:
        color_c->color = DARKGREEN;
        break;
    case 4:
        color_c->color = DARKPURPLE;
        break;
    }

    move_c->speed     = 100.0f;
    move_c->direction = (Vector2){0, 0};

    health_c->max_hp = 10;
    health_c->hp     = health_c->max_hp;

    damage_c->dmg = GetRandomValue(1, 3);

    target_c->pos        = target_pos;
    target_c->track_once = false;

    return id;
}

uint32_t create_bullet(World *world, const Vector2 start_pos,
                       const Vector2 *target_pos)
{
    assert(world);

    const uint32_t id = create_entity(world);

    world->mask_list[id] = TAG_BULLET | COMP_POSITION | COMP_RADIUS |
                           COMP_COLOR | COMP_MOVE | COMP_DAMAGE |
                           COMP_LIFETIME | COMP_TARGET;

    PositionComponent *position_c = &world->position_list[id];
    RadiusComponent *radius_c     = &world->radius_list[id];
    ColorComponent *color_c       = &world->color_list[id];
    MoveComponent *move_c         = &world->move_list[id];
    DamageComponent *damage_c     = &world->damage_list[id];
    LifetimeComponent *lifetime_c = &world->lifetime_list[id];
    TargetComponent *target_c     = &world->target_list[id];

    position_c->pos = start_pos;

    radius_c->radius = 2.0f;

    color_c->color = RED;

    move_c->speed     = 300.0f;
    move_c->direction = (Vector2){0, 0};

    damage_c->dmg = 1;

    lifetime_c->life = BULLET_MAX_LIFETIME;

    target_c->pos        = target_pos;
    target_c->track_once = true;

    return id;
}
