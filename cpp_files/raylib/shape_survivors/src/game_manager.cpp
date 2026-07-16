#include "game_manager.hpp"
#include "settings.hpp"
#include "systems.hpp"
#include <algorithm>
#include <cmath>

GameManager::GameManager()
    : state(GameState::RUNNING),
      collision_manager(player, enemy_manager, bullet_manager, drop_manager),
      ui_manager(player, enemy_manager), upgrade_manager(player),
      camera({.offset   = {BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
              .target   = {0, 0},
              .rotation = 0.0f,
              .zoom     = 1.0f}) {}

void GameManager::update_camera(void) {
    const float half_w = BASE_WIDTH / 2.0f;
    const float half_h = BASE_HEIGHT / 2.0f;

    camera.target.x = std::max(half_w, std::min(player.position.x, MAP_SIZE - half_w));
    camera.target.y = std::max(half_h, std::min(player.position.y, MAP_SIZE - half_h));
}

Vector2 GameManager::get_player_target(void) {
    float   min_distance = MAP_SIZE * MAP_SIZE;
    Vector2 target       = {0, 0};

    for (const Enemy& enemy : enemy_manager.enemies) {
        const float dx       = enemy.position.x - player.position.x;
        const float dy       = enemy.position.y - player.position.y;
        const float distance = std::sqrt((dx * dx) + (dy * dy));
        if (distance < min_distance) {
            min_distance = distance;
            target       = {enemy.position.x, enemy.position.y};
        }
    }

    return target;
}

void GameManager::update(const float dt) {
    switch (state) {
        case GameState::TITLE:
            break;

        case GameState::RUNNING: {
            player.update(dt);
            enemy_manager.update(dt, {player.position.x, player.position.y}, drop_manager);
            bullet_manager.update(dt);
            drop_manager.update();
            update_camera();

            // spawn
            // player bullet
            if (player.bullet_timer.tick()) {
                bullet_manager.spawn(player.bullet_config,
                                     {player.position.x, player.position.y},
                                     get_player_target());
            }

            // collision
            collision_manager.update();

            // level up
            if (player.level.pending > 0) {
                player.level.pending -= 1;
                upgrade_manager.gen_choices();
                state = GameState::UPGRADE;
            }

        } break;

        case GameState::UPGRADE: {
            upgrade_manager.update();
            if (upgrade_manager.choices.empty()
                && upgrade_manager.selected_upgrade == UpgradeType::NONE)
                //
                state = GameState::RUNNING;

        } break;

        case GameState::EXIT:
            break;
    }
}

void GameManager::draw(const Vector2& world_mouse) {
    switch (state) {
        case GameState::TITLE:
            break;

        case GameState::RUNNING: {
            BeginMode2D(camera);

            Systems::draw_background_grid();
            drop_manager.draw();
            bullet_manager.draw();
            player.draw();
            enemy_manager.draw();

            ui_manager.draw_enemy_hp_bar();
            ui_manager.draw_player_hp_bar();

            EndMode2D();

            ui_manager.draw_player_xp_bar();

        } break;

        case GameState::UPGRADE: {
            upgrade_manager.draw(world_mouse);
        } break;

        case GameState::EXIT:
            break;
    }
}
