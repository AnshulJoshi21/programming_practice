#include <raylib.h>

int
main(void)
{
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;
    const char SCREEN_TITLE[] = "SIMPLE SPACE DEFENSE";
    const Color SCREEN_BACKGROUND = LIGHTGRAY;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    const char* spritesheet_xml_path = "/home/anonymous/Downloads/programming_practice/c_files/raylib/"
                                   "simple_space/assets/simpleSpace_sheet.xml";

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);
        EndDrawing();
    }

    return 0;
}
