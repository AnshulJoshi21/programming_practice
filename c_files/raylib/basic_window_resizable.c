#include <assert.h>
#include <math.h>
#include <raylib.h>

#define BASE_WIDTH 800
#define BASE_HEIGHT 600

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "");
    SetTargetFPS(60);

    RenderTexture canvas = LoadRenderTexture(BASE_WIDTH, BASE_HEIGHT);
    assert(IsRenderTextureValid(canvas));

    while (!WindowShouldClose()) {
        BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
        EndTextureMode();

        const float   scale  = fminf((float) GetScreenWidth() / (float) BASE_WIDTH,
                                  (float) GetScreenHeight() / (float) BASE_HEIGHT);
        const Vector2 offset = (Vector2){(GetScreenWidth() - (BASE_WIDTH * scale)) / 2.0f,
                                         (GetScreenHeight() - (BASE_HEIGHT * scale)) / 2.0f};

        const Rectangle source = (Rectangle){0, 0, BASE_WIDTH, -BASE_HEIGHT};
        const Rectangle dest =
            (Rectangle){offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale};

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(canvas.texture, source, dest, (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadRenderTexture(canvas);

    return 0;
}
