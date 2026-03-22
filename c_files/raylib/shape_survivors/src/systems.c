#include "../include/systems.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

void system_despawner(World *world, uint32_t *count)
{
    assert(world && count);

    for (uint32_t id = 0; id < world->entity_count; id++) {

        bool despawn = false;

        if (world->mask_list[id] & COMP_HEALTH) {

            const HealthComponent *health_c = &world->health_list[id];

            if (health_c->hp <= 0) {
                despawn = true;
            }

        } else if (world->mask_list[id] & COMP_LIFETIME) {

            const LifetimeComponent *lifetime_c = &world->lifetime_list[id];

            if (lifetime_c->life <= 0) {
                despawn = true;
            }
        }

        if (despawn) {
            delete_entity(world, id);
            *count -= 1;
            id--;
        }
    }
}

void system_draw(const World *world)
{
    assert(world);

    uint32_t target_mask_rect = COMP_POSITION | COMP_SIZE | COMP_COLOR;

    uint32_t target_mask_circle = COMP_POSITION | COMP_RADIUS | COMP_COLOR;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & target_mask_rect) == target_mask_rect) {

            const PositionComponent *position_c = &world->position_list[id];
            const SizeComponent *size_c         = &world->size_list[id];
            const ColorComponent *color_c       = &world->color_list[id];

            const Rectangle rect =
                (Rectangle){position_c->pos.x, position_c->pos.y, size_c->size,
                            size_c->size};

            DrawRectangleRec(rect, color_c->color);

            if ((world->mask_list[id] & TAG_PLAYER) == TAG_PLAYER)
                utils_center_and_draw_text("P", rect, 20, WHITE);

            if ((world->mask_list[id] & TAG_ENEMY) == TAG_ENEMY)
                utils_center_and_draw_text("E", rect, 20, WHITE);

        } else if ((world->mask_list[id] & target_mask_circle) ==
                   target_mask_circle) {

            const PositionComponent *position_c = &world->position_list[id];
            const RadiusComponent *radius_c     = &world->radius_list[id];
            const ColorComponent *color_c       = &world->color_list[id];

            DrawCircleV((Vector2){position_c->pos.x, position_c->pos.y},
                        radius_c->radius, color_c->color);
        }
    }
}

void system_handle_input(World *world)
{
    assert(world);

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & TAG_PLAYER) == TAG_PLAYER) {

            MoveComponent *move_c = &world->move_list[id];

            move_c->direction.x =
                (int)IsKeyDown((KEY_D)) - (int)IsKeyDown(KEY_A);
            move_c->direction.y =
                (int)IsKeyDown((KEY_S)) - (int)IsKeyDown(KEY_W);

            move_c->direction = Vector2Normalize(move_c->direction);
        }
    }
}

void system_set_direction(World *world)
{
    assert(world);

    const uint32_t target_mask = COMP_POSITION | COMP_MOVE | COMP_TARGET;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if (world->mask_list[id] & TAG_PLAYER)
            continue;

        if ((world->mask_list[id] & target_mask) == target_mask) {

            PositionComponent *position_c = &world->position_list[id];
            MoveComponent *move_c         = &world->move_list[id];
            TargetComponent *target_c     = &world->target_list[id];

            const float dx       = target_c->pos->x - position_c->pos.x;
            const float dy       = target_c->pos->y - position_c->pos.y;
            const float distance = sqrtf(dx * dx + dy * dy);
            if (distance > 0) {
                move_c->direction = (Vector2){dx / distance, dy / distance};
            }

            if (target_c->track_once)
                world->mask_list[id] &= ~COMP_TARGET;
        }
    }
}

void system_move(World *world, const float dt)
{
    assert(world);

    const uint32_t target_mask = COMP_POSITION | COMP_MOVE;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            PositionComponent *position_c = &world->position_list[id];
            MoveComponent *move_c         = &world->move_list[id];

            position_c->pos.x += move_c->direction.x * move_c->speed * dt;
            position_c->pos.y += move_c->direction.y * move_c->speed * dt;
        }
    }
}

void system_set_bounds(World *world)
{
    assert(world);

    const uint32_t target_mask = COMP_POSITION | COMP_SIZE;

    for (uint32_t id = 0; id < world->entity_count; id++) {

        if ((world->mask_list[id] & target_mask) == target_mask) {

            PositionComponent *position_c = &world->position_list[id];
            SizeComponent *size_c         = &world->size_list[id];

            position_c->pos.x =
                fmaxf(0.0f, fminf(position_c->pos.x, MAP_SIZE - size_c->size));
            position_c->pos.y =
                fmaxf(0.0f, fminf(position_c->pos.y, MAP_SIZE - size_c->size));
        }
    }
}
