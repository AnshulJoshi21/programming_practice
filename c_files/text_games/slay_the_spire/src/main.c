#include <assert.h>
#include <stdio.h>

#define INITIAL_ENERGY 3

typedef struct Player {
    int energy;
} Player;

int get_input(void) {}

typedef enum {
    GAME_STATE_TITLE,
    GAME_STATE_CHARACTER_SELECTION,
    GAME_STATE_EXIT,
} GameState;

typedef struct {
    GameState current_state;
} GameManager;

void game_manager_init(GameManager* gm) {
    assert(gm);
    gm->current_state = GAME_STATE_TITLE;
}

void game_manager_update(GameManager* gm) {
    assert(gm);

    switch (gm->current_state) {
        case GAME_STATE_TITLE:
            break;

        case GAME_STATE_CHARACTER_SELECTION:
            break;

        case GAME_STATE_EXIT:
            break;
    }
}

void game_manager_draw(GameManager* gm) {
    assert(gm);

    switch (gm->current_state) {
        case GAME_STATE_TITLE: {
            printf("1). Play\n");
            printf("2). Card Library\n");
            printf("3). Relic Collection\n");
            printf("4). Statistics\n");
            printf("5). Quit\n");
        } break;

        case GAME_STATE_CHARACTER_SELECTION:
            break;

        case GAME_STATE_EXIT:
            break;
    }
}

void game_manager_run(GameManager* gm) {
    assert(gm);

    while (1) {
        game_manager_update(gm);
        game_manager_draw(gm);
    }
}

int main(void) {
    GameManager game_manager;
    game_manager_init(&game_manager);

    game_manager_run(&game_manager);

    return 0;
}
