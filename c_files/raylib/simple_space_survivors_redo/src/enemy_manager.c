#include "../include/enemy_manager.h"
#include "../include/settings.h"
#include "../include/sprite_data.h"
#include "../include/utils.h"

#include <assert.h>
#include <math.h>

static const float ENEMY_SCALE_OFFSET = 1.0f;
static const float MIN_SPAWN_DISTANCE = 400.0f;

// ------ ENEMY -----------------------------
void enemy_init(Enemy *enemy, const Vector2 start_pos)
{
    assert(enemy);

    enemy->sprite_name = GetRandomValue(SPRITE_ENEMY_A, SPRITE_ENEMY_E);

    const Rectangle source = sprite_db[enemy->sprite_name];

    enemy->dest =
        (Rectangle){start_pos.x, start_pos.y, source.width * ENEMY_SCALE_OFFSET,
                    source.height * ENEMY_SCALE_OFFSET};
    enemy->origin =
        (Vector2){enemy->dest.width / 2.0f, enemy->dest.height / 2.0f};
    enemy->tint = WHITE;

    enemy->max_hp = 10.0f;
    enemy->hp     = enemy->max_hp;
}

static void enemy_rotate(Enemy *enemy, const Vector2 target_pos)
{
    assert(enemy);

    float dx = target_pos.x - enemy->dest.x;
    float dy = target_pos.y - enemy->dest.y;

    enemy->rotation = atan2f(dy, dx) * RAD2DEG + ROTATION_OFFSET;
}

static void enemy_move(Enemy *enemy, const float dt, const float speed,
                       const Vector2 target_pos)
{
    assert(enemy);

    float dx = target_pos.x - enemy->dest.x;
    float dy = target_pos.y - enemy->dest.y;

    float distance = sqrtf(dx * dx + dy * dy);
    if (distance > 0) {
        dx /= distance;
        dy /= distance;

        enemy->dest.x += dx * speed * dt;
        enemy->dest.y += dy * speed * dt;
    }
}

static void enemy_bounds(Enemy *enemy)
{
    assert(enemy);

    enemy->dest.x =
        fmaxf(enemy->dest.width / 2.0f,
              fminf(enemy->dest.x, MAP_SIZE - enemy->dest.width / 2.0f));

    enemy->dest.y =
        fmaxf(enemy->dest.height / 2.0f,
              fminf(enemy->dest.y, MAP_SIZE - enemy->dest.height / 2.0f));
}

// ------- ENEMY MANAGER ----------------------------
void enemy_manager_init(EnemyManager *em)
{
    assert(em);

    em->size = 0;

    em->speed = 150.0f;

    em->last_spawn_time = GetTime();
    em->spawn_interval  = 2.0f;
}

void enemy_manager_draw(const EnemyManager *em, const Texture2D spritesheet)
{
    assert(em);

    for (int i = 0; i < em->size; i++) {
        const Enemy *e = &em->enemy_list[i];

        const Rectangle source = sprite_db[e->sprite_name];

        DrawTexturePro(spritesheet, source, e->dest, e->origin, e->rotation,
                       e->tint);
    }
}

static void em_add_enemy(EnemyManager *em, const Vector2 target_pos)
{
    assert(em);

    // add enemy to list
    if (em->size < MAX_ENEMIES) {
        bool can_spawn = false;

        if (em->size <= 0)
            can_spawn = true;
        else {
            const float current_time = GetTime();
            if (current_time - em->last_spawn_time >= em->spawn_interval) {
                em->last_spawn_time = current_time;

                can_spawn = true;
            }
        }

        if (can_spawn) {
            float random_angle = random_uniform(0, 2 * PI);

            const Vector2 start_pos = (Vector2){
                cosf(random_angle) * MIN_SPAWN_DISTANCE + target_pos.x,
                sinf(random_angle) * MIN_SPAWN_DISTANCE + target_pos.y,
            };

            enemy_init(&em->enemy_list[em->size], start_pos);
            em->size++;
        }
    }
}

void enemy_manager_update(EnemyManager *em, const float dt,
                          const Vector2 target_pos)
{
    assert(em);

    em_add_enemy(em, target_pos);

    //
    for (int i = 0; i < em->size; i++) {
        Enemy *e = &em->enemy_list[i];

        enemy_rotate(e, target_pos);
        enemy_move(e, dt, em->speed, target_pos);
        enemy_bounds(e);

        // remove dead enemy
        if (e->hp <= 0) {
            em->enemy_list[i] = em->enemy_list[em->size - 1];
            em->size--;
            i--;
        }
    }
}
