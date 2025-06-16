#include <raylib.h>
#include <raymath.h>

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
  float last_time;
  float blink_interval;
  bool active;
  bool show_text;

} Ball;

void
ball_init(Ball* ball)
{
  ball->radius = 10.0f;
  ball->initial_x = GetScreenWidth() * 0.5f;
  ball->initial_y = GetScreenHeight() * 0.5f;
  ball->x = ball->initial_x;
  ball->y = ball->initial_y;
  ball->speed = 400.0f;
  ball->direction = (Vector2){
    GetRandomValue(0, 1) == 0 ? -1 : 1,
    GetRandomValue(0, 1) == 0 ? -1 : 1,
  };
  ball->active = false;
  ball->show_text = false;
  ball->last_time = 0.0f;
  ball->blink_interval = 2.0f;
  ball->color = RED;
}

void
ball_reset(Ball* ball)
{
  ball->x = ball->initial_x;
  ball->y = ball->initial_y;
  ball->active = false;
  ball->show_text = false;
  ball->direction = (Vector2){
    GetRandomValue(0, 1) == 0 ? -1 : 1,
    GetRandomValue(0, 1) == 0 ? -1 : 1,
  };
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
ball_update(Ball* ball)
{
  if (!ball->active) {
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
  // restrict to diagonal movement
  if (ball->direction.x != 0 && ball->direction.y != 0) {
    ball->direction = Vector2Normalize(ball->direction);
  }

  // ball bounds
  if (ball->y < ball->radius || ball->y > GetScreenHeight() - ball->radius) {
    ball->direction.y *= -1;
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
paddle_init(Paddle* paddle, float x)
{
  paddle->width = 10.0f;
  paddle->height = 100.0f;
  paddle->initial_x = x;
  paddle->initial_y = GetScreenHeight() * 0.5f - paddle->height / 2;
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
paddle_update_player(Paddle* paddle)
{
  if (IsKeyDown(KEY_UP) && paddle->y > 0) {
    paddle->y -= paddle->speed * GetFrameTime();
  }
  if (IsKeyDown(KEY_DOWN) && paddle->y < GetScreenHeight() - paddle->height) {
    paddle->y += paddle->speed * GetFrameTime();
  }
}

void
paddle_update_ai(Paddle* paddle, Ball* ball)
{
  if (ball->y < paddle->y + paddle->height / 2 && paddle->y > 0) {
    paddle->y -= paddle->speed * GetFrameTime();
  }
  if (ball->y > paddle->y + paddle->height / 2 &&
      paddle->y < GetScreenHeight() - paddle->height) {
    paddle->y += paddle->speed * GetFrameTime();
  }
}

// GAME RESET
void
game_reset(Ball* ball, Paddle* player, Paddle* ai)
{
  ball_reset(ball);
  paddle_reset(player);
  paddle_reset(ai);
}

// MAIN
int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "Pong";
  const Color SCREEN_BACKGROUND = SKYBLUE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  // INIT
  int score_left = 0;
  int score_right = 0;

  Ball ball;
  Paddle player;
  Paddle ai;

  ball_init(&ball);
  paddle_init(&player, 10.0f);
  paddle_init(&ai, GetScreenWidth() - player.width - 10.0f);

  while (!WindowShouldClose()) {

    // UPDATE
    ball_update(&ball);
    paddle_update_player(&player);
    paddle_update_ai(&ai, &ball);

    // ball collision paddle
    if (CheckCollisionCircleRec(
          (Vector2){ ball.x, ball.y },
          ball.radius,
          (Rectangle){ player.x, player.y, player.width, player.height })) {
      ball.direction.x *= -1;
    }
    if (CheckCollisionCircleRec(
          (Vector2){ ball.x, ball.y },
          ball.radius,
          (Rectangle){ ai.x, ai.y, ai.width, ai.height })) {
      ball.direction.x *= -1;
    }

    // update scores
    if (ball.x < ball.radius) {
      score_right++;
      game_reset(&ball, &player, &ai);
    }
    if (ball.x > GetScreenWidth() - ball.radius) {
      score_left++;
      game_reset(&ball, &player, &ai);
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    // DRAW
    // draw scores
    DrawText(TextFormat("%d", score_left), 200, 30, 40, BLACK);
    DrawText(
      TextFormat("%d", score_right), GetScreenWidth() - 200, 30, 40, BLACK);

    ball_draw(&ball);
    paddle_draw(&player);
    paddle_draw(&ai);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}