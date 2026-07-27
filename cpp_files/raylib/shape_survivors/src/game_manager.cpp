#include "game_manager.hpp"
#include "settings.hpp"
#include <raymath.h>

static void draw_background_grid(void) {
    const float thick      = 2.0f;
    const Color color      = LIGHTGRAY;
    const float block_size = 100.0f;

    for (float x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx({x, 0}, {x, MAP_SIZE}, thick, color);
    }
    for (float y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx({0, y}, {MAP_SIZE, y}, thick, color);
    }
}

GameManager::GameManager()
    : current_state(GameState::RUNNING),
      camera({.offset   = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
              .target   = {0, 0},
              .rotation = 0.0f,
              .zoom     = 1.0f}) {}

void GameManager::update_camera(void) {
    const float half_w = SCREEN_WIDTH / 2.0f;
    const float half_h = SCREEN_HEIGHT / 2.0f;

    camera.target.x = Clamp(player.rect.x, half_w, MAP_SIZE - half_w);
    camera.target.y = Clamp(player.rect.y, half_h, MAP_SIZE - half_h);
}

void GameManager::update(const float dt) {
    player.update(dt);
    enemy_manager.update(dt, {player.rect.x, player.rect.y});
    update_camera();
}

void GameManager::draw(const Vector2& world_mouse) const {
    BeginMode2D(camera);

    draw_background_grid();
    player.draw();
    enemy_manager.draw();

    EndMode2D();
}
