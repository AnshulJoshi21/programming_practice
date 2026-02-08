#include "utils.h"

#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH  = 800;
static const int SCREEN_HEIGHT = 600;

#define BRICK_ROWS 5
#define BRICK_COLS 10
#define MAX_BRICKS (BRICK_ROWS * BRICK_COLS)

static const float MARGIN = 5.0f;

static const int BRICK_HEIGHT = 30;
static const int BRICK_GAP    = 2;

static float get_brick_width(void)
{
    // horizontal
    float total_gaps             = BRICK_GAP * (BRICK_COLS - 1);
    float total_margin           = MARGIN * 2;
    float available_screen_width = GetScreenWidth() - total_gaps - total_margin;

    return available_screen_width / BRICK_COLS;
}

//-- BRICKS -------------------------------------------//
typedef struct Brick
{
    Rectangle rect;
    bool is_active;
} Brick;

static void bricks_init(Brick *bricks)
{
    assert(bricks);

    float brick_width = get_brick_width();

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            int x = j * (brick_width + BRICK_GAP) + MARGIN;
            int y = i * (BRICK_HEIGHT + BRICK_GAP) + MARGIN;

            bricks[i * BRICK_COLS + j] =
                (Brick){(Rectangle){x, y, brick_width, BRICK_HEIGHT}, true};
        }
    }
}

static void bricks_draw(Brick *bricks)
{
    assert(bricks);

    Color color = GRAY;

    for (int i = 0; i < MAX_BRICKS; i++) {
        if (bricks[i].is_active) {
            DrawRectangleRec(bricks[i].rect, color);
        }
    }
}

//-- PADDLE -------------------------------------------//
typedef struct Paddle
{
    Rectangle rect;
    float speed;
    Color color;

} Paddle;

static void paddle_reset(Paddle *paddle)
{
    assert(paddle);

    paddle->rect.x = SCREEN_WIDTH / 2.0f - paddle->rect.width / 2.0f;
}

static void paddle_init(Paddle *paddle)
{
    assert(paddle);

    float width  = 100.0f;
    float height = 10.0f;
    float y      = SCREEN_HEIGHT - height - 10.0f;

    paddle->rect = (Rectangle){0, y, width, height};

    // set rect.x
    paddle_reset(paddle);

    paddle->speed = 300.0f;
    paddle->color = BLACK;
}

static void paddle_draw(const Paddle *paddle)
{
    assert(paddle);

    DrawRectangleRec(paddle->rect, paddle->color);
}

static void paddle_update(Paddle *paddle, float dt)
{
    assert(paddle);

    if (IsKeyDown(KEY_A) && paddle->rect.x > 0) {
        paddle->rect.x -= paddle->speed * dt;
    }
    if (IsKeyDown(KEY_D) &&
        paddle->rect.x < SCREEN_WIDTH - paddle->rect.width) {
        paddle->rect.x += paddle->speed * dt;
    }
}

//-- BALL -------------------------------------------//
typedef struct Ball
{
    Vector2 center;
    float radius;
    float speed;
    float speed_increment;
    Vector2 direction;
    Color color;
    bool is_active;
    bool show_activation_text;
    float last_blink_time;
    float blink_interval;

} Ball;

static void ball_reset(Ball *ball, Paddle paddle)
{
    assert(ball);

    ball->center    = (Vector2){paddle.rect.x + paddle.rect.width / 2.0f,
                                paddle.rect.y - ball->radius - 5.0f};
    ball->speed     = 400.0f;
    ball->direction = (Vector2){GetRandomValue(0, 1) == 0 ? -1 : 1, -1};
    ball->is_active = false;
    ball->show_activation_text = false;
    ball->last_blink_time      = GetTime();
}

static void ball_init(Ball *ball, Paddle paddle)
{
    assert(ball);

    ball->radius          = 10.0f;
    ball->speed_increment = 5.0f;
    ball->color           = RED;
    ball->blink_interval  = 1.0f;

    ball_reset(ball, paddle);
}

static void ball_draw(const Ball *ball)
{
    assert(ball);

    if (ball->show_activation_text) {
        center_and_draw_text(
            "Press [SPACE] to begin", 20.0f, 2.0f,
            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200}, BLACK);
    }

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball *ball, float dt, Paddle paddle)
{
    assert(ball);

    // ball activation text update
    if (!ball->is_active) {
        float current_time = GetTime();
        if (current_time - ball->last_blink_time >= ball->blink_interval) {
            ball->last_blink_time = current_time;

            ball->show_activation_text = !ball->show_activation_text;
        }

        // update position
        ball->center = (Vector2){paddle.rect.x + paddle.rect.width / 2.0f,
                                 paddle.rect.y - ball->radius - 10.0f};
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
        if (ball->center.x < ball->radius ||
            ball->center.x > SCREEN_WIDTH - ball->radius) {
            ball->direction.x *= -1;
        }
        if (ball->center.y < ball->radius) {
            ball->direction.y *= -1;
        }
    }
}

