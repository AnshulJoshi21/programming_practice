#include "../include/entities.h"
#include "../include/settings.h"
#include "../include/sprite_data.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>

int create_player(World *world)
{
    assert(world);

    const int id = create_entity(world);

    world->mask_list[id] = TAG_PLAYER | COMP_TRANSFORM | COMP_SPRITE |
                           COMP_MOVE | COMP_HEALTH | COMP_TARGET;

    TransformComponent *transform = &world->transform_list[id];
    SpriteComponent *sprite       = &world->sprite_list[id];
    MoveComponent *move           = &world->move_list[id];
    HealthComponent *health       = &world->health_list[id];

    transform->pos      = (Vector2){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f};
    const float scale   = 0.5f;
    transform->scale    = (Vector2){scale, scale};
    transform->rotation = ROTATION_OFFSET;

    sprite->current_sprite = SPRITE_PLAYERSHIP1_BLUE;
    sprite->tint           = WHITE;

    move->direction = (Vector2){0, 0};
    move->speed     = 400.0f;

    health->max_hp = 100;
    health->hp     = health->max_hp;

    return id;
}

int create_enemy(World *world, Vector2 target_pos)
{
    assert(world);

    const int id = create_entity(world);

    world->mask_list[id] = COMP_TRANSFORM | COMP_SPRITE | COMP_MOVE |
                           COMP_HEALTH | COMP_DAMAGE | COMP_TARGET;

    TransformComponent *transform = &world->transform_list[id];
    SpriteComponent *sprite       = &world->sprite_list[id];
    MoveComponent *move           = &world->move_list[id];
    HealthComponent *health       = &world->health_list[id];
    DamageComponent *damage       = &world->damage_list[id];
    TargetComponent *target       = &world->target_list[id];

    const float random_angle = random_uniform(0, 2 * PI);
    const Vector2 start_pos =
        (Vector2){cosf(random_angle) * ENEMY_SPAWN_DISTANCE + target_pos.x,
                  sinf(random_angle) * ENEMY_SPAWN_DISTANCE + target_pos.y};

    transform->pos      = start_pos;
    const float scale   = 0.6f;
    transform->scale    = (Vector2){scale, scale};
    transform->rotation = ROTATION_OFFSET;

    sprite->current_sprite =
        GetRandomValue(SPRITE_ENEMYBLACK1, SPRITE_ENEMYRED5);
    sprite->tint = WHITE;

    // set direction using systems
    move->speed = 100.0f;

    health->max_hp = 10;
    health->hp     = health->max_hp;

    damage->damage = GetRandomValue(1, 3);

    target->pos              = &target_pos;
    target->continous_update = true;

    return id;
}

int create_laser(World *world, const Vector2 start_pos, Vector2 target_pos)
{
    assert(world);

    const int id = create_entity(world);

    world->mask_list[id] = COMP_TRANSFORM | COMP_SPRITE | COMP_MOVE |
                           COMP_HEALTH | COMP_DAMAGE | COMP_TARGET;

    TransformComponent *transform = &world->transform_list[id];
    SpriteComponent *sprite       = &world->sprite_list[id];
    MoveComponent *move           = &world->move_list[id];
    HealthComponent *health       = &world->health_list[id];
    DamageComponent *damage       = &world->damage_list[id];
    TargetComponent *target       = &world->target_list[id];

    transform->pos      = start_pos;
    const float scale   = 0.6f;
    transform->scale    = (Vector2){scale, scale};
    transform->rotation = ROTATION_OFFSET;

    sprite->current_sprite =
        GetRandomValue(SPRITE_ENEMYBLACK1, SPRITE_ENEMYRED5);
    sprite->tint = WHITE;

    // set direction using systems
    move->speed = 100.0f;

    health->max_hp = 10;
    health->hp     = health->max_hp;

    damage->damage = GetRandomValue(1, 3);

    target->pos              = &target_pos;
    target->continous_update = false;

    return id;
}
