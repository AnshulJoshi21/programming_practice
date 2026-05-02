#include "game_manager.h"
#include <assert.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void game_manager_init(GameManager *gm) {
  assert(gm);

  gm->current_state = GAME_STATE_TITLE;
  gm->prev_state = GAME_STATE_TITLE;
  gm->selected = 0;
  gm->menu_size = 0;

  tb_init();
}

// MENUS
typedef struct Menu {
  const char *title;
  const char **arr;
  const int size;

} Menu;

static const char *main_menu_arr[] = {"New Game", "Exit"};
static const Menu main_menu = (Menu){.title = "Simple Rpg",
                                     .arr = main_menu_arr,
                                     .size = ARRAY_SIZE(main_menu_arr)};

static const char *character_selection_arr[] = {"Warrior", "Rogue", "Mage"};
static const Menu character_selection_menu =
    (Menu){.title = "Character Selection",
           .arr = character_selection_arr,
           .size = ARRAY_SIZE(character_selection_arr)};

static void draw_menu(const int selected, const Menu *menu) {
  assert(menu);
  assert(selected >= 0);

  int x = 2;
  int y = 2;

  int row = 0;

  // header
  tb_printf(x, y + row, TB_WHITE, TB_DEFAULT,
            "=============%s=============", menu->title);
  row += 2;

  // menu
  for (int i = 0; i < menu->size; i++) {
    const int fg = (i == selected) ? TB_BLACK : TB_WHITE;
    const int bg = (i == selected) ? TB_WHITE : TB_DEFAULT;

    tb_printf(x, y + row, fg, bg, menu->arr[i]);
    row += 2;
  }

  // footer
  const int title_len = strlen(menu->title);
  char temp[title_len + 1];
  for (int i = 0; i < title_len; i++) {
    temp[i] = '=';
  }
  temp[title_len] = '\0';

  tb_printf(x, y + row, TB_WHITE, TB_DEFAULT,
            "=============%s=============", temp);
}

static void game_manager_draw(GameManager *gm) {
  assert(gm);

  tb_clear();

  switch (gm->current_state) {
  case GAME_STATE_TITLE: {
    draw_menu(gm->selected, &main_menu);
  } break;

  case GAME_STATE_CHARACTER_CREATION: {
    draw_menu(gm->selected, &character_selection_menu);
  } break;

  case GAME_STATE_TOWN: {
  } break;

  case GAME_STATE_EXPLORE: {
  } break;

  case GAME_STATE_COMBAT: {
  } break;

  case GAME_STATE_SHOP: {
  } break;

  case GAME_STATE_PROFILE: {
  } break;

  default:
    break;
  }

  tb_present();
}

static void game_manager_update(GameManager *gm, int *running) {
  assert(gm);

  // reset selection
  if (gm->current_state != gm->prev_state) {
    gm->prev_state = gm->current_state;
    gm->selected = 0;
  }

  tb_poll_event(&gm->ev);

  if (gm->ev.type == TB_EVENT_KEY) {

    switch (gm->current_state) {

    case GAME_STATE_TITLE: {
      gm->menu_size = main_menu.size;

      if (gm->ev.key == TB_KEY_ENTER) {
        if (gm->selected == 0)
          gm->current_state = GAME_STATE_CHARACTER_CREATION;
        else if (gm->selected == 1)
          *running = 0;
      }
    } break;

    case GAME_STATE_CHARACTER_CREATION: {
      gm->menu_size = character_selection_menu.size;

      // back to title screen
      if (gm->ev.key == TB_KEY_ESC) {
        gm->current_state = GAME_STATE_TITLE;
      }

    } break;

    case GAME_STATE_TOWN: {
    } break;

    case GAME_STATE_EXPLORE: {
    } break;

    case GAME_STATE_COMBAT: {
    } break;

    case GAME_STATE_SHOP: {
    } break;

    case GAME_STATE_PROFILE: {
    } break;

    default:
      break;
    }

    // handle input
    if (gm->ev.key == TB_KEY_ARROW_UP) {
      if (gm->selected > 0)
        gm->selected--;
    }

    if (gm->ev.key == TB_KEY_ARROW_DOWN) {
      if (gm->selected < gm->menu_size - 1) {
        gm->selected++;
      }
    }
  }
}

void game_manager_run(GameManager *gm) {
  assert(gm);

  int running = 1;

  while (running) {
    game_manager_draw(gm);
    game_manager_update(gm, &running);
  }

  tb_shutdown();
}
