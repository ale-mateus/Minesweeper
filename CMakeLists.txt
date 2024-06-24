cmake_minimum_required(VERSION 3.26)
project(project4v2)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(project4v2 main.cpp
        Minesweeper.cpp
        Minesweeper.h
        GameState.cpp
        GameState.h
        Tile.cpp
        Tile.h
        Toolbox.cpp
        Toolbox.h
        Button.cpp
        Button.h)

target_link_libraries(project4v2 sfml-graphics sfml-audio)
