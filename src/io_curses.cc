#include "io.h"
#include "maze.h"
#include <curses.h>
#include <queue>

int init_io(int width, int height) {
    if (initscr() == 0) {
        return 1;
    }
    int maxx, maxy;
    getmaxyx(stdscr, maxy, maxx);
    if (maxx < width || maxy < height) {
        endwin();
        return 1;
    }
    nodelay(stdscr, true);
    cbreak();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    set_escdelay(15);
    return 0;
}

std::queue<IOEvent> process_input() {
    std::queue<IOEvent> events;

    int ch;
    while ((ch = getch()) != ERR) {
        switch (ch) {
        case 27:
        case 'q':
            events.push(IOEvent::Quit);
            break;

        case 'k':
        case KEY_UP:
            events.push(IOEvent::MoveUp);
            break;

        case 'j':
        case KEY_DOWN:
            events.push(IOEvent::MoveDown);
            break;

        case 'h':
        case KEY_LEFT:
            events.push(IOEvent::MoveLeft);
            break;

        case 'l':
        case KEY_RIGHT:
            events.push(IOEvent::MoveRight);
            break;

        case '\n':
            events.push(IOEvent::Select);
            break;
        }
    }

    return events;
}

void refresh_io(const Maze &maze) {
    erase();

    for (int i = 0; static_cast<std::size_t>(i) < maze.height(); ++i) {
        for (int j = 0; static_cast<std::size_t>(j) < maze.width(); ++j) {
            if (maze[{j, i}]) {
                mvaddch(i, j, '#');
            }
        }
    }

    mvaddch(maze.player().y, maze.player().x, '@');
    mvaddch(maze.goal().y, maze.goal().x, '>');

    refresh();
}

void quit_io() {
    keypad(stdscr, false);
    nodelay(stdscr, false);
    noraw();
    nocbreak();
    echo();
    curs_set(1);
    endwin();
}
