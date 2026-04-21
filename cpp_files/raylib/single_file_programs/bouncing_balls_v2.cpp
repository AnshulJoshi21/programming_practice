#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <raylib.h>

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
    Vector2 velocity;
    Color color;

    Ball()
        : radius(random_float(5, 30)),
          center({random_float(radius, GetScreenWidth() - radius),
                  random_float(radius, GetScreenHeight() - radius)}),
          color({static_cast<unsigned char>(random_float(0, 255)),
                 static_cast<unsigned char>(random_float(0, 255)),
                 static_cast<unsigned char>(random_float(0, 255)), 255})
    {
        const float speed = random_float(100, 300);
        const float random_angle = random_float(0, 2 * PI);

        velocity = {std::cos(random_angle) * speed,
                    std::sin(random_angle) * speed};
    }

    void draw(void) const { DrawCircleV(center, radius, color); }

    void update(const float dt)
    {
        // move
        center.x += velocity.x * dt;
        center.y += velocity.y * dt;

        // bounds
        if (center.x < radius || center.x > GetScreenWidth() - radius) {
            velocity.x *= -1;
        }
        if (center.y < radius || center.y > GetScreenHeight() - radius) {
            velocity.y *= -1;
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
