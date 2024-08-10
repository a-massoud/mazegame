#include "maze.h"
#include <random>
#include <stdexcept>
#include <vector>

Maze::Maze(std::size_t width, std::size_t height)
    : maze_(width * height), width_(width), height_(height), player_(1, 1),
      goal_(width - 2, height - 2) {
    if (width % 2 == 0 || height % 2 == 0 || width < 5 || height < 5)
        throw std::invalid_argument(
            "Width and height must be odd and at least 5");

    std::mt19937 rnd;
    {
        std::random_device rdev;
        std::seed_seq sq{rdev(), rdev(), rdev(), rdev()};
        rnd.seed(sq);
    }

    for (std::size_t i = 0; i < width * height; ++i)
        maze_[i] = true;
    maze_[width + 1] = false;

    std::vector<std::pair<Coord, Coord>> frontier = {{{1, 1}, {1, 1}}};
    while (!frontier.empty()) {
        std::size_t idx =
            (std::uniform_int_distribution<>(0, frontier.size() - 1))(rnd);
        auto [loc, parent] = frontier[idx];
        frontier.erase(frontier.begin() + idx);

        // break down the wall between them
        maze_[((loc.x + parent.x) / 2) + ((loc.y + parent.y) / 2) * width_] =
            false;

        if (loc.x > 1 && maze_[(loc.x - 2) + loc.y * width_]) {
            maze_[(loc.x - 2) + loc.y * width_] = false;
            frontier.push_back({{loc.x - 2, loc.y}, loc});
        }
        if (loc.y > 1 && maze_[loc.x + (loc.y - 2) * width_]) {
            maze_[loc.x + (loc.y - 2) * width_] = false;
            frontier.push_back({{loc.x, loc.y - 2}, loc});
        }
        if (static_cast<std::size_t>(loc.x) < width_ - 2 &&
            maze_[(loc.x + 2) + loc.y * width_]) {
            maze_[(loc.x + 2) + loc.y * width_] = false;
            frontier.push_back({{loc.x + 2, loc.y}, loc});
        }
        if (static_cast<std::size_t>(loc.y) < height_ - 2 &&
            maze_[loc.x + (loc.y + 2) * width_]) {
            maze_[loc.x + (loc.y + 2) * width_] = false;
            frontier.push_back({{loc.x, loc.y + 2}, loc});
        }
    }
}
