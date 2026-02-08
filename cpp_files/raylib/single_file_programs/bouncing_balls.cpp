#include "utils.h"

#include <array>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Bouncing Balls";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const size_t MAX_BALLS = 200;

class Ball {
  public:
    float radius;
    Vector2 center;
    float speed;
    Vector2 direction;
    Color color;

    Ball()
        : radius(random_uniform(5, 30)),
          center((Vector2){random_uniform(radius, SCREEN_WIDTH - radius),
                           random_uniform(radius, SCREEN_HEIGHT - radius)}),
          speed(random_uniform(100, 300)),
          direction((Vector2){
              static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
              static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1)}),
          color((Color){static_cast<unsigned char>(GetRandomValue(0, 255)),
                        static_cast<unsigned char>(GetRandomValue(0, 255)),
                        static_cast<unsigned char>(GetRandomValue(0, 255)),
                        255})
    {
    }

    void draw(void) const { DrawCircleV(center, radius, color); }

    void update(float dt)
    {
        direction = Vector2Normalize(direction);

        // move
        center.x += direction.x * speed * dt;
        center.y += direction.y * speed * dt;

        // bounds
        if (center.x < radius || center.x > SCREEN_WIDTH - radius) {
            direction.x *= -1;
        }
        if (center.y < radius || center.y > SCREEN_HEIGHT - radius) {
            direction.y *= -1;
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
