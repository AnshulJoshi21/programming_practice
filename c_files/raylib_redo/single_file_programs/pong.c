#include "timer.h"
#include "utils.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int BASE_WIDTH  = 800;
static const int BASE_HEIGHT = 600;

typedef struct Ball {
    float   radius;
    Vector2 center;
    float   speed;
    float   speed_increment;
    Vector2 direction;
    Color   color;
    bool    active;
} Ball;

static void ball_reset(Ball* ball) {
    assert(ball);

    ball->center    = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f};
    ball->speed     = 300.0f;
    ball->direction = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->active = false;
}

static void ball_init(Ball* ball) {
    assert(ball);

    ball->radius          = 10.0f;
    ball->speed_increment = 10.0f;
    ball->color           = RED;

    ball_reset(ball);
}

static void ball_draw(const Ball* ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball* ball, const float dt) {
    assert(ball);

    if (IsKeyPressed(KEY_SPACE)) {
        ball->active = true;
    }

    if (ball->active) {
        ball->direction = Vector2Normalize(ball->direction);

        // move
        ball->center.x += ball->direction.x * ball->speed * dt;
        ball->center.y += ball->direction.y * ball->speed * dt;

        // bounds
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

typedef struct Paddle {
    Rectangle rect;
    float     roundness;
    int       segments;
    float     speed;
    Color     color;
} Paddle;

static void paddle_reset(Paddle* paddle) {
    assert(paddle);

    paddle->rect.y = BASE_HEIGHT / 2.0f - paddle->rect.height / 2.0f;
}

static void paddle_init(Paddle* paddle, const float x) {
    assert(paddle);

    const float width  = 15.0f;
    const float height = 100.0f;

    paddle->rect      = (Rectangle){x, 0, width, height};
    paddle->roundness = 0.90f;
    paddle->segments  = 0;
    paddle->speed     = 300.0f;
    paddle->color     = BLACK;

    paddle_reset(paddle);
}

static void paddle_draw(const Paddle* paddle) {
    assert(paddle);

    DrawRectangleRounded(paddle->rect, paddle->roundness, paddle->segments, paddle->color);
}

static void paddle_update_player(Paddle* paddle, const float dt) {
    assert(paddle);

    if (IsKeyDown(KEY_W) && paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * dt;
    }
    if (IsKeyDown(KEY_S) && paddle->rect.y < BASE_HEIGHT - paddle->rect.height) {
        paddle->rect.y += paddle->speed * dt;
    }
}

static void paddle_update_ai(Paddle* paddle, const float dt, const float ball_y) {
    assert(paddle);

    if (ball_y < paddle->rect.y + paddle->rect.height / 2.0f && paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * dt;
    }
    if (ball_y > paddle->rect.y + paddle->rect.height / 2.0f
        && paddle->rect.y < BASE_HEIGHT - paddle->rect.height) {
        paddle->rect.y += paddle->speed * dt;
    }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Pong");

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    int score_left  = 0;
    int score_right = 0;

    Ball ball;
    ball_init(&ball);

    IntervalTimer ball_activation_text_timer;
    interval_timer_init(&ball_activation_text_timer, 1.0f);
    bool draw_ball_activation_text = false;

    Paddle player;
    paddle_init(&player, 10.0f);

    Paddle ai;
    paddle_init(&ai, BASE_WIDTH - player.rect.width - 10.0f);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        // ball activation text update
        if (!ball.active) {
            if (interval_timer_tick(&ball_activation_text_timer)) {
                draw_ball_activation_text = !draw_ball_activation_text;
            }
        } else {
            draw_ball_activation_text = false;
        }

        ball_update(&ball, dt);
        paddle_update_player(&player, dt);
        paddle_update_ai(&ai, dt, ball.center.y);

        // ball collision paddles
        if (CheckCollisionCircleRec(ball.center, ball.radius, player.rect)) {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment * dt;
        }
        if (CheckCollisionCircleRec(ball.center, ball.radius, ai.rect)) {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment * dt;
        }

        // update scores
        if (ball.center.x < -ball.radius) {
            score_right++;
            ball_reset(&ball);
            paddle_reset(&player);
            paddle_reset(&ai);
        }
        if (ball.center.x > BASE_WIDTH + ball.radius) {
            score_left++;
            ball_reset(&ball);
            paddle_reset(&player);
            paddle_reset(&ai);
        }

        BeginTextureMode(canvas);
        ClearBackground(LIGHTGRAY);

        // draw scores
        DrawText(TextFormat("%d", score_left), 200, 30, 30, DARKGRAY);
        DrawText(TextFormat("%d", score_right), BASE_WIDTH - 200, 30, 30, DARKGRAY);

        // screen divider
        DrawLineEx((Vector2){BASE_WIDTH / 2.0f, 0},
                   (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT},
                   2.0f,
                   DARKGRAY);

        ball_draw(&ball);

        paddle_draw(&player);
        paddle_draw(&ai);

        // ball activation text
        if (draw_ball_activation_text) {
            center_and_draw_text(ORIGIN_TOP_LEFT,
                                 (Rectangle){0, 0, BASE_WIDTH, BASE_HEIGHT + 300},
                                 "press SPACE to start",
                                 20.0f,
                                 2.0f,
                                 DARKGRAY);
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
