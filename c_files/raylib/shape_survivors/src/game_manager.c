#include "game_manager.h"
#include "settings.h"
#include "systems.h"
#include <assert.h>
#include <math.h>

void game_manager_init(GameManager *gm) {
  assert(gm);

  player_init(&gm->player);

  gm->camera =
      (Camera2D){.offset = (Vector2){BASE_WIDTH / 2.0f, BASE_HEIGHT / 2.0f},
                 .target = (Vector2){0, 0},
                 .rotation = 0.0f,
                 .zoom = 1.0f};
}

void game_manager_draw(const GameManager *gm) {
  assert(gm);

  BeginMode2D(gm->camera);

  system_draw_background_grid();

  player_draw(&gm->player);

  EndMode2D();
}

static void game_manager_update_camera(GameManager *gm) {
  assert(gm);

  const float half_w = BASE_WIDTH / 2.0f;
  const float half_h = BASE_HEIGHT / 2.0f;

  gm->camera.target.x =
      fminf(half_w, fminf(gm->player.position.x, MAP_SIZE - half_w));
  gm->camera.target.y =
      fminf(half_h, fminf(gm->player.position.y, MAP_SIZE - half_h));
}

void game_manager_update(GameManager *gm, const float dt) {
  assert(gm);

  // update entities
  player_update(&gm->player, dt);

  game_manager_update_camera(gm);
}
