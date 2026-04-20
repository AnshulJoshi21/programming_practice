#ifndef UPGRADE_MANAGER_H
#define UPGRADE_MANAGER_H

#include "player.h"
#define MAX_CHOICES 3

typedef enum UpgradeType {
    UPGRADE_NONE = 0,
    UPGRADE_PLAYER_HP,
    UPGRADE_PLAYER_SPEED,
    UPGRADE_BULLET_SPEED,
    UPGRADE_BULLET_DAMAGE,
    UPGRADE_BULLET_RATE,
    UPGRADE_BULLET_RANGE,
    UPGRADE_MAX

} UpgradeType;

typedef struct Upgrade {
    const char* name;
    const char* desc;

} Upgrade;

typedef struct UpgradeManager {
    UpgradeType choices[MAX_CHOICES];
    UpgradeType current_choice;

} UpgradeManager;

void upgrade_manager_init(UpgradeManager* um);
void upgrade_manager_draw(UpgradeManager* um, const Vector2 mouse_pos);
void upgrade_manager_update(UpgradeManager* um, Player* player);

#endif  // UPGRADE_MANAGER_H
