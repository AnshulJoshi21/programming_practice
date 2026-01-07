#include "utils.h"

#include <raylib.h>

static const int SCREEN_WIDTH        = 600;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Snake";
static const Color SCREEN_BACKGROUND = RAYWHITE;
static const int GAME_FPS            = 60;

static const int BLOCK_SIZE = 25;
static const int MARGIN     = 50;

#define GRID_SIZE 20

//************************************************//
// GRID
//************************************************//
static void draw_grid(void)
{
    float line_thickness = 2.0f;
    Color color          = LIGHTGRAY;

    // vertical lines
    for (int x = MARGIN + BLOCK_SIZE; x < SCREEN_WIDTH - MARGIN; x += BLOCK_SIZE) {
        DrawLineEx((Vector2){x, MARGIN}, (Vector2){x, SCREEN_WIDTH - MARGIN}, line_thickness,
                   color);
    }

    // horizontal lines
    for (int y = MARGIN + BLOCK_SIZE; y < SCREEN_HEIGHT - MARGIN; y += BLOCK_SIZE) {
        DrawLineEx((Vector2){MARGIN, y}, (Vector2){SCREEN_WIDTH - MARGIN, y}, line_thickness,
                   color);
    }

    // outline rectangle
    line_thickness = 5.0f;
    color          = GRAY;

    DrawRectangleLinesEx(
        (Rectangle){MARGIN, MARGIN, SCREEN_WIDTH - MARGIN * 2, SCREEN_HEIGHT - MARGIN * 2},
        line_thickness, color);
}

//************************************************//
// SNAKE
//************************************************//
typedef enum Direction {
    D_RIGHT,
    D_LEFT,
    D_UP,
    D_DOWN

} Direction;

typedef struct Point
{
    int x;
    int y;

} Point;

typedef struct Snake
{
    int x;
    int y;
    Direction direction;
    int body_size;
    Point body[GRID_SIZE * GRID_SIZE];

    float last_move_time;
    float move_interval;

} Snake;

static void snake_init(Snake *snake)
{
    if (!snake)
        return;

    snake->x         = MARGIN;
    snake->y         = MARGIN;
    snake->direction = D_RIGHT;
    snake->body_size = 1;
    snake->body[0]   = (Point){snake->x, snake->y};

    snake->last_move_time = 0.0f;
    snake->move_interval  = 0.09f;
}

static void snake_draw(const Snake *snake)
{
    if (!snake)
        return;

    for (int i = 0; i < snake->body_size; i++) {
        Color color = (i == 0) ? BLUE : SKYBLUE;

        DrawRectangle(snake->body[i].x, snake->body[i].y, BLOCK_SIZE, BLOCK_SIZE, color);
    }
}

static void snake_handle_input(Snake *snake)
{
    if (!snake)
        return;

    if (IsKeyPressed(KEY_D) && snake->direction != D_LEFT) {
        snake->direction = D_RIGHT;
    } else if (IsKeyPressed(KEY_A) && snake->direction != D_RIGHT) {
        snake->direction = D_LEFT;
    } else if (IsKeyPressed(KEY_S) && snake->direction != D_UP) {
        snake->direction = D_DOWN;
    } else if (IsKeyPressed(KEY_W) && snake->direction != D_DOWN) {
        snake->direction = D_UP;
    }
}

static void snake_move(Snake *snake)
{
    if (!snake)
        return;

    switch (snake->direction) {
    case D_RIGHT:
        snake->x += BLOCK_SIZE;
        break;
    case D_LEFT:
        snake->x -= BLOCK_SIZE;
        break;
    case D_UP:
        snake->y -= BLOCK_SIZE;
        break;
    case D_DOWN:
        snake->y += BLOCK_SIZE;
        break;
    }
}

static bool snake_collision_walls(Snake *snake)
{
    if (!snake)
        return true;

    return (snake->x < MARGIN || snake->x > SCREEN_WIDTH - MARGIN - BLOCK_SIZE ||
            snake->y < MARGIN || snake->y > SCREEN_HEIGHT - MARGIN - BLOCK_SIZE);
}

