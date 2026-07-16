#ifndef UPGRADE_MANAGER_H
#define UPGRADE_MANAGER_H

#include "player.h"

#define MAX_CHOICES 3

typedef enum UpgradeType {
    UPGRADE_TYPE_NONE = 0,

    UPGRADE_TYPE_PLAYER_SPEED,
    UPGRADE_TYPE_PLAYER_HEALTH,

    UPGRADE_TYPE_BULLET_SPEED,
    UPGRADE_TYPE_BULLET_DAMAGE,
    UPGRADE_TYPE_BULLET_RANGE,

    UPGRADE_TYPE_MAX
} UpgradeType;

typedef struct Upgrade {
    UpgradeType type;
    const char* name;
    const char* description;
    float       value;
} Upgrade;

typedef struct UpgradeManager {
    Player*  player;
    Upgrade* selected_upgrade;

    Upgrade choices[MAX_CHOICES];

} UpgradeManager;

void upgrade_manager_init(UpgradeManager* um, Player* player);
void upgrade_manager_update(UpgradeManager* um);
void upgrade_manager_draw(UpgradeManager* um, const Vector2 world_mouse);

#endif // UPGRADE_MANAGER_H
