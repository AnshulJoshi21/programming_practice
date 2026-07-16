#include "animation_data.h"
#include "systems.h"
#include "utils.h"
#include <assert.h>
#include <raymath.h>
#include <stdlib.h>

// LEVEL + EXP
int system_get_xp_next(const CLevel* level) {
    assert(level);

    return 10 + ((level->current * level->current) * 2);
}

// RENDER
void system_render_texture(const CTransform* transform, const CRender* render) {
    assert(transform);
    assert(render);

    const Rectangle dest
        = (Rectangle){transform->pos.x, transform->pos.y, render->size.x, render->size.y};
    DrawTexturePro(
        render->texture, render->source, dest, render->origin, transform->rotation, render->tint);
}

// MOVEMENT
void system_set_direction(const CTransform* transform,
                          CMovement*        movement,
                          const Vector2     target_pos) {
    assert(transform);
    assert(movement);

    const float dx       = target_pos.x - transform->pos.x;
    const float dy       = target_pos.y - transform->pos.y;
    const float distance = sqrtf((dx * dx) + (dy * dy));
    if (distance > 0) {
        movement->direction = (Vector2){dx / distance, dy / distance};
    }
}

void system_move_x(CTransform* transform, const CMovement* movement, const float dt) {
    assert(transform);
    assert(movement);

    transform->pos.x += movement->direction.x * movement->speed_x * dt;
    transform->pos.y += movement->direction.y * movement->speed_x * dt;
}

void system_set_bounds(CTransform* transform, CRender* render, const Rectangle bounds) {
    assert(transform);
    assert(render);

    transform->pos.x = Clamp(
        transform->pos.x, bounds.x + render->size.x / 2.0f, bounds.width - render->size.x / 2.0f);
    transform->pos.y = Clamp(
        transform->pos.y, bounds.y + render->size.y / 2.0f, bounds.height - render->size.y / 2.0f);
}

// UPDATE
void system_update_xp(CLevel* level, CXp* xp) {
    assert(level);
    assert(xp);

    if (xp->current >= xp->next) {
        xp->current -= xp->next;
        level->current++;
        xp->pending_levelups++;

        xp->next = system_get_xp_next(level);
    }
}

void system_update_lifetime(CLifetime* lifetime, const float dt) {
    assert(lifetime);

    lifetime->current -= dt;
    if (lifetime->current <= 0) {
        lifetime->current = 0;
    }
}

void system_update_health(CHealth* health) {
    assert(health);

    health->current = utils_max_int(0, utils_min_int(health->current, health->max));
}

bool system_timer_tick(CTimer* timer) {
    assert(timer);

    const float current_time = GetTime();
    if (current_time - timer->elapsed >= timer->interval) {
        timer->elapsed = current_time;
        return true;
    }
    return false;
}

void system_animate(const Entity entity, CAnimation* animation, const float dt) {
    assert(animation);

    if (animation->is_finished)
        return;

    const AnimationConfig* config = NULL;

    switch (entity) {
        case ENTITY_WARRIOR:
            config = &warrior_animation_configs[animation->type];
            break;
    }

    const float frame_time = config->duration / config->count;

    animation->timer += dt;
    if (animation->timer >= frame_time) {
        animation->current++;
        animation->timer -= frame_time;

        if (animation->current >= config->count) {
            if (config->loops) {
                animation->current = 0;
            } else {
                animation->current     = config->count - 1;
                animation->is_finished = true;
                return;
            }
        }
    }
}

void system_update_dimenions(const Entity      entity,
                             const CTransform* transform,
                             CRender*          render,
                             const CAnimation* animation) {
    assert(transform);
    assert(render);
    assert(animation);

    const AnimationConfig* config = NULL;

    switch (entity) {
        case ENTITY_WARRIOR:
            config = &warrior_animation_configs[animation->type];
            break;
    }

    render->source = config->frames[animation->current];
    render->size   = (Vector2){render->source.width * transform->scale.x,
                               render->source.height * transform->scale.y};
    render->origin = (Vector2){render->size.x / 2.0f, render->size.y / 2.0f};
}
