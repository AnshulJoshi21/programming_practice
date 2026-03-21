#include "../include/sprite_data.h"
#include "../include/systems.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

void system_draw(const World *world, const Texture2D spritesheet)
{
    assert(world);

    const uint32_t target_mask = COMP_TRANSFORM | COMP_COLOR | COMP_ANIMATION;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            const TransformComponent *transform = &world->transform_list[id];
            const ColorComponent *color         = &world->color_list[id];
            const AnimationComponent *animation = &world->animation_list[id];

            const Rectangle source = sprite_db[animation->current_sprite];
            const Rectangle dest =
                utils_get_dest_rect(transform->pos, transform->scale, source);
            const Vector2 origin =
                (Vector2){dest.width / 2.0f, dest.height / 2.0f};

            DrawTexturePro(spritesheet, source, dest, origin,
                           transform->rotation, color->tint);
        }
    }
}

void system_handle_input(World *world)
{
    assert(world);

    for (uint32_t id = 0; id < world->entity_count; id++) {

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

    uint32_t target_mask = COMP_TRANSFORM | COMP_MOVE | COMP_TARGET;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if (world->mask_list[id] & TAG_PLAYER)
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

            if (target->track_once)
                world->mask_list[id] &= ~COMP_TARGET;
        }
    }
}

void system_rotate(World *world)
{
    assert(world);

    const uint32_t target_mask = COMP_TRANSFORM | COMP_TARGET;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            TransformComponent *transform = &world->transform_list[id];
            const TargetComponent *target = &world->target_list[id];

            const float dx = target->pos->x - transform->pos.x;
            const float dy = target->pos->y - transform->pos.y;

            transform->rotation = atan2f(dy, dx) * RAD2DEG + ROTATION_OFFSET;

            if (target->track_once)
                world->mask_list[id] &= ~COMP_TARGET;
        }
    }
}

void system_move(World *world, const float dt)
{
    assert(world);

    const uint32_t target_mask = COMP_TRANSFORM | COMP_MOVE;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            TransformComponent *transform = &world->transform_list[id];
            const MoveComponent *move     = &world->move_list[id];

            transform->pos.x += move->direction.x * move->speed * dt;
            transform->pos.y += move->direction.y * move->speed * dt;
        }
    }
}

void system_set_bounds(World *world)
{
    assert(world);

    const uint32_t target_mask = COMP_TRANSFORM | COMP_ANIMATION;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            TransformComponent *transform = &world->transform_list[id];
            AnimationComponent *animation = &world->animation_list[id];

            const Rectangle source = sprite_db[animation->current_sprite];
            const Rectangle dest =
                utils_get_dest_rect(transform->pos, transform->scale, source);

            const float half_w = dest.width / 2.0f;
            const float half_h = dest.height / 2.0f;

            transform->pos.x =
                fmaxf(half_w, fminf(transform->pos.x, MAP_SIZE - half_w));
            transform->pos.y =
                fmaxf(half_h, fminf(transform->pos.y, MAP_SIZE - half_h));
        }
    }
}
