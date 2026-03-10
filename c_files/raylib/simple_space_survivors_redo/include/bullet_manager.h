#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#define MAX_BULLETS 50

#include "sprite_data.h"

#include <raylib.h>

typedef struct Bullet
{
    SpriteData sprite_name;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;

    float speed;
    Vector2 direction;
    float damage;

    float lifetime;

} Bullet;

void bullet_init(Bullet *bullet, const Vector2 start_pos,
                 const Vector2 target_pos);

typedef struct BulletManager
{

} BulletManager;

void bullet_manager_init(BulletManager *bullet_manager);
void bullet_manager_draw(const BulletManager *bullet_manager);
void bullet_manager_update(BulletManager *bullet_manager, const float dt);

#endif // BULLET_MANAGER_H
