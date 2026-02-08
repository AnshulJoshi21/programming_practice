#include <assert.h>
#include <raylib.h>
#include <raymath.h>
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
    float speed;
    Vector2 direction;
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
    ball->speed     = RANDOM_UNIFORM(100, 300);
    ball->direction = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1,
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

    ball->direction = Vector2Normalize(ball->direction);

    // move
    ball->center.x += ball->direction.x * ball->speed * delta_time;
    ball->center.y += ball->direction.y * ball->speed * delta_time;

    // bounds
    if (ball->center.x < ball->radius ||
        ball->center.x > SCREEN_WIDTH - ball->radius) {
        ball->direction.x *= -1;
    }
    if (ball->center.y < ball->radius ||
        ball->center.y > SCREEN_HEIGHT - ball->radius) {
        ball->direction.y *= -1;
    }
}

//-- MAIN --------------------------------------//
int main(void)
{
    srand(time(NULL));

    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boucning Balls");

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
