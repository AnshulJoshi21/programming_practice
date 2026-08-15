#include <assert.h>
#include <math.h>
#include <raylib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    SetTargetFPS(60);

    RenderTexture canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    while (!WindowShouldClose()) {
        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
        EndTextureMode();

        const float   scale  = fminf((float) GetScreenWidth() / (float) SCREEN_WIDTH,
                                  (float) GetScreenHeight() / (float) SCREEN_HEIGHT);
        const Vector2 offset = (Vector2){(GetScreenWidth() - (SCREEN_WIDTH * scale)) / 2.0f,
                                         (GetScreenHeight() - (SCREEN_HEIGHT * scale)) / 2.0f};

        const Rectangle source = (Rectangle){0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT};
        const Rectangle dest
            = (Rectangle){offset.x, offset.y, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    CloseWindow();

    return 0;
}
