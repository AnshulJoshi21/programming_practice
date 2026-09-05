#include <assert.h>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH  = 1280;
static const int SCREEN_HEIGHT = 720;

static void draw_centered_text(const char* text, const Rectangle bounds) {
    assert(text);

    const Font    font      = GetFontDefault();
    const float   font_size = 30.0f;
    const float   spacing   = 2.0f;
    const Vector2 text_size = MeasureTextEx(font, text, font_size, spacing);
    const Vector2 pos       = (Vector2){
        bounds.x + (bounds.width - text_size.x) / 2.0f,
        bounds.y + (bounds.height - text_size.y) / 2.0f,
    };
    const Color tint = BLACK;

    DrawTextEx(font, text, pos, font_size, spacing, tint);
}

typedef struct {
    Vector2 center;
    float   radius;
    Color   color;
    float   speed;
    float   speed_increment;
    Vector2 direction;
    bool    active;
} Ball;

static void ball_reset(Ball* ball) {
    assert(ball);
    ball->center = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    ball->speed  = 400.0f;
    ball->direction
        = (Vector2){GetRandomValue(0, 1) == 0 ? -1 : 1, GetRandomValue(0, 1) == 0 ? -1 : 1};
    ball->active = false;
}

static void ball_init(Ball* ball) {
    assert(ball);

    ball->radius          = 10.0f;
    ball->color           = RED;
    ball->speed_increment = 10.0f;

    ball_reset(ball);
}

static void ball_update(Ball* ball, const float dt) {
    assert(ball);

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
        if (ball->center.y < ball->radius) {
            ball->center.y = ball->radius;
            ball->direction.y *= -1;
        }

        if (ball->center.y > GetScreenHeight() - ball->radius) {
            ball->center.y = GetScreenHeight() - ball->radius;
            ball->direction.y *= -1;
        }
    }
}

static void ball_draw(const Ball* ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

typedef struct {
    Rectangle rect;
    Color     color;
    float     speed;
} Paddle;

static void paddle_reset(Paddle* paddle) {
    assert(paddle);

    paddle->rect.y = (GetScreenHeight() - paddle->rect.height) / 2.0f;
}

static void paddle_init(Paddle* paddle, const float x) {
    assert(paddle);

    const float width  = 15.0f;
    const float height = 100.0f;
    paddle->rect       = (Rectangle){x, 0, width, height};
    paddle->color      = BLACK;
    paddle->speed      = 300.0f;

    paddle_reset(paddle);
}

static void paddle_update_player(Paddle* paddle, const float dt) {
    if (IsKeyDown(KEY_W) && paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * dt;
    }
    if (IsKeyDown(KEY_S) && paddle->rect.y < GetScreenHeight() - paddle->rect.height) {
        paddle->rect.y += paddle->speed * dt;
    }
}

static void paddle_update_ai(Paddle* paddle, const float dt, const float ball_y) {
    if (ball_y < paddle->rect.y + paddle->rect.height / 2.0f && paddle->rect.y > 0) {
        paddle->rect.y -= paddle->speed * dt;
    }
    if (ball_y > paddle->rect.y + paddle->rect.height / 2.0f
        && paddle->rect.y < GetScreenHeight() - paddle->rect.height) {
        paddle->rect.y += paddle->speed * dt;
    }
}

static void paddle_draw(const Paddle* paddle) {
    assert(paddle);

    DrawRectangleRec(paddle->rect, paddle->color);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");

    int score_left  = 0;
    int score_right = 0;

    Ball ball;
    ball_init(&ball);

    Paddle player;
    paddle_init(&player, 10.0f);
    Paddle ai;
    paddle_init(&ai, GetScreenWidth() - player.rect.width - 10.0f);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        ball_update(&ball, dt);
        paddle_update_player(&player, dt);
        paddle_update_ai(&ai, dt, ball.center.y);

        // collisions
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
        if (ball.center.x > GetScreenWidth() + ball.radius) {
            score_left++;
            ball_reset(&ball);
            paddle_reset(&player);
            paddle_reset(&ai);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // draw scores
        DrawText(TextFormat("%d", score_left), GetScreenWidth() / 4, 30, 30, BLACK);
        DrawText(
            TextFormat("%d", score_right), GetScreenWidth() - GetScreenWidth() / 4, 30, 30, BLACK);

        if (!ball.active) {
            draw_centered_text("press SPACE to begin",
                               (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200});
        }

        ball_draw(&ball);
        paddle_draw(&player);
        paddle_draw(&ai);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
