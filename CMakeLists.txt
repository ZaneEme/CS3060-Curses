cmake_minimum_required(VERSION 3.20 )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXXSTANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CURSES_USE_NCURSES TRUE)

set(SHARED_FLAGS " -Wall -lncurses")


project ( CS_3060_NCURSES)

include_directories( include )

file(GLOB GAME "src/Game/*.cpp")
file(GLOB MENU "src/Menu/*.cpp")


add_executable( main main.cpp ${GAME} ${MENU})

target_link_libraries(main ncurses)
