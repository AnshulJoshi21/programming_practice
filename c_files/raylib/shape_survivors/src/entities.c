#include "../include/entities.h"
#include "../include/settings.h"

#include <assert.h>

int create_player(World *world)
{
    assert(world);

    const int id = create_entity(world);

    world->mask_list[id] = TAG_PLAYER | COMP_POSITION | COMP_COLOR | COMP_MOVE |
                           COMP_HEALTH | COMP_ANIMATION;

    world->pos_list[id].pos     = (Vector2){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f};
    world->color_list[id].color = GRAY;
    world->move_list[id].speed  = 200.0f;
    world->move_list[id].direction      = (Vector2){0, 0};
    world->health_list[id].max_hp       = 100;
    world->health_list[id].hp           = world->health_list[id].max_hp;
    world->animation_list[id].hit_timer = 0.0f;

    return id;
}

int create_enemy(World *world)
{
    assert(world);

    const int id = create_entity(world);

    world->mask_list[id] = TAG_ENEMY | COMP_POSITION | COMP_COLOR | COMP_MOVE |
                           COMP_HEALTH | COMP_DAMAGE | COMP_ANIMATION;
    world->pos_list[id].pos             = (Vector2){0, 0};
    world->color_list[id].color         = DARKGRAY;
    world->move_list[id].speed          = 100.0f;
    world->move_list[id].direction      = (Vector2){0, 0};
    world->health_list[id].max_hp       = 10;
    world->health_list[id].hp           = world->health_list[id].max_hp;
    world->damage_list[id].damage       = 1;
    world->animation_list[id].hit_timer = 0.0f;

    return id;
}