//-- GAME MANAGER -------------------------------------------//
typedef struct GameManager
{
    int lives;
    bool game_over;
    bool game_win;

    bool show_end_game_status;
    float last_blink_time;
    float blink_interval;

    Brick bricks[MAX_BRICKS];
    Paddle paddle;
    Ball ball;

} GameManager;

static void gm_reset(GameManager *gm)
{
    assert(gm);

    gm->lives     = 5;
    gm->game_over = false;
    gm->game_win  = false;

    gm->show_end_game_status = false;
    gm->last_blink_time      = 0.0f;

    paddle_init(&gm->paddle);
    ball_init(&gm->ball, gm->paddle);
    bricks_init(gm->bricks);
}

static void gm_init(GameManager *gm)
{
    assert(gm);

    gm_reset(gm);

    gm->blink_interval = 1.0f;
}

static void gm_draw_game_status(const GameManager *gm)
{
    assert(gm);

    if (gm->game_over || gm->game_win) {
        float width          = 300.0f;
        float height         = 150.0f;
        float x              = SCREEN_WIDTH / 2.0f - width / 2.0f;
        float y              = SCREEN_HEIGHT / 2.0f - height / 2.0f;
        float line_thickness = 5.0f;
        Color color          = BLACK;
        Rectangle rect       = (Rectangle){x, y, width, height};

        // draw background rect
        DrawRectangleLinesEx(rect, line_thickness, color);

        const char *status_text = "";
        if (gm->game_over)
            status_text = "GAME OVER";
        if (gm->game_win)
            status_text = "YOU WIN";

        center_and_draw_text(status_text, 40.0f, 2.0f, rect, color);

        if (gm->show_end_game_status) {
            center_and_draw_text(
                "Press [ENTER] to restart", 20.0f, 2.0f,
                (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200}, color);
        }
    }
}

static void gm_draw(GameManager *gm)
{
    assert(gm);

    // draw lives
    DrawText(TextFormat("%d", gm->lives), 20, SCREEN_HEIGHT - 40, 30, BLACK);

    paddle_draw(&gm->paddle);
    ball_draw(&gm->ball);
    bricks_draw(gm->bricks);

    gm_draw_game_status(gm);
}

static void gm_handle_collisions(GameManager *gm, float dt)
{
    assert(gm);

    // ball collision paddle
    if (CheckCollisionCircleRec(gm->ball.center, gm->ball.radius,
                                gm->paddle.rect)) {
        gm->ball.direction.y *= -1;
        gm->ball.speed += gm->ball.speed_increment * dt;
    }

    // ball collision bricks
    for (int i = 0; i < MAX_BRICKS; i++) {
        if (gm->bricks[i].is_active) {
            if (CheckCollisionCircleRec(gm->ball.center, gm->ball.radius,
                                        gm->bricks[i].rect)) {
                gm->bricks[i].is_active = false;
                gm->ball.direction.y *= -1;
            }
        }
    }
}

static void gm_handle_game_status(GameManager *gm)
{
    assert(gm);

    // game lose condition
    if (gm->lives <= 0) {
        gm->game_over = true;
    }

    // game win condition
    bool all_bricks_inactive = true;
    for (int i = 0; i < MAX_BRICKS; i++) {
        if (gm->bricks[i].is_active) {
            all_bricks_inactive = false;
            break;
        }
    }

    if (all_bricks_inactive) {
        gm->game_win = true;
    }
}

static void gm_update_lives(GameManager *gm)
{
    assert(gm);

    if (gm->ball.center.y > SCREEN_HEIGHT + gm->ball.radius) {
        gm->lives--;
        paddle_reset(&gm->paddle);
        ball_reset(&gm->ball, gm->paddle);
    }
}

static void gm_update(GameManager *gm, float dt)
{
    assert(gm);

    // game running
    if (!gm->game_over && !gm->game_win) {

        paddle_update(&gm->paddle, dt);
        ball_update(&gm->ball, dt, gm->paddle);

        gm_handle_collisions(gm, dt);
        gm_handle_game_status(gm);
        gm_update_lives(gm);

    } else {
        // update end game status
        float current_time = GetTime();
        if (current_time - gm->last_blink_time >= gm->blink_interval) {
            gm->last_blink_time = current_time;

            gm->show_end_game_status = !gm->show_end_game_status;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            gm_reset(gm);
        }
    }
}

//-- MAIN -------------------------------------------//
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout");

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
