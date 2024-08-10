set(mazegame_SRCS main.cc
                  io.h
                  maze.h
                  maze.cc)

if(CURSES_BUILD)
    list(APPEND mazegame_SRCS io_curses.cc)
else()
    list(APPEND mazegame_SRCS io_sdl.cc)
endif()

add_executable(mazegame ${mazegame_SRCS})
target_include_directories(mazegame PRIVATE .)

if(CURSES_BUILD)
    target_include_directories(mazegame PRIVATE ${CURSES_INCLUDE_DIRS})
    target_link_libraries(mazegame PRIVATE ${CURSES_LIBRARIES})
else()
    target_link_libraries(mazegame PRIVATE SDL2::SDL2)
endif()

if(MSVC)
    target_compile_options(mazegame PRIVATE /W4)
else()
    target_compile_options(mazegame PRIVATE -Wall -Wextra -pedantic)
endif()
