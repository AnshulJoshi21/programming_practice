#pragma once

#include "player.hpp"
#include <functional>
#include <string>

static const int MAX_CHOICES = 3;

enum class UpgradeType {
    NONE,

    PLAYER_SPEED,
    PLAYER_MAX_HEALTH,
    PLAYER_RECOVER,

    BULLET_SPEED,
    BULLET_DAMAGE,
    BULLET_RANGE,

    COUNT
};

struct Upgrade {
    UpgradeType type;
    std::string name;
    std::string description;
    float       amount;

    std::function<void(Player&, float)> apply;
};

class UpgradeManager {
  public:
    Player player;

    std::vector<UpgradeType> choices;
    UpgradeType              selected_upgrade;

    UpgradeManager(Player& player);

    void gen_choices(void);
    void update(void);
    void draw(const Vector2& world_mouse);
};
