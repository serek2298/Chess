//
// Created by Mirek on 19.05.2020.
//

#include "Figure.h"
bool isOnBoard(int x,int y){
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

bool isRealFigure(Figure *object) {
    try {
        std::cout<<typeid(object).name()<<"\n";
    }catch(std::bad_typeid& error){
        return false;
    }
    return true;
}

void Figure::unDrag() {
    this->dragging = false;
}

void Figure::Drag() {
    this->dragging = true;
}

void Figure::makeBlack() {
    this->color = 0;//Black
}

bool Figure::isDragged() {
    return dragging;
}

void Figure::setPoz(int x, int y) {
    MyPoz.x=x;
    MyPoz.y=y;
}

int Figure::getPozX() {
    return this->MyPoz.x;
}

int Figure::getPozY() {
    return this->MyPoz.y;
}

int Figure::getColor() {
    return this->color;
}

void Figure::setTexture(std::string path) {
    this->texture.loadFromFile(path);
}

sf::Texture &Figure::getTexture() {
    return this->texture;
}

void Figure::setSprite() {
    this->sprite.setTexture(this->texture);
    sprite.setPosition(100*MyPoz.x,100*MyPoz.y);
}

sf::Sprite &Figure::getSprite() {
    return this->sprite;
}

void Figure::setSpritePoz(int x,int y) {
    sprite.setPosition(x,y);
}

std::string Figure::getName() {
    return this->name;
}


std::vector<Poz> &King::moves() {
    auto *Vec = new std::vector<Poz>;
    if(isOnBoard(getPozX()+1,getPozY()-1))Vec->push_back(Poz{getPozX()+1,getPozY()-1});
    if(isOnBoard(getPozX()+1,getPozY()+0))Vec->push_back(Poz{getPozX()+1,getPozY()+0});
    if(isOnBoard(getPozX()+1,getPozY()+1))Vec->push_back(Poz{getPozX()+1,getPozY()+1});
    if(isOnBoard(getPozX()-1,getPozY()-1))Vec->push_back(Poz{getPozX()-1,getPozY()-1});
    if(isOnBoard(getPozX()-1,getPozY()+0))Vec->push_back(Poz{getPozX()-1,getPozY()+0});
    if(isOnBoard(getPozX()-1,getPozY()+1))Vec->push_back(Poz{getPozX()-1,getPozY()+1});
    if(isOnBoard(getPozX()+0,getPozY()-1))Vec->push_back(Poz{getPozX()+0,getPozY()-1});
    if(isOnBoard(getPozX()+0,getPozY()+1))Vec->push_back(Poz{getPozX()+0,getPozY()+1});
    return *Vec;
}

King::King() {
this->name ="King";
}

std::vector<Poz> &Queen::moves() {
    auto *Vec = new std::vector<Poz>;
    for(int i=0;i<8;i++){
        if(isOnBoard(getPozX()+i,getPozY()+i))Vec->push_back(Poz{getPozX()+i,getPozY()+i});
        if(isOnBoard(getPozX()+i,getPozY()-i))Vec->push_back(Poz{getPozX()+i,getPozY()-i});
        if(isOnBoard(getPozX()-i,getPozY()+i))Vec->push_back(Poz{getPozX()-i,getPozY()+i});
        if(isOnBoard(getPozX()-i,getPozY()-i))Vec->push_back(Poz{getPozX()-i,getPozY()-i});
    }
    for(int i=0;i<8;i++) {
        Vec->push_back(Poz{getPozX(), i});
        Vec->push_back(Poz{i, getPozY()});
    }
    return *Vec;
}

Queen::Queen() {
this->name = "Queen";
}


std::vector<Poz> &Bishop::moves() {
    auto *Vec = new std::vector<Poz>;
    for(int i=0;i<8;i++){
        if(isOnBoard(getPozX()+i,getPozY()+i))Vec->push_back(Poz{getPozX()+i,getPozY()+i});
        if(isOnBoard(getPozX()+i,getPozY()-i))Vec->push_back(Poz{getPozX()+i,getPozY()-i});
        if(isOnBoard(getPozX()-i,getPozY()+i))Vec->push_back(Poz{getPozX()-i,getPozY()+i});
        if(isOnBoard(getPozX()-i,getPozY()-i))Vec->push_back(Poz{getPozX()-i,getPozY()-i});
    }
    return *Vec;
}

Bishop::Bishop() {
this->name = "Bishop";
}





std::vector<Poz> &Knight::moves() {
    auto *Vec = new std::vector<Poz>;
    int k[] = {-1,1};
    for(int i:k) {
        for (int j:k) {
            if(isOnBoard(getPozX() + 2 * i, getPozY() + j))
                Vec->push_back(Poz{getPozX() + 2 * i, getPozY() + j});
            if(isOnBoard(getPozX() + i, getPozY() + j * 2))
                Vec->push_back(Poz{getPozX() + i, getPozY() + j * 2});
        }
    }

    return *Vec;
}

Knight::Knight() {
 this->name = "Knight";
}

std::vector<Poz> &Rook::moves() {
    auto *Vec = new std::vector<Poz>;
        for(int i=0;i<8;i++) {
            Vec->push_back(Poz{getPozX(), i});
            Vec->push_back(Poz{i, getPozY()});
        }

    return *Vec;
}



Rook::Rook() {
    this->name = "Rook";
}

std::vector<Poz> &Pawn::moves() {
    auto *Vec = new std::vector<Poz>;
    if(this->getColor() == 1) {
        Vec->push_back(Poz{getPozX(),getPozY()-1});
        if(getPozY()-2>=4)Vec->push_back(Poz{getPozX(),getPozY()-2});
    }else{
        Vec->push_back(Poz{getPozX(),getPozY()+1});
        if(getPozY()+2<=3)Vec->push_back(Poz{getPozX(),getPozY()+2});
    }
    return *Vec;
}

Pawn::Pawn() {
    this->name = "Pawn";
}

Blank::Blank() {
    this->name = "Blank";
    this->color = 2;
    this->setTexture("jpges/King_White.png");
    this->setSprite();
    this->getSprite().setColor(sf::Color(0,0,0,0));
}

std::vector<Poz> &Blank::moves() {
    auto *k=new std::vector<Poz>;
    return *k;
}
