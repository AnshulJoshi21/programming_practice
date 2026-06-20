#include "game_manager.h"
#include "settings.h"
#include "settler.h"
#include <assert.h>
#include <stdio.h>

#define BUFFER_SIZE 128

void settler_init(Settler* settler, const int index) {
    assert(settler);

    snprintf(settler->name, sizeof(settler->name), "Settler%d", index);
    settler->hunger        = 80; // 0-100
    settler->alive         = 1;
    settler->current_state = SETTLER_STATE_IDLE;
    settler->current_job   = SETTLER_JOB_UNEMPLOYED;
}

int settler_is_hungry(const Settler* settler) {
    assert(settler);

    return (settler->hunger > HUNGER_DEATH / 2) ? 1 : 0;
}

void settler_set(Settler* settler, const GameManager* gm) {
    assert(settler);
    assert(gm);

    char buffer[BUFFER_SIZE];

    if (gm->predator_event) {
        settler->current_state = SETTLER_STATE_HIDING;
        settler->current_job   = SETTLER_JOB_UNEMPLOYED;
        return;
    }

    if (settler_is_hungry(settler) && gm->consumable_count > 0) {
        settler->current_state = SETTLER_STATE_EATING;
        settler->current_job   = SETTLER_JOB_UNEMPLOYED;
    }

    settler->current_job   = SETTLER_JOB_UNEMPLOYED;
    settler->current_state = SETTLER_STATE_IDLE;
}

void settler_execute(Settler* settler, GameManager* gm) {
    assert(settler);
    assert(gm);

    char buffer[BUFFER_SIZE];

    switch (settler->current_job) {}
}
