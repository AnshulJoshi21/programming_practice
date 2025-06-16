#include <raylib.h>

#define ROWS 20
#define COLS 20
#define BLOCK_SIZE 30
#define MARGIN 100

typedef enum Direction
{
  RIGHT,
  LEFT,
  UP,
  DOWN

} Direction;

// SNAKE
typedef struct Snake
{
  int x;
  int y;
  int size;
  Direction direction;
  Rectangle list[ROWS * COLS];
  float last_time;
  float move_interval;

} Snake;

void
snake_init(Snake* snake)
{
  snake->x = MARGIN;
  snake->y = MARGIN;
  snake->direction = RIGHT;
  snake->size = 1;
  snake->list[0] = (Rectangle){ snake->x, snake->y, BLOCK_SIZE, BLOCK_SIZE };

  snake->last_time = 0.0f;
  snake->move_interval = 0.08f;
}

void
snake_draw(Snake* snake)
{
  for (int i = 0; i < snake->size; i++) {
    Color color = (i == 0) ? BLUE : SKYBLUE;

    DrawRectangleRec(snake->list[i], color);
  }
}

void
snake_handle_input(Snake* snake)
{
  if (IsKeyPressed(KEY_RIGHT) && snake->direction != LEFT) {
    snake->direction = RIGHT;
  }
  if (IsKeyPressed(KEY_LEFT) && snake->direction != RIGHT) {
    snake->direction = LEFT;
  }
  if (IsKeyPressed(KEY_DOWN) && snake->direction != UP) {
    snake->direction = DOWN;
  }
  if (IsKeyPressed(KEY_UP) && snake->direction != DOWN) {
    snake->direction = UP;
  }
}

bool
snake_collision_itself(Snake* snake)
{
  for (int i = 1; i < snake->size; i++) {
    if (CheckCollisionRecs(
          (Rectangle){ snake->x, snake->y, BLOCK_SIZE, BLOCK_SIZE },
          snake->list[i])) {
      return true;
    }
  }
  return false;
}

bool
snake_collision_walls(Snake* snake)
{
  if (snake->x < MARGIN || snake->x > GetScreenWidth() - MARGIN - BLOCK_SIZE) {
    return true;
  }
  if (snake->y < MARGIN || snake->y > GetScreenHeight() - MARGIN - BLOCK_SIZE) {
    return true;
  }

  return false;
}

void
snake_move(Snake* snake)
{
  switch (snake->direction) {
    case RIGHT:
      snake->x += BLOCK_SIZE;
      break;
    case LEFT:
      snake->x -= BLOCK_SIZE;
      break;
    case UP:
      snake->y -= BLOCK_SIZE;
      break;
    case DOWN:
      snake->y += BLOCK_SIZE;
      break;
  }
}

bool
snake_update(Snake* snake)
{
  snake_handle_input(snake);

  float current_time = GetTime();
  if (current_time - snake->last_time >= snake->move_interval) {
    snake->last_time = current_time;

    for (int i = snake->size - 1; i > 0; i--) {
      snake->list[i] = snake->list[i - 1];
    }

    snake_move(snake);

    if (snake_collision_itself(snake))
      return true;
    if (snake_collision_walls(snake))
      return true;

    snake->list[0] = (Rectangle){ snake->x, snake->y, BLOCK_SIZE, BLOCK_SIZE };
    
  }

  return false;
}

// FOOD
typedef struct Food
{
  Rectangle rect;
  Color color;

} Food;

void
food_gen_position(Food* food, Snake* snake)
{
  while (1) {
    bool pos_in_list = false;

    float x = GetRandomValue(0, COLS - 1) * BLOCK_SIZE + MARGIN;
    float y = GetRandomValue(0, ROWS - 1) * BLOCK_SIZE + MARGIN;

    for (int i = 0; i < snake->size; i++) {
      if (snake->list[i].x == x && snake->list[i].y == y) {
        pos_in_list = true;
        break;
      }
    }

    if (!pos_in_list) {
      food->rect = (Rectangle){ x, y, BLOCK_SIZE, BLOCK_SIZE };
      return;
    }
  }
}

void
food_init(Food* food, Snake* snake)
{
  food->color = RED;
  food_gen_position(food, snake);
}

void
food_draw(Food* food)
{
  DrawRectangleRec(food->rect, food->color);
}

// UTILITY FUNCTIONS
void
draw_grid()
{
  // outline rectangle
  DrawRectangleLinesEx((Rectangle){ MARGIN,
                                    MARGIN,
                                    GetScreenWidth() - MARGIN * 2,
                                    GetRenderHeight() - MARGIN * 2 },
                       5.0,
                       BLACK);

  // vertical lines
  for (int x = MARGIN + BLOCK_SIZE; x < GetScreenWidth() - MARGIN;
       x += BLOCK_SIZE) {
    DrawLineEx((Vector2){ x, MARGIN },
               (Vector2){ x, GetScreenHeight() - MARGIN },
               2.0f,
               BLACK);
  }
  // horizontal lines
  for (int y = MARGIN + BLOCK_SIZE; y < GetScreenHeight() - MARGIN;
       y += BLOCK_SIZE) {
    DrawLineEx((Vector2){ MARGIN, y },
               (Vector2){ GetScreenWidth() - MARGIN, y },
               2.0f,
               BLACK);
  }
}

void
center_and_draw_text(const char* text,
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

// MAIN
int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 800;
  const char SCREEN_TITLE[] = "Snake";
  const Color SCREEN_BACKGROUND = RAYWHITE;
  const int GAME_FPS = 60;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
  SetTargetFPS(GAME_FPS);

  // INIT
  int score = 0;
  bool game_over = false;
  bool show_text = false;
  float last_time = 0.0f;
  float blink_interval = 1.0f;

  Snake snake;
  Food food;

  snake_init(&snake);
  food_init(&food, &snake);

  while (!WindowShouldClose()) {
    // UPDATES
    if (game_over) {
      float current_time = GetTime();
      if (current_time - last_time >= blink_interval) {
        last_time = current_time;
        show_text = !show_text;
      }
    }

    if (!game_over) {
      game_over = snake_update(&snake);

      // food collision snake
      if (CheckCollisionRecs(food.rect, snake.list[0])) {
        food_gen_position(&food, &snake);
        snake.list[snake.size] = snake.list[snake.size - 1];
        snake.size++;
        score++;
      }

    } else {
      if (IsKeyPressed(KEY_ENTER)) {
        score = 0;
        game_over = false;
        show_text = false;
        last_time = 0.0f;

        snake_init(&snake);
        food_init(&food, &snake);
      }
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    // DRAW
    if (!game_over) {
      // draw score
      center_and_draw_text(
        TextFormat("Score: %d", score), 30, 0, 0, GetScreenWidth(), 150, BLACK);

      snake_draw(&snake);
      food_draw(&food);

      draw_grid();

    } else {
      center_and_draw_text(
        "GAME OVER", 40, 0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

      center_and_draw_text("press ENTER to restart",
                           30,
                           0,
                           0,
                           GetScreenWidth(),
                           GetScreenHeight() + 300,
                           BLACK);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}