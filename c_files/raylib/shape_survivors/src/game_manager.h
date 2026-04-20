#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game_state.h"
#include "player.h"
#include "upgrade_manager.h"

#include "bullets/bullet_manager.h"
#include "drops/drop_manager.h"
#include "enemies/enemy_manager.h"
#include "particles/particle_manager.h"

#include <raylib.h>

typedef struct GameManager {
    GameState current_state;
    BulletManager bullet_manager;
    Player player;
    EnemyManager enemy_manager;
    DropManager drop_manager;
    ParticleManager particle_manager;
    UpgradeManager upgrade_manager;

    Camera2D camera;

} GameManager;

void game_manager_init(GameManager *gm);
void game_manager_draw(GameManager *gm, const Vector2 mouse_pos);
void game_manager_update(GameManager *gm, const float dt);

#endif  // GAME_MANAGER_H
