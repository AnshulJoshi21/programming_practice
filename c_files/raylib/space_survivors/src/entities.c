#include "../include/components.h"
#include "../include/entities.h"
#include "../include/settings.h"

#include <assert.h>

uint32_t create_player(World *world)
{
    assert(world);

    const uint32_t id = create_entity(world);

    world->mask_list[id] = TAG_PLAYER | COMP_TRANSFORM | COMP_ANIMATION |
                           COMP_COLOR | COMP_MOVE | COMP_HEALTH | COMP_TARGET;

    TransformComponent *transform = &world->transform_list[id];
    AnimationComponent *animation = &world->animation_list[id];
    ColorComponent *color         = &world->color_list[id];
    MoveComponent *move           = &world->move_list[id];
    HealthComponent *health       = &world->health_list[id];
    TargetComponent *target       = &world->target_list[id];

    transform->pos      = (Vector2){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f};
    transform->scale    = (Vector2){PLAYER_SCALE, PLAYER_SCALE};
    transform->rotation = ROTATION_OFFSET;

    animation->current_sprite = SPRITE_PLAYERSHIP1_BLUE;

    color->tint = WHITE;

    move->speed     = 200.0f;
    move->direction = (Vector2){0, 0};

    health->max_hp = 100;
    health->hp     = health->max_hp;

    target->pos        = &(Vector2){0, 0};
    target->track_once = false;

    return id;
}
