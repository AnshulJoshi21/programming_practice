#include "player.hpp"
#include "settings.hpp"
#include "systems.hpp"
#include "utils.hpp"
#include <raymath.h>

static constexpr float PLAYER_SIZE                  = 40.0f;
static constexpr int   PLAYER_MAX_HEALTH            = 100;
static constexpr float PLAYER_MAX_HIT_TIMER         = 0.2f;
static constexpr float PLAYER_BULLET_SPAWN_INTERVAL = 1.0f;

Player::Player()
    : level({
          .current = 1,
          .pending = 0,
      }),
      xp({
          .current = 0,
          .next    = Systems::get_xp_next(level),
      }),
      position({
          .x = MAP_SIZE / 2.0f,
          .y = MAP_SIZE / 2.0f,
      }),
      rect({
          .width  = PLAYER_SIZE,
          .height = PLAYER_SIZE,
      }),
      rotation({.angle = 0.0f}), color({.tint = BLUE}), text({
                                                            .text      = "P",
                                                            .font_size = 20.0f,
                                                            .spacing   = 0.0f,
                                                            .tint      = WHITE,
                                                        }),
      movement({
          .speed     = 120.0,
          .direction = {0, 0},
      }),
      health({
          .max     = PLAYER_MAX_HEALTH,
          .current = PLAYER_MAX_HEALTH,
      }),
      animation({
          .max_hit_timer = PLAYER_MAX_HIT_TIMER,
          .hit_timer     = 0.0,
      }),
      bullet_timer({
          .elapsed  = static_cast<float>(GetTime()),
          .interval = PLAYER_BULLET_SPAWN_INTERVAL,
      }),
      bullet_config({
          .damage   = 1,
          .speed    = 300.0,
          .lifetime = 1.0,
      })

{}

void Player::handle_input(void) {
    movement.direction.x
        = static_cast<float>(IsKeyDown(KEY_D)) - static_cast<float>(IsKeyDown(KEY_A));
    movement.direction.y
        = static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W));
    movement.direction = Vector2Normalize(movement.direction);
}

void Player::update(const float dt) {
    Systems::update_xp(level, xp);
    handle_input();
    Systems::move(position, movement, dt);
    Systems::set_bounds(position, rect.width / 2.0, rect.height / 2.0, {0, 0, MAP_SIZE, MAP_SIZE});
    Systems::update_hit_timer(animation, dt);
    Systems::update_health(health);
}

void Player::draw(void) const {
    Systems::draw_rect(position, rotation, rect, color, animation);
    Utils::center_and_draw_text(
        Utils::OriginType::CENTER, {position.x, position.y, rect.width, rect.height}, text);
}
