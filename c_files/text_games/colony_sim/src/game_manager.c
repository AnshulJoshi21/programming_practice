#include "game_manager.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void game_manager_init(GameManager* gm) {
    assert(gm);

    gm->current_day    = 0;
    gm->predator_event = 0;

    // INVENTORY
    memset(gm->inventory, 0, sizeof(gm->inventory));

    // SETTLERS
    gm->settler_count = MAX_SETTLERS;
    for (int i = 0; i < gm->settler_count; i++) {
        char buffer[128];

        settler_init(&gm->settlers[i], i);
    }

    memset(gm->job_count, 0, sizeof(gm->job_count));
    gm->job_count[SETTLER_JOB_UNEMPLOYED] = gm->settler_count;
}

void game_manager_log_event(const GameManager* gm, const char* msg) {
    assert(gm);

    printf("[Day %3d] %s\n", gm->current_day, msg);
}
