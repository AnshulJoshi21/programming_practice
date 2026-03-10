#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Particle Emitter";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const int MAX_PARTICLES    = 200;
static const int MAX_LIFETIME     = 1.0f;
static const float SPAWN_INTERVAL = 0.005f;

static inline float random_uniform(float min, float max)
{
    return min + (rand() / (float)RAND_MAX) * (max - min);
}

typedef struct Particle
{
    float radius;
    Vector2 center;
    float speed;
    Vector2 velocity;
    Color color;
    float lifetime;
    bool active;

} Particle;

static void particle_init(Particle *particle)
{
    assert(particle);

    particle->radius    = random_uniform(1, 4);
    particle->center    = GetMousePosition();
    float speed         = random_uniform(100, 300);
    float angle_radians = random_uniform(0, 2 * PI);
    particle->velocity =
        (Vector2){cosf(angle_radians) * speed, sinf(angle_radians) * speed};
    particle->color    = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255),
                                 GetRandomValue(0, 255), 255};
    particle->lifetime = 0.0f;
    particle->active   = true;
}

static void particle_draw(const Particle *particle)
{
    assert(particle);

    if (particle->active) {
        DrawCircleV(particle->center, particle->radius, particle->color);
    }
}

static void particle_update(Particle *particle, float dt)
{
    assert(particle);

    if (particle->lifetime >= MAX_LIFETIME) {
        particle->active = false;
    }

    if (particle->active) {
        particle->lifetime += dt;

        particle->center.x += particle->velocity.x * dt;
        particle->center.y += particle->velocity.y * dt;
    }
}

int main(void)
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    Particle particles[MAX_PARTICLES];
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particle_init(&particles[i]);
    }

    float last_spawn_time = GetTime();

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        float current_time = GetTime();
        if (current_time - last_spawn_time >= SPAWN_INTERVAL) {
            last_spawn_time = current_time;

            for (int i = 0; i < MAX_PARTICLES; i++) {
                if (particles[i].active)
                    continue;

                particle_init(&particles[i]);
                break;
            }
        }

        for (int i = 0; i < MAX_PARTICLES; i++) {
            particle_update(&particles[i], dt);
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        for (int i = 0; i < MAX_PARTICLES; i++) {
            particle_draw(&particles[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
