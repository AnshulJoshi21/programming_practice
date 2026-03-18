#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CHOICES 10

static void clear_screen(void)
{
    printf("\033[2J"); // clear screen
    printf("\033[H");  // move cursor top left
}

static void clear_lines(uint8_t n)
{
    for (uint8_t i = 0; i < n; i++) {
        printf("\033[K"); // clear to end of line
        printf("\033[F"); // move cursor 1 line up
    }
}

typedef enum GameState {
    STATE_MAIN_MENU,
    STATE_CHARACTER_CREATION,
    STATE_TOWN,
    STATE_EXPLORATION,
    STATE_COMBAT,
    STATE_CHARACTER_SHEET,
    STATE_INVENTORY,
    STATE_QUIT

} GameState;

static void print_main_menu(void)
{
    printf("\n");
    printf("=== Simple Rpg ===\n");
    printf("\n");
    printf("1. New Game\n");
    printf("2. Quit\n");
    printf("\n");
}

static void print_input_error_msg(void)
{
    printf("invalid input, try again\n");
    sleep(1);
    clear_lines(2);
}

static void fill_choices_arr(uint8_t *choices_arr, const uint8_t choices_size)
{
    assert(choices_arr);

    for (uint8_t i = 0; i < choices_size; i++) {
        choices_arr[i] = i + 1;
    }
}

static void get_user_input(const uint8_t *choices_arr,
                           const uint8_t choices_size, uint8_t *user_input)
{
    assert(choices_arr);
    assert(user_input);

    char buffer[100];
    char *endptr;
    long value;

    while (1) {
        printf("> ");

        if (fgets(buffer, sizeof(buffer), stdin)) {
            errno = 0;
            value = strtol(buffer, &endptr, 10);

            if (errno == ERANGE) {
                print_input_error_msg();
                continue;
            }

            if (endptr == buffer) {
                print_input_error_msg();
                continue;
            }

            if (*endptr != '\n' && *endptr != '\0') {
                print_input_error_msg();
                continue;
            }

            for (uint8_t i = 0; i < choices_size; i++) {
                if ((uint8_t)value == choices_arr[i]) {
                    *user_input = choices_arr[i];
                    return;
                }
            }

            print_input_error_msg();

        } else {
            print_input_error_msg();
        }
    }
}

int main(void)
{
    GameState current_state = STATE_MAIN_MENU;
    uint8_t current_zone    = 1;

    uint8_t user_input = 0;

    // available choices
    uint8_t choices_arr[MAX_CHOICES] = {0};
    uint8_t choices_size             = 0;

    uint8_t running = 1;

    while (running) {
        clear_screen();

        switch (current_state) {

        case STATE_MAIN_MENU:
            print_main_menu();

            choices_size = 2; // available main menu choices
            fill_choices_arr(choices_arr, choices_size);

            get_user_input(choices_arr, choices_size, &user_input);

            switch (user_input) {
            case 1:
                current_state = STATE_CHARACTER_CREATION;
                break;

            case 2:
                current_state = STATE_QUIT;
                break;
            }

            break;

        case STATE_CHARACTER_CREATION:
            break;

        case STATE_TOWN:
            break;

        case STATE_EXPLORATION:
            break;

        case STATE_COMBAT:
            break;

        case STATE_CHARACTER_SHEET:
            break;

        case STATE_INVENTORY:
            break;

        case STATE_QUIT:
            printf("exiting...\n");
            running = 0;
            break;
        }
    }

    return 0;
}
