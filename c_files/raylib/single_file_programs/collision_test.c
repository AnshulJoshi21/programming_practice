#include <raylib.h>
#include <raymath.h>

static const int SCREEN_WIDTH        = 800;
static const int SCREEN_HEIGHT       = 600;
static const char *SCREEN_TITLE      = "Collision Test";
static const Color SCREEN_BACKGROUND = RAYWHITE;
static const int FPS                 = 60;

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(FPS);

    Rectangle rect1   = (Rectangle){0, 0, 50, 50};
    Color rect1_color = BLUE;
    float rect1_speed = 400.0f;

    Rectangle rect2   = (Rectangle){GetScreenWidth() / 2.0f - 150,
                                    GetScreenHeight() / 2.0f - 75, 300, 150};
    Color rect2_color = GRAY;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        Vector2 direction = (Vector2){
            IsKeyDown(KEY_D) - IsKeyDown(KEY_A),
            IsKeyDown(KEY_S) - IsKeyDown(KEY_W),
        };
        direction = Vector2Normalize(direction);

        rect1.x += direction.x * rect1_speed * dt;
        rect1.y += direction.y * rect1_speed * dt;

        // collision resolution
        float rect1_left   = rect1.x;
        float rect1_right  = rect1.x + rect1.width;
        float rect1_top    = rect1.y;
        float rect1_bottom = rect1.y + rect1.height;

        float rect2_left   = rect2.x;
        float rect2_right  = rect2.x + rect2.width;
        float rect2_top    = rect2.y;
        float rect2_bottom = rect2.y + rect2.height;

        if (rect1_right > rect2_left && rect1_left < rect2_right &&
            rect1_bottom > rect2_top && rect1_top < rect2_bottom) {

            float overlap_left   = rect1_right - rect2_left;
            float overlap_right  = rect2_right - rect1_left;
            float overlap_top    = rect1_bottom - rect2_top;
            float overlap_bottom = rect2_bottom - rect1_top;

            float overlap_min = overlap_left;
            int direction     = 0; // 0 = left, 1=right, 2=top, 3=bottom

            if (overlap_right < overlap_min) {
                overlap_min = overlap_right;
                direction   = 1;
            }
            if (overlap_top < overlap_min) {
                overlap_min = overlap_top;
                direction   = 2;
            }
            if (overlap_bottom < overlap_min) {
                overlap_min = overlap_bottom;
                direction   = 3;
            }

            // resolution
            switch (direction) {
            case 0:
                rect1.x -= overlap_left;
                rect2.x += overlap_left;
                break;
            case 1:
                rect1.x += overlap_right;
                rect2.x -= overlap_right;
                break;
            case 2:
                rect1.y -= overlap_top;
                rect2.y += overlap_top;
                break;
            case 3:
                rect1.y += overlap_bottom;
                rect2.y -= overlap_bottom;
                break;
            }
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        DrawRectangleRec(rect1, rect1_color);
        DrawRectangleRec(rect2, rect2_color);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
