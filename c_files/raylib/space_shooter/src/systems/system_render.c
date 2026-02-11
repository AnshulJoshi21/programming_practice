#include "../../include/systems/system_render.h"

#include <assert.h>
#include <raymath.h>

Rectangle system_get_dest_rect(const TransformComponent *t,
                               const RenderComponent *r)
{
    assert(t && r);

    return (Rectangle){t->position.x, t->position.y,
                       r->source.width * t->scale.x,
                       r->source.height * t->scale.y};
}

void system_render_texture(const TransformComponent *t,
                           const RenderComponent *r)
{
    assert(t && r);

    Rectangle dest = system_get_dest_rect(t, r);

    DrawTexturePro(r->texture, r->source, dest, r->origin, t->rotation,
                   r->tint);
}
