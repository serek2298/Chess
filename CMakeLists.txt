cmake_minimum_required(VERSION 3.1)

project(ChessAI)
 set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/Mirek/Desktop/Wojciech/SFML/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)
add_executable(ChessAI main.cpp Figure.cpp Figure.h Chess.cpp Chess.h Ai.cpp Ai.h)
target_link_libraries(ChessAI sfml-graphics sfml-window sfml-system sfml-audio)