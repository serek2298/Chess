//
// Created by Mirek on 19.05.2020.
//

#ifndef CHESSAI_CHESS_H
#define CHESSAI_CHESS_H
#include "Figure.h"
#include "Ai.h"

class Chess {
private:
public:
    Figure* Board[8][8]{};

    int turn=1;//white
    int state=1;//0-menu, 1-play, 2-settings, 3-quit;
    int bot=1;
    int botcolor=0;
    int botlvl=4;

    Chess();
    ~Chess()= default;
    void GameIsON();
    bool ifColide(int x1,int y1,int x2,int y2);
    void  AIMove( int color);
};


#endif //CHESSAI_CHESS_H
