#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>

#define BASE_WIDTH  1920
#define BASE_HEIGHT 1080
#define MAX_BALLS   200

static inline float random_float(const float min, const float max)
{
    if (min == max)
        return min;

    const float minimum = (min < max) ? min : max;
    const float maximum = (min < max) ? max : min;

    return minimum + ((float)rand() / (float)RAND_MAX) * (maximum - minimum);
}

typedef struct {
    float   radius;
    Vector2 center;
    float   speed;
    Vector2 direction;
    Color   color;

} Ball;

static void ball_init(Ball *ball)
{
    assert(ball);

    ball->radius = random_float(5, 50);
    ball->center = (Vector2){
            random_float(ball->radius, BASE_WIDTH - ball->radius),
            random_float(ball->radius, BASE_HEIGHT - ball->radius),
    };
    ball->speed     = random_float(100, 500);
    ball->direction = (Vector2){
            GetRandomValue(0, 1) == 0 ? -1 : 1,
            GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->color = (Color){GetRandomValue(0, 255),
                          GetRandomValue(0, 255),
                          GetRandomValue(0, 255),
                          255};
}

static void ball_draw(const Ball *ball)
{
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball *ball, const float dt)
{
    assert(ball);

    ball->direction = Vector2Normalize(ball->direction);

    // move
    ball->center.x += ball->direction.x * ball->speed * dt;
    ball->center.y += ball->direction.y * ball->speed * dt;

    // bounds
    if (ball->center.x <= ball->radius
        || ball->center.x >= BASE_WIDTH - ball->radius) {
        ball->direction.x *= -1;
    }
    if (ball->center.y <= ball->radius
        || ball->center.y >= BASE_HEIGHT - ball->radius) {
        ball->direction.y *= -1;
    }
}

int main(void)
{
    srand(time(NULL));

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Bouncing Balls");
    SetTargetFPS(60);

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    Ball balls[MAX_BALLS];

    for (int i = 0; i < MAX_BALLS; i++) {
        ball_init(&balls[i]);
    }

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_update(&balls[i], dt);
        }

        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_draw(&balls[i]);
        }

        EndTextureMode();

        const float scale
                = fminf((float)GetScreenWidth() / (float)BASE_WIDTH,
                        (float)GetScreenHeight() / (float)BASE_HEIGHT);
        const Vector2 offset = (Vector2){
                (GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
                (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f,
        };

        const Rectangle source = (Rectangle){0, 0, BASE_WIDTH, BASE_HEIGHT};
        const Rectangle dest   = (Rectangle){offset.x,
                                             offset.y,
                                             BASE_WIDTH * scale,
                                             BASE_HEIGHT * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture,
                       source,
                       dest,
                       (Vector2){0, 0},
                       0.0f,
                       WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