static bool snake_collision_itself(Snake *snake)
{
    if (!snake)
        return true;

    for (int i = 0; i < snake->body_size; i++) {
        if (snake->x == snake->body[i].x && snake->y == snake->body[i].y) {
            return true;
        }
    }

    return false;
}

static bool snake_update(Snake *snake)
{
    if (!snake)
        return true;

    snake_handle_input(snake);

    float current_time = GetTime();
    if (current_time - snake->last_move_time >= snake->move_interval) {
        snake->last_move_time = current_time;

        snake_move(snake);

        if (snake_collision_walls(snake) || snake_collision_itself(snake))
            return true;

        for (int i = snake->body_size - 1; i > 0; i--) {
            snake->body[i] = snake->body[i - 1];
        }

        snake->body[0] = (Point){snake->x, snake->y};
    }

    return false;
}

//************************************************//
// FOOD
//************************************************//
typedef struct Food
{
    int x;
    int y;
    Color color;

} Food;

static void food_gen_random(Food *food, Point *snake_body, int snake_body_size)
{
    if (!food)
        return;

    int max_tries = 1000;

    for (int i = 0; i < max_tries; i++) {
        bool food_inside_snake_body = false;

        int x = GetRandomValue(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN;
        int y = GetRandomValue(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN;

        for (int j = 0; j < snake_body_size; j++) {
            if (x == snake_body[j].x && y == snake_body[j].y) {
                food_inside_snake_body = true;
                break;
            }
        }

        if (!food_inside_snake_body) {
            food->x = x;
            food->y = y;
            break;
        }
    }
}

static void food_init(Food *food, Point *snake_body, int snake_body_size)
{
    if (!food)
        return;

    food_gen_random(food, snake_body, snake_body_size);
    food->color = RED;
}

static void food_draw(const Food *food)
{
    if (!food)
        return;

    DrawRectangle(food->x, food->y, BLOCK_SIZE, BLOCK_SIZE, food->color);
}

//************************************************//
// MAIN
//************************************************//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    int score      = 0;
    bool game_over = false;

    bool show_blinking_text = false;
    float last_blink_time   = 0.0f;
    float blink_interval    = 1.0f;

    Snake snake;
    snake_init(&snake);

    Food food;
    food_init(&food, snake.body, snake.body_size);

    while (!WindowShouldClose()) {
        // 2.UPDATE

        // game running
        if (!game_over) {
            //
            game_over = snake_update(&snake);

            // snake eating food
            if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
                score++;

                // Avoid bug where block appears/dissappears at (0, 0)
                // 1. capture the current tail before growing
                Point last_tail_pos = snake.body[snake.body_size - 1];
                // 2. increase snake body size
                snake.body_size++;
                // 3. update snake tail
                snake.body[snake.body_size - 1] = last_tail_pos;

                food_gen_random(&food, snake.body, snake.body_size);
            }

        } else {
            // update status text
            float current_time = GetTime();
            if (current_time - last_blink_time >= blink_interval) {
                last_blink_time = current_time;

                show_blinking_text = !show_blinking_text;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                game_over = false;
                score     = 0;

                snake_init(&snake);
                food_init(&food, snake.body, snake.body_size);
            }
        }

        // 3.DRAW
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        // draw score
        center_and_draw_text(TextFormat("Score: %d", score), 20.0f, 2.0f,
                             (Rectangle){0, 0, SCREEN_WIDTH, 60}, GRAY);

        snake_draw(&snake);
        food_draw(&food);

        draw_grid();

        if (game_over) {
            float width     = 300.0f;
            float height    = 150.0f;
            float x         = SCREEN_WIDTH / 2.0f - width / 2.0f;
            float y         = SCREEN_HEIGHT / 2.0f - height / 2.0f;
            Rectangle rect  = (Rectangle){x, y, width, height};
            Color color     = BLACK;
            float thickness = 5.0f;

            // draw background rect
            DrawRectangleLinesEx(rect, thickness, color);

            center_and_draw_text("GAME OVER", 40.0F, 2.0F, rect, color);

            if (show_blinking_text) {
                center_and_draw_text("Press [ENTER] to restart", 20.0f, 2.0f,
                                     (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT + 200}, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
