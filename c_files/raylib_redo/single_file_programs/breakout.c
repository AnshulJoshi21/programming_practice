#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int BASE_WIDTH  = 800;
static const int BASE_HEIGHT = 600;

typedef struct Paddle {
    Rectangle rect;
    float     speed;
    float     roundness;
    int       segments;
    Color     color;
} Paddle;

static void paddle_reset(Paddle* paddle) {
    assert(paddle);

    paddle->rect.x = BASE_WIDTH / 2.0f - paddle->rect.width / 2.0f;
}

static void paddle_init(Paddle* paddle) {
    assert(paddle);

    const float width  = 100.0f;
    const float height = 15.0f;

    paddle->rect      = (Rectangle){0, BASE_HEIGHT - (height * 2), width, height};
    paddle->speed     = 300.0f;
    paddle->color     = BLACK;
    paddle->roundness = 0.90f;
    paddle->segments  = 0;

    paddle_reset(paddle);
}

static void paddle_draw(const Paddle* paddle) {
    assert(paddle);

    DrawRectangleRounded(paddle->rect, paddle->roundness, paddle->segments, paddle->color);
}

static void paddle_update(Paddle* paddle, const float dt) {
    assert(paddle);

    if (IsKeyDown(KEY_A) && paddle->rect.x > 0) {
        paddle->rect.x -= paddle->speed * dt;
    }
    if (IsKeyDown(KEY_D) && paddle->rect.x < BASE_WIDTH - paddle->rect.width) {
        paddle->rect.x += paddle->speed * dt;
    }
}

typedef struct Ball {
    float   radius;
    Vector2 center;
    float   speed;
    float   speed_increment;
    Vector2 direction;
    Color   color;
    bool    active_start;
    bool    active;
} Ball;

static void ball_update_center(Ball* ball, const Rectangle* paddle_rect) {
    assert(ball);

    ball->center = (Vector2){paddle_rect->x + paddle_rect->width / 2.0f,
                             paddle_rect->y - (ball->radius * 2)};
}

static void ball_reset(Ball* ball, const Rectangle* paddle_rect) {
    assert(ball);
    ball_update_center(ball, paddle_rect);
    ball->speed        = 300.0f;
    ball->direction    = (Vector2){GetRandomValue(0, 1) == 0 ? -1 : 1, -1};
    ball->active_start = false;
    ball->active       = false;
}

static void ball_init(Ball* ball, const Rectangle* paddle_rect) {
    assert(ball);
    ball->radius          = 10.0f;
    ball->speed_increment = 10.0f;
    ball->color           = RED;

    ball_reset(ball, paddle_rect);
}

static void ball_draw(const Ball* ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball* ball, const float dt, const Rectangle* paddle_rect) {
    assert(ball);

    // update ball position when inactive
    if (!ball->active) {
        ball_update_center(ball, paddle_rect);
    }

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
        if (ball->center.x < ball->radius) {
            ball->center.x = ball->radius;
            ball->direction.x *= -1;
        }

        if (ball->center.x > BASE_WIDTH - ball->radius) {
            ball->center.x = BASE_WIDTH - ball->radius;
            ball->direction.x *= -1;
        }

        if (ball->center.y < ball->radius) {
            ball->center.y = ball->radius;
            ball->direction.y *= -1;
        }

        if (ball->center.y > BASE_HEIGHT - ball->radius) {
            ball->center.y = BASE_HEIGHT - ball->radius;
            ball->direction.y *= -1;
        }
    }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Breakout");

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    Paddle paddle;
    paddle_init(&paddle);

    Ball ball;
    ball_init(&ball, &paddle.rect);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        paddle_update(&paddle, dt);
        ball_update(&ball, dt, &paddle.rect);

        // ball collision paddle
        if (CheckCollisionCircleRec(ball.center, ball.radius, paddle.rect)) {
            ball.direction.y *= -1;
            ball.speed += ball.speed_increment * dt;
        }

        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);

        paddle_draw(&paddle);
        ball_draw(&ball);

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
