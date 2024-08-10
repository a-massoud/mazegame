cmake_minimum_required(VERSION 3.20)
project(mazegame LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CURSES_BUILD)
    find_package(Curses REQUIRED)
else()
    find_package(SDL2 REQUIRED)
endif()

add_subdirectory(src)
