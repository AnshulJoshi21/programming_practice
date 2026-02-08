#include "utils.h"

#include <assert.h>
#include <raylib.h>

static const int SCREEN_WIDTH  = 600;
static const int SCREEN_HEIGHT = 600;

static const int BLOCK_SIZE = 25;
static const int MARGIN     = 50;

#define GRID_SIZE 20

//-- GRID ----------------------------------------------//
static void draw_grid(void)
{
    float line_thickness = 2.0f;
    Color color          = LIGHTGRAY;

    // vertical lines
    for (int x = MARGIN + BLOCK_SIZE; x < SCREEN_WIDTH - MARGIN;
         x += BLOCK_SIZE) {
        DrawLineEx((Vector2){x, MARGIN}, (Vector2){x, SCREEN_WIDTH - MARGIN},
                   line_thickness, color);
    }

    // horizontal lines
    for (int y = MARGIN + BLOCK_SIZE; y < SCREEN_HEIGHT - MARGIN;
         y += BLOCK_SIZE) {
        DrawLineEx((Vector2){MARGIN, y}, (Vector2){SCREEN_WIDTH - MARGIN, y},
                   line_thickness, color);
    }

    // outline rectangle
    line_thickness = 3.0f;
    color          = GRAY;

    DrawRectangleLinesEx((Rectangle){MARGIN, MARGIN, SCREEN_WIDTH - MARGIN * 2,
                                     SCREEN_HEIGHT - MARGIN * 2},
                         line_thickness, color);
}

//-- SNAKE ----------------------------------------------//
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
    assert(snake);

    // screen center position
    snake->x = MARGIN + ((GRID_SIZE - 1) / 2 * BLOCK_SIZE);
    snake->y = MARGIN + ((GRID_SIZE - 1) / 2 * BLOCK_SIZE);

    snake->direction = D_UP;

    snake->body[0]   = (Point){snake->x, snake->y};
    snake->body[1]   = (Point){snake->x, snake->y + BLOCK_SIZE};
    snake->body_size = 2;

    snake->last_move_time = GetTime();
    snake->move_interval  = 0.09f;
}

static void snake_draw(const Snake *snake)
{
    assert(snake);

    for (int i = 0; i < snake->body_size; i++) {
        Color color = (i == 0) ? BLUE : SKYBLUE;

        DrawRectangle(snake->body[i].x, snake->body[i].y, BLOCK_SIZE,
                      BLOCK_SIZE, color);
    }
}

static void snake_handle_input(Snake *snake)
{
    assert(snake);

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
    assert(snake);

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
    assert(snake);

    return (
        snake->x < MARGIN || snake->x > SCREEN_WIDTH - MARGIN - BLOCK_SIZE ||
        snake->y < MARGIN || snake->y > SCREEN_HEIGHT - MARGIN - BLOCK_SIZE);
}

static bool snake_collision_itself(Snake *snake)
{
    assert(snake);

    for (int i = 0; i < snake->body_size; i++) {
        if (snake->x == snake->body[i].x && snake->y == snake->body[i].y) {
            return true;
        }
    }

    return false;
}

static bool snake_update(Snake *snake)
{
    assert(snake);

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

//-- FOOD ----------------------------------------------//
typedef struct Food
{
    int x;
    int y;
    Color color;

} Food;

static void food_gen_random(Food *food, Point *snake_body, int snake_body_size)
{
    assert(food);

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
    assert(food);

    food_gen_random(food, snake_body, snake_body_size);
    food->color = RED;
}

static void food_draw(const Food *food)
{
    assert(food);

    DrawRectangle(food->x, food->y, BLOCK_SIZE, BLOCK_SIZE, food->color);
}

//-- GAME MANAGER ----------------------------------------------//
typedef struct GameManager
{
    int score;
    bool game_over;

    Snake snake;
    Food food;

    bool show_blinking_text;
    float last_blink_time;
    float blink_interval;

} GameManager;

static void gm_reset(GameManager *gm)
{
    assert(gm);

    gm->score              = 0;
    gm->game_over          = false;
    gm->show_blinking_text = false;
    gm->last_blink_time    = GetTime();

    snake_init(&gm->snake);
    food_init(&gm->food, gm->snake.body, gm->snake.body_size);
}

static void gm_init(GameManager *gm)
{
    assert(gm);

    gm->blink_interval = 1.0f;

    gm_reset(gm);
}

static void gm_draw_game_status(const GameManager *gm)
{
    assert(gm);

    if (gm->game_over) {
        float width     = 300.0f;
        float height    = 150.0f;
        float x         = GetScreenWidth() / 2.0f - width / 2.0f;
        float y         = GetScreenHeight() / 2.0f - height / 2.0f;
        Rectangle rect  = (Rectangle){x, y, width, height};
        Color color     = BLACK;
        float thickness = 5.0f;

        // draw background rect
        DrawRectangleLinesEx(rect, thickness, color);

        center_and_draw_text("GAME OVER", 40.0F, 2.0F, rect, color);

        if (gm->show_blinking_text) {
            center_and_draw_text(
                "Press [ENTER] to restart", 20.0f, 2.0f,
                (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight() + 200},
                color);
        }
    }
}

static void gm_draw(const GameManager *gm)
{
    assert(gm);

    // draw score
    center_and_draw_text(TextFormat("Score: %d", gm->score), 20.0f, 2.0f,
                         (Rectangle){0, 0, GetScreenWidth(), MARGIN + 20},
                         GRAY);

    snake_draw(&gm->snake);
    food_draw(&gm->food);

    draw_grid();

    gm_draw_game_status(gm);
}

static void gm_update(GameManager *gm)
{
    assert(gm);

    if (!gm->game_over) {
        //
        gm->game_over = snake_update(&gm->snake);

        // snake eating food
        if (gm->snake.body[0].x == gm->food.x &&
            gm->snake.body[0].y == gm->food.y) {
            gm->score++;

            // Avoid bug where block appears/dissappears at (0, 0)
            // 1. capture the current tail before growing
            Point last_tail_pos = gm->snake.body[gm->snake.body_size - 1];
            // 2. increase snake body size
            gm->snake.body_size++;
            // 3. update snake tail
            gm->snake.body[gm->snake.body_size - 1] = last_tail_pos;

            food_gen_random(&gm->food, gm->snake.body, gm->snake.body_size);
        }

    } else {
        // update status text
        float current_time = GetTime();
        if (current_time - gm->last_blink_time >= gm->blink_interval) {
            gm->last_blink_time = current_time;

            gm->show_blinking_text = !gm->show_blinking_text;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            gm_reset(gm);
        }
    }
}

//-- MAIN ----------------------------------------------//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
    SetTargetFPS(60);

    GameManager gm;
    gm_init(&gm);

    while (!WindowShouldClose()) {

        gm_update(&gm);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        gm_draw(&gm);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
