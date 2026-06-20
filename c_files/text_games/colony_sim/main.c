#include <assert.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 32
#define BUFFER_SIZE 128

static const int MAX_SETTLERS = 16;
static const int MAX_LOG      = 8; // log lines printed per tick

static const int HUNGER_RATE  = 8;  // hunger gained per tick
static const int FORAGE_YIELD = 15; // food gained per forage action
static const int EAT_AMOUNT   = 30; // food eaten per eat action
static const int HUNGER_DEATH = 100;

static const int MAX_FOOD_STORAGE = 500;

static const int PREDATOR_EVENT_INTERVAL = 7; // 7 days

typedef enum {
    JOB_IDLE,
    JOB_FORAGE,
    JOB_EAT,
} Job;

typedef struct Settler {
    char name[NAME_SIZE];
    int  hunger; // 0-100, 100 = dead;
    int  alive;
    Job  current_job;
} Settler;

typedef struct World {
    int food_stored;
} World;

static int current_day    = 0;
static int predator_event = 0;

void log_event(const char* msg) {
    assert(msg);

    printf("[Day %3d] %s\n", current_day, msg);
}

int settler_is_hungry(Settler* settler) {
    assert(settler);

    return (settler->hunger > HUNGER_DEATH / 2);
}

Job choose_job(Settler* settler, World* world) {
    assert(settler);
    assert(world);

    if (settler_is_hungry(settler) && world->food_stored > 0)
        return JOB_EAT;

    if (!predator_event) {
        if (world->food_stored < MAX_FOOD_STORAGE - FORAGE_YIELD)
            return JOB_FORAGE;
    }
    return JOB_IDLE;
}

void execute_job(Settler* settler, World* world) {
    assert(settler);
    assert(world);

    char buf[BUFFER_SIZE];

    switch (settler->current_job) {
        case JOB_IDLE:
            break;
        case JOB_EAT:
            if (world->food_stored <= 0) {
                snprintf(
                    buf, BUFFER_SIZE, "%s tried to eat but food storage is EMPTY.", settler->name);
                log_event(buf);
                break;
            }

            world->food_stored -= 1;
            settler->hunger -= EAT_AMOUNT;

            if (settler->hunger < 0)
                settler->hunger = 0;

            snprintf(buf,
                     BUFFER_SIZE,
                     "%s eats. Hunger: %d, Food left: %d.",
                     settler->name,
                     settler->hunger,
                     world->food_stored);
            log_event(buf);
            break;

        case JOB_FORAGE:
            if (world->food_stored < MAX_FOOD_STORAGE - FORAGE_YIELD) {
                world->food_stored += FORAGE_YIELD;
                snprintf(buf,
                         BUFFER_SIZE,
                         "%s forages. Food found: %d, Storage: %d",
                         settler->name,
                         FORAGE_YIELD,
                         world->food_stored);
                log_event(buf);
                break;
            } else {
                snprintf(buf,
                         BUFFER_SIZE,
                         "%s forages. Food found: %d, Storage: %d(full), Food discarded.",
                         settler->name,
                         FORAGE_YIELD,
                         world->food_stored);
                log_event(buf);
            }
            break;

        default:
            break;
    }
}

// one full tick for 1 settler
void settler_tick(Settler* settler, World* world) {
    assert(settler);
    assert(world);

    if (!settler->alive)
        return;

    char buf[BUFFER_SIZE];

    settler->hunger += HUNGER_RATE;

    if (settler->hunger >= HUNGER_DEATH) {
        settler->alive = 0;
        snprintf(buf, BUFFER_SIZE, "%s has STARVED TO DEATH.", settler->name);
        log_event(buf);
        return;
    }

    settler->current_job = choose_job(settler, world);
    execute_job(settler, world);
}

int main(void) {
    World world = {.food_stored = 100};

    Settler settlers[MAX_SETTLERS];
    int     settler_count = MAX_SETTLERS;

    for (int i = 0; i < MAX_SETTLERS; i++) {
        snprintf(settlers[i].name, NAME_SIZE, "Anon%d", i + 1);
        settlers[i].hunger      = 20;
        settlers[i].alive       = 1;
        settlers[i].current_job = JOB_IDLE;
    }

    printf("=== Colony Sim ===\n");
    printf("Starting Food: %d\n", world.food_stored);

    for (int day = 0; day < 60; day++) {
        current_day    = day;
        predator_event = (current_day % PREDATOR_EVENT_INTERVAL == 0 && current_day != 0) ? 1 : 0;

        if (predator_event)
            log_event("Predator roams the forest.");

        int anyone_alive = 0;
        for (int i = 0; i < settler_count; i++) {
            settler_tick(&settlers[i], &world);
            if (settlers[i].alive)
                anyone_alive = 1;
            else
                settler_count--;
        }

        if (!anyone_alive) {
            log_event("Colony is dead. Simulation ends.");
            break;
        }
    }

    printf("=== End of Simulation ===\n");
    printf("Food Remaining: %d\n", world.food_stored);

    return 0;
}
