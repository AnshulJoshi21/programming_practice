#include "../settings.hpp"
#include "../systems.hpp"
#include "../utils.hpp"
#include "enemy.hpp"
#include <cmath>
#include <raymath.h>

static Color get_random_dark_color(void)
{
    const int random_num = GetRandomValue(1, 5);
    Color random_color;

    switch (random_num) {
    case 1:
        random_color = DARKBLUE;
        break;
    case 2:
        random_color = DARKBROWN;
        break;
    case 3:
        random_color = DARKGRAY;
        break;
    case 4:
        random_color = DARKGREEN;
        break;
    case 5:
        random_color = DARKPURPLE;
        break;
    default:
        random_color = DARKBLUE;
        break;
    }

    return random_color;
}

Enemy::Enemy(const Vector2 target_pos)
    : rect({.width = 45.0f, .height = 45.0f}), rotation({.angle = 0.0f}),
      color({.tint = get_random_dark_color()}), text({.text = "E"}),
      move({.speed = 100.0f, .direction = {0, 0}}),
      health({.max_hp = 5, .hp = 5}), damage({.amount = GetRandomValue(0, 5)}),
      animation({.hit_timer = 0.0f})
{
    const float random_angle = random_float(0, 2 * PI);
    const float random_distance = random_float(GetScreenWidth() / 2.0f + 100.0f,
                                               GetScreenWidth() / 2.0f +
                                                   200.0f);

    position = {
        std::cos(random_angle) * random_distance + target_pos.x,
        std::sin(random_angle) * random_distance + target_pos.y,
    };
}

void Enemy::draw(void) const
{
    system_draw_rect(position, rect, rotation, color, animation);
    system_draw_centered_text(position, rect.width, rect.height, text);
}

void Enemy::update(const float dt, const Vector2 target_pos)
{
    system_set_direction(position, move, target_pos);
    system_move(position, move, dt);
    system_set_bounds(position, rect.width / 2.0f, rect.height / 2.0f,
                      {0, 0, MAP_SIZE, MAP_SIZE});
    system_update_hit_timer(animation, dt);
}
