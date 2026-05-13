#include <assert.h>
#include <raylib.h>
#include <raymath.h>

#define BASE_WIDTH  1920
#define BASE_HEIGHT 1080

typedef struct Ball {
    Vector2 center;
    float   radius;
    float   speed;
    float   speed_increment;
    Vector2 direction;
    Color   color;
    bool    active;

} Ball;

static void ball_init(Ball *ball)
{
    assert(ball);

    ball->radius = 10.0f;
    ball->center = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    ball->speed  = 400.0f;
    ball->speed_increment = 10.f;
    ball->direction       = (Vector2){
            GetRandomValue(0, 1) == 0 ? -1 : 1,
            GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->color  = RED;
    ball->active = false;
}

static void ball_draw(const Ball *ball)
{
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball *ball, const float dt)
{
    assert(ball);

    // activate ball
    if (IsKeyPressed(KEY_SPACE)) {
        ball->active = true;
    }

    if (ball->active) {
        ball->direction = Vector2Normalize(ball->direction);

        // move
        ball->center.x += ball->direction.x * ball->speed * dt;
        ball->center.y += ball->direction.y * ball->speed * dt;

        // bounds
        if (ball->center.x < ball->radius
            || ball->center.x > GetScreenWidth() - ball->radius) {
            ball->direction.x *= -1;
        }
        if (ball->center.y < ball->radius
            || ball->center.y > GetScreenHeight() - ball->radius) {
            ball->direction.y *= -1;
        }
    }
}

int main(void)
{
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Pong");

    Ball ball;
    ball_init(&ball);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        ball_update(&ball, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        ball_draw(&ball);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
