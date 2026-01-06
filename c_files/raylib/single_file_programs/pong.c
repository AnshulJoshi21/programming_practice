#include "./utils.h"

#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Pong";
static const Color SCREEN_BACKGROUND = RAYWHITE;

//************************************************//
// BALL
//************************************************//
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

static void ball_init(Ball *ball)
{
    if (!ball)
        return;

    ball->radius          = 10.0f;
    ball->center          = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    ball->speed           = 400.0f;
    ball->speed_increment = 5.0f;
    ball->color           = RED;
    ball->direction       = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->is_active            = false;
    ball->show_activation_text = false;
    ball->last_blink_time      = 0.0f;
    ball->blink_interval       = 1.0f;
}

static void ball_reset(Ball *ball)
{
    if (!ball)
        return;

    ball->center    = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    ball->speed     = 400.0f;
    ball->direction = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->is_active            = false;
    ball->show_activation_text = false;
    ball->last_blink_time      = 0.0f;
}

static void ball_draw(const Ball *ball)
{
    if (!ball)
        return;

    if (ball->show_activation_text) {
        center_and_draw_text("Press [SPACE] to begin", 20.0f, 2.0f,
                             (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200}, BLACK);
    }

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball *ball, float delta_time)
{
    if (!ball)
        return;

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
        ball->center.x += ball->direction.x * ball->speed * delta_time;
        ball->center.y += ball->direction.y * ball->speed * delta_time;

        // bounds
        if (ball->center.y < ball->radius || ball->center.y > SCREEN_HEIGHT - ball->radius) {
            ball->direction.y *= -1;
        }
    }
}

//************************************************//
// PADDLE
//************************************************//
typedef struct Paddle
{
    Rectangle rect;
    float speed;
    Color color;

} Paddle;

static void paddle_init(Paddle *paddle, float x)
{
    if (!paddle)
        return;

    float width  = 10.0f;
    float height = 100.0f;
    float y      = SCREEN_HEIGHT / 2.0f - height / 2.0f;

    paddle->rect  = (Rectangle){x, y, width, height};
    paddle->speed = 300.0f;
    paddle->color = BLACK;
}

static void paddle_reset(Paddle *paddle)
{
    if (!paddle)
        return;

    paddle->rect.y = SCREEN_HEIGHT / 2.0f - paddle->rect.height / 2.0f;
}

static void paddle_draw(const Paddle *paddle)
{
    if (!paddle)
        return;

    DrawRectangleRec(paddle->rect, paddle->color);
}

static void paddle_update_player(Paddle *paddle, float delta_time)
{
    if (!paddle)
        return;

    if (IsKeyDown(KEY_W) && paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * delta_time;
    }
    if (IsKeyDown(KEY_S) && paddle->rect.y < SCREEN_HEIGHT - paddle->rect.height) {
        paddle->rect.y += paddle->speed * delta_time;
    }
}

static void paddle_update_ai(Paddle *paddle, float delta_time, float ball_y)
{
    if (!paddle)
        return;

    if (ball_y < paddle->rect.y + paddle->rect.height / 2.0f && paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * delta_time;
    }
    if (ball_y > paddle->rect.y + paddle->rect.height / 2.0f &&
        paddle->rect.y < SCREEN_HEIGHT - paddle->rect.height) {
        paddle->rect.y += paddle->speed * delta_time;
    }
}

//************************************************//
// MAIN
//************************************************//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    int score_left  = 0;
    int score_right = 0;

    Ball ball;
    ball_init(&ball);

    Paddle player;
    paddle_init(&player, 10.0f);
    Paddle ai;
    paddle_init(&ai, SCREEN_WIDTH - player.rect.width - 10.0f);

    while (!WindowShouldClose()) {
        // 2.UPDATE
        float delta_time = GetFrameTime();

        ball_update(&ball, delta_time);
        paddle_update_player(&player, delta_time);
        paddle_update_ai(&ai, delta_time, ball.center.y);

        // ball collision paddles
        if (CheckCollisionCircleRec(ball.center, ball.radius, player.rect)) {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment * delta_time;
        }
        if (CheckCollisionCircleRec(ball.center, ball.radius, ai.rect)) {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment * delta_time;
        }

        // update scores
        if (ball.center.x < -ball.radius) {
            score_right++;
            ball_reset(&ball);
            paddle_reset(&player);
            paddle_reset(&ai);
        }
        if (ball.center.x > SCREEN_WIDTH + ball.radius) {
            score_left++;
            ball_reset(&ball);
            paddle_reset(&player);
            paddle_reset(&ai);
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        // draw scores
        DrawText(TextFormat("%d", score_left), 200, 30, 30, BLACK);
        DrawText(TextFormat("%d", score_right), SCREEN_WIDTH - 200, 30, 30, BLACK);

        ball_draw(&ball);
        paddle_draw(&player);
        paddle_draw(&ai);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
