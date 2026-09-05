#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH  = 1280;
static const int SCREEN_HEIGHT = 720;

static const int   BRICK_ROWS   = 5;
static const int   BRICK_COLS   = 12;
static const float BRICK_HEIGHT = 30.0f;
static const float BRICK_GAP    = 5.0f;
static const float BRICK_MARGIN = 50.0f;

static void draw_centered_text(const char* text, const Rectangle bounds, const float font_size) {
    assert(text);

    const Font    font      = GetFontDefault();
    const float   spacing   = 2.0f;
    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    const Vector2 pos       = (Vector2){
        bounds.x + (bounds.width - text_size.x) / 2.0f,
        bounds.y + (bounds.height - text_size.y) / 2.0f,
    };
    const Color tint = BLACK;

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}

static inline float get_brick_width(void) {
    const float available_width
        = GetScreenWidth() - (BRICK_MARGIN * 2) - (BRICK_GAP * (BRICK_COLS - 1));

    return available_width / BRICK_COLS;
}

typedef struct {
    float x;
    float y;
} Brick;

typedef struct {
    Rectangle rect;
    Color     color;
    float     speed;
} Paddle;

static void paddle_reset(Paddle* paddle) {
    assert(paddle);

    paddle->rect.x = (GetScreenWidth() - paddle->rect.width) / 2.0f;
}

static void paddle_init(Paddle* paddle) {
    assert(paddle);

    const float width  = 100.0f;
    const float height = 15.0f;
    paddle->rect       = (Rectangle){0, GetScreenHeight() - (height * 2), width, height};
    paddle->color      = BLACK;
    paddle->speed      = 300.0f;

    paddle_reset(paddle);
}

static void paddle_update(Paddle* paddle, const float dt) {
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

typedef struct {
    const Paddle* paddle;
    Vector2       center;
    float         radius;
    Color         color;
    float         speed;
    float         speed_increment;
    Vector2       direction;
    bool          active;
} Ball;

static void ball_update_pos(Ball* ball) {
    assert(ball);

    ball->center = (Vector2){
        ball->paddle->rect.x + ball->paddle->rect.width / 2.0f,
        ball->paddle->rect.y - (ball->radius * 2),
    };
}

static void ball_reset(Ball* ball) {
    assert(ball);
    ball->speed     = 400.0f;
    ball->direction = (Vector2){GetRandomValue(0, 1) == 0 ? -1 : 1, -1};
    ball->active    = false;

    ball_update_pos(ball);
}

static void ball_init(Ball* ball, const Paddle* paddle) {
    assert(ball);
    assert(paddle);

    ball->paddle          = paddle;
    ball->radius          = 10.0f;
    ball->color           = RED;
    ball->speed_increment = 10.0f;

    ball_reset(ball);
}

static void ball_update(Ball* ball, const float dt) {
    assert(ball);

    // update pos
    if (!ball->active) {
        ball_update_pos(ball);
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

        // set bounds
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

    int  lives     = 5;
    bool game_over = false;
    bool game_won  = false;

    const float brick_width = get_brick_width();
    const Color brick_color = GRAY;

    int   brick_size = BRICK_ROWS * BRICK_COLS;
    Brick bricks[brick_size];
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            const int x = j * (brick_width + BRICK_GAP) + BRICK_MARGIN;
            const int y = i * (BRICK_HEIGHT + BRICK_GAP) + BRICK_MARGIN;

            bricks[i * BRICK_COLS + j] = (Brick){x, y};
        }
    }

    Paddle paddle;
    paddle_init(&paddle);

    Ball ball;
    ball_init(&ball, &paddle);

    while (!WindowShouldClose()) {
        if (brick_size == 0) game_won = true;
        if (lives == 0) game_over = true;

        if (!game_over && !game_won) {
            const float dt = GetFrameTime();

            paddle_update(&paddle, dt);
            ball_update(&ball, dt);

            // collisions
            // ball vs paddle
            if (CheckCollisionCircleRec(ball.center, ball.radius, paddle.rect)) {
                ball.speed += ball.speed_increment * dt;
                ball.direction.y *= -1;
            }
            // ball vs bricks
            for (int i = 0; i < brick_size; i++) {
                const Brick* brick = &bricks[i];

                if (CheckCollisionCircleRec(
                        ball.center,
                        ball.radius,
                        (Rectangle){brick->x, brick->y, brick_width, BRICK_HEIGHT})) {
                    ball.direction.y *= -1;
                    bricks[i] = bricks[--brick_size];
                    break;
                }
            }

            // update lives
            if (ball.center.y > GetScreenHeight() + ball.radius) {
                lives--;
                paddle_reset(&paddle);
                ball_reset(&ball);
            }

        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                lives     = 5;
                game_over = false;
                game_won  = false;

                brick_size = BRICK_ROWS * BRICK_COLS;
                for (int i = 0; i < BRICK_ROWS; i++) {
                    for (int j = 0; j < BRICK_COLS; j++) {
                        const int x = j * (brick_width + BRICK_GAP) + BRICK_MARGIN;
                        const int y = i * (BRICK_HEIGHT + BRICK_GAP) + BRICK_MARGIN;

                        bricks[i * BRICK_COLS + j] = (Brick){x, y};
                    }
                }
                paddle_init(&paddle);
                ball_init(&ball, &paddle);
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // draw lives
        DrawText(TextFormat("%d", lives), 20, GetScreenHeight() - 60, 30, BLACK);

        if (!ball.active && !game_over && !game_won) {
            draw_centered_text("press SPACE to begin",
                               (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200},
                               20.0f);
        }

        ball_draw(&ball);
        paddle_draw(&paddle);
        // draw bricks
        for (int i = 0; i < brick_size; i++) {
            const Brick* brick = &bricks[i];
            DrawRectangleRec((Rectangle){brick->x, brick->y, brick_width, BRICK_HEIGHT},
                             brick_color);
        }

        if (game_over || game_won) {
            const char* text = (game_over) ? "GAME OVER" : "YOU WIN";

            const float     width     = 300.0f;
            const float     height    = 150.0f;
            const Rectangle rect      = (Rectangle){(GetScreenWidth() - width) / 2.0f,
                                                    (GetScreenHeight() - height) / 2.0f,
                                                    width,
                                                    height};
            const Color     color     = BLACK;
            const float     thickness = 5.0f;

            draw_centered_text(text, rect, 30.0f);
            draw_centered_text("press ENTER to restart",
                               (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200},
                               20.0f);

            // draw outline rect
            DrawRectangleLinesEx(rect, thickness, color);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
