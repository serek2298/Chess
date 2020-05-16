//
// Created by serek on 15.05.2020.
//

#ifndef CHESSTEST_FIGURE_H
#define CHESSTEST_FIGURE_H

#include <utility>
#include <vector>
#include <memory>

struct Poz{
    int x;
    int y;
};
class Figure {
private:
    int color=1; // White
    Poz MyPoz{};

public:

    void makeBlack(){
        this->color = 0;//Black
    }

    virtual bool isDragged()=0;
    void setPoz(int x,int y){
        MyPoz.x=x;
        MyPoz.y=y;
    };
    int getPozX(){
        return this->MyPoz.x;
    }
    int getPozY(){
        return this->MyPoz.y;
    }
    int getColor(){
        return this->color;
    }
    virtual std::vector<Poz>& moves()=0;

friend class Chess;
};

class Pawn:public Figure{
    std::vector<Poz>& moves() override{//attacks not included
        std::unique_ptr<std::vector<Poz>> Vec(new std::vector<Poz>);
        if(this->getColor() == 1) {
            Vec->push_back(Poz{getPozX(),getPozY()-1});
            if(getPozY()-2>=4)Vec->push_back(Poz{getPozX(),getPozY()-2});
        }else{
            Vec->push_back(Poz{getPozX(),getPozY()+1});
            if(getPozY()+2<=3)Vec->push_back(Poz{getPozX(),getPozY()+2});
        }
        return *Vec;
    };
    friend class Chess;
};

class Rook: public Figure{

    std::vector<Poz>& moves() override{//attacks not included
       std::unique_ptr<std::vector<Poz>> Vec(new std::vector<Poz>);
        for(int i=0;i<8;i++) {
            Vec->push_back(Poz{getPozX(), i});
            Vec->push_back(Poz{i, getPozY()});
        }
        return *Vec;
    };
    friend class Chess;
};

class Kight: public Figure{

    std::vector<Poz>& moves() override{//attacks not included
        std::unique_ptr<std::vector<Poz>> Vec(new std::vector<Poz>);
        int k[] = {-1,1};
        for(int i:k) {
            for (int j:k) {
            Vec->push_back(Poz{getPozX() + 2 * i, getPozY() + i});
            Vec->push_back(Poz{getPozX() + i, getPozY() + i * 2});
        }
        }

        return *Vec;
    };
    friend class Chess;
};



#endif //CHESSTEST_FIGURE_H
