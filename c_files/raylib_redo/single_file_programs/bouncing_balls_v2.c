#include "utils.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>

static const int BASE_WIDTH  = 800;
static const int BASE_HEIGHT = 600;
static const int MAX_BALLS   = 200;

typedef struct Ball {
    Vector2 center;
    float   radius;
    Vector2 velocity;
    Color   color;
} Ball;

static void ball_init(Ball* ball) {
    assert(ball);

    ball->radius = randf(5, 30);
    ball->center = (Vector2){
        randf(ball->radius, BASE_WIDTH - ball->radius),
        randf(ball->radius, BASE_HEIGHT - ball->radius),
    };
    const float speed = randf(100, 300);
    const float angle = randf(0, 2 * PI);

    ball->velocity = (Vector2){
        cosf(angle) * speed,
        sinf(angle) * speed,
    };
    ball->color
        = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
}

static void ball_draw(const Ball* ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball* ball, const float dt) {
    assert(ball);

    // move
    ball->center.x += ball->velocity.x * dt;
    ball->center.y += ball->velocity.y * dt;

    // bounds
    if (ball->center.x < ball->radius) {
        ball->center.x = ball->radius;
        ball->velocity.x *= -1;
    }

    if (ball->center.x > BASE_WIDTH - ball->radius) {
        ball->center.x = BASE_WIDTH - ball->radius;
        ball->velocity.x *= -1;
    }

    if (ball->center.y < ball->radius) {
        ball->center.y = ball->radius;
        ball->velocity.y *= -1;
    }

    if (ball->center.y > BASE_HEIGHT - ball->radius) {
        ball->center.y = BASE_HEIGHT - ball->radius;
        ball->velocity.y *= -1;
    }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Bouncing Balls V2");

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

        const float   scale  = fminf((float) GetScreenWidth() / (float) BASE_WIDTH,
                                  (float) GetScreenHeight() / (float) BASE_HEIGHT);
        const Vector2 offset = (Vector2){
            (GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
            (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f,
        };

        const Rectangle source = (Rectangle){0, 0, BASE_WIDTH, -BASE_HEIGHT};
        const Rectangle dest
            = (Rectangle){offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
