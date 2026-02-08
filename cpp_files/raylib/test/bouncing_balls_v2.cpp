#include <array>
#include <cassert>
#include <cmath>
#include <random>
#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Bouncing Balls";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const size_t MAX_BALLS = 200;

static inline float random_uniform(float min, float max)
{
    assert(min < max);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(min, max);

    return distr(gen);
}

// == MAIN ===========================================
typedef struct Ball
{
    Vector2 center;
    float radius;
    Vector2 velocity;
    Color color;

} Ball;

static void ball_init(Ball &ball)
{
    ball.radius = random_uniform(5, 30);
    ball.center =
        (Vector2){random_uniform(ball.radius, SCREEN_WIDTH - ball.radius),
                  random_uniform(ball.radius, SCREEN_HEIGHT - ball.radius)};
    float speed         = random_uniform(100, 300);
    float angle_radians = random_uniform(0, 2 * PI);
    ball.velocity       = (Vector2){
        std::cos(angle_radians) * speed,
        std::sin(angle_radians) * speed,
    };
    ball.color =
        (Color){static_cast<unsigned char>(GetRandomValue(0, 255)),
                static_cast<unsigned char>(GetRandomValue(0, 255)),
                static_cast<unsigned char>(GetRandomValue(0, 255)), 255};
}

static void ball_draw(const Ball &ball)
{
    DrawCircleV(ball.center, ball.radius, ball.color);
}

static void ball_update(Ball &ball, float dt)
{
    // move
    ball.center.x += ball.velocity.x * dt;
    ball.center.y += ball.velocity.y * dt;

    // bounds
    if (ball.center.x < ball.radius ||
        ball.center.x > SCREEN_WIDTH - ball.radius) {
        ball.velocity.x *= -1;
    }
    if (ball.center.y < ball.radius ||
        ball.center.y > SCREEN_HEIGHT - ball.radius) {
        ball.velocity.y *= -1;
    }
}

// == MAIN ===========================================
int main(void)
{
    // == INIT ===========================================
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    std::array<Ball, MAX_BALLS> balls;

    for (size_t i = 0; i < MAX_BALLS; i++) {
        ball_init(balls[i]);
    }

    while (!WindowShouldClose()) {
        // == UPDATE ===========================================

        float dt = GetFrameTime();

        for (size_t i = 0; i < balls.size(); i++) {
            ball_update(balls[i], dt);
        }

        // == DRAW ===========================================
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        for (size_t i = 0; i < balls.size(); i++) {
            ball_draw(balls[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
