//
// Created by Mirek on 20.05.2020.
//

#include "Ai.h"

unsigned long long combo = 1;

void BruteForce::loadBoard(Figure *B[8][8]) {
    //Injecting state of Board to AI
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (B[i][j]->getName() == "Pawn")Board[i][j] = 10;
            else if (B[i][j]->getName() == "Knight")Board[i][j] = 30;
            else if (B[i][j]->getName() == "Bishop")Board[i][j] = 35;
            else if (B[i][j]->getName() == "Rook")Board[i][j] = 50;
            else if (B[i][j]->getName() == "Queen")Board[i][j] = 90;
            else if (B[i][j]->getName() == "King")Board[i][j] = 900;
            else Board[i][j] = 0;
            if (B[i][j]->getColor() == 0) Board[i][j] *= -1;
        }
    }
}

std::pair<Poz, Poz> BruteForce::MinMaxAlgorithm(int depth, int color) {

    return getMove(this->Board, depth, color, 1).second;
}

std::pair<int, std::pair<Poz, Poz>>
BruteForce::getMove(int fakeBoard[8][8], int depth, int color, int minmax/* 0-MIN 1-MAX*/) {
    if (depth <= 0)return {}; // if depth limit reached
    std::pair<int, std::pair<Poz, Poz>> BestMove;
    int min = 0, max = 0;
    auto moves = this->searchMove(fakeBoard, color);
    if (minmax == 1) {
        BestMove.first = -1000000;
        for (auto &move:moves) {
            if (true) {
                //std::cout<<move.first<<"\t"<<move.second.first.x<<"|"<<move.second.first.y<<"==>"<<move.second.second.x<<"|"<<move.second.second.y<<"\n";
                int fakeBoard2[8][8];
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        fakeBoard2[i][j] = fakeBoard[i][j];
                    }
                }
                fakeBoard2[move.second.second.x][move.second.second.y] = fakeBoard2[move.second.first.x][move.second.first.y];
                fakeBoard2[move.second.first.x][move.second.first.y] = 0;
                max++;
                auto MinMax = getMove(fakeBoard2, depth - 1, (color + 1) % 2, (minmax + 1) % 2);
                std::pair<int, std::pair<Poz, Poz>> NewMove = std::make_pair(MinMax.first + move.first, move.second);

                if ((BestMove.first < NewMove.first)) {//BestMove update
//                    std::cout<<"=========================================================================\n";
//                    std::cout<<"Best move value"<<BestMove.first<<"\n";
//                    std::cout<<"Movevalue "<<NewMove.first<<"MinMax valyue: "<<MinMax.first<<"\t"<<NewMove.second.first.x<<"|"<<NewMove.second.first.y<<" ==> "<<NewMove.second.second.x<<"|"<<NewMove.second.second.y<<"\n";
//                    std::cout<<"=========================================================================\n";
                    BestMove = move;
                }
            }
        }

    } else if (minmax == 0) {
        BestMove.first = 1000000;

        for (auto it = moves.rbegin(); it != moves.rend(); it++) {
            if (true) {
                int fakeBoard2[8][8];
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        fakeBoard2[i][j] = fakeBoard[i][j];
                    }
                }
                fakeBoard2[it->second.second.x][it->second.second.y] = fakeBoard2[it->second.first.x][it->second.first.y];
                fakeBoard2[it->second.first.x][it->second.first.y] = 0;
                min++;
                auto MinMax = getMove(fakeBoard2, depth - 1, (color + 1) % 2, (minmax + 1) % 2);
                std::pair<int, std::pair<Poz, Poz>> NewMove = std::make_pair(MinMax.first + it->first, it->second);
                if (BestMove.first > NewMove.first) {//BestMove update
//                    std::cout<<"=========================================================================\n";
//                    std::cout<<"Best move value"<<BestMove.first<<"\n";
//                    std::cout<<"Move value "<<NewMove.first<<"MinMax value: "<<MinMax.first<<"\t"<<NewMove.second.first.x<<"|"<<NewMove.second.first.y<<" ==> "<<NewMove.second.second.x<<"|"<<NewMove.second.second.y<<"\n";
//                    std::cout<<"=========================================================================\n";
                    BestMove = *it;
                }
            }
        }
    }
