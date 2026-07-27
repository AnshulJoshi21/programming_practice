#include "player.hpp"
#include "settings.hpp"
#include "utils.hpp"
#include <raymath.h>

Player::Player()
    : rect({MAP_SIZE / 2.0f, MAP_SIZE / 2.0f, PLAYER_SIZE, PLAYER_SIZE}),
      origin({PLAYER_SIZE / 2.0f, PLAYER_SIZE / 2.0f}), rotation(0.0f), color(BLUE),
      speed(PLAYER_SPEED), direction({0, 0}), hp(PLAYER_MAX_HP), hit_timer(PLAYER_MAX_HIT_TIMER) {}

void Player::handle_input(void) {
    direction.x = static_cast<float>(IsKeyDown(KEY_D)) - static_cast<float>(IsKeyDown(KEY_A));
    direction.y = static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W));
    direction   = Vector2Normalize(direction);
}

void Player::update(const float dt) {
    handle_input();

    // move
    rect.x += direction.x * speed * dt;
    rect.y += direction.y * speed * dt;

    // set bounds
    rect.x = Clamp(rect.x, PLAYER_SIZE / 2.0f, MAP_SIZE - PLAYER_SIZE / 2.0f);
    rect.y = Clamp(rect.y, PLAYER_SIZE / 2.0f, MAP_SIZE - PLAYER_SIZE / 2.0f);
}

void Player::draw(void) const {
    DrawRectanglePro(rect, origin, rotation, color);

    utils::draw_centered_text(OriginType::CENTER, "P", rect, 20.0f, 0.0f, WHITE);
}
