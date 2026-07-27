#include <assert.h>
#include <math.h>
#include <raylib.h>

static const int   SCREEN_WIDTH       = 800;
static const int   SCREEN_HEIGHT      = 600;
static const int   MAX_BALLS          = 8;
static const float BALL_ORBIT_RADIUS  = 100.0f;
static const float BALL_ANGULAR_SPEED = 1.0f;

typedef struct Ball {
    Vector2 center;
    float   radius;
    Color   color;

    float speed;
} Ball;

static void ball_init(Ball* ball, const Vector2 origin) {
    assert(ball);

    ball->center = origin;
    ball->radius = 10.0f;
    ball->color  = RED;

    ball->speed = 1.0f;
}

static void ball_draw(const Ball* ball) {
    assert(ball);

    DrawCircleV(ball->center, ball->radius, ball->color);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");

    const Vector2 origin = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    Ball balls[MAX_BALLS];
    for (int i = 0; i < MAX_BALLS; i++) {
        ball_init(&balls[i], origin);
    }

    float angle = 0.0f;

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();
        angle += BALL_ANGULAR_SPEED * dt;

        for (int i = 0; i < MAX_BALLS; i++) {
            float angle_step = (2 * PI) / MAX_BALLS;

            balls[i].center = (Vector2){
                origin.x + cosf(angle + (i * angle_step)) * BALL_ORBIT_RADIUS,
                origin.y + sinf(angle + (i * angle_step)) * BALL_ORBIT_RADIUS,
            };
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // center
        DrawCircleV(origin, 5, BLUE);

        // orbit
        DrawCircleLinesV(origin, BALL_ORBIT_RADIUS, GRAY);

        // ball
        for (int i = 0; i < MAX_BALLS; i++) {
            ball_draw(&balls[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
