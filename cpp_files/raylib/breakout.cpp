#include "./center_and_draw_text.cpp"
#include <array>
#include <raylib.h>
#include <raymath.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr const char* SCREEN_TITLE = "BREAKOUT";
constexpr Color SCREEN_BACKGROUND = LIGHTGRAY;

constexpr int ROW = 5;
constexpr int COL = 10;
constexpr int BRICK_WIDTH = (SCREEN_WIDTH / COL - 1);
constexpr int BRICK_HEIGHT = 30;
constexpr int BRICK_GAP = 2;

class Brick
{
  public:
    Rectangle rect;
    Color color;
    bool is_active;

    Brick() = default;

    Brick(float x, float y)
    {
        rect = (Rectangle){ x, y, BRICK_WIDTH, BRICK_HEIGHT };
        color = GRAY;
        is_active = true;
    }

    void draw() const
    {
        if (is_active)
        {
            DrawRectangleRec(rect, color);
        }
    }
};

class Paddle
{
  public:
    Rectangle initial_rect;
    Rectangle rect;
    float speed;
    Color color;

    Paddle()
    {
        float width = 100.0f;
        float height = 10.0f;
        initial_rect = (Rectangle){ static_cast<float>(GetScreenWidth()) / 2 - width / 2,
                                    GetScreenHeight() - height * 2,
                                    width,
                                    height };
        rect = initial_rect;
        speed = 300.0f;
        color = BLACK;
    }

    void reset()
    {
        rect = initial_rect;
    }

    void draw() const
    {
        DrawRectangleRec(rect, color);
    }

    void update()
    {
        if (IsKeyDown(KEY_LEFT) && rect.x > 0)
        {
            rect.x -= speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_RIGHT) && rect.x < GetScreenWidth() - rect.width)
        {
            rect.x += speed * GetFrameTime();
        }
    }
};

class Ball
{
  public:
    Vector2 initial_pos;
    Vector2 pos;
    Vector2 direction;
    float radius;
    float initial_speed;
    float speed;
    float speed_increment;
    Color color;
    bool is_active;

    Ball()
    {
        initial_pos = (Vector2){ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
        pos = initial_pos;
        direction = (Vector2){
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
            1,
        };
        radius = 10.0f;
        initial_speed = 300.0f;
        speed = initial_speed;
        speed_increment = 10.0f;
        color = RED;
        is_active = false;
    }

    void reset()
    {
        pos = initial_pos;
        speed = initial_speed;
        direction = (Vector2){
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
            1,
        };
        is_active = false;
    }

    void draw() const
    {
        DrawCircleV(pos, radius, color);
    }

    void update()
    {
        // activate/deactivate ball
        if (IsKeyPressed(KEY_SPACE))
        {
            is_active = !is_active;
        }

        // move ball
        if (is_active)
        {
            pos.x += direction.x * speed * GetFrameTime();
            pos.y += direction.y * speed * GetFrameTime();
        }

        // normalize direction vector
        if (direction.x != 0 && direction.y != 0)
        {
            direction = Vector2Normalize(direction);
        }

        // ball bounds
        if (pos.x < radius || pos.x > GetScreenWidth() - radius)
        {
            direction.x *= -1;
        }
        if (pos.y < radius)
        {
            direction.y *= -1;
        }
    }
};

int
main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    int lives = 5;
    bool game_over = false;
    bool game_won = false;

    std::array<Brick, ROW * COL> bricks;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            float x = j * (BRICK_WIDTH + BRICK_GAP);
            float y = i * (BRICK_HEIGHT + BRICK_GAP);

            bricks[i * COL + j] = Brick(x, y);
        }
    }

    Paddle paddle;
    Ball ball;

    while (!WindowShouldClose())
    {
        // game over condition
        if (lives <= 0)
        {
            game_over = true;
        }

        // game win condition
        bool all_bricks_inactive = true;
        for (const Brick& brick : bricks)
        {
            if (brick.is_active)
            {
                all_bricks_inactive = false;
                break;
            }
        }
        if (all_bricks_inactive)
        {
            game_won = true;
        }

        // game start
        if (!game_over && !game_won)
        {
            paddle.update();
            ball.update();

            // ball collision paddle
            if (CheckCollisionCircleRec(ball.pos, ball.radius, paddle.rect))
            {
                ball.direction.y *= -1;
                ball.speed += ball.speed_increment;
            }

            // ball collision bricks
            for (Brick& brick : bricks)
            {
                if (CheckCollisionCircleRec(ball.pos, ball.radius, brick.rect) && brick.is_active)
                {
                    ball.direction.y *= -1;
                    brick.is_active = false;
                }
            }

            // update lives
            if (ball.pos.y > GetScreenHeight() - ball.radius)
            {
                lives--;
                ball.reset();
                paddle.reset();
            }
        }
        else
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                lives = 5;
                game_over = false;
                game_won = false;

                for (Brick& brick : bricks)
                {
                    brick.is_active = true;
                }
                Paddle paddle;
                Ball ball;
            }
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        // draw lives
        DrawText(TextFormat("%d", lives), 20, GetScreenHeight() - 50, 40, DARKGRAY);

        if (!game_over && !game_won)
        {
            paddle.draw();
            ball.draw();
            for (const Brick& brick : bricks)
            {
                brick.draw();
            }
        }
        else if (game_over)
        {
            center_and_draw_text(
              "GAME OVER",
              40,
              (Rectangle){
                0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
              DARKGRAY);
            center_and_draw_text("press ENTER to restart",
                                 30,
                                 (Rectangle){ 0,
                                              0,
                                              static_cast<float>(GetScreenWidth()),
                                              static_cast<float>(GetScreenHeight() + 100) },
                                 DARKGRAY);
        }
        else if (game_won)
        {
            center_and_draw_text(
              "YOU WIN",
              40,
              (Rectangle){
                0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
              DARKGRAY);
            center_and_draw_text("press ENTER to restart",
                                 30,
                                 (Rectangle){ 0,
                                              0,
                                              static_cast<float>(GetScreenWidth()),
                                              static_cast<float>(GetScreenHeight() + 100) },
                                 DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}