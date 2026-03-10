#include <stdio.h>
#include <stdlib.h>

static const int PLAYER_MAX_HP = 100;

typedef struct Entity
{
    const char *name;
    int damage;
    int max_hp;
    int hp;

} Entity;

static void entity_combat(Entity *player, Entity *enemy)
{
    assert(player && enemy);

    enemy->hp -= player->damage;
    player->hp -= enemy->damage;
}

int main(void)
{

    Entity player = (Entity){.name    = "Player",
                             .damage  = 5,
                             .defense = 5,
                             .max_hp  = PLAYER_MAX_HP,
                             .hp      = PLAYER_MAX_HP};

    Entity enemy = (Entity){
        .name = "Enemy", .damage = 2, .defense = 5, .max_hp = 10, .hp = 10};

    while (player.hp > 0) {
        system("clear");

        printf("Player: %d + %d/%d\n", player.hp, player.defense,
               player.max_hp);
        printf("Enemy: %d + %d/%d\n", enemy.hp, enemy.defense, enemy.max_hp);
        printf("\n");

        printf("Combat: \n\n");
        entity_combat(&player, &enemy);

        if (enemy.hp <= 0) {
            enemy = (Entity){.name    = "Enemy",
                             .damage  = 2,
                             .defense = 5,
                             .max_hp  = 10,
                             .hp      = 10};
        }
    }

    return 0;
}
