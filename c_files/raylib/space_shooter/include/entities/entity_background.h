#ifndef ENTITY_BACKGROUND_H
#define ENTITY_BACKGROUND_H

#include "../components.h"

typedef struct Background
{
    TransformComponent transform;
    RenderComponent render;

} Background;

void background_init(Background *background,
                     const Texture2D background_texture);
void background_draw(const Background *background);

#endif // ENTITY_BACKGROUND_H
