#include <raylib.h>
#include <raymath.h>

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
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
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
        direction = (Vector2){
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
            static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
        };
        speed = initial_speed;
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
        if (pos.y < radius || pos.y > GetScreenHeight() - radius)
        {
            direction.y *= -1;
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

    Paddle(float x)
    {
        float height = 100.0f;
        initial_rect =
          (Rectangle){ x, static_cast<float>(GetScreenHeight()) / 2 - height / 2, 10.0f, height };
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

    void update_player()
    {
        if (IsKeyDown(KEY_UP) && rect.y > 0)
        {
            rect.y -= speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN) && rect.y < GetScreenHeight() - rect.height)
        {
            rect.y += speed * GetFrameTime();
        }
    }

    void update_ai(float ball_y)
    {
        if (ball_y < rect.y + rect.height / 2 && rect.y > 0)
        {
            rect.y -= speed * GetFrameTime();
        }
        if (ball_y > rect.y + rect.height / 2 && rect.y < GetScreenHeight() - rect.height)
        {
            rect.y += speed * GetFrameTime();
        }
    }
};

int
main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char SCREEN_TITLE[] = "PONG";
    const Color SCREEN_BACKGROUND = LIGHTGRAY;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    int score_left = 0;
    int score_right = 0;

    Ball ball;
    Paddle player(10.0f);
    Paddle ai(GetScreenWidth() - player.rect.width - 10.0f);

    while (!WindowShouldClose())
    {
        ball.update();
        player.update_player();
        ai.update_ai(ball.pos.y);

        // ball collision paddle
        if (CheckCollisionCircleRec(ball.pos, ball.radius, player.rect))
        {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment;
        }
        if (CheckCollisionCircleRec(ball.pos, ball.radius, ai.rect))
        {
            ball.direction.x *= -1;
            ball.speed += ball.speed_increment;
        }

        // update scores
        if (ball.pos.x < ball.radius)
        {
            score_right++;
            ball.reset();
            player.reset();
            ai.reset();
        }
        if (ball.pos.x > GetScreenWidth() - ball.radius)
        {
            score_left++;
            ball.reset();
            player.reset();
            ai.reset();
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        // draw scores
        DrawText(TextFormat("%d", score_left), 200, 30, 40, DARKGRAY);
        DrawText(TextFormat("%d", score_right), GetScreenWidth() - 200, 30, 40, DARKGRAY);

        ball.draw();
        player.draw();
        ai.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}