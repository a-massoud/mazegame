#include "io.h"
#include "maze.h"
#include <SDL.h>
#include <queue>

const int CELL_SIZE = 10;

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

int init_io(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        return 1;

    window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width * CELL_SIZE,
                              height * CELL_SIZE, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        return 1;
    }

    return 0;
}

std::queue<IOEvent> process_input() {
    std::queue<IOEvent> events;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            events.push(IOEvent::Quit);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_q:
                events.push(IOEvent::Quit);
                break;

            case SDLK_k:
            case SDLK_UP:
                events.push(IOEvent::MoveUp);
                break;

            case SDLK_j:
            case SDLK_DOWN:
                events.push(IOEvent::MoveDown);
                break;

            case SDLK_h:
            case SDLK_LEFT:
                events.push(IOEvent::MoveLeft);
                break;

            case SDLK_l:
            case SDLK_RIGHT:
                events.push(IOEvent::MoveRight);
                break;

            case SDLK_RETURN:
                events.push(IOEvent::Select);
                break;
            }
        }
    }

    return events;
}

void refresh_io(const Maze &maze) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect{0, 0, CELL_SIZE, CELL_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; static_cast<std::size_t>(i) < maze.height(); ++i) {
        for (int j = 0; static_cast<std::size_t>(j) < maze.width(); ++j) {
            if (maze[{j, i}]) {
                rect.x = j * CELL_SIZE;
                rect.y = i * CELL_SIZE;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    rect.x = maze.player().x * CELL_SIZE;
    rect.y = maze.player().y * CELL_SIZE;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect.x = maze.goal().x * CELL_SIZE;
    rect.y = maze.goal().y * CELL_SIZE;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void quit_io() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
