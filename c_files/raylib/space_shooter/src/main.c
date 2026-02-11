#include "../include/game_manager.h"
#include "../include/settings.h"

#include <assert.h>
#include <raylib.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    const Texture2D spritesheet = LoadTexture("assets/spritesheet/sheet.png");
    const Texture2D background_texture =
        LoadTexture("assets/backgrounds/black.png");

    assert(spritesheet.id != 0);
    assert(background_texture.id != 0);

    GameManager gm;
    gm_init(&gm, spritesheet, background_texture);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();
        Vector2 mouse_pos_world =
            GetScreenToWorld2D(GetMousePosition(), gm.camera);

        gm_update(&gm, dt, mouse_pos_world);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        gm_draw(&gm);

        EndDrawing();
    }

    UnloadTexture(spritesheet);
    UnloadTexture(background_texture);

    CloseWindow();

    return 0;
}
