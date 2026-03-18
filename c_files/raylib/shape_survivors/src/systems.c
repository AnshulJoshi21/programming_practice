#include "../include/settings.h"
#include "../include/systems.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>
#include <raymath.h>

void system_draw(const World *world)
{
    assert(world);

    const int target_mask = COMP_POSITION | COMP_COLOR | COMP_ANIMATION;

    for (int i = 0; i < world->entity_count; i++) {
        if ((world->mask_list[i] & target_mask) == target_mask) {
            const PositionComponent *p  = &world->pos_list[i];
            const ColorComponent *c     = &world->color_list[i];
            const AnimationComponent *a = &world->animation_list[i];

            Vector2 origin;
            float rotation;
            const char *text;
            float half_size;

            if (world->mask_list[i] & TAG_PLAYER) {
                origin    = (Vector2){PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f};
                rotation  = PLAYER_ROTATION;
                text      = "P";
                half_size = PLAYER_SIZE / 2.0f;
            }

            if (world->mask_list[i] & TAG_ENEMY) {
                origin    = (Vector2){ENEMY_SIZE / 2.0f, ENEMY_SIZE / 2.0f};
                rotation  = ENEMY_ROTATION;
                text      = "E";
                half_size = ENEMY_SIZE / 2.0f;
            }

            const Color color = (a->hit_timer > 0.0f) ? HIT_COLOR : c->color;

            DrawRectanglePro(
                (Rectangle){p->pos.x, p->pos.y, PLAYER_SIZE, PLAYER_SIZE},
                origin, rotation, color);

            const Rectangle layout_rect =
                (Rectangle){p->pos.x - half_size, p->pos.y - half_size,
                            half_size * 2, half_size * 2};

            center_and_draw_text(text, layout_rect, 20.0f, 0.0f, WHITE);
        }
    }
}

void system_handle_update(World *world)
{
    assert(world);

    for (int i = 0; i < world->entity_count; i++) {
        if ((world->mask_list[i] & TAG_PLAYER) == TAG_PLAYER) {
            MoveComponent *m = &world->move_list[i];

            m->direction.x = (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
            m->direction.y = (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);

            m->direction = Vector2Normalize(m->direction);
        }
    }
}

void system_move(World *world, const float dt)
{
    assert(world);

    int target_mask = COMP_POSITION | COMP_MOVE;

    for (int i = 0; i < world->entity_count; i++) {
        if ((world->mask_list[i] & target_mask) == target_mask) {
            PositionComponent *p = &world->pos_list[i];
            MoveComponent *m     = &world->move_list[i];

            p->pos.x += m->direction.x * m->speed * dt;
            p->pos.y += m->direction.y * m->speed * dt;
        }
    }
}

void system_set_bounds(World *world)
{
    assert(world);

    for (int i = 0; i < world->entity_count; i++) {
        if ((world->mask_list[i] & TAG_PLAYER) == TAG_PLAYER ||
            (world->mask_list[i] & TAG_ENEMY) == TAG_ENEMY) {
            PositionComponent *p = &world->pos_list[i];

            float half_size;

            if ((world->mask_list[i] & TAG_PLAYER) == TAG_PLAYER)
                half_size = PLAYER_SIZE / 2.0f;
            else
                half_size = ENEMY_SIZE / 2.0f;

            p->pos.x = fmaxf(half_size, fminf(p->pos.x, MAP_SIZE - half_size));
            p->pos.y = fmaxf(half_size, fminf(p->pos.y, MAP_SIZE - half_size));
        }
    }
}
