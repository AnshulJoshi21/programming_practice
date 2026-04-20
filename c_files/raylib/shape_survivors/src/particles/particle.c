#include "particle.h"

#include "../systems.h"
#include "../utils.h"

#include <assert.h>
#include <math.h>

void particle_init(Particle *particle, const ParticleType type, const Vector2 start_pos) {
    assert(particle);

    particle->particle.type = type;

    particle->position.x = start_pos.x;
    particle->position.y = start_pos.y;

    const float random_angle = random_float(0, 2 * PI);

    if (type == PARTICLE_SMOKE) {
        particle->circle.radius = random_float(1, 3);

        particle->color.tint = (Color){255, (unsigned char) GetRandomValue(150, 220), 0, 255};

        particle->move.speed = random_float(200, 600);

        particle->move.direction = (Vector2){cosf(random_angle), sinf(random_angle)};

        particle->lifetime.max = random_float(0.5f, 0.8f);
        particle->lifetime.remaining = particle->lifetime.max;

    } else if (type == PARTICLE_SPARK) {
        particle->circle.radius = random_float(6, 12);

        particle->color.tint = (Color){100, 100, 100, 200};

        particle->move.speed = random_float(50, 150);

        particle->move.direction =
            (Vector2){cosf(random_angle),
                      sinf(random_angle) - random_float(0.2f, 0.8f)};  // slight upward drift

        particle->lifetime.max = random_float(0.6f, 1.2f);
        particle->lifetime.remaining = particle->lifetime.max;
    }
}

void particle_draw(const Particle *particle) {
    assert(particle);

    int temp = 255;
    if (particle->particle.type == PARTICLE_SPARK) {
        BeginBlendMode(BLEND_ADDITIVE);
        temp = 255;
    } else if (particle->particle.type == PARTICLE_SMOKE) {
        temp = 180;
    }

    const float lifeRatio = particle->lifetime.remaining / particle->lifetime.max;

    Color tint = particle->color.tint;
    tint.a = (unsigned char) (temp * lifeRatio);

    DrawCircleV((Vector2){particle->position.x, particle->position.y}, particle->circle.radius,
                tint);

    if (particle->particle.type == PARTICLE_SPARK) {
        EndBlendMode();
    }
}

void particle_update(Particle *particle, const float dt) {
    assert(particle);

    if (particle->particle.type == PARTICLE_SPARK) {
        // drag
        particle->move.direction.x *= 0.92f;
        particle->move.direction.y *= 0.92f;

        // shrink
        particle->circle.radius *= 0.96f;

    } else if (particle->particle.type == PARTICLE_SMOKE) {
        // slow drift
        particle->move.direction.x *= 0.98f;
        particle->move.direction.y *= 0.98f;

        // expand smoke
        particle->circle.radius *= 1.01f;
    }

    system_move(&particle->position, &particle->move, dt);
    system_update_lifetime(&particle->lifetime, dt);
}
