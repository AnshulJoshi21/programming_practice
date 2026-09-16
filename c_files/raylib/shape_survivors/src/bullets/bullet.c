#include "../settings.h"
#include "bullet.h"
#include <assert.h>
#include <math.h>

void bullet_init(Bullet* bullet, const BulletInitConfig config) {
    assert(bullet);

    bullet->behaviour = config.behaviour;
    bullet->type      = config.type;

    const BulletData* data = &bullet_db[config.behaviour][config.type];
    bullet->radius         = data->base_radius;
    bullet->color          = palette.dark;
    bullet->damage         = data->base_damage;
    bullet->lifetime       = data->base_lifetime;

    switch (config.behaviour) {
        case BULLET_BEHAVIOUR_PROJECTILE: {
            Projectile*           projectile = &bullet->bullet.projectile;
            const ProjectileData* pdata      = &data->bullet.projectile;

            projectile->target_pos = config.bullet.projectile.target_pos;
            projectile->center     = config.bullet.projectile.start_pos;
            projectile->speed      = pdata->base_speed;
            projectile->direction  = (Vector2){0, 0};

            const float dx       = projectile->target_pos->x - projectile->center.x;
            const float dy       = projectile->target_pos->y - projectile->center.y;
            const float distance = sqrtf((dx * dx) + (dy * dy));
            if (distance > 0) {
                projectile->direction = (Vector2){dx / distance, dy / distance};
            }
        } break;

        case BULLET_BEHAVIOUR_ORBITAL: {
            Orbital*           orbital = &bullet->bullet.orbital;
            const OrbitalData* odata   = &data->bullet.orbital;

            orbital->player         = config.bullet.orbital.player;
            orbital->orbital_angle  = 0.0f;
            orbital->orbital_count  = odata->base_orbital_count;
            orbital->orbital_radius = odata->base_orbital_radius;
            orbital->orbital_speed  = odata->base_orbital_speed;
        } break;

        default:
            return;
    }
}

void bullet_update(Bullet* bullet, const float dt) {
    assert(bullet);

    switch (bullet->behaviour) {
        case BULLET_BEHAVIOUR_PROJECTILE: {
            Projectile* projectile = &bullet->bullet.projectile;

            // move
            projectile->center.x += projectile->direction.x * projectile->speed * dt;
            projectile->center.y += projectile->direction.y * projectile->speed * dt;

        } break;

        case BULLET_BEHAVIOUR_ORBITAL: {
            Orbital* orbital = &bullet->bullet.orbital;

            orbital->orbital_angle += orbital->orbital_speed * dt;
            if (orbital->orbital_angle == (2 * PI)) orbital->orbital_angle = 0.0f;

            const float angle_step = (2 * PI) / orbital->orbital_count;

            for (int i = 0; i < orbital->orbital_count; i++) {
                const float   angle  = i * angle_step + orbital->orbital_angle;
                const Vector2 center = (Vector2){
                    cosf(angle) * orbital->orbital_radius + orbital->player->rect.x,
                    sinf(angle) * orbital->orbital_radius + orbital->player->rect.y,
                };

                orbital->centers[i] = center;
            }

        } break;

        default:
            return;
    }

    // update lifetime
    if (bullet->lifetime > 0) {
        bullet->lifetime -= dt;
        if (bullet->lifetime <= 0.0f) {
            bullet->lifetime = 0.0f;
        }
    }
}

void bullet_draw(const Bullet* bullet) {
    assert(bullet);

    switch (bullet->behaviour) {
        case BULLET_BEHAVIOUR_PROJECTILE: {
            const Projectile* projectile = &bullet->bullet.projectile;

            DrawCircleV(projectile->center, bullet->radius, bullet->color);
        } break;

        case BULLET_BEHAVIOUR_ORBITAL: {
            const Orbital* orbital = &bullet->bullet.orbital;

            for (int i = 0; i < orbital->orbital_count; i++) {
                const Vector2 center = orbital->centers[i];

                DrawCircleV(center, bullet->radius, bullet->color);
            }

        } break;

        default:
            return;
    }
}
