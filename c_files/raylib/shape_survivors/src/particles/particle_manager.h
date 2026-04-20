#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "particle.h"

#include "../components.h"

#define MAX_PARTICLES 1000

typedef struct ParticleManager {
    Particle particles[MAX_PARTICLES];

    SpawnerComponent spawner;

} ParticleManager;

void particle_manager_init(ParticleManager* em);
void particle_manager_draw(const ParticleManager* em);
void particle_manager_update(ParticleManager* bm, const float dt);

void particle_manager_spawn(ParticleManager* pm, const ParticleType type, const Vector2 start_pos);
void particle_manager_despawn(ParticleManager* bm, const int index);

#endif  // PARTICLE_MANAGER_H
