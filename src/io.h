#ifndef IO_H_AJUOM4ZR
#define IO_H_AJUOM4ZR

#include "maze.h"
#include <queue>

enum class IOEvent { Quit, MoveUp, MoveLeft, MoveRight, MoveDown, Select };

// Initializes IO system
// Returns 0 on success
int init_io(int width, int height);

// Processes input; returns queue of events
std::queue<IOEvent> process_input();

// Draws screen
void refresh_io(const Maze &maze);

// Cleans up IO system
void quit_io();

#endif /* IO_H_AJUOM4ZR */
