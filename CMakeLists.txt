cmake_minimum_required(VERSION 3.1)

project(ChessAI)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Users/serek/OneDrive/Pulpit/Programming/Libs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(ChessAI main.cpp Ai.cpp Figure.cpp Chess.cpp Ai.h Figure.h Chess.h)
target_link_libraries(ChessAI sfml-graphics sfml-audio)