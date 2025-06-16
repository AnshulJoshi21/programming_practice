#include <raylib.h>
#include <raymath.h>

#define NUM_OF_BALLS 200

// BALL
typedef struct Ball
{
  float x;
  float y;
  float radius;
  float speed;
  Vector2 direction;
  Color color;

} Ball;

void
ball_init(Ball* ball)
{
  ball->radius = GetRandomValue(10, 30);
  ball->x = GetRandomValue(ball->radius, GetScreenWidth() - ball->radius);
  ball->y = GetRandomValue(ball->radius, GetScreenHeight() - ball->radius);
  ball->speed = GetRandomValue(100, 300);
  ball->direction = (Vector2){
    GetRandomValue(0, 1) == 0 ? -1 : 1,
    GetRandomValue(0, 1) == 0 ? -1 : 1,
  };
  ball->color = (Color){
    GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255
  };
}

void
ball_draw(Ball* ball)
{
  DrawCircleV((Vector2){ ball->x, ball->y }, ball->radius, ball->color);
}

void
ball_update(Ball* ball)
{
  // move ball
  ball->x += ball->direction.x * ball->speed * GetFrameTime();
  ball->y += ball->direction.y * ball->speed * GetFrameTime();

  // normalize direction vector
  if (ball->direction.x != 0 && ball->direction.y != 0) {
    ball->direction = Vector2Normalize(ball->direction);
  }

  // ball bounds
  if (ball->x < ball->radius || ball->x > GetScreenWidth() - ball->radius) {
    ball->direction.x *= -1;
  }
  if (ball->y < ball->radius || ball->y > GetScreenHeight() - ball->radius) {
    ball->direction.y *= -1;
  }
}

// MAIN
int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "Bouncing Balls";
  const Color SCREEN_BACKGROUND = RAYWHITE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  // INIT
  Ball balls[NUM_OF_BALLS];

  for (int i = 0; i < NUM_OF_BALLS; i++) {
    Ball ball;
    ball_init(&ball);

    balls[i] = ball;
  }

  while (!WindowShouldClose()) {

    // UPDATE
    for (int i = 0; i < NUM_OF_BALLS; i++) {
      ball_update(&balls[i]);
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    // DRAW
    for (int i = 0; i < NUM_OF_BALLS; i++) {
      ball_draw(&balls[i]);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}