#include <raylib.h>
#include <raymath.h>

#define ROWS 5
#define COLS 10
#define BRICK_WIDTH 79
#define BRICK_HEIGHT 30
#define BRICK_GAP 2

void
center_and_draw_text(char* text,
                     int font_size,
                     int rect_x,
                     int rect_y,
                     int rect_width,
                     int rect_height,
                     Color color)
{
  int text_width = MeasureText(text, font_size);
  int text_x = rect_x + rect_width / 2 - text_width / 2;
  int text_y = rect_y + rect_height / 2 - font_size / 2;

  DrawText(text, text_x, text_y, font_size, color);
}

// BRICKS
typedef struct Brick
{
  Rectangle rect;
  Color color;
  bool active;

} Brick;

void
brick_init(Brick* brick, int x, int y)
{
  brick->rect = (Rectangle){ x, y, BRICK_WIDTH, BRICK_HEIGHT };
  brick->color = GRAY;
  brick->active = true;
}

void
brick_draw(Brick* brick)
{
  if (brick->active) {
    DrawRectangleRec(brick->rect, brick->color);
  }
}

// PADDLE
typedef struct Paddle
{
  float initial_x;
  float initial_y;
  float x;
  float y;
  float width;
  float height;
  float speed;
  Color color;

} Paddle;

void
paddle_init(Paddle* paddle)
{
  paddle->width = 100.0f;
  paddle->height = 10.0f;
  paddle->initial_x = GetScreenWidth() * 0.5f - paddle->width / 2;
  paddle->initial_y = GetScreenHeight() - paddle->height - 10.0f;
  paddle->x = paddle->initial_x;
  paddle->y = paddle->initial_y;
  paddle->speed = 300.0f;
  paddle->color = BLACK;
}

void
paddle_reset(Paddle* paddle)
{
  paddle->x = paddle->initial_x;
  paddle->y = paddle->initial_y;
}

void
paddle_draw(Paddle* paddle)
{
  DrawRectangleRec(
    (Rectangle){ paddle->x, paddle->y, paddle->width, paddle->height },
    paddle->color);
}

void
paddle_update(Paddle* paddle)
{
  if (IsKeyDown(KEY_LEFT) && paddle->x > 0) {
    paddle->x -= paddle->speed * GetFrameTime();
  }
  if (IsKeyDown(KEY_RIGHT) && paddle->x < GetScreenWidth() - paddle->width) {
    paddle->x += paddle->speed * GetFrameTime();
  }
}

// BALL
typedef struct Ball
{
  float initial_x;
  float initial_y;
  float x;
  float y;
  float radius;
  float speed;
  Vector2 direction;
  Color color;
  bool active;
  bool show_text;
  float last_time;
  float blink_interval;

} Ball;

void
ball_init(Ball* ball, Paddle* paddle)
{
  ball->radius = 10.0f;
  ball->initial_x = paddle->x + paddle->width / 2;
  ball->initial_y = paddle->y - ball->radius;
  ball->x = ball->initial_x;
  ball->y = ball->initial_y;
  ball->speed = 400.0f;
  ball->direction = (Vector2){
    GetRandomValue(0, 1) == 0 ? -1 : 1,
    GetRandomValue(0, 1) == 0 ? -1 : 1,
  };
  ball->color = RED;
  ball->active = false;
  ball->show_text = false;
  ball->last_time = 0.0f;
  ball->blink_interval = 1.0f;
}

void
ball_reset(Ball* ball)
{
  ball->x = ball->initial_x;
  ball->y = ball->initial_y;
  ball->direction = (Vector2){
    GetRandomValue(0, 1) == 0 ? -1 : 1,
    GetRandomValue(0, 1) == 0 ? -1 : 1,
  };
  ball->show_text = false;
  ball->active = false;
  ball->last_time = 0.0f;
}

void
ball_draw(Ball* ball)
{
  if (ball->show_text) {
    center_and_draw_text("press SPACE to start",
                         30,
                         0,
                         0,
                         GetScreenWidth(),
                         GetScreenHeight() + 300,
                         BLACK);
  }

  DrawCircleV((Vector2){ ball->x, ball->y }, ball->radius, ball->color);
}

