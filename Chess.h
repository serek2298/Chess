//
// Created by serek on 15.05.2020.
//

#ifndef CHESSTEST_CHESS_H
#define CHESSTEST_CHESS_H
#include <utility>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define LENGHT 7
#define BLACK_PAWN 1
#define BLACK_ROOK 2
#define BLACK_KNIGHT 3
#define BLACK_BITSHOP 4
#define BLACK_QUEEN 5
#define BLACK_KING 6
#define WHITE_PAWN 1
#define WHITE_ROOK 2
#define WHITE_KNIGHT 3
#define WHITE_BITSHOP 4
#define WHITE_QUEEN 5
#define WHITE_KING 6

#include "Figure.h"

class Chess  {
    std::pair<int,int> position;
    int board[8][8] = {
            2, 3, 4, 5, 6, 4, 3, 2, 
            1, 1, 1, 1, 1, 1, 1, 1, 
            0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 
            -1,-1,-1,-1,-1,-1,-1,-1,
            -2,-3,-4,-5,-6,-4,-3,-2,
    };
    int turn;




};


#endif //CHESSTEST_CHESS_H
