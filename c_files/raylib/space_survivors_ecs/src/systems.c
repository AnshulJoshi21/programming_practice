#include "../include/systems.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

void system_draw(const World *world, const Texture2D spritesheet)
{
    assert(world);

    const int target_mask = COMP_TRANSFORM | COMP_SPRITE;

    for (int id = 0; id < world->enttity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            const Rectangle source = get_source_rect(world, id);
            const Rectangle dest   = get_dest_rect(world, id);
            const Vector2 origin   = get_origin_vector(world, id);

            const TransformComponent *transform = &world->transform_list[id];
            const SpriteComponent *sprite       = &world->sprite_list[id];

            DrawTexturePro(spritesheet, source, dest, origin,
                           transform->rotation, sprite->tint);
        }
    }
}

void system_handle_input(World *world)
{
    assert(world);

    for (int id = 0; id < world->enttity_count; id++) {

        if ((world->mask_list[id] & TAG_PLAYER) == TAG_PLAYER) {

            MoveComponent *move = &world->move_list[id];

            move->direction.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
            move->direction.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);

            move->direction = Vector2Normalize(move->direction);
        }
    }
}

void system_set_direction(World *world)
{
    assert(world);

    const int target_mask = COMP_TRANSFORM | COMP_MOVE | COMP_TARGET;

    for (int id = 0; id < world->enttity_count; id++) {

        if ((world->mask_list[id] & TAG_PLAYER) == TAG_PLAYER)
            continue;

        if ((world->mask_list[id] & target_mask) == target_mask) {

            TransformComponent *transform = &world->transform_list[id];
            MoveComponent *move           = &world->move_list[id];
            TargetComponent *target       = &world->target_list[id];

            const float dx       = target->pos->x - transform->pos.x;
            const float dy       = target->pos->y - transform->pos.y;
            const float distance = sqrtf(dx * dx + dy * dy);
            if (distance > 0) {
                move->direction = (Vector2){dx / distance, dy / distance};
            }

            if (!target->continous_update)
                world->mask_list[id] &= ~COMP_TARGET;
        }
    }
}

void system_rotate(World *world)
{
    assert(world);

    const int target_mask = COMP_TRANSFORM | COMP_TARGET;

    for (int id = 0; id < world->enttity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            TransformComponent *transform = &world->transform_list[id];
            TargetComponent *target       = &world->target_list[id];

            const float dx      = target->pos->x - transform->pos.x;
            const float dy      = target->pos->y - transform->pos.y;
            transform->rotation = atan2f(dy, dx) * RAD2DEG + ROTATION_OFFSET;

            if (!target->continous_update)
                world->mask_list[id] &= ~COMP_TARGET;
        }
    }
}

void system_move(World *world, const float dt)
{
    assert(world);

    const int target_mask = COMP_TRANSFORM | COMP_MOVE;

    for (int id = 0; id < world->enttity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            TransformComponent *transform = &world->transform_list[id];
            MoveComponent *move           = &world->move_list[id];

            transform->pos.x += move->direction.x * move->speed * dt;
            transform->pos.y += move->direction.y * move->speed * dt;
        }
    }
}

void system_set_bounds(World *world)
{
    assert(world);

    for (int id = 0; id < world->enttity_count; id++) {
        TransformComponent *transform = &world->transform_list[id];

        const Rectangle dest = get_dest_rect(world, id);

        const float half_w = dest.width / 2.0f;
        const float half_h = dest.height / 2.0f;

        transform->pos.x =
            fmaxf(half_w, fminf(transform->pos.x, MAP_SIZE - half_w));
        transform->pos.y =
            fmaxf(half_h, fminf(transform->pos.y, MAP_SIZE - half_h));
    }
}
