#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>

static const int SCREEN_WIDTH  = 1280;
static const int SCREEN_HEIGHT = 720;
static const int MAX_BALLS     = 600;

static inline float randf(const float min, const float max) {
    if (min == max) return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float) rand() / (float) RAND_MAX) * (maximum - minimum);
}

typedef struct {
    float   radius;
    Vector2 center;
    float   speed;
    Vector2 direction;
    Color   color;
} Ball;

static void ball_init(Ball* ball) {
    assert(ball);

    ball->radius = randf(5, 40);
    ball->center = (Vector2){
        randf(ball->radius, GetScreenWidth() - ball->radius),
        randf(ball->radius, GetScreenHeight() - ball->radius),
    };
    ball->speed     = randf(100, 300);
    ball->direction = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->color = (Color){
        GetRandomValue(0, 255),
        GetRandomValue(0, 255),
        GetRandomValue(0, 255),
        255,
    };
}

static void ball_update(Ball* ball, const float dt) {
    assert(ball);

    ball->direction = Vector2Normalize(ball->direction);

    // move
    ball->center.x += ball->direction.x * ball->speed * dt;
    ball->center.y += ball->direction.y * ball->speed * dt;

    // set bounds
    if (ball->center.x < ball->radius) {
        ball->center.x = ball->radius;
        ball->direction.x *= -1;
    }

    if (ball->center.x > GetScreenWidth() - ball->radius) {
        ball->center.x = GetScreenWidth() - ball->radius;
        ball->direction.x *= -1;
    }

    if (ball->center.y < ball->radius) {
        ball->center.y = ball->radius;
        ball->direction.y *= -1;
    }

    if (ball->center.y > GetScreenHeight() - ball->radius) {
        ball->center.y = GetScreenHeight() - ball->radius;
        ball->direction.y *= -1;
    }
}

static void ball_draw(const Ball* ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

int main(void) {
    srand((unsigned int) time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boucing Balls");

    Ball balls[MAX_BALLS];
    for (int i = 0; i < MAX_BALLS; i++) {
        ball_init(&balls[i]);
    }

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_update(&balls[i], dt);
        }

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
