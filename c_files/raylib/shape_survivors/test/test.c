#include <raylib.h>

#define BASE_WIDTH 800
#define BASE_HEIGHT 600

int main(void) {
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    const float height = 150.0f;
    const float margin = 100.0f;
    const float gap    = 50.0f;

    const float total_width = BASE_WIDTH - margin * 2;
    const float width       = (total_width - (gap * 2)) / 3;

    const float thickness = 10.0f;

    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < 3; i++) {
            float x = (width + gap) * i + margin;
            float y = BASE_HEIGHT / 2.0f - height / 2.0f;

            Rectangle rect = (Rectangle){x, y, width, height};

            Color color = (CheckCollisionPointRec(mouse_pos, rect)) ? RED : BLACK;
            DrawRectangleLinesEx(rect, thickness, color);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
