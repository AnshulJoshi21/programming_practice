#include "utils.h"

#include <array>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Bouncing Balls v2";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const size_t MAX_BALLS = 200;

class Ball {

  public:
    float radius;
    Vector2 center;
    Vector2 velocity;
    Color color;

    Ball()
        : radius(random_uniform(5, 30)),
          center((Vector2){random_uniform(radius, SCREEN_WIDTH - radius),
                           random_uniform(radius, SCREEN_HEIGHT - radius)}),
          velocity(get_random_velocity()),
          color((Color){static_cast<unsigned char>(GetRandomValue(0, 255)),
                        static_cast<unsigned char>(GetRandomValue(0, 255)),
                        static_cast<unsigned char>(GetRandomValue(0, 255)),
                        255})
    {
    }

    Vector2 get_random_velocity(void)
    {
        float speed         = random_uniform(100, 300);
        float angle_radians = random_uniform(0, 2 * PI);

        return (Vector2){std::cos(angle_radians) * speed,
                         std::sin(angle_radians) * speed

        };
    }

    void draw(void) const { DrawCircleV(center, radius, color); }

    void update(float dt)
    {
        // move
        center.x += velocity.x * dt;
        center.y += velocity.y * dt;

        // bounds
        if (center.x < radius || center.x > SCREEN_WIDTH - radius) {
            velocity.x *= -1;
        }
        if (center.y < radius || center.y > SCREEN_HEIGHT - radius) {
            velocity.y *= -1;
        }
    }
};

class GameManager {
  public:
    std::array<Ball, MAX_BALLS> balls;

    GameManager() {}

    void draw(void) const
    {
        for (size_t i = 0; i < MAX_BALLS; i++) {
            balls[i].draw();
        }
    }

    void update(float dt)
    {
        for (size_t i = 0; i < MAX_BALLS; i++) {
            balls[i].update(dt);
        }
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
