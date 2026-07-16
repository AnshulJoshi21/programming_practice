#include "upgrade_manager.hpp"

#include "components.hpp"
#include "settings.hpp"
#include "utils.hpp"
#include <algorithm>
#include <random>
#include <unordered_map>

static const std::unordered_map<UpgradeType, Upgrade> upgrade_db = {
    {UpgradeType::PLAYER_SPEED,
     {UpgradeType::PLAYER_SPEED,
      "Player Speed",
      "Increase Speed",
      10,
      [](Player& player, const float amount) { player.movement.speed += amount; }

     }},
    {UpgradeType::PLAYER_MAX_HEALTH,
     {UpgradeType::PLAYER_MAX_HEALTH,
      "Player Health",
      "Increase Max Health",
      20,
      [](Player& player, const float amount) { player.health.max += static_cast<int>(amount); }}},

    {UpgradeType::PLAYER_RECOVER,
     {UpgradeType::PLAYER_RECOVER,
      "Player Recover",
      "Recover Player Health",
      20,
      [](Player& player, const float amount) {
          player.health.current += static_cast<int>(amount);
      }}},
    {UpgradeType::BULLET_SPEED,
     {UpgradeType::BULLET_SPEED,
      "Bullet Speed",
      "Increase Bullet Speed",
      10,
      [](Player& player, const float amount) { player.bullet_config.speed += amount; }}},

    {UpgradeType::BULLET_DAMAGE,
     {UpgradeType::BULLET_DAMAGE,
      "Bullet Damage",
      "Increase Bullet Damage",
      1,
      [](Player& player, const float amount) {
          player.bullet_config.damage += static_cast<int>(amount);
      }}},

    {UpgradeType::BULLET_RANGE,
     {UpgradeType::BULLET_RANGE,
      "Bullet Range",
      "Increase Bullet Range",
      1,
      [](Player& player, const float amount) { player.bullet_config.lifetime += amount; }}}};

UpgradeManager::UpgradeManager(Player& player)
    : player(player), selected_upgrade(UpgradeType::NONE) {}

void UpgradeManager::gen_choices(void) {
    std::vector<UpgradeType> upgrade_list;

    for (int i = static_cast<int>(UpgradeType::PLAYER_SPEED);
         i < static_cast<int>(UpgradeType::COUNT);
         i++) {
        upgrade_list.push_back(static_cast<UpgradeType>(i));
    }

    std::random_device rd;
    std::mt19937       rng(rd());

    std::shuffle(upgrade_list.begin(), upgrade_list.end(), rng);
    std::copy_n(upgrade_list.begin(), MAX_CHOICES, choices.begin());
}

void UpgradeManager::update(void) {
    if (selected_upgrade == UpgradeType::NONE)
        return;

    const Upgrade& upgrade = upgrade_db.at(selected_upgrade);
    upgrade.apply(player, upgrade.amount);

    selected_upgrade = UpgradeType::NONE;
    choices.clear();
}

void UpgradeManager::draw(const Vector2& world_mouse) {
    if (choices.empty())
        return;

    const float margin       = 100.0f;
    const float gap          = 30.0f;
    const float usable_width = BASE_WIDTH - (margin * 2);
    const float rect_width   = (usable_width - (gap * (MAX_CHOICES - 1))) / MAX_CHOICES;
    const float rect_height  = 150.0f;
    const float rect_y       = BASE_HEIGHT / 2.0f - rect_height / 2.0f;

    const float line_thickness = 5.0f;

    bool hovered = false;

    for (int i = 0; i < static_cast<int>(choices.size()); i++) {
        const Rectangle rect = {(rect_width + gap) * i + margin, rect_y, rect_width, rect_height};

        hovered = CheckCollisionPointRec(world_mouse, rect);

        const Color line_color = (hovered) ? RED : BLACK;

        if (hovered and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            selected_upgrade = choices[i];
            return;

            DrawRectangleLinesEx(rect, line_thickness, line_color);

            Upgrade upgrade = upgrade_db.at(choices[i]);

            // name
            Utils ::center_and_draw_text(Utils::OriginType::TOP_LEFT,
                                         rect,
                                         Components::Text({upgrade.name, 20.0f, 2.0f, BLACK}));

            // description
            Utils::center_and_draw_text(
                Utils::OriginType::TOP_LEFT,
                {rect.x, rect.y, rect.width, rect.height + 100},
                Components::Text({upgrade.description, 10.0f, 2.0f, BLACK}));
        }
    }
}
