#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

typedef enum { STATE_MENU, STATE_OPTIONS, STATE_PLAYING } GameState;

int main() {
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "raygui - Simple Game Menu");

  GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

  GameState currentState = STATE_MENU;
  float musicVolume = 0.5f;
  bool showExitPopup = false;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update Logic (Check for Escape to return to menu)
    if (IsKeyPressed(KEY_ESCAPE) && currentState != STATE_MENU) {
      currentState = STATE_MENU;
    }

    // Draw Logic
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    switch (currentState) {
    case STATE_MENU: {
      // Draw a title
      DrawText("MY AWESOME GAME", screenWidth / 2 - 150, 100, 30, DARKGRAY);

      // Menu Buttons
      if (GuiButton((Rectangle){screenWidth / 2 - 60, 200, 120, 40},
                    "START GAME")) {
        currentState = STATE_PLAYING;
      }

      if (GuiButton((Rectangle){screenWidth / 2 - 60, 250, 120, 40},
                    "OPTIONS")) {
        currentState = STATE_OPTIONS;
      }

      if (GuiButton((Rectangle){screenWidth / 2 - 60, 300, 120, 40}, "EXIT")) {
        showExitPopup = true;
      }
    } break;

    case STATE_OPTIONS: {
      DrawText("OPTIONS", screenWidth / 2 - 50, 100, 20, GRAY);

      // Volume Slider
      GuiSliderBar((Rectangle){screenWidth / 2 - 60, 200, 120, 20}, "VOL",
                   TextFormat("%i%%", (int)(musicVolume * 100)), &musicVolume,
                   0, 1);

      if (GuiButton((Rectangle){screenWidth / 2 - 60, 300, 120, 40}, "BACK")) {
        currentState = STATE_MENU;
      }
    } break;

    case STATE_PLAYING: {
      DrawText("THE GAME IS RUNNING", 250, 200, 20, MAROON);
      DrawText("Press ESC to return to Menu", 250, 230, 10, DARKGRAY);
    } break;
    }

    // Global Overlay (e.g., Exit Confirmation Window)
    if (showExitPopup) {
      int result = GuiMessageBox(
          (Rectangle){screenWidth / 2 - 125, screenHeight / 2 - 50, 250, 100},
          "#159# Closing App", "Do you really want to exit?", "Yes;No");

      if (result == 1)
        break; // "Yes" clicked
      if (result == 2 || result == 0)
        showExitPopup = false; // "No" or "X" clicked
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
