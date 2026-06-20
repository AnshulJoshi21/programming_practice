#pragma once

#include "resources.h"
#include "settings.h"
#include "settler.h"

typedef struct GameManager {
    int current_day;
    int predator_event;
    int inventory[RESOURCE_MAX];
    int consumable_count;

    Settler settlers[MAX_SETTLERS];
    int     settler_count;
    int     job_count[SETTLER_JOB_MAX];
} GameManager;

void game_manager_init(GameManager* gm);
void game_manager_log_event(const GameManager* gm, const char* msg);
