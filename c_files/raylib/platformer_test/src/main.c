#include "game_manager.h"
#include "settings.h"
#include <assert.h>
#include <raylib.h>

int main(void)
{
    InitWindow(BASE_WIDTH, BASE_HEIGHT, "Platformer Test");

    const Texture2D sheet = LoadTexture("sheet.png");
    assert(IsTextureValid(sheet));

    GameManager game_manager;
    game_manager_init(&game_manager);

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        game_manager_update(&game_manager, dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        game_manager_draw(&game_manager, sheet);

        EndDrawing();
    }

    UnloadTexture(sheet);

    CloseWindow();

    return 0;
}
