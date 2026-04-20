#include "particle_manager.h"

#include <assert.h>

void particle_manager_init(ParticleManager* pm) {
    assert(pm);

    pm->spawner.max = MAX_PARTICLES;
    pm->spawner.count = 0;
}

void particle_manager_draw(const ParticleManager* pm) {
    assert(pm);

    for (int i = 0; i < pm->spawner.count; i++) {
        particle_draw(&pm->particles[i]);
    }
}

void particle_manager_spawn(ParticleManager* pm, const ParticleType type, const Vector2 start_pos) {
    assert(pm);

    const int spawns = 50;
    if (pm->spawner.count < pm->spawner.max && pm->spawner.max - pm->spawner.count >= spawns) {
        for (int i = 0; i < spawns; i++) {
            //
            particle_init(&pm->particles[pm->spawner.count], type, start_pos);
            pm->spawner.count++;
        }
    }
}

void particle_manager_despawn(ParticleManager* pm, const int index) {
    assert(pm);
    assert(index >= 0 && index < pm->spawner.count);

    pm->particles[index] = pm->particles[pm->spawner.count - 1];
    pm->spawner.count--;
}

void particle_manager_update(ParticleManager* pm, const float dt) {
    assert(pm);

    // update
    for (int i = 0; i < pm->spawner.count; i++) {
        Particle* particle = &pm->particles[i];

        particle_update(particle, dt);

        if (particle->lifetime.remaining <= 0) {
            particle_manager_despawn(pm, i);
            i--;
        }
    }
}
