#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Array Pooling Test";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const int MAX_BALLS      = 200;
static const float MAX_LIFETIME = 0.8f;

static float random_uniform(float min, float max)
{
    return (min + (rand() / (float)RAND_MAX) * (max - min));
}

typedef struct Ball
{
    Vector2 center;
    float radius;
    Vector2 velocity;
    Color color;
    float lifetime;
    bool active;

} Ball;

static void ball_reset(Ball *ball)
{
    assert(ball);

    ball->center = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    float speed  = 300.0f;
    float angle_radians = random_uniform(0, 2 * PI);
    ball->velocity      = (Vector2){
        cosf(angle_radians) * speed,
        sinf(angle_radians) * speed,
    };
    ball->lifetime = 0.0f;
    ball->active   = false;
}

static void ball_init(Ball *ball)
{
    assert(ball);

    ball->radius = 10.0f;
    ball->color  = RED;

    ball_reset(ball);
}

static void ball_draw(const Ball *ball)
{
    assert(ball);

    if (ball->active) {
        DrawCircleV(ball->center, ball->radius, ball->color);
    }
}

static void ball_update(Ball *ball, float dt)
{
    assert(ball);

    if (ball->active) {

        // move
        ball->center.x += ball->velocity.x * dt;
        ball->center.y += ball->velocity.y * dt;

        // update lifetime
        ball->lifetime += dt;
    }

    if (ball->lifetime >= MAX_LIFETIME) {
        //
        ball_reset(ball);
    }
}

//-- MAIN ---------------------------------------//
int main(void)
{
    srand(time(NULL));

    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(60);

    float spawn_interval = 0.09f;
    float last_time      = GetTime();
    float current_time   = GetTime();

    Ball balls[MAX_BALLS];

    for (int i = 0; i < MAX_BALLS; i++) {
        ball_init(&balls[i]);
    }

    while (!WindowShouldClose()) {
        // 2.UPDATE
        float dt = GetFrameTime();

        for (int i = 0; i < MAX_BALLS; i++) {
            if (balls[i].active)
                continue;

            current_time = GetTime();
            if (current_time - last_time >= spawn_interval) {
                last_time       = current_time;
                balls[i].active = true;
            }
        }

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_update(&balls[i], dt);
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_draw(&balls[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
