#include <algorithm>
#include <array>
#include <random>
#include <raylib.h>
#include <raymath.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int MAX_BALLS = 200;

static inline float random_float(const float min, const float max)
{
    if (min == max)
        return min;

    const float minimum = std::min(min, max);
    const float maximum = std::max(min, max);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distr(minimum, maximum);

    return distr(gen);
}

class Ball {
  public:
    float radius;
    Vector2 center;
    float speed;
    Vector2 direction;
    Color color;

    Ball()
        : radius(random_float(5, 30)),
          center({random_float(radius, GetScreenWidth() - radius),
                  random_float(radius, GetScreenHeight() - radius)}),
          speed(random_float(100, 300)),
          direction({static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
                     static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1)}),
          color({static_cast<unsigned char>(random_float(0, 255)),
                 static_cast<unsigned char>(random_float(0, 255)),
                 static_cast<unsigned char>(random_float(0, 255)), 255})
    {
    }

    void draw(void) const { DrawCircleV(center, radius, color); }

    void update(const float dt)
    {
        direction = Vector2Normalize(direction);

        // move
        center.x += direction.x * speed * dt;
        center.y += direction.y * speed * dt;

        // bounds
        if (center.x < radius || center.x > GetScreenWidth() - radius) {
            direction.x *= -1;
        }
        if (center.y < radius || center.y > GetScreenHeight() - radius) {
            direction.y *= -1;
        }
    }
};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncing Balls");
    SetTargetFPS(60);

    std::array<Ball, MAX_BALLS> balls;

    while (!WindowShouldClose()) {

        const float dt = GetFrameTime();

        for (Ball &ball : balls) {
            ball.update(dt);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const Ball &ball : balls) {
            ball.draw();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