//    std::cout << "Moves for depth: " << depth << "| dla search tree";
//    if (minmax == 1) {
//        combo += max;
//        std::cout << "max = " << max << "\n";
//    } else {
//        combo += min;
//        std::cout << "min = " << min << "\n";
//    }
//    std::cout << "Final Combinations= " << combo << "\n";
    return BestMove;
}


std::multimap<int, std::pair<Poz, Poz>> BruteForce::searchMove(int fakeBoard[8][8], int color) {
    std::multimap<int, std::pair<Poz, Poz>> Moves;
    int whiteking=0,blackking=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int Figure = fakeBoard[i][j];
            if ((Figure < 0 && color == 0) || (Figure > 0 && color == 1)) {
                switch (abs(Figure)) {
                    case 10:
                        if (color == 0) {//Black Pawn
                            if(j==1 && fakeBoard[i][j+1]== 0 && fakeBoard[i][j+2]==0)Moves.emplace(0, std::make_pair(Poz{i, j}, Poz{i, j + 2}));
                            if (fakeBoard[i][j + 1] == 0)Moves.emplace(0, std::make_pair(Poz{i, j}, Poz{i, j + 1}));
                            if(isOnBoard(j+1,j+1))if (fakeBoard[i + 1][j + 1] > 0)
                                Moves.emplace(fakeBoard[i + 1][j + 1], std::make_pair(Poz{i, j}, Poz{i + 1, j + 1}));
                            if (isOnBoard(i-1,j+1))if(fakeBoard[i - 1][j + 1] > 0)
                                Moves.emplace(fakeBoard[i - 1][j + 1], std::make_pair(Poz{i, j}, Poz{i - 1, j + 1}));

                        } else if (color == 1) {//White Pawn
                            if(j==6 && fakeBoard[i][j-1]== 0 && fakeBoard[i][j-2]==0)Moves.emplace(0, std::make_pair(Poz{i, j}, Poz{i, j - 2}));
                            if (fakeBoard[i][j - 1] == 0)Moves.emplace(0, std::make_pair(Poz{i, j}, Poz{i, j - 1}));
                            if(isOnBoard(i+1,j-1))if (fakeBoard[i + 1][j - 1] < 0)
                                Moves.emplace(fakeBoard[i + 1][j - 1], std::make_pair(Poz{i, j}, Poz{i + 1, j - 1}));
                            if (isOnBoard(i-1,j-1))if(fakeBoard[i - 1][j - 1] < 0)
                                Moves.emplace(fakeBoard[i - 1][j - 1], std::make_pair(Poz{i, j}, Poz{i - 1, j - 1}));
                        }
                        break;

                    case 30://Knight
                    {
                        int k[] = {-1, 1};
                        for (int &a:k) {
                            for (int b:k) {
                                if (isOnBoard(i + 2 * a, j + b) && ((fakeBoard[i + 2 * a][j + b] >= 0 && color == 0) ||
                                                                    (fakeBoard[i + 2 * a][j + b] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i + 2 * a][j + b],
                                                  std::make_pair(Poz{i, j}, Poz{i + 2 * a, j + b}));

                                if (isOnBoard(i + a, j + b * 2) && ((fakeBoard[i + a][j + 2 * b] >= 0 && color == 0) ||
                                                                    (fakeBoard[i + a][j + 2 * b] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i + a][j + 2 * b],
                                                  std::make_pair(Poz{i, j}, Poz{i + a, j + 2 * b}));
                            }
                        }
                    }
                    case 35://Bishop
                    {
                        int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
                        for (int a = 0; a < 8; a++) {
                            if (isOnBoard(i + a, j + a) && a1 == 0) {
                                if (fakeBoard[i + a][j + a] != 0)a1++;
                                if (((fakeBoard[i + a][j + a] >= 0 && color == 0) ||
                                     (fakeBoard[i + a][j + a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i + a][j + a],
                                                  std::make_pair(Poz{i, j}, Poz{i + a, j + a}));
                            }
                            if (isOnBoard(i + a, j - a) && a2 == 0) {
                                if (fakeBoard[i + a][j - a] != 0)a2++;
                                if (((fakeBoard[i + a][j - a] >= 0 && color == 0) ||
                                     (fakeBoard[i + a][j - a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i + a][j - a],
                                                  std::make_pair(Poz{i, j}, Poz{i + a, j - a}));
                            }
                            if (isOnBoard(i - a, j + a) && a3 == 0) {
                                if (fakeBoard[i - a][j + a] != 0)a3++;
                                if (((fakeBoard[i - a][j + a] >= 0 && color == 0) ||
                                     (fakeBoard[i - a][j + a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i - a][j + a],
                                                  std::make_pair(Poz{i, j}, Poz{i - a, j + a}));
                            }
                            if (isOnBoard(i - a, j - a) && a4 == 0) {
                                if (fakeBoard[i - a][j - a] != 0)a4++;
                                if (((fakeBoard[i - a][j - a] >= 0 && color == 0) ||
                                     (fakeBoard[i - a][j - a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i - a][j - a],
                                                  std::make_pair(Poz{i, j}, Poz{i - a, j - a}));
                            }
                        }
                    }
                        break;
                    case 50: {
                        int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
                        for (int a = 1; a < 8; a++) {

                            if (isOnBoard(i + a, j) && a1 == 0) {//right
                                if (fakeBoard[i + a][j] != 0)a1++;
                                if (((fakeBoard[i + a][j] >= 0 && color == 0) ||
                                     (fakeBoard[i + a][j] <= 0 && color == 1))) {
                                    Moves.emplace(fakeBoard[i + a][j], std::make_pair(Poz{i, j}, Poz{i + a, j}));
                                }
                            }
                            if (isOnBoard(i - a, j) && a2 == 0) {//left
                                if (fakeBoard[i - a][j] != 0)a2++;
                                if (((fakeBoard[i - a][j] >= 0 && color == 0) ||
                                     (fakeBoard[i - a][j] <= 0 && color == 1))) {
                                    Moves.emplace(fakeBoard[i - a][j], std::make_pair(Poz{i, j}, Poz{i - a, j}));
                                }
                            }

                            if (isOnBoard(i, j + a) && a3 == 0) {//up
                                if (fakeBoard[i][j + a] != 0)a3++;
                                if (((fakeBoard[i][j + a] >= 0 && color == 0) ||
                                     (fakeBoard[i][j + a] <= 0 && color == 1))) {
                                    Moves.emplace(fakeBoard[i][j + a], std::make_pair(Poz{i, j}, Poz{i, j + a}));
                                }
                            }
                            if (isOnBoard(i, j - a) && a4 == 0) {//down
                                if (fakeBoard[i][j - a] != 0)a4++;
                                if (((fakeBoard[i][j - a] >= 0 && color == 0) ||
                                     (fakeBoard[i][j - a] <= 0 && color == 1))) {
                                    Moves.emplace(fakeBoard[i][j - a], std::make_pair(Poz{i, j}, Poz{i, j - a}));
                                }
                            }

                        }
                    }
                        break;
                    case 90: {
                        int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a11 = 0, a22 = 0, a33 = 0, a44 = 0;
                        for (int a = 1; a < 8; a++) {
                            if (isOnBoard(i + a, j) && a11 == 0) {//right
                                if (fakeBoard[i + a][j] != 0)a11++;
                                if (((fakeBoard[i + a][j] >= 0 && color == 0) ||
                                     (fakeBoard[i + a][j] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i + a][j], std::make_pair(Poz{i, j}, Poz{i + a, j}));
                            }
                            if (isOnBoard(i - a, j) && a22 == 0) {//left
                                if (fakeBoard[i - a][j] != 0)a22++;
                                if (((fakeBoard[i - a][j] >= 0 && color == 0) ||
                                     (fakeBoard[i - a][j] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i - a][j], std::make_pair(Poz{i, j}, Poz{i - a, j}));
                            }

                            if (isOnBoard(i, j + a) && a33 == 0) {//up
                                if (fakeBoard[i][j + a] != 0)a33++;
                                if (((fakeBoard[i][j + a] >= 0 && color == 0) ||
                                     (fakeBoard[i][j + a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i][j + a], std::make_pair(Poz{i, j}, Poz{i, j + a}));
                            }
                            if (isOnBoard(i, j - a) && a44 == 0) {//down
                                if (fakeBoard[i][j - a] != 0)a44++;
                                if (((fakeBoard[i][j - a] >= 0 && color == 0) ||
                                     (fakeBoard[i][j - a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i][j - a], std::make_pair(Poz{i, j}, Poz{i, j - a}));
                            }
                            if (isOnBoard(i + a, j + a) && a1 == 0) {
                                if (fakeBoard[i + a][j + a] != 0)a1++;
                                if (((fakeBoard[i + a][j + a] >= 0 && color == 0) ||
                                     (fakeBoard[i + a][j + a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i + a][j + a],
                                                  std::make_pair(Poz{i, j}, Poz{i + a, j + a}));
                            }
                            if (isOnBoard(i + a, j - a) && a2 == 0) {
                                if (fakeBoard[i + a][j - a] != 0)a2++;
                                if (((fakeBoard[i + a][j - a] >= 0 && color == 0) ||
                                     (fakeBoard[i + a][j - a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i + a][j - a],
                                                  std::make_pair(Poz{i, j}, Poz{i + a, j - a}));
                            }
                            if (isOnBoard(i - a, j + a) && a3 == 0) {
                                if (fakeBoard[i - a][j + a] != 0)a3++;
                                if (((fakeBoard[i - a][j + a] >= 0 && color == 0) ||
                                     (fakeBoard[i - a][j + a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i - a][j + a],
                                                  std::make_pair(Poz{i, j}, Poz{i - a, j + a}));
                            }
                            if (isOnBoard(i - a, j - a) && a4 == 0) {
                                if (fakeBoard[i - a][j - a] != 0)a4++;
                                if (((fakeBoard[i - a][j - a] >= 0 && color == 0) ||
                                     (fakeBoard[i - a][j - a] <= 0 && color == 1)))
                                    Moves.emplace(fakeBoard[i - a][j - a],
                                                  std::make_pair(Poz{i, j}, Poz{i - a, j - a}));
                            }
                        }
                    }
                        break;
                    case 900: {
                        if(color == 1)whiteking++;
                        if(color == 0)blackking++;
                        for (int a = -1; a < 2; a++) {
                            if (isOnBoard(i + a, j - 1) && ((fakeBoard[i + a][j - 1] >= 0 && color == 0) ||
                                                            (fakeBoard[i + a][j - 1] <= 0 && color == 1)))
                                Moves.emplace(fakeBoard[i + a][j - 1], std::make_pair(Poz{i, j}, Poz{i + a, j - 1}));
                            if (isOnBoard(i + a, j + 1) && ((fakeBoard[i + a][j + 1] >= 0 && color == 0) ||
                                                            (fakeBoard[i + a][j + 1] <= 0 && color == 1)))
                                Moves.emplace(fakeBoard[i + a][j + 1], std::make_pair(Poz{i, j}, Poz{i + a, j + 1}));
                        }
                        if (((fakeBoard[i + 1][j] >= 0 && color == 0) || (fakeBoard[i + 1][j] <= 0 && color == 1)) &&
                            isOnBoard(i + 1, j))
                            Moves.emplace(fakeBoard[i + 1][j], std::make_pair(Poz{i, j}, Poz{i + 1, j}));
                        if (((fakeBoard[i - 1][j] >= 0 && color == 0) || (fakeBoard[i - 1][j] <= 0 && color == 1)) &&
                            isOnBoard(i - 1, j))
                            Moves.emplace(fakeBoard[i - 1][j], std::make_pair(Poz{i, j}, Poz{i - 1, j}));
                    }
                        break;
                }
            }
        }
    }
    if((whiteking==0 && color ==1)|| (blackking==0 && color ==0))return {};
    return Moves;
}

int BruteForce::evaluate(int a, int b, int x, int y) {
    return 0;
}

