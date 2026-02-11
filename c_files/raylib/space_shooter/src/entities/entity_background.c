#include "../../include/entities/entity_background.h"
#include "../../include/systems/system_render.h"

#include <assert.h>

void background_init(Background *background, const Texture2D background_texture)
{
    assert(background);

    background->transform.position = (Vector2){0, 0};
    background->transform.rotation = 0.0f;
    background->transform.scale    = (Vector2){1, 1};

    background->render.texture = background_texture;
    background->render.source =
        (Rectangle){0, 0, background_texture.width, background_texture.height};
    background->render.origin = (Vector2){0, 0};
    background->render.tint   = WHITE;
}

void background_draw(const Background *background)
{
    assert(background);

    system_render(&background->transform, &background->render);
}
