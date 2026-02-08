#include <array>
#include <cassert>
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
    float speed;
    Vector2 direction;
    Color color;

} Ball;

static void ball_init(Ball &ball)
{
    ball.radius = random_uniform(5, 30);
    ball.center =
        (Vector2){random_uniform(ball.radius, SCREEN_WIDTH - ball.radius),
                  random_uniform(ball.radius, SCREEN_HEIGHT - ball.radius)};
    ball.speed     = random_uniform(100, 300);
    ball.direction = (Vector2){
        static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
        static_cast<float>(GetRandomValue(0, 1) == 0 ? -1 : 1),
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
    ball.direction = Vector2Normalize(ball.direction);

    // move
    ball.center.x += ball.direction.x * ball.speed * dt;
    ball.center.y += ball.direction.y * ball.speed * dt;

    // bounds
    if (ball.center.x < ball.radius ||
        ball.center.x > SCREEN_WIDTH - ball.radius) {
        ball.direction.x *= -1;
    }
    if (ball.center.y < ball.radius ||
        ball.center.y > SCREEN_HEIGHT - ball.radius) {
        ball.direction.y *= -1;
    }
}

// == GAME MANAGER ===========================================
typedef struct GameManager
{
    std::array<Ball, MAX_BALLS> balls;

} GameManager;

static void gm_init(GameManager &gm) {}

static void gm_draw(const GameManager &gm)
{
    for (size_t i = 0; i < gm.balls.size(); i++) {
        ball_draw(gm.balls[i]);
    }
}

static void gm_update(GameManager &gm, float dt)
{

    for (size_t i = 0; i < gm.balls.size(); i++) {
        ball_update(gm.balls[i], dt);
    }
}

// == MAIN ===========================================
int main(void)
{
    // == INIT ===========================================
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    GameManager gm;
    gm_init(gm);

    while (!WindowShouldClose()) {
        // == UPDATE ===========================================

        float dt = GetFrameTime();

        gm_update(gm, dt);

        // == DRAW ===========================================
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        gm_draw(gm);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
