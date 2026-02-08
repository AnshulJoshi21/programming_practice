#include "center_and_draw_text.h"

#include <deque>
#include <raylib.h>

static const int SCREEN_SIZE         = 600;
static const char *SCREEN_TITLE      = "Snake";
static const Color SCREEN_BACKGROUND = RAYWHITE;
static const int GAME_FPS            = 60;

static const int MARGIN     = 50;
static const int BLOCK_SIZE = 20;
static const int GRID_SIZE  = (SCREEN_SIZE - MARGIN * 2) / BLOCK_SIZE;

typedef enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN

} Direction;

typedef struct Point
{
    int x;
    int y;

} Point;

class Snake {

  public:
    int x;
    int y;
    Direction direction;
    std::deque<Point> body;

    float last_time;
    float move_interval;

    Snake()
        : x(get_center_coordinate()), y(get_center_coordinate()),
          direction(RIGHT), last_time(GetTime()), move_interval(0.09f)
    {
        body.push_front(Point{x, y});
        body.push_back(Point{x, y + BLOCK_SIZE});
        body.push_back(Point{x, y + BLOCK_SIZE * 2});
    }

    static int get_center_coordinate(void)
    {
        return (((GRID_SIZE - 1) / 2) * BLOCK_SIZE) + MARGIN;
    }

    void draw(void) const
    {
        for (size_t i = 0; i < body.size(); i++) {
            Color color = (i == 0) ? BLUE : SKYBLUE;

            DrawRectangle(body[i].x, body[i].y, BLOCK_SIZE, BLOCK_SIZE, color);
        }
    }
};

class Food {
  public:
    int x;
    int y;
    Color color;

    Food() {}

    void draw(void) const
    {
        DrawRectangle(x, y, BLOCK_SIZE, BLOCK_SIZE, color);
    }
};

class GameManager {
  public:
    int score;
    bool game_over;

    Snake snake;
    Food food;

    GameManager() : score(0), game_over(false) {}

    void draw_grid(void) const
    {
        float thickness = 2.0f;
        Color color     = LIGHTGRAY;

        // vertical lines
        for (int x = MARGIN + BLOCK_SIZE; x < SCREEN_SIZE - MARGIN;
             x += BLOCK_SIZE) {
            DrawLineEx((Vector2){(float)x, MARGIN},
                       (Vector2){(float)x, SCREEN_SIZE - MARGIN}, thickness,
                       color);
        }

        // horizontal lines
        for (int y = MARGIN + BLOCK_SIZE; y < SCREEN_SIZE - MARGIN;
             y += BLOCK_SIZE) {
            DrawLineEx((Vector2){MARGIN, (float)y},
                       (Vector2){SCREEN_SIZE - MARGIN, (float)y}, thickness,
                       color);
        }

        // outline rect
        thickness       = 3.0f;
        color           = GRAY;
        float rect_size = SCREEN_SIZE - MARGIN * 2;
        Rectangle rect  = (Rectangle){MARGIN, MARGIN, rect_size, rect_size};

        DrawRectangleLinesEx(rect, thickness, color);
    }

    void draw(void) const
    {
        draw_grid();

        // draw score
        center_and_draw_text(TextFormat("Score: %d", score),
                             (Rectangle){0, 0, SCREEN_SIZE, MARGIN + 20},
                             GetFontDefault(), 20.0f);

        snake.draw();
        food.draw();
    }

    void update(void) { ; }
};

int main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    GameManager gm;

    while (!WindowShouldClose()) {

        gm.update();

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        gm.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
