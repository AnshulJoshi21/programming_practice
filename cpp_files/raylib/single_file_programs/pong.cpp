#include "center_and_draw_text.h"

#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Pong";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const int PLACEMENT_OFFSET = 10.0f;

class Ball {
  public:
    float radius;
    Vector2 center;
    float speed;
    float speed_increment;
    Vector2 direction;
    Color color;
    bool active;

    Ball() : radius(10.0f), speed_increment(10.0f), color(RED) { reset(); }

    void reset(void)
    {
        center    = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
        speed     = 400.0f;
        direction = (Vector2){
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
        };
        active = false;
    }

    void draw(void) const
    {
        DrawCircleV(center, radius, color);

        // draw activation text
        if (!active) {
            center_and_draw_text(
                "press SPACE to begin",
                (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200},
                GetFontDefault(), 20.0f);
        }
    }

    void update(float dt)
    {
        // activate ball
        if (IsKeyPressed(KEY_SPACE)) {
            active = true;
        }

        if (active) {
            direction = Vector2Normalize(direction);

            // move
            center.x += direction.x * speed * dt;
            center.y += direction.y * speed * dt;

            // bounds
            if (center.y < radius || center.y > SCREEN_HEIGHT - radius) {
                direction.y *= -1;
            }
        }
    }
};

class Paddle {
  public:
    Rectangle rect;
    float speed;
    Color color;

    Paddle(float x)
        : rect((Rectangle){x, 0, 10.0f, 100.0f}), speed(300.0f), color(BLACK)
    {
        // set rect.y
        reset();
    }

    void reset(void) { rect.y = (SCREEN_HEIGHT - rect.height) / 2.0f; }

    void draw(void) const { DrawRectangleRec(rect, color); }

    void update_player(float dt)
    {
        if (IsKeyDown(KEY_W) && rect.y > 0) {
            rect.y -= speed * dt;
        }
        if (IsKeyDown(KEY_S) && rect.y < SCREEN_HEIGHT - rect.height) {
            rect.y += speed * dt;
        }
    }

    void update_ai(float dt, float ball_y)
    {
        if (ball_y < rect.y + rect.height / 2.0f && rect.y > 0) {
            rect.y -= speed * dt;
        }
        if (ball_y > rect.y + rect.height / 2.0f &&
            rect.y < SCREEN_HEIGHT - rect.height) {
            rect.y += speed * dt;
        }
    }
};

class GameManager {
  public:
    int score_left;
    int score_right;

    Ball ball;
    Paddle player;
    Paddle ai;

    GameManager()
        : score_left(0), score_right(0), ball(), player(PLACEMENT_OFFSET),
          ai(SCREEN_WIDTH - player.rect.width - PLACEMENT_OFFSET)
    {
    }

    void draw(void) const
    {
        // draw scores
        DrawText(TextFormat("%d", score_left), 200, 30, 30, BLACK);
        DrawText(TextFormat("%d", score_right), SCREEN_WIDTH - 200, 30, 30,
                 BLACK);

        ball.draw();
        player.draw();
        ai.draw();
    }

    void handle_collision(float dt)
    {
        // ball collision paddles
        if (CheckCollisionCircleRec(ball.center, ball.radius, player.rect)) {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment * dt;
        }
        if (CheckCollisionCircleRec(ball.center, ball.radius, ai.rect)) {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment * dt;
        }
    }

    void reset_ball_and_paddles(void)
    {
        ball.reset();
        player.reset();
        ai.reset();
    }

    void update_scores(void)
    {
        if (ball.center.x < -ball.radius) {
            score_right++;
            reset_ball_and_paddles();
        }
        if (ball.center.x > SCREEN_WIDTH - ball.radius) {
            score_left++;
            reset_ball_and_paddles();
        }
    }

    void update(float dt)
    {
        ball.update(dt);
        player.update_player(dt);
        ai.update_ai(dt, ball.center.y);

        handle_collision(dt);
        update_scores();
    }
};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    GameManager game_manager;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        game_manager.update(dt);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        game_manager.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
