#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <raylib.h>

typedef struct TransformComponent
{
    Vector2 position;
    float rotation;
    Vector2 scale;

} TransformComponent;

typedef struct RenderComponent
{
    Texture2D texture;
    Rectangle source;
    Vector2 origin;
    Color tint;

} RenderComponent;

typedef struct MovementComponent
{
    float speed;
    Vector2 move_direction;
    Vector2 look_direction;

} MovementComponent;

#endif // COMPONENTS_H
