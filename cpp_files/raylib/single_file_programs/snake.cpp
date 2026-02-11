#include "center_and_draw_text.h"

#include <deque>
#include <raylib.h>

static const int SCREEN_SIZE         = 700;
static const char *SCREEN_TITLE      = "Snake";
static const Color SCREEN_BACKGROUND = RAYWHITE;
static const int GAME_FPS            = 60;

static const float MARGIN     = 50.0f;
static const float BLOCK_SIZE = 25.0f;
static const int GRID_SIZE    = (SCREEN_SIZE - MARGIN * 2) / BLOCK_SIZE;

typedef enum Direction {
    D_RIGHT,
    D_LEFT,
    D_UP,
    D_DOWN,

} Direction;

class Snake {
  public:
    Vector2 pos;
    Direction direction;

    float last_time;
    float move_interval;

    std::deque<Vector2> body;

    Snake()
        : pos((Vector2){MARGIN + (GRID_SIZE / 2 * BLOCK_SIZE),
                        MARGIN + (GRID_SIZE / 2 * BLOCK_SIZE)}),
          direction(D_UP), last_time(0.0f), move_interval(0.09f)
    {
        body.emplace_back((Vector2){pos.x, pos.y});
        body.emplace_back((Vector2){pos.x, pos.y + BLOCK_SIZE});
    }

    void draw(void) const
    {
        for (size_t i = 0; i < body.size(); i++) {
            Color color = (i == 0) ? BLUE : SKYBLUE;

            DrawRectangleRec(
                (Rectangle){body[i].x, body[i].y, BLOCK_SIZE, BLOCK_SIZE},
                color);
        }
    }

    void handle_input(void)
    {
        if (IsKeyPressed(KEY_A) && direction != D_RIGHT)
            direction = D_LEFT;
        if (IsKeyPressed(KEY_D) && direction != D_LEFT)
            direction = D_RIGHT;
        if (IsKeyPressed(KEY_W) && direction != D_DOWN)
            direction = D_UP;
        if (IsKeyPressed(KEY_S) && direction != D_UP)
            direction = D_DOWN;
    }

    void move(void)
    {
        switch (direction) {
        case D_LEFT:
            pos.x -= BLOCK_SIZE;
            break;
        case D_RIGHT:
            pos.x += BLOCK_SIZE;
            break;
        case D_UP:
            pos.y -= BLOCK_SIZE;
            break;
        case D_DOWN:
            pos.y += BLOCK_SIZE;
            break;
        default:
            return;
        }
    }

    bool collision_walls(void)
    {
        return (
            pos.x < MARGIN || pos.x > GetScreenWidth() - MARGIN - BLOCK_SIZE ||
            pos.y < MARGIN || pos.y > GetScreenHeight() - MARGIN - BLOCK_SIZE);
    }

    bool collision_itself(void)
    {
        for (size_t i = 0; i < body.size(); i++) {
            if (pos.x == body[i].x && pos.y == body[i].y) {
                return true;
            }
        }

        return false;
    }

    bool update(void)
    {

        handle_input();

        float current_time = GetTime();
        if (current_time - last_time > move_interval) {
            last_time = current_time;

            move();

            if (collision_itself() || collision_walls())
                return true;

            body.push_front((Vector2){pos.x, pos.y});
            body.pop_back();
        }

        return false;
    }
};

class Food {
  public:
    Vector2 pos;
    Color color;

    void gen_random_food(std::deque<Vector2> snake_body)
    {
        int max_tries = 10000;

        for (int i = 0; i < max_tries; i++) {
            bool food_inside_body = false;

            float x = GetRandomValue(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN;
            float y = GetRandomValue(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN;

            for (size_t j = 0; j < snake_body.size(); j++) {
                if (x == snake_body[j].x && y == snake_body[j].y) {
                    food_inside_body = true;
                    break;
                }
            }

            if (!food_inside_body) {
                pos.x = x;
                pos.y = y;
                return;
            }
        }
    }

    Food(std::deque<Vector2> snake_body)
    {
        gen_random_food(snake_body);
        color = RED;
    }

    void draw(void) const
    {
        DrawRectangleRec((Rectangle){pos.x, pos.y, BLOCK_SIZE, BLOCK_SIZE},
                         color);
    }
};

class GameManager {
  public:
    int score;
    bool game_over;

    Snake snake;
    Food food;

    void reset(void)
    {
        score     = 0;
        game_over = false;

        snake = Snake();
        food  = Food(snake.body);
    }

    GameManager() : food(snake.body) { reset(); }

    void draw_grid(void) const
    {
        float thickness = 2.0f;
        Color color     = LIGHTGRAY;

        // vertical lines
        for (int x = MARGIN + BLOCK_SIZE; x < GetScreenWidth() - MARGIN;
             x += BLOCK_SIZE) {
            DrawLineEx(
                (Vector2){static_cast<float>(x), MARGIN},
                (Vector2){static_cast<float>(x), GetScreenWidth() - MARGIN},
                thickness, color);
        }
        // vertical lines
        for (int y = MARGIN + BLOCK_SIZE; y < GetScreenHeight() - MARGIN;
             y += BLOCK_SIZE) {
            DrawLineEx(
                (Vector2){MARGIN, static_cast<float>(y)},
                (Vector2){GetScreenWidth() - MARGIN, static_cast<float>(y)},
                thickness, color);
        }

        // outline rect
        thickness = 3.0f;
        color     = GRAY;

        DrawRectangleLinesEx((Rectangle){MARGIN, MARGIN,
                                         GetScreenWidth() - MARGIN * 2,
                                         GetScreenHeight() - MARGIN * 2},
                             thickness, color);
    }

    void draw_game_status(void) const
    {
        if (game_over) {
            // outline rect
            float width  = 300.0f;
            float height = 150.0f;
            float x      = (SCREEN_SIZE - width) / 2.0f;
            float y      = (SCREEN_SIZE - height) / 2.0f;

            Rectangle rect  = (Rectangle){x, y, width, height};
            float thickness = 5.0f;
            Color color     = BLACK;

            DrawRectangleLinesEx(rect, thickness, color);

            center_and_draw_text("GAME OVER", rect);
            center_and_draw_text(
                "press ENTER to continue",
                (Rectangle){0, 0, SCREEN_SIZE, SCREEN_SIZE + 200},
                GetFontDefault(), 20.0f);
        }
    }

    void draw(void) const
    {
        center_and_draw_text(TextFormat("Score: %d", score),
                             (Rectangle){0, 0,
                                         static_cast<float>(GetScreenWidth()),
                                         MARGIN + 20},
                             GetFontDefault(), 20.0f);

        draw_grid();

        snake.draw();
        food.draw();

        draw_game_status();
    }

    void update_score(void)
    {
        for (size_t i = 0; i < snake.body.size(); i++) {
            if (snake.body[i].x == food.pos.x &&
                snake.body[i].y == food.pos.y) {
                //
                snake.body.push_back(snake.body.back()); // append last element
                food.gen_random_food(snake.body);
                score++;
            }
        }
    }

    void update(void)
    {
        if (!game_over) {
            game_over = snake.update();

            update_score();

        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                reset();
            }
        }
    }
};

int main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    GameManager game_manager;

    while (!WindowShouldClose()) {

        game_manager.update();

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        game_manager.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
