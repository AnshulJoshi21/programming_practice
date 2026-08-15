#include "utils.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAX_LIVES 5

#define BRICK_ROWS 5
#define BRICK_COLS 12
#define BRICK_GAP 2
#define BRICK_HEIGHT 30
#define HORIZONTAL_MARGIN 50
#define VERTICAL_MARGIN 30

typedef struct Brick {
    float x;
    float y;
} Brick;

static float get_brick_width(void) {
    const float available_width
        = (GetScreenWidth() - (HORIZONTAL_MARGIN * 2)) - (BRICK_GAP * (BRICK_COLS - 2));

    return available_width / BRICK_COLS;
}

static void fill_bricks_array(Brick* bricks) {
    assert(bricks);
    const float brick_width = get_brick_width();

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            const float x = (j * (brick_width + BRICK_GAP)) + HORIZONTAL_MARGIN;
            const float y = (i * (BRICK_HEIGHT + BRICK_GAP)) + VERTICAL_MARGIN;

            bricks[j + (i * BRICK_COLS)] = (Brick){x, y};
        }
    }
}

static void draw_bricks_array(const Brick* bricks, const int size) {
    assert(bricks);

    for (int i = 0; i < size; i++) {
        DrawRectangle(bricks[i].x, bricks[i].y, get_brick_width(), BRICK_HEIGHT, GRAY);
    }
}

typedef struct Paddle {
    Rectangle rect;
    Color     color;
    float     speed;
} Paddle;

static void paddle_reset(Paddle* paddle) {
    assert(paddle);

    paddle->rect.x = GetScreenWidth() / 2.0f - paddle->rect.width / 2.0f;
}

static void paddle_init(Paddle* paddle) {
    assert(paddle);

    const float width  = 100.0f;
    const float height = 15.0f;
    paddle->rect       = (Rectangle){0, GetScreenHeight() - height - 10.0f, width, height};
    paddle->color      = BLACK;
    paddle->speed      = 300.0f;

    // set rect.x
    paddle_reset(paddle);
}

static void paddle_update(Paddle* paddle, const float dt) {
    assert(paddle);

    if (IsKeyDown(KEY_A) && paddle->rect.x > 0) {
        paddle->rect.x -= paddle->speed * dt;
    }

    if (IsKeyDown(KEY_D) && paddle->rect.x < GetScreenWidth() - paddle->rect.width) {
        paddle->rect.x += paddle->speed * dt;
    }
}

static void paddle_draw(const Paddle* paddle) {
    assert(paddle);

    DrawRectangleRec(paddle->rect, paddle->color);
}

typedef struct Ball {
    Vector2 center;
    float   radius;
    Color   color;
    float   speed;
    float   speed_increment;
    Vector2 direction;
    bool    active;
} Ball;

static void ball_update_pos(Ball* ball, const Rectangle paddle_rect) {
    assert(ball);

    ball->center
        = (Vector2){paddle_rect.x + paddle_rect.width / 2.0f, paddle_rect.y - ball->radius};
}

static void ball_reset(Ball* ball, const Rectangle paddle_rect) {
    assert(ball);

    ball_update_pos(ball, paddle_rect);
    ball->speed     = 400.0f;
    ball->direction = (Vector2){GetRandomValue(0, 1) == 0 ? -1 : 1, -1};
    ball->active    = false;
}

static void ball_init(Ball* ball, const Rectangle paddle_rect) {
    assert(ball);

    ball->radius          = 12.0f;
    ball->color           = RED;
    ball->speed_increment = 10.0f;

    ball_reset(ball, paddle_rect);
}

static void ball_update(Ball* ball, const float dt, const Rectangle paddle_rect) {
    assert(ball);

    // update pos
    if (!ball->active) {
        ball_update_pos(ball, paddle_rect);
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

        if (ball->center.x > GetScreenWidth() - ball->radius) {
            ball->center.x = GetScreenWidth() - ball->radius;
            ball->direction.x *= -1;
        }

        if (ball->center.y < ball->radius) {
            ball->center.y = ball->radius;
            ball->direction.y *= -1;
        }
    }
}

static void ball_draw(const Ball* ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout");

    int  lives     = MAX_LIVES;
    bool game_over = false;
    bool game_win  = false;

    int   bricks_size = BRICK_ROWS * BRICK_COLS;
    Brick bricks[bricks_size];
    fill_bricks_array(bricks);

    Paddle paddle;
    paddle_init(&paddle);

    Ball ball;
    ball_init(&ball, paddle.rect);

    while (!WindowShouldClose()) {
        if (bricks_size == 0) game_win = true;
        if (lives == 0) game_over = true;

        if (!game_over && !game_win) {
            const float dt = GetFrameTime();

            paddle_update(&paddle, dt);
            ball_update(&ball, dt, paddle.rect);

            // collisions
            // paddle vs ball
            if (CheckCollisionCircleRec(ball.center, ball.radius, paddle.rect)) {
                ball.direction.y *= -1;
                ball.speed += ball.speed_increment * dt;
            }

            // bricks vs ball
            for (int i = 0; i < bricks_size; i++) {
                Brick* brick = &bricks[i];

                if (CheckCollisionCircleRec(
                        ball.center,
                        ball.radius,
                        (Rectangle){brick->x, brick->y, get_brick_width(), BRICK_HEIGHT})) {
                    ball.direction.y *= -1;
                    // remove brick
                    bricks[i] = bricks[--bricks_size];
                    i--;
                }
            }

            // update lives
            if (ball.center.y > GetScreenHeight() + ball.radius) {
                lives--;
                paddle_reset(&paddle);
                ball_reset(&ball, paddle.rect);
            }
        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                lives     = MAX_LIVES;
                game_over = false;
                game_win  = false;

                bricks_size = BRICK_ROWS * BRICK_COLS;
                fill_bricks_array(bricks);

                paddle_init(&paddle);
                ball_init(&ball, paddle.rect);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // draw lives
        DrawText(TextFormat("Lives: %d", lives), 10, GetScreenHeight() - 50, 30, BLACK);

        if (!game_over && !game_win) {
            // draw ball activation text
            if (!ball.active) {
                draw_centered_text(ORIGIN_TOP_LEFT,
                                   GetFontDefault(),
                                   "press SPACE to begin",
                                   (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                                   30.0f,
                                   2.0f,
                                   BLACK);
            }

            draw_bricks_array(bricks, bricks_size);

            paddle_draw(&paddle);
            ball_draw(&ball);

        } else {
            const char* text = "Error";

            if (game_over) text = "Game Over";
            if (game_win) text = "You Win";

            const float width  = 300.0f;
            const float height = 150.0f;
            const float x      = GetScreenWidth() / 2.0f - width / 2.0f;
            const float y      = GetScreenHeight() / 2.0f - height / 2.0f;

            const Rectangle status_rect = (Rectangle){x, y, width, height};

            draw_centered_text(
                ORIGIN_TOP_LEFT, GetFontDefault(), text, status_rect, 40.0f, 2.0f, DARKGRAY);
            draw_centered_text(ORIGIN_TOP_LEFT,
                               GetFontDefault(),
                               "press ENTER to continue",
                               (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 300},
                               30.0f,
                               2.0f,
                               DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
