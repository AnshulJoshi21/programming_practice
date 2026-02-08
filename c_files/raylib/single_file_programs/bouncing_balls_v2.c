#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 600;

static const int MAX_BALLS = 200;

#define RANDOM_UNIFORM(min, max)                                               \
    ((min) + ((float)rand() / RAND_MAX * ((max) - (min))))

//-- BALL --------------------------------------//
typedef struct Ball
{
    Vector2 center;
    float radius;
    Vector2 velocity;
    Color color;

} Ball;

static void ball_init(Ball *ball)
{
    assert(ball);

    ball->radius = RANDOM_UNIFORM(5, 30);
    ball->center = (Vector2){
        RANDOM_UNIFORM(ball->radius, SCREEN_WIDTH - ball->radius),
        RANDOM_UNIFORM(ball->radius, SCREEN_HEIGHT - ball->radius),
    };
    float speed         = RANDOM_UNIFORM(100, 300);
    float angle_radians = RANDOM_UNIFORM(0, 2 * PI);
    ball->velocity      = (Vector2){
        cosf(angle_radians) * speed,
        sinf(angle_radians) * speed,
    };
    ball->color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255),
                          GetRandomValue(0, 255), 255};
}

static void ball_draw(const Ball *ball)
{
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball *ball, float delta_time)
{
    assert(ball);

    // move
    ball->center.x += ball->velocity.x * delta_time;
    ball->center.y += ball->velocity.y * delta_time;

    // bounds
    if (ball->center.x < ball->radius ||
        ball->center.x > SCREEN_WIDTH - ball->radius) {
        ball->velocity.x *= -1;
    }
    if (ball->center.y < ball->radius ||
        ball->center.y > SCREEN_HEIGHT - ball->radius) {
        ball->velocity.y *= -1;
    }
}

//-- MAIN --------------------------------------//
int main(void)
{
    srand(time(NULL));

    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncing Balls V2");

    Ball balls[MAX_BALLS];

    for (int i = 0; i < MAX_BALLS; i++) {
        ball_init(&balls[i]);
    }

    while (!WindowShouldClose()) {
        // 2.UPDATE
        float delta_time = GetFrameTime();

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_update(&balls[i], delta_time);
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_draw(&balls[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
