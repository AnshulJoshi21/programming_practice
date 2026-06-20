#include "game_manager.hpp"
#include "settings.hpp"

GameManager::GameManager()
    : camera({
          .offset   = {BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
          .target   = {0, 0},
          .rotation = 0.0f,
          .zoom     = 1.0f,
      }) {}

GameManager::~GameManager() {}

void GameManager::update(const float dt) {}

static void draw_background_grid(void) {
    const float thick      = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = MAP_SIZE / 4.0f;

    for (float x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx({x, 0}, {x, MAP_SIZE}, thick, color);
    }
    for (float y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx({0, y}, {MAP_SIZE, y}, thick, color);
    }
}

void GameManager::draw(void) const {
    BeginMode2D(camera);

    draw_background_grid();

    EndMode2D();
}
