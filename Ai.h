//
// Created by Mirek on 20.05.2020.
//

#ifndef CHESSAI_AI_H
#define CHESSAI_AI_H
#include "Chess.h"

class BruteForce {
private:
int Board[8][8]{};
public:
    BruteForce()= default;
    void loadBoard(Figure* B[8][8]);
    ~BruteForce()= default;
    std::pair<Poz,Poz> MinMaxAlgorithm(int depth, int color);
    std::pair<int,std::pair<Poz,Poz>> getMove(int fakeBoard[8][8],int depth,int color,int minmax);
    std::multimap<int,std::pair<Poz, Poz>> searchMove(int fakeBoard[8][8],int color);
    int evaluate(int a,int b,int x,int y);


};


#endif //CHESSAI_AI_H
