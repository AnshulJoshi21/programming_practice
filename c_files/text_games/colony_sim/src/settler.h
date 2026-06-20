#pragma once

#define NAME_SIZE 32

typedef struct GameManager GameManager;

typedef enum SettlerState {
    SETTLER_STATE_IDLE,
    SETTLER_STATE_MOVING,
    SETTLER_STATE_WORKING,
    SETTLER_STATE_EATING,
    SETTLER_STATE_SLEEPING,
    SETTLER_STATE_HIDING,
    SETTLER_STATE_DEAD,
} SettlerState;

typedef enum SettlerJob {
    SETTLER_JOB_UNEMPLOYED,
    SETTLER_JOB_FORAGER,
    SETTLER_JOB_GUARD,
    SETTLER_JOB_BUILDER,
    SETTLER_JOB_FARMER,
    SETTLER_JOB_MAX
} SettlerJob;

typedef struct Settler {
    char         name[NAME_SIZE];
    int          hunger; // 0-100
    int          alive;
    SettlerState current_state;
    SettlerJob   current_job;
} Settler;

void settler_init(Settler* settler, const int index);
int  settler_is_hungry(const Settler* settler);
void settler_set(Settler* settler, const GameManager* gm);
void settler_execute(Settler* settler, GameManager* gm);
