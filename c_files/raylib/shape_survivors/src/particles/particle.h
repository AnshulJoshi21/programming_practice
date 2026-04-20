#ifndef PARTICLE_H
#define PARTICLE_H

#include "../components.h"

typedef enum ParticleType {
    PARTICLE_NONE = 0,
    PARTICLE_SPARK,
    PARTICLE_SMOKE,
    PARTICLE_MAX

} ParticleType;

typedef struct Particle {
    ParticleComponent particle;
    PositionComponent position;
    CircleComponent circle;
    ColorComponent color;
    MoveComponent move;
    LifetimeComponent lifetime;

} Particle;

void particle_init(Particle *particle, const ParticleType type, const Vector2 start_pos);
void particle_draw(const Particle *particle);
void particle_update(Particle *particle, const float dt);

#endif  // PARTICLE_H
