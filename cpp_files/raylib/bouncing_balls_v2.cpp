#include <array>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

constexpr int NUM_OF_BALLS = 200;

class Ball
{
  public:
    Vector2 pos;
    float radius;
    Vector2 velocity;
    Color color;

    Ball()
    {
        radius = GetRandomValue(10, 30);
        pos = (Vector2){ static_cast<float>(GetRandomValue(radius, GetScreenWidth() - radius)),
                         static_cast<float>(GetRandomValue(radius, GetScreenHeight() - radius)) };
        float speed = GetRandomValue(100, 300);
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        velocity = (Vector2){ std::cos(angle) * speed, std::sin(angle) * speed };
        color = (Color){ static_cast<unsigned char>(GetRandomValue(0, 255)),
                         static_cast<unsigned char>(GetRandomValue(0, 255)),
                         static_cast<unsigned char>(GetRandomValue(0, 255)),
                         255 };
    }

    void draw() const
    {
        DrawCircleV(pos, radius, color);
    }

    void update()
    {
        // move ball
        pos.x += velocity.x * GetFrameTime();
        pos.y += velocity.y * GetFrameTime();

        // ball bounds
        if (pos.x < radius || pos.x > GetScreenWidth() - radius)
        {
            velocity.x *= -1;
        }
        if (pos.y < radius || pos.y > GetScreenHeight() - radius)
        {
            velocity.y *= -1;
        }
    }
};

int
main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char SCREEN_TITLE[] = "BOUNCING BALLS";
    const Color SCREEN_BACKGROUND = RAYWHITE;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    std::array<Ball, NUM_OF_BALLS> balls;
    for (int i = 0; i < NUM_OF_BALLS; i++)
    {
        balls[i] = Ball();
    }

    while (!WindowShouldClose())
    {
        for (Ball& ball : balls)
        {
            ball.update();
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        for (const Ball& ball : balls)
        {
            ball.draw();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
