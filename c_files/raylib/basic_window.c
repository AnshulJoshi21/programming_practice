#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//-- MAIN ---------------------------------------//
int main(void)
{
    // 1.INIT
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 2.UPDATE

        // 3.DRAW
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
