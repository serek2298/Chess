cmake_minimum_required(VERSION 3.15)
project(ChessTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessTest main.cpp Chess.cpp Chess.h Figure.cpp Figure.h)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(ChessTest ${SFML_LIBRARIES})
endif()