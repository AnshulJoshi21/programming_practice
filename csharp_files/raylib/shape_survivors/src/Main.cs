using Raylib_cs;
using static Raylib_cs.Raylib;
using static MyGame.Settings;

class Program
{
    static void Main()
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "test");
        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(Color.RayWhite);
            EndDrawing();
        }

        CloseWindow();

    }
}
