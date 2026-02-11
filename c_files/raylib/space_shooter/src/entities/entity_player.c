#include "../../include/entities/entity_player.h"
#include "../../include/settings.h"
#include "../../include/sprite_data.h"
#include "../../include/systems/system_movement.h"
#include "../../include/systems/system_render.h"

#include <assert.h>
#include <raymath.h>

const float PLAYER_TEXTURE_SCALE = 0.5f;

void player_init(Player *player, const Texture2D spritesheet)
{
    assert(player);

    player->transform.position = (Vector2){MAP_SIZE / 2.0f, MAP_SIZE / 2.0f};
    player->transform.rotation = ROTATION_OFFSET;
    player->transform.scale =
        (Vector2){PLAYER_TEXTURE_SCALE, PLAYER_TEXTURE_SCALE};

    player->render.texture = spritesheet;
    player->render.source  = sprite_db[SPRITE_PLAYERSHIP1_BLUE];
    player->render.origin  = (Vector2){
        (player->render.source.width * player->transform.scale.x) / 2.0f,
        (player->render.source.height * player->transform.scale.y) / 2.0f};
    player->render.tint = WHITE;

    player->movement.speed          = 300.0f;
    player->movement.look_direction = (Vector2){0, 0};
    player->movement.move_direction = (Vector2){0, 0};
}

void player_draw(const Player *player)
{
    assert(player);

    system_render_texture(&player->transform, &player->render);
}

static void player_handle_input(Player *player)
{
    assert(player);

    player->movement.move_direction.x =
        (int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A);
    player->movement.move_direction.y =
        (int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W);

    if (Vector2Length(player->movement.move_direction) > 0.0f) {
        player->movement.move_direction =
            Vector2Normalize(player->movement.move_direction);
    }
}

void player_update(Player *player, float dt, Vector2 mouse_pos_world)
{
    assert(player);

    system_rotate_towards_target(&player->transform, &player->movement,
                                 mouse_pos_world);

    player_handle_input(player);

    system_move(&player->transform, &player->movement, dt);

    system_set_bounds(&player->transform, &player->render,
                      (Rectangle){0, 0, MAP_SIZE, MAP_SIZE});
}
