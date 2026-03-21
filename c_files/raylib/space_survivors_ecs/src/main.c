#include "../include/game_manager.h"
#include "../include/settings.h"

#include <raylib.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    const Texture2D spritesheet = LoadTexture("assets/sheet.png");
    const Texture2D background  = LoadTexture("assets/backgrounds/purple.png");

    GameManager game_manager;
    game_manager_init(&game_manager);

    while (!WindowShouldClose()) {

        const float dt = GetFrameTime();
        const Vector2 mouse_pos_world =
            GetScreenToWorld2D(GetMousePosition(), game_manager.camera);

        game_manager_update(&game_manager, dt, mouse_pos_world);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        game_manager_draw(&game_manager, background, spritesheet);

        EndDrawing();
    }

    UnloadTexture(spritesheet);
    UnloadTexture(background);

    CloseWindow();

    return 0;
}
