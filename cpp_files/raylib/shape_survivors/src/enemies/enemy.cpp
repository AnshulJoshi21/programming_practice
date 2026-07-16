#include "../settings.hpp"
#include "../systems.hpp"
#include "../utils.hpp"
#include "enemy.hpp"
#include <cmath>

static const float ENEMY_SIZE          = 45.0f;
static const int   ENEMY_MAX_HEALTH    = 5;
static const float ENEMY_MAX_HIT_TIMER = 0.1f;

static Color get_random_dark_color(void) {
    const int random_num = GetRandomValue(1, 5);

    switch (random_num) {
        case 1:
            return DARKBLUE;
        case 2:
            return DARKBROWN;
        case 3:
            return DARKGRAY;
        case 4:
            return DARKGREEN;
        case 5:
            return DARKPURPLE;
        default:
            return DARKBLUE;
    }
}

Enemy::Enemy(const Vector2& target_pos)
    : rect({
          .width  = ENEMY_SIZE,
          .height = ENEMY_SIZE,
      }),

      rotation({.angle = 0.0f}),

      color({.tint = get_random_dark_color()}),

      text({
          .text      = "E",
          .font_size = 20.0f,
          .spacing   = 0.0f,
          .tint      = WHITE,
      }),

      movement({
          .speed     = 100.0f,
          .direction = {0, 0},
      }),

      health({
          .max     = ENEMY_MAX_HEALTH,
          .current = ENEMY_MAX_HEALTH,
      }),

      damage({.current = GetRandomValue(0, 5)}),

      animation({
          .max_hit_timer = ENEMY_MAX_HIT_TIMER,
          .hit_timer     = 0.0f,
      }) {
    //
    const float random_angle    = Utils::randf(0, 2 * PI);
    const float random_distance = Utils::randf(BASE_WIDTH / 2.0f, (BASE_WIDTH / 2.0f) + 100.0f);

    position.x = std::cos(random_angle) * random_distance + target_pos.x;
    position.y = std::sin(random_angle) * random_distance + target_pos.y;
}

void Enemy::update(const float dt, const Vector2& target_pos) {
    Systems::set_direction(position, movement, target_pos);
    Systems::move(position, movement, dt);
    Systems ::set_bounds(position, rect.width / 2.0, rect.height / 2.0, {0, 0, MAP_SIZE, MAP_SIZE});
    Systems::update_hit_timer(animation, dt);
    Systems::update_health(health);
}

void Enemy::draw(void) const {
    Systems::draw_rect(position, rotation, rect, color, animation);

    Utils::center_and_draw_text(
        Utils::OriginType::CENTER, {position.x, position.y, rect.width, rect.height}, text);
}
