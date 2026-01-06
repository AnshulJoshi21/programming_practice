#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <time.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Bouncing Balls";
static const Color SCREEN_BACKGROUND = RAYWHITE;

static const int MAX_BALLS = 200;

//************************************************//
// RANDOM FUNCTION
//************************************************//
static inline float random_uniform(float min, float max)
{
    return (min + ((float)rand() / RAND_MAX * (max - min)));
}

//************************************************//
// BALL
//************************************************//
typedef struct Ball
{
    Vector2 center;
    float radius;
    float speed;
    Vector2 direction;
    Color color;

} Ball;

static void ball_init(Ball *ball)
{
    if (!ball)
        return;

    ball->radius = random_uniform(5, 30);
    ball->center = (Vector2){
        random_uniform(ball->radius, SCREEN_WIDTH - ball->radius),
        random_uniform(ball->radius, SCREEN_HEIGHT - ball->radius),
    };
    ball->speed     = random_uniform(100, 300);
    ball->direction = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1,
    };
    ball->color =
        (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
}

static void ball_draw(const Ball *ball)
{
    if (!ball)
        return;

    DrawCircleV(ball->center, ball->radius, ball->color);
}

static void ball_update(Ball *ball, float delta_time)
{
    if (!ball)
        return;

    ball->direction = Vector2Normalize(ball->direction);

    // move
    ball->center.x += ball->direction.x * ball->speed * delta_time;
    ball->center.y += ball->direction.y * ball->speed * delta_time;

    // bounds
    if (ball->center.x < ball->radius || ball->center.x > SCREEN_WIDTH - ball->radius) {
        ball->direction.x *= -1;
    }
    if (ball->center.y < ball->radius || ball->center.y > SCREEN_HEIGHT - ball->radius) {
        ball->direction.y *= -1;
    }
}

//************************************************//
// MAIN
//************************************************//
int main(void)
{
    srand(time(NULL));

    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    Ball balls[MAX_BALLS];

    for (int i = 0; i < MAX_BALLS; i++) {
        ball_init(&balls[i]);
    }

    while (!WindowShouldClose()) {
        // 2.UPDATE
        float delta_time = GetFrameTime();

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_update(&balls[i], delta_time);
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        for (int i = 0; i < MAX_BALLS; i++) {
            ball_draw(&balls[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
