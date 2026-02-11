#include "../../include/systems/system_render.h"

#include <assert.h>
#include <raymath.h>

void system_render(const TransformComponent *t, const RenderComponent *r)
{
    assert(t && r);

    Rectangle dest =
        (Rectangle){t->position.x, t->position.y, r->source.width * t->scale.x,
                    r->source.height * t->scale.y};

    DrawTexturePro(r->texture, r->source, dest, r->origin, t->rotation,
                   r->tint);
}