void
ball_update(Ball* ball, Paddle* paddle)
{
  if (!ball->active) {
    // update ball position
    ball->x = paddle->x + paddle->width / 2;
    ball->y = paddle->y - ball->radius;

    float current_time = GetTime();
    if (current_time - ball->last_time >= ball->blink_interval) {
      ball->last_time = current_time;
      ball->show_text = !ball->show_text;
    }
  }

  // activate ball
  if (IsKeyPressed(KEY_SPACE)) {
    ball->active = !ball->active;
    ball->show_text = false;
  }

  // move ball
  if (ball->active) {
    ball->x += ball->direction.x * ball->speed * GetFrameTime();
    ball->y += ball->direction.y * ball->speed * GetFrameTime();
  }

  // normalize direction vector
  if (ball->direction.x != 0 && ball->direction.y != 0) {
    ball->direction = Vector2Normalize(ball->direction);
  }

  // ball bounds
  if (ball->x < ball->radius || ball->x > GetScreenWidth() - ball->radius) {
    ball->direction.x *= -1;
  }
  if (ball->y < ball->radius) {
    ball->direction.y *= -1;
  }
}

// GAME RESET
void
game_reset(Paddle* paddle, Ball* ball)
{
  paddle_reset(paddle);
  ball_reset(ball);
}

// MAIN
int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "Breakout";
  const Color SCREEN_BACKGROUND = RAYWHITE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  // INIT
  int lives = 5;
  bool game_over = false;
  bool game_won = false;

  float last_time = 0.0f;
  float blink_interval = 1.0f;
  bool show_text = false;

  Brick bricks[ROWS * COLS];
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int x = j * (BRICK_WIDTH + BRICK_GAP);
      int y = i * (BRICK_HEIGHT + BRICK_GAP);

      Brick brick;
      brick_init(&brick, x, y);

      bricks[i * COLS + j] = brick;
    }
  }

  Paddle paddle;
  Ball ball;

  paddle_init(&paddle);
  ball_init(&ball, &paddle);

  while (!WindowShouldClose()) {

    // UPDATE
    // blinking text
    if (game_over || game_won) {
      float current_time = GetTime();
      if (current_time - last_time >= blink_interval) {
        last_time = current_time;
        show_text = !show_text;
      }
    }

    // game over condition
    if (lives <= 0) {
      game_over = true;
    }

    // game win condition
    bool all_bricks_inactive = true;
    for (int i = 0; i < ROWS * COLS; i++) {
      if (bricks[i].active) {
        all_bricks_inactive = false;
        break;
      }
    }

    if (all_bricks_inactive) {
      game_won = true;
    }

    // game start
    if (!game_over && !game_won) {
      paddle_update(&paddle);
      ball_update(&ball, &paddle);

      // ball collision paddle
      if (CheckCollisionCircleRec(
            (Vector2){ ball.x, ball.y },
            ball.radius,
            (Rectangle){ paddle.x, paddle.y, paddle.width, paddle.height })) {
        ball.direction.y *= -1;
      }

      // ball collision bricks
      for (int i = 0; i < ROWS * COLS; i++) {
        if (bricks[i].active) {
          if (CheckCollisionCircleRec(
                (Vector2){ ball.x, ball.y }, ball.radius, bricks[i].rect)) {
            ball.direction.y *= -1;
            bricks[i].active = false;
          }
        }
      }

      // update lives
      if (ball.y > GetScreenHeight()) {
        lives--;
        game_reset(&paddle, &ball);
      }
    } else {
      if (IsKeyPressed(KEY_ENTER)) {
        lives = 5;
        game_won = false;
        game_over = false;
        show_text = false;
        last_time = 0.0f;

        paddle_init(&paddle);
        ball_init(&ball, &paddle);
        // activate all bricks
        for (int i = 0; i < ROWS * COLS; i++) {
          bricks[i].active = true;
        }
      }
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    // DRAW
    // draw lives
    DrawText(TextFormat("%d", lives), 20, GetScreenHeight() - 50, 40, BLACK);

    // draw bricks
    for (int i = 0; i < ROWS * COLS; i++) {
      brick_draw(&bricks[i]);
    }

    paddle_draw(&paddle);
    ball_draw(&ball);

    if (game_over) {
      center_and_draw_text(
        "GAME OVER", 40, 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

      if (show_text) {
        center_and_draw_text("press ENTER to restart",
                             30,
                             0,
                             0,
                             GetScreenWidth(),
                             GetScreenHeight() + 300,
                             BLACK);
      }
    }

    if (game_won) {
      center_and_draw_text(
        "YOU WIN", 40, 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

      if (show_text) {
        center_and_draw_text("press ENTER to restart",
                             30,
                             0,
                             0,
                             GetScreenWidth(),
                             GetScreenHeight() + 300,
                             BLACK);
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}