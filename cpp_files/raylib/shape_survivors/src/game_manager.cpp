#include "collision_manager.hpp"
#include "game_manager.hpp"
#include "settings.hpp"
#include "ui.hpp"
#include <algorithm>
#include <cmath>

void draw_background_grid(void)
{
    const float thickness = 2.0f;
    const Color color = LIGHTGRAY;
    const float block_size = 400.0f;

    for (float x = 0; x < MAP_SIZE; x += block_size) {
        DrawLineEx({x, 0}, {x, MAP_SIZE}, thickness, color);
    }
    for (float y = 0; y < MAP_SIZE; y += block_size) {
        DrawLineEx({0, y}, {MAP_SIZE, y}, thickness, color);
    }
}

GameManager::GameManager()
    : camera({.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
              .target = {0, 0},
              .rotation = 0.0f,
              .zoom = 1.0f})
{
}

void GameManager::draw(void) const
{
    BeginMode2D(camera);

    draw_background_grid();

    drop_manager.draw();
    bullet_manager.draw();
    player.draw();
    enemy_manager.draw();

    EndMode2D();

    ui_player_xp_bar(player);
}

void GameManager::camera_update()
{
    const float half_w = GetScreenWidth() / 2.0f;
    const float half_h = GetScreenHeight() / 2.0f;

    camera.target.x = std::max(half_w,
                               std::min(player.position.x, MAP_SIZE - half_w));
    camera.target.y = std::max(half_h,
                               std::min(player.position.y, MAP_SIZE - half_h));
}

Vector2 GameManager::get_player_target(void)
{
    float min_distance = MAP_SIZE;
    Vector2 target = {0, 0};

    for (const Enemy &enemy : enemy_manager.enemies) {
        const float dx = enemy.position.x - player.position.x;
        const float dy = enemy.position.y - player.position.y;
        const float distance = std::sqrt((dx * dx) + (dy * dy));
        if (distance < min_distance) {
            min_distance = distance;
            target = {enemy.position.x, enemy.position.y};
        }
    }

    return target;
}

void GameManager::update(const float dt)
{
    // entity updates
    player.update(dt);
    enemy_manager.update(dt, {player.position.x, player.position.y},
                         [&](const DropType type, const Vector2 start_pos) {
                             drop_manager.spawn(type, start_pos);
                         });
    bullet_manager.update(dt);
    drop_manager.update();

    camera_update();

    // spawn

    if (player.bullet_timer.tick())
        bullet_manager.spawn(player.bullet_config,
                             {player.position.x, player.position.y},
                             get_player_target());

    // collisions
    player_colision_enemy(player, enemy_manager);
    player_colision_drop(player, drop_manager);
    bullet_colision_enemy(bullet_manager, enemy_manager);
    enemy_colision_enemy(enemy_manager);
}
