#include "utils.h"

#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Breakout";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const int BRICK_ROWS   = 5;
static const int BRICK_COLS   = 10;
static const int BRICK_WIDTH  = 79;
static const int BRICK_HEIGHT = 30;
static const int BRICK_GAP    = 2;
static const int MAX_BRICKS   = BRICK_ROWS * BRICK_COLS;

//************************************************//
// BRICKS
//************************************************//
typedef struct Brick
{
    int x;
    int y;
    bool is_active;
} Brick;

static void bricks_init(Brick *bricks)
{
    if (!bricks)
        return;

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            int x = j * (BRICK_WIDTH + BRICK_GAP);
            int y = i * (BRICK_HEIGHT + BRICK_GAP);

            bricks[i * BRICK_COLS + j] = (Brick){x, y, true};
        }
    }
}

static void bricks_draw(Brick *bricks)
{
    if (!bricks)
        return;

    for (int i = 0; i < MAX_BRICKS; i++) {
        if (bricks[i].is_active) {
            DrawRectangle(bricks[i].x, bricks[i].y, BRICK_WIDTH, BRICK_HEIGHT, GRAY);
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

static void paddle_init(Paddle *paddle)
{
    if (!paddle)
        return;

    float width  = 100.0f;
    float height = 10.0f;
    float x      = SCREEN_WIDTH / 2.0f - width / 2.0f;
    float y      = SCREEN_HEIGHT - height - 10.0f;

    paddle->rect  = (Rectangle){x, y, width, height};
    paddle->speed = 300.0f;
    paddle->color = BLACK;
}

static void paddle_reset(Paddle *paddle)
{
    if (!paddle)
        return;

    paddle->rect.x = SCREEN_WIDTH / 2.0f - paddle->rect.width / 2.0f;
}

static void paddle_draw(const Paddle *paddle)
{
    if (!paddle)
        return;

    DrawRectangleRec(paddle->rect, paddle->color);
}

static void paddle_update(Paddle *paddle, float delta_time)
{
    if (!paddle)
        return;

    if (IsKeyDown(KEY_A) && paddle->rect.x > 0) {
        paddle->rect.x -= paddle->speed * delta_time;
    }
    if (IsKeyDown(KEY_D) && paddle->rect.x < SCREEN_WIDTH - paddle->rect.width) {
        paddle->rect.x += paddle->speed * delta_time;
    }
}

//************************************************//
// BALL
//************************************************//
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
    if (!ball)
        return;

    ball->center =
        (Vector2){paddle.rect.x + paddle.rect.width / 2.0f, paddle.rect.y - ball->radius - 5.0f};
    ball->speed                = 400.0f;
    ball->direction            = (Vector2){GetRandomValue(0, 1) == 0 ? -1 : 1, -1};
    ball->is_active            = false;
    ball->show_activation_text = false;
    ball->last_blink_time      = 0.0f;
}

static void ball_init(Ball *ball, Paddle paddle)
{
    if (!ball)
        return;

    ball->radius          = 10.0f;
    ball->speed_increment = 5.0f;
    ball->color           = RED;
    ball->blink_interval  = 1.0f;

    ball_reset(ball, paddle);
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

static void ball_update(Ball *ball, float delta_time, Paddle paddle)
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
        ball->center.x += ball->direction.x * ball->speed * delta_time;
        ball->center.y += ball->direction.y * ball->speed * delta_time;

        // bounds
        if (ball->center.x < ball->radius || ball->center.x > SCREEN_WIDTH - ball->radius) {
            ball->direction.x *= -1;
        }
        if (ball->center.y < ball->radius) {
            ball->direction.y *= -1;
        }
    }
}

//************************************************//
// MAIN
//************************************************//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    int lives      = 5;
    bool game_over = false;
    bool game_won  = false;

    bool show_end_game_status = false;
    float last_blink_time     = 0.0f;
    float blink_interval      = 1.0f;

    Brick bricks[MAX_BRICKS];
    bricks_init(bricks);

    Paddle paddle;
    paddle_init(&paddle);

    Ball ball;
    ball_init(&ball, paddle);

    while (!WindowShouldClose()) {
        // 2.UPDATE
        //
        // game lose condition
        if (lives <= 0) {
            game_over = true;
        }

        // game win condition
        bool all_bricks_inactive = true;
        for (int i = 0; i < MAX_BRICKS; i++) {
            if (bricks[i].is_active) {
                all_bricks_inactive = false;
                break;
            }
        }

        if (all_bricks_inactive) {
            game_won = true;
        }

        // game running
        if (!game_over && !game_won) {
            float delta_time = GetFrameTime();

            paddle_update(&paddle, delta_time);
            ball_update(&ball, delta_time, paddle);

            // ball collision paddle
            if (CheckCollisionCircleRec(ball.center, ball.radius, paddle.rect)) {
                ball.direction.y *= -1;
                ball.speed += ball.speed_increment * delta_time;
            }

            // ball collision bricks
            for (int i = 0; i < MAX_BRICKS; i++) {
                if (bricks[i].is_active) {
                    if (CheckCollisionCircleRec(
                            ball.center, ball.radius,
                            (Rectangle){bricks[i].x, bricks[i].y, BRICK_WIDTH, BRICK_HEIGHT})) {
                        bricks[i].is_active = false;
                        ball.direction.y *= -1;
                    }
                }
            }

            // update lives
            if (ball.center.y > SCREEN_HEIGHT + ball.radius) {
                lives--;
                paddle_reset(&paddle);
                ball_reset(&ball, paddle);
            }

        } else {
            // update end game status
            float current_time = GetTime();
            if (current_time - last_blink_time >= blink_interval) {
                last_blink_time = current_time;

                show_end_game_status = !show_end_game_status;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                game_over = false;
                game_won  = false;
                lives     = 5;

                paddle_init(&paddle);
                ball_init(&ball, paddle);
                bricks_init(bricks);
            }
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        // draw lives
        DrawText(TextFormat("%d", lives), 20, SCREEN_HEIGHT - 40, 30, BLACK);

        paddle_draw(&paddle);
        ball_draw(&ball);
        bricks_draw(bricks);

        if (game_over || game_won) {
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
            if (game_over) {
                status_text = "GAME OVER";
            } else if (game_won) {
                status_text = "YOU WIN";
            }

            center_and_draw_text(status_text, 40.0f, 2.0f, rect, color);

            if (show_end_game_status) {
                center_and_draw_text("Press [ENTER] to restart", 20.0f, 2.0f,
                                     (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200}, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
