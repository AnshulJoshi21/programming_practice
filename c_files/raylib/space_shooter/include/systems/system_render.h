#ifndef SYSTEM_RENDER_H
#define SYSTEM_RENDER_H

#include "../components.h"

Rectangle system_get_dest_rect(const TransformComponent *t,
                               const RenderComponent *r);
void system_render_texture(const TransformComponent *t,
                           const RenderComponent *r);

#endif // SYSTEM_RENDER_H
