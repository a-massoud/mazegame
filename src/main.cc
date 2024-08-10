#include "io.h"
#include "maze.h"
#include <cstdlib>
#include <iostream>

const int WIDTH = 79;
const int HEIGHT = 23;

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    if (init_io(WIDTH, HEIGHT) != 0) {
        std::cerr << "Failed to initialize IO\n";
        return 1;
    }
    std::atexit(quit_io);

    Maze maze(WIDTH, HEIGHT);

    bool running = true;
    while (running) {
        std::queue<IOEvent> events = process_input();
        for (; !events.empty(); events.pop()) {
            IOEvent event = events.front();
            switch (event) {
            case IOEvent::Quit:
                running = false;
                break;

            case IOEvent::MoveUp:
                if (maze.player().y - 1 >= 0 &&
                    maze[{maze.player().x, maze.player().y - 1}] == false)
                    maze.player().y -= 1;
                break;

            case IOEvent::MoveLeft:
                if (maze.player().x - 1 >= 0 &&
                    maze[{maze.player().x - 1, maze.player().y}] == false)
                    maze.player().x -= 1;
                break;

            case IOEvent::MoveRight:
                if (static_cast<std::size_t>(maze.player().x + 1) <
                        maze.width() &&
                    maze[{maze.player().x + 1, maze.player().y}] == false)
                    maze.player().x += 1;
                break;

            case IOEvent::MoveDown:
                if (static_cast<std::size_t>(maze.player().y + 1) <
                        maze.height() &&
                    maze[{maze.player().x, maze.player().y + 1}] == false)
                    maze.player().y += 1;
                break;

            case IOEvent::Select:
                running = false;
                break;
            }
        }

        if (maze.player() == maze.goal())
            running = false;

        refresh_io(maze);
    }

    return 0;
}
