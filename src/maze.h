#ifndef MAZE_H_MIW6FINP
#define MAZE_H_MIW6FINP

#include <vector>

struct Coord {
    int x;
    int y;

    Coord(int x_, int y_) : x(x_), y(y_) {}
    bool operator==(const Coord &other) const {
        return x == other.x && y == other.y;
    }
};

class Maze {
  private:
    std::vector<bool> maze_;
    std::size_t width_;
    std::size_t height_;
    Coord player_;
    Coord goal_;

  public:
    Maze(std::size_t width, std::size_t height);

    const Coord &player() const { return player_; };
    Coord &player() { return player_; };

    Coord goal() const { return goal_; };

    std::size_t width() const { return width_; };
    std::size_t height() const { return height_; };

    bool operator[](Coord loc) const {
        if (static_cast<std::size_t>(loc.x) >= width_ || loc.x < 0 ||
            static_cast<std::size_t>(loc.y) >= height_ || loc.y < 0)
            return false;
        return maze_[loc.y * width_ + loc.x];
    }
};

#endif /* MAZE_H_MIW6FINP */
