//
// Created by Mirek on 19.05.2020.
//

#ifndef CHESSAI_FIGURE_H
#define CHESSAI_FIGURE_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
bool isOnBoard(int x,int y);

struct Poz{
    int x;
    int y;
};
class Figure {
protected:
    std::string name="name";
    int color=1; // White
    bool dragging=false;
    Poz MyPoz{0,0};
    sf::Texture texture;
    sf::Sprite sprite;

public:

    virtual ~Figure() {};
    void makeBlack();
    void Drag();
    void unDrag();
    bool isDragged();
    void setPoz(int x,int y);
    int getPozX();
    int getPozY();
    int getColor();
    std::string getName();
    void setTexture(std::string path);
    void setSprite();
    void setSpritePoz(int x,int y);
    sf::Sprite& getSprite();
    sf::Texture& getTexture();
    virtual std::vector<Poz>& moves()=0;

    friend class Chess;
};

class Pawn:public Figure{
private:

public:
    std::vector<Poz>& moves() override;;
    ~Pawn() override= default;;
    Pawn();

    friend class Chess;

};

class Rook: public Figure{
public:
    Rook();
    ~Rook() override= default;
    std::vector<Poz>& moves() override;
    friend class Chess;
};

class Knight: public Figure{
public:
    Knight();
    ~Knight() override= default;
    std::vector<Poz>& moves() override;
    friend class Chess;
};
class Bishop: public Figure{
public:
    Bishop();
    ~Bishop() override= default;
    std::vector<Poz>& moves() override;
    friend class Chess;
};

class Queen: public Figure{
public:
    Queen();
    ~Queen() override= default;
    std::vector<Poz>& moves() override;
    friend class Chess;
};
class King: public Figure{
public:
    King();
    ~King() override= default;
    std::vector<Poz>& moves() override;
    friend class Chess;
};

class Blank:public Figure{

public:
    Blank();
    ~Blank() override=default;
    std::vector<Poz>& moves() override;
    friend class Chess;
};

bool isRealFigure(Figure *object);



#endif //CHESSAI_FIGURE_H
