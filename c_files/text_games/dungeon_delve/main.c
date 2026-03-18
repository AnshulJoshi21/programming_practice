#include "data/character_data.h"
#include "data/weapon_data.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CHOICES 100

typedef enum GameState {
    STATE_MAIN_MENU,
    STATE_CHARACTER_CREATION,
    STATE_TOWN,
    STATE_COMBAT,
    STATE_EXIT

} GameState;

static void clear_screen(void)
{
    printf("\033[2J"); // clear screen
    printf("\033[H");  // move cursor to top left corner
}

static void clear_lines(uint8_t n)
{
    for (int i = 0; i < n; i++) {
        printf("\033[K"); // clear from cursor to end of line
        printf("\033[F"); // move cursor up 1 line
    }
}

static void fill_choices_arr(uint8_t *choices_arr, uint8_t size)
{
    assert(choices_arr);
    assert(size <= MAX_CHOICES);

    for (int i = 0; i < size; i++) {
        choices_arr[i] = i + 1;
    }
}

static void print_main_menu(void)
{
    printf("\n");
    printf("Simple Rpg\n");
    printf("\n");
    printf("1) New Game\n");
    printf("2) Exit\n");
    printf("\n");
}

static void print_input_error_msg(void)
{
    printf("\n");
    printf("Invalid input, try again\n");
    sleep(1);
}

static void get_user_input(uint8_t *choices_arr, uint8_t arr_size,
                           uint8_t *user_input)
{
    assert(choices_arr);
    assert(user_input);

    char buffer[100];
    char *end_ptr;
    long value;

    while (1) {

        printf("> ");

        if (fgets(buffer, sizeof(buffer), stdin)) {
            errno = 0;
            value = strtol(buffer, &end_ptr, 10);

            if (errno == ERANGE) {
                print_input_error_msg();
                continue;
            }

            if (end_ptr == buffer) {
                print_input_error_msg();
                continue;
            }

            if (*end_ptr != '\n' && *end_ptr != '\0') {
                print_input_error_msg();
                continue;
            }

            // compare available choices
            for (uint8_t i = 0; i < arr_size; i++) {
                if ((int)value == choices_arr[i]) {
                    *user_input = choices_arr[i];
                    return;
                }
            }

            // if for loop fails
            print_input_error_msg();

        } else {
            print_input_error_msg();
        }
    }
}

static void print_character_info(CharacterClass class)
{
    const BaseCharacter *c = &base_character_db[class];

    printf("\n");
    printf("%s\n", c->name);
    printf("\n");
    printf("HP: %d\n", c->base_hp);
    printf("MP: %d\n", c->base_mp);
    printf("STR: %d\n", c->base_str);
    printf("DEX: %d\n", c->base_dex);
    printf("INT: %d\n", c->base_int);
    printf("VIT: %d\n", c->base_vit);
    printf("WEAPON: %s\n", base_weapon_db[c->primary_weapon].name);
}

int main(void)
{
    GameState current_state = STATE_MAIN_MENU;
    uint8_t user_input;

    uint8_t choices_arr[MAX_CHOICES] = {0};
    uint8_t arr_size                 = 0;

    CharacterClass current_class;

    bool running = true;

    while (running) {
        clear_screen();

        switch (current_state) {
        case STATE_MAIN_MENU:
            print_main_menu();

            arr_size = 2; // available choices

            fill_choices_arr(choices_arr, arr_size);

            get_user_input(choices_arr, arr_size, &user_input);

            switch (user_input) {
            case 1:
                current_state = STATE_CHARACTER_CREATION;
                break;
            case 2:
                current_state = STATE_EXIT;
                break;
            }

            break;

        case STATE_CHARACTER_CREATION:
            for (int i = 0; i < CLASS_MAX; i++) {
                print_character_info(i);
            }

            arr_size = CLASS_MAX;

            get_user_input(choices_arr, arr_size, &user_input);
            current_class = (CharacterClass)user_input;

            current_state = STATE_TOWN;

            break;

        case STATE_TOWN:
            printf("Current class: %s", base_character_db[current_class].name);
            getchar();

            break;

        case STATE_COMBAT:
            break;

        case STATE_EXIT:
            printf("exiting ...\n");
            printf("\n");
            printf("thank you for playing\n");
            printf("\n");

            running = false;
            break;
        }
    }

    return 0;
}
