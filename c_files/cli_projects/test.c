#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static inline float random_uniform(float min, float max)
{
    return (min + (rand() / (float)RAND_MAX) * (max - min));
}

typedef struct Entity
{
    int id;
    const char *name;
    float min_damage;
    float max_damage;
    float max_health;
    float health;

} Entity;

bool entity_is_alive(Entity *e) { return e->health > 0; }

void entity_print_health(Entity *e)
{
    if (e->health <= 0.0f)
        e->health = 0.0f;

    printf("%s HP: %.2lf\n", e->name, e->health);
}

void entity_attack(Entity *e, Entity *target)
{
    assert(e && target);

    float damage = random_uniform(e->min_damage, e->max_damage);

    target->health -= damage;
    printf("%s attacks %s for %.2lf damage\n", e->name, target->name, damage);
}

int main(void)
{
    srand(time(NULL));

    int sleep_interval = 1; // in seconds

    Entity player = (Entity){.id         = 0,
                             .name       = "player",
                             .min_damage = 2,
                             .max_damage = 10,
                             .max_health = 100.0f,
                             .health     = player.max_health};

    Entity goblin = (Entity){.id         = 1,
                             .name       = "goblin",
                             .min_damage = 1,
                             .max_damage = 5,
                             .max_health = 10.0f,
                             .health     = goblin.max_health};

    while (entity_is_alive(&player)) {
        system("clear");

        entity_print_health(&player);
        entity_attack(&player, &goblin);
        printf("\n");

        entity_print_health(&goblin);
        entity_attack(&goblin, &player);
        printf("\n");

        if (!entity_is_alive(&goblin)) {
            printf("%s is dead\n", goblin.name);

            goblin = (Entity){.id         = 1,
                              .name       = "goblin",
                              .min_damage = 1,
                              .max_damage = 5,
                              .max_health = 10.0f,
                              .health     = goblin.max_health};
        }

        sleep(sleep_interval);
    }

    system("clear");
    printf("\n");
    entity_print_health(&player);
    printf("%s is dead\n", player.name);

    return 0;
}
