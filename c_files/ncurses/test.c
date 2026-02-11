#include <ncurses.h>

int main(void)
{
    int x = 10, y = 5;
    int ch;

    initscr();

    int screen_width  = getmaxx(stdscr);
    int screen_height = getmaxy(stdscr);

    if (!has_colors()) {
        endwin();
        printf("No color support\n");
        return 1;
    }

    cbreak();
    noecho();
    curs_set(0);

    WINDOW *win;

    while ((ch = getch()) != 'q') {
        clear();

        int win_width  = 20;
        int win_height = 10;
        int win_x      = screen_width / 2 - win_width / 2;
        int win_y      = screen_height / 2 - win_height / 2;

        win = newwin(win_height, win_width, win_y, win_x);
        box(win, 0, 0);

        switch (ch) {
        case 'w':
            y--;
            break;
        case 's':
            y++;
            break;
        case 'a':
            x--;
            break;
        case 'd':
            x++;
            break;
        }

        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);

        attron(COLOR_PAIR(1));
        // mvprintw(y, x, "@");
        mvwprintw(win, y, x, "@");
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(2));
        mvprintw(0, 0, "use arrow keys, q to quit");
        attroff(COLOR_PAIR(2));

        wrefresh(win);

        refresh();
    }

    delwin(win);
    endwin();

    return 0;
}
