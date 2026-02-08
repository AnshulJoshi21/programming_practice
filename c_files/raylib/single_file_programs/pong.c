
#include "./utils.h"

#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 600;

//-- BALL --------------------------------------//
typedef struct Ball
{
    Vector2 center;
    float radius;
    Color color;
    float speed;
    float speed_increment;
    Vector2 direction;
    bool is_active;
    bool show_activation_text;
    float last_blink_time;
    float blink_interval;

} Ball;

static void ball_reset(Ball *ball)
{
    assert(ball);

    ball->center = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    ball->speed  = 400.0f;
    ball->direction = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->is_active            = false;
    ball->show_activation_text = false;
    ball->last_blink_time      = GetTime();
}

static void ball_init(Ball *ball)
{
    assert(ball);

    ball->radius          = 10.0f;
    ball->speed_increment = 5.0f;
    ball->color           = RED;
    ball->blink_interval  = 1.0f;

    ball_reset(ball);
}

static void ball_draw(const Ball *ball)
{
    assert(ball);

    if (ball->show_activation_text) {
        center_and_draw_text(
            "Press [SPACE] to begin", 20.0f, 2.0f,
            (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200},
            BLACK);
    }

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball *ball, float dt)
{
    assert(ball);

    // ball activation text update
    if (!ball->is_active) {
        float current_time = GetTime();
        if (current_time - ball->last_blink_time >= ball->blink_interval) {
            ball->last_blink_time = current_time;

            ball->show_activation_text = !ball->show_activation_text;
        }
    }

    // activate ball
    if (IsKeyPressed(KEY_SPACE)) {
        ball->is_active            = true;
        ball->show_activation_text = false;
    }

    if (ball->is_active) {
        ball->direction = Vector2Normalize(ball->direction);

        // move
        ball->center.x += ball->direction.x * ball->speed * dt;
        ball->center.y += ball->direction.y * ball->speed * dt;

        // bounds
        if (ball->center.y < ball->radius ||
            ball->center.y > GetScreenHeight() - ball->radius) {
            ball->direction.y *= -1;
        }
    }
}

//-- PADDLE --------------------------------------//
typedef struct Paddle
{
    Rectangle rect;
    float speed;
    Color color;

} Paddle;

static void paddle_reset(Paddle *paddle)
{
    assert(paddle);

    paddle->rect.y = GetScreenHeight() / 2.0f - paddle->rect.height / 2.0f;
}

static void paddle_init(Paddle *paddle, float x)
{
    assert(paddle);

    float width  = 10.0f;
    float height = 100.0f;

    paddle->rect = (Rectangle){x, 0, width, height};

    // set rect.y
    paddle_reset(paddle);

    paddle->speed = 300.0f;
    paddle->color = BLACK;
}

static void paddle_draw(const Paddle *paddle)
{
    assert(paddle);

    DrawRectangleRec(paddle->rect, paddle->color);
}

static void paddle_update_player(Paddle *paddle, float dt)
{
    assert(paddle);

    if (IsKeyDown(KEY_W) && paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * dt;
    }
    if (IsKeyDown(KEY_S) &&
        paddle->rect.y < GetScreenHeight() - paddle->rect.height) {
        paddle->rect.y += paddle->speed * dt;
    }
}

static void paddle_update_ai(Paddle *paddle, float dt, float ball_y)
{
    assert(paddle);

    if (ball_y < paddle->rect.y + paddle->rect.height / 2.0f &&
        paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * dt;
    }
    if (ball_y > paddle->rect.y + paddle->rect.height / 2.0f &&
        paddle->rect.y < GetScreenHeight() - paddle->rect.height) {
        paddle->rect.y += paddle->speed * dt;
    }
}

//-- GAME MANAGER --------------------------------------//
typedef struct GameManager
{

    int score_left;
    int score_right;

    Ball ball;
    Paddle player;
    Paddle ai;

} GameManager;

static void gm_init(GameManager *gm)
{
    assert(gm);

    gm->score_left  = 0;
    gm->score_right = 0;

    ball_init(&gm->ball);
    paddle_init(&gm->player, 10.0f);
    paddle_init(&gm->ai, GetScreenWidth() - gm->player.rect.width - 10.0f);
}

static void gm_draw(const GameManager *gm)
{
    assert(gm);

    // draw scores
    DrawText(TextFormat("%d", gm->score_left), 200, 30, 30, BLACK);
    DrawText(TextFormat("%d", gm->score_right), GetScreenWidth() - 200, 30, 30,
             BLACK);

    ball_draw(&gm->ball);
    paddle_draw(&gm->player);
    paddle_draw(&gm->ai);
}

static void gm_reset(GameManager *gm)
{
    assert(gm);

    ball_reset(&gm->ball);
    paddle_reset(&gm->player);
    paddle_reset(&gm->ai);
}

static void gm_update(GameManager *gm, float dt)
{
    assert(gm);

    ball_update(&gm->ball, dt);
    paddle_update_player(&gm->player, dt);
    paddle_update_ai(&gm->ai, dt, gm->ball.center.y);

    // ball collision paddles
    if (CheckCollisionCircleRec(gm->ball.center, gm->ball.radius,
                                gm->player.rect)) {
        gm->ball.direction.x *= -1;
        gm->ball.speed += gm->ball.speed_increment * dt;
    }
    if (CheckCollisionCircleRec(gm->ball.center, gm->ball.radius,
                                gm->ai.rect)) {
        gm->ball.direction.x *= -1;
        gm->ball.speed += gm->ball.speed_increment * dt;
    }

    // update scores
    if (gm->ball.center.x < -gm->ball.radius) {
        gm->score_right++;
        gm_reset(gm);
    }
    if (gm->ball.center.x > GetScreenWidth() + gm->ball.radius) {
        gm->score_left++;
        gm_reset(gm);
    }
}

//-- MAIN --------------------------------------//
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");

    GameManager gm;
    gm_init(&gm);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        gm_update(&gm, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        gm_draw(&gm);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
