#include <raylib.h>

static const int BASE_WIDTH  = 800;
static const int BASE_HEIGHT = 600;

int main(void) {
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    float width  = 300.0f;
    float height = 150.0f;

    Rectangle rect = (Rectangle){
        BASE_WIDTH / 2.0f - width / 2.0f, BASE_HEIGHT / 2.0f - height / 2.0f, width, height};
    Color color     = BLUE;
    float roundness = 1.0f;
    int   segments  = 5;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP)) {
            roundness += 0.1f;
            if (roundness > 1.0f)
                roundness = 1.0f;
        } else if (IsKeyPressed(KEY_DOWN)) {
            roundness -= 0.1f;
            if (roundness < 0.0f)
                roundness = 0.0f;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRounded(rect, roundness, segments, color);

        DrawText(TextFormat("Roundness: %0.2f", roundness), 50, 30, 30, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
