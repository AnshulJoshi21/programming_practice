#include "player.hpp"
#include "settings.hpp"
#include "systems.hpp"
#include <raymath.h>

Player::Player()
    : level({.current = 1, .pending_levelups = 0}),
      xp({.xp = 0, .xp_next = system_get_xp_next(level)}),
      position({.x = MAP_SIZE / 2.0f, .y = MAP_SIZE / 2.0f}),
      rect({.width = 40.0f, .height = 40.0f}), rotation({.angle = 0.0f}),
      color({.tint = BLUE}), text({.text = "P"}),
      move({.speed = 120.0f, .direction = {0, 0}}),
      health({.max_hp = 100, .hp = 100}), animation({.hit_timer = 0.0f}),
      bullet_timer(
          {.elapsed = static_cast<float>(GetTime()), .interval = 1.0f}),
      bullet_config({.damage = 1, .speed = 300.0f, .lifetime = 1.0f})
{
}

void Player::draw(void) const
{
    system_draw_rect(position, rect, rotation, color, animation);
    system_draw_centered_text(position, rect.width, rect.height, text);
}

static void handle_input(MoveComponent &move)
{
    move.direction.x = static_cast<float>(IsKeyDown(KEY_D)) -
                       static_cast<float>(IsKeyDown(KEY_A));
    move.direction.y = static_cast<float>(IsKeyDown(KEY_S)) -
                       static_cast<float>(IsKeyDown(KEY_W));

    move.direction = Vector2Normalize(move.direction);
}

void Player::update(const float dt)
{
    handle_input(move);
    system_move(position, move, dt);
    system_set_bounds(position, rect.width / 2.0f, rect.height / 2.0f,
                      {0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(animation, dt);
}
