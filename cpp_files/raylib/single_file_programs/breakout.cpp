#include "center_and_draw_text.h"

#include <raylib.h>
#include <raymath.h>
#include <vector>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Breakout";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const int PLACEMENT_OFFSET = 10.0f;

static const int ROWS = 5;
static const int COLS = 10;

static const float MARGIN       = 3.0f;
static const float BRICK_HEIGHT = 25.0f;
static const float BRICK_GAP    = 2.0f;

static float get_brick_width(void)
{
    float total_gaps          = (COLS - 1) * BRICK_GAP;
    float usable_screen_width = SCREEN_WIDTH - MARGIN * 2 - total_gaps;

    return usable_screen_width / COLS;
}

class Brick {
  public:
    Rectangle rect;
    Color color;
    bool active;

    Brick(float x, float y)
        : rect((Rectangle){x, y, get_brick_width(), BRICK_HEIGHT}), color(GRAY),
          active(true)
    {
    }

    void draw(void) const
    {
        if (active) {
            DrawRectangleRec(rect, color);
        }
    }
};

class Paddle {
  private:
    float rect_height = 10.0f;
    float rect_width  = 100.0f;

  public:
    Rectangle rect;
    float speed;
    Color color;

    Paddle()
        : rect((Rectangle){0, SCREEN_HEIGHT - PLACEMENT_OFFSET - rect_height,
                           rect_width, rect_height}),
          speed(300.0f), color(BLACK)
    {
        reset();
    }

    void reset(void) { rect.x = (SCREEN_WIDTH - rect.width) / 2.0f; }

    void draw(void) const { DrawRectangleRec(rect, color); }

    void update(float dt)
    {
        if (IsKeyDown(KEY_A) && rect.x > 0) {
            rect.x -= speed * dt;
        }
        if (IsKeyDown(KEY_D) && rect.x < SCREEN_WIDTH - rect.width) {
            rect.x += speed * dt;
        }
    }
};

class Ball {
  public:
    float radius;
    Vector2 center;
    float speed;
    float speed_increment;
    Vector2 direction;
    Color color;
    bool active;

    Ball(Rectangle player_rect)
        : radius(10.0f), speed_increment(10.0f), color(RED)
    {
        reset(player_rect);
    }

    void update_pos(Rectangle player_rect)
    {
        center = (Vector2){player_rect.x + player_rect.width / 2.0f,
                           player_rect.y - radius - PLACEMENT_OFFSET};
    }

    void reset(Rectangle player_rect)
    {
        update_pos(player_rect);
        speed     = 400.0f;
        direction = (Vector2){
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1), -1};
        active = false;
    }

    void draw(const bool game_over, const bool game_win) const
    {
        DrawCircleV(center, radius, color);

        // draw activation text
        if (!game_over && !game_win && !active) {
            center_and_draw_text(
                "press SPACE to begin",
                (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200},
                GetFontDefault(), 20.0f);
        }
    }

    void update(float dt, Rectangle player_rect)
    {
        // update position while inactive
        if (!active) {
            update_pos(player_rect);
        }

        // activate
        if (IsKeyPressed(KEY_SPACE)) {
            active = true;
        }

        if (active) {
            direction = Vector2Normalize(direction);

            // move
            center.x += direction.x * speed * dt;
            center.y += direction.y * speed * dt;

            // bounds
            if (center.x < radius || center.x > SCREEN_WIDTH - radius) {
                direction.x *= -1;
            }
            if (center.y < radius) {
                direction.y *= -1;
            }
        }
    }
};

class GameManager {
  public:
    int lives;
    bool game_over;
    bool game_win;

    std::vector<Brick> bricks;
    Paddle paddle;
    Ball ball;

    GameManager() : ball(paddle.rect) { game_reset(); }

    void game_reset(void)
    {
        lives     = 5;
        game_over = false;
        game_win  = false;

        // brick init

        bricks.reserve(ROWS * COLS);
        for (int i = 0; i < ROWS * COLS; i++) {
            float x = (i % COLS) * (get_brick_width() + BRICK_GAP) + MARGIN;

            float y = (i / COLS) * (BRICK_HEIGHT + BRICK_GAP) + MARGIN;

            bricks.emplace_back(Brick(x, y));
        }

        // reset
        paddle.reset();
        ball.reset(paddle.rect);
    }

    void draw_game_status(void) const
    {
        if (game_over || game_win) {
            const char *text;

            if (game_over)
                text = "GAME OVER";
            if (game_win)
                text = "YOU WIN";

            // outline rect
            float width  = 300.0f;
            float height = 150.0f;
            float x      = (SCREEN_WIDTH - width) / 2.0f;
            float y      = (SCREEN_HEIGHT - height) / 2.0f;

            Rectangle rect  = (Rectangle){x, y, width, height};
            float thickness = 5.0f;
            Color color     = BLACK;

            DrawRectangleLinesEx(rect, thickness, color);

            center_and_draw_text(text, rect);
            center_and_draw_text(
                "press ENTER to continue",
                (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200},
                GetFontDefault(), 20.0f);
        }
    }

    void draw(void) const
    {
        // draw lives
        DrawText(TextFormat("%d", lives), 20, SCREEN_HEIGHT - 50, 30, BLACK);

        for (size_t i = 0; i < bricks.size(); i++) {
            bricks[i].draw();
        }

        paddle.draw();
        ball.draw(game_over, game_win);

        draw_game_status();
    }

    void handle_collisions(float dt)
    {
        // ball collision paddle
        if (CheckCollisionCircleRec(ball.center, ball.radius, paddle.rect)) {
            ball.direction.y *= -1;
            ball.speed += ball.speed_increment * dt;
        }

        // ball collision brick
        for (size_t i = 0; i < bricks.size(); i++) {
            if (bricks[i].active) {
                if (CheckCollisionCircleRec(ball.center, ball.radius,
                                            bricks[i].rect)) {
                    ball.direction.y *= -1;
                    bricks[i].active = false;
                }
            }
        }
    }

    void update_lives(void)
    {
        if (ball.center.y > SCREEN_HEIGHT + ball.radius) {
            lives--;
            paddle.reset();
            ball.reset(paddle.rect);
        }
    }

    void handle_game_status(void)
    {
        // game over condition
        if (lives <= 0)
            game_over = true;

        // game win condition
        bool all_bricks_inactive = true;
        for (size_t i = 0; i < bricks.size(); i++) {
            if (bricks[i].active) {
                all_bricks_inactive = false;
                break;
            }
        }

        if (all_bricks_inactive)
            game_win = true;
    }

    void update(float dt)
    {
        // game running
        if (!game_over && !game_win) {
            paddle.update(dt);
            ball.update(dt, paddle.rect);

            handle_collisions(dt);
            update_lives();

            handle_game_status();

        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                game_reset();
            }
        }
    }
};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    GameManager gm;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        gm.update(dt);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        gm.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
