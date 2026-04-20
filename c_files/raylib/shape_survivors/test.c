// #include "src/utils.h"

#include <raylib.h>

void draw_progress_bar(const int max, int current, const Rectangle rect, const float thickness,
                       const Color background, const Color outline, const Color bar) {
    //
    DrawRectangleRec(rect, background);

    float progress = ((float) current / (float) max) * rect.width;
    DrawRectangleRec((Rectangle){rect.x, rect.y, progress, rect.height}, bar);

    DrawRectangleLinesEx(rect, thickness, outline);
}

int main(void) {
    const int BASE_WIDTH = 800;
    const int BASE_HEIGHT = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    const RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    SetTextureFilter(canvas.texture, TEXTURE_FILTER_BILINEAR);

    int choices = 3;
    float gap = 20;
    float margin = 100;
    float width = (BASE_WIDTH - (margin * 2) - (gap * (choices - 1))) / choices;
    float height = 150.0f;
    float y = (BASE_HEIGHT - height) / 2.0f;
    float thickness = 5.0f;
    Color color = BLACK;

    const int max = 100;
    int current = 0;

    const float w = 500.0f;
    const float h = 40.0f;
    const Rectangle progress_bar =
        (Rectangle){(GetScreenWidth() - w) / 2.0f, (GetScreenHeight() - h) / 2.0f, w, h};

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP))
            current++;
        if (IsKeyPressed(KEY_DOWN))
            current--;

        if (current > max)
            current = max;
        if (current < 0)
            current = 0;

        BeginTextureMode(canvas);

        // for (int i = 0; i < choices; i++) {
        //     float x = margin + i * (width + gap);

        //     DrawRectangleLinesEx((Rectangle){x, y, width, height}, thickness, color);

        //     center_and_draw_text(ORIGIN_TOP_LEFT, "Name", (Rectangle){x, y, width, height
        //     / 2.0f},
        //                          30.0f, 2.0f, color);
        //     center_and_draw_text(ORIGIN_TOP_LEFT, "Description",
        //                          (Rectangle){x, y + height / 2.0f, width, height / 2.0f}, 20.0f,
        //                          2.0f, color);
        // }

        draw_progress_bar(max, current, progress_bar, 5.0f, LIGHTGRAY, BLACK, GRAY);

        EndTextureMode();

        const Rectangle source = (Rectangle){0, 0, canvas.texture.width, -canvas.texture.height};
        const Rectangle dest = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
