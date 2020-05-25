//
// Created by Mirek on 19.05.2020.
//
#define Infinity 1000000;


#include "Chess.h"

Chess::Chess() {
//INITIALIZATION
for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        Board[i][j]= new Blank;
    }
}
    //Black

    for(auto & i : Board){
        i[1] =new Pawn;
        i[1]->setTexture("jpges/Pawn_Black.png");
    }
    Board[0][0]= new Rook;
    Board[0][0]->setTexture("jpges/Rook_Black.png");
    Board[1][0] = new Knight;
    Board[1][0]->setTexture("jpges/Knight_Black.png");
    Board[2][0] = new Bishop;
    Board[2][0]->setTexture("jpges/Bishop_Black.png");
    Board[3][0] = new King;
    Board[3][0]->setTexture("jpges/King_Black.png");
    Board[4][0] = new Queen;
    Board[4][0]->setTexture("jpges/Queen_Black.png");
    Board[7][0]= new Rook;
    Board[7][0]->setTexture("jpges/Rook_Black.png");
    Board[6][0] = new Knight;
    Board[6][0]->setTexture("jpges/Knight_Black.png");
    Board[5][0] = new Bishop;
    Board[5][0]->setTexture("jpges/Bishop_Black.png");
    //painting for black
    for(auto & i : Board){
        i[0]->makeBlack();
        i[1]->makeBlack();
    }

//White
    for(auto & i : Board){
        i[6] = new Pawn;
        i[6]->setTexture("jpges/Pawn_White.png");
    }
    Board[0][7]= new Rook;
    Board[0][7]->setTexture("jpges/Rook_White.png");
    Board[1][7] = new Knight;
    Board[1][7]->setTexture("jpges/Knight_White.png");
    Board[2][7] = new Bishop;
    Board[2][7]->setTexture("jpges/Bishop_White.png");
    Board[4][7] = new King;
    Board[4][7]->setTexture("jpges/King_White.png");
    Board[3][7] = new Queen;
    Board[3][7]->setTexture("jpges/Queen_White.png");
    Board[7][7]= new Rook;
    Board[7][7]->setTexture("jpges/Rook_White.png");
    Board[6][7] = new Knight;
    Board[6][7]->setTexture("jpges/Knight_White.png");
    Board[5][7] = new Bishop;
    Board[5][7]->setTexture("jpges/Bishop_White.png");
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            try {

                typeid(*Board[i][j]).name();
                Board[i][j]->setSprite();
            }catch(std::bad_typeid& error){
                //TUTAJ NIC NIE ROBI
            }
        }
    }
}
void Chess::GameIsON() {
    std::cout<<"Game is On !\n";

    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess by 244117");
    sf::RectangleShape move(sf::Vector2f(100.f,100.f));
    sf::RectangleShape attack(sf::Vector2f(100.f,100.f));
    move.setFillColor(sf::Color(0, 255, 0, 64));
    attack.setFillColor(sf::Color(255,0,0,64));
    sf::Texture t1;
    int a=0,b=0,c=0,d=0;//Mouse drag variables
    t1.loadFromFile("jpges/Board.png");
    sf::Sprite board(t1);
    // window.draw(square2);

    //Game
        bool WhiteKingMoved=false, WhiteRightRookMoved=false, WhiteLeftRookMoved=false;
        bool BlackKingMoved=false, BlackRightRookMoved=false, BlackLeftRookMoved=false;
        int win=-1; //WINNING CONDITION
        while(window.isOpen() && win < 0){
            int white = 0,black =0;//
//BOT IS COMING
            if(bot==1 && botcolor == turn)this->AIMove(botcolor);
        window.clear();
        window.draw(board);
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {

            int x = (int) event.mouseButton.x / 100;
            int y = (int) event.mouseButton.y / 100;

            if (isOnBoard(x, y) && Board[x][y]->name != "Blank" && Board[x][y]->getColor() == turn) {
                a=x;
                b=y;
                Board[a][b]->Drag();
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {

            Board[a][b]->unDrag();
            int x = (int) c / 100, y = (int) d / 100;
            std::cout << x << "|" << y << "\n";
            if (isOnBoard(x, y) && (a!=x || b!=y)) {


                if(Board[x][y]->getColor() != Board[a][b]->getColor() && !ifColide(a,b,x,y)) {//Dont beat yourself
                    int check = 0;
                    for (auto k:Board[a][b]->moves()) {// IS it possible ?
                        if(Board[a][b]->getName()=="Rook")std::cout<<"Rook at"<<a<<"|"<<b<<"move from "<<x<<"|"<<y<<" To "<<k.x<<"|"<<k.y<<"\n";
                        if (k.x == x && k.y == y)check=1;
                    }
                    //Pawn's attack
                    if(Board[a][b]->getName() == "Pawn" && Board[x][y]->getName() != "Blank"){
                        switch(Board[a][b]->getColor()){
                            case 1:

                                if(x==a+1 || x==a-1)check = 1;
                                if(y==b-1 && x==a){
                                    check = 0;
                                    std::cout<<"White attacks from "<<a<<"|"<<b<<" To "<<x<<"|"<<y<<"\n";
                                }
                                break;

                            case 0:
                                std::cout<<"Black attacks from "<<a<<"|"<<b<<" To "<<x<<"|"<<y<<"\n";
                                if(x==a+1 || x==a-1)check = 1;
                                if(y==b+1 && x==a)check = 0;
                                break;
                        }
                    }
                    //Castling
                    if(a==3 && b==0 && y==b && !BlackKingMoved){// Black King
                        if(x==1 && !BlackLeftRookMoved){//To left
                            Board[x][y] = Board[a][b];
                            Board[a][b]= new Blank;
                            Board[2][0]=Board[0][0];
                            Board[0][0] = new Blank;
                            BlackKingMoved = true;
                            check = 0;
                            turn = (turn + 1) % 2;
                        }else if(x==6 && !BlackRightRookMoved){//To Right
                            Board[x][y] = Board[a][b];
                            Board[a][b]= new Blank;
                            Board[5][0]=Board[7][0];
                            Board[7][0] = new Blank;
                            BlackKingMoved = true;
                            check = 0;
                            turn = (turn + 1) % 2;
                        }
                    }else if(a==4 && b==7 && y==b && !WhiteKingMoved){//White King
                        if(x==1 && !WhiteLeftRookMoved){
                            Board[x][y] = Board[a][b];
                            Board[a][b]= new Blank;
                            Board[2][y]=Board[0][7];
                            Board[0][7] = new Blank;
                            WhiteKingMoved = true;
                            check = 0;
                            turn = (turn + 1) % 2;
                        }else if(x==6 && !WhiteRightRookMoved){
                            Board[x][y] = Board[a][b];
                            Board[a][b]= new Blank;
                            Board[5][y]=Board[7][7];
                            Board[7][7] = new Blank;
                            WhiteKingMoved = true;
                            check = 0;
                            turn = (turn + 1) % 2;
                        }
                    }
                    if (check == 1 ) {
                        //checking if castling's figures moved
                        if(a==0 && b==0)BlackLeftRookMoved=true;
                        if(a==7 && b==0)BlackRightRookMoved=true;
                        if(a==0 && b==7)WhiteLeftRookMoved=true;
                        if(a==7 && b==7)WhiteRightRookMoved=true;
                        if(a==3 && b==0)BlackKingMoved=true;
                        if(a==4 && b==7)WhiteKingMoved=true;
                        /////////////////////////////////////
                        //Promotion
                        if(Board[a][b]->getName()=="Pawn" && Board[a][b]->getColor()==1 && y==0){
                            Board[a][b]=new Queen;
                            Board[a][b]->setTexture("jpges/Queen_White.png");
                            Board[a][b]->setSprite();
                        }else if(Board[a][b]->getName()=="Pawn" && Board[a][b]->getColor()==0 && y==7){
                            Board[a][b]=new Queen;
                            Board[a][b]->makeBlack();
                            Board[a][b]->setTexture("jpges/Queen_Black.png");
                            Board[a][b]->setSprite();
                        }
                        turn = (turn + 1) % 2;
                        Board[x][y] = Board[a][b];
                        Board[a][b] = new Blank;
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            d = event.mouseMove.y;
            c = event.mouseMove.x;
        }
    }


    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            try{
            if(Board[i][j]->name !="Blank") {
                Board[i][j]->setPoz(i, j);
                if(Board[i][j]->getColor() == 1 && Board[i][j]->getName() == "King")white++;
                if(Board[i][j]->getColor() == 0 && Board[i][j]->getName() == "King")black++;
                if (Board[i][j]->isDragged()) {
                    //DRAWING POSSIBLE MOVES NOT IMPORTANT
//                    for(auto m:Board[i][j]->moves()){
//                        if(isOnBoard(m.x,m.y) && Board[m.x][m.y]->getColor() != Board[i][j]->getColor()){
//                        }
//                    }
                    Board[i][j]->setSpritePoz(c-50, d-50);
                } else {
                    Board[i][j]->setSpritePoz(i * 100, j * 100);
                }

                window.draw(Board[i][j]->getSprite()); // Drawing
            }
            }catch(...){
                std::cout<<"nie ma rysowania\n";
            }
        }
    }
    window.display();
    if(black == 0)win = 1;
    if(white == 0)win = 0;
        }
        window.clear();
        if(win==1){
            //white win
        }else if(win == 0){
            //black win
        }
        window.display();
        //delay
        state = 0;
}
bool Chess::ifColide(int x1,int y1,int x2,int y2){//if there is a Figure  => returns TRUE
    if(Board[x1][y1]->getName()=="Knight")return false;
    if(x1>x2)x1--;else if(x1<x2)x1++;
    if(y1<y2)y1++;else if (y1>y2)y1--;

        while(x1 !=x2 || y1 != y2){
            if(Board[x1][y1]->getName() != "Blank")return true;
            if(x1>x2)x1--;else if(x1<x2)x1++;
            if(y1<y2)y1++;else if (y1>y2)y1--;
        }
        return false;
}

void Chess::AIMove(int color) {
    BruteForce BOT;
    BOT.loadBoard(this->Board);
    auto newMove = BOT.MinMaxAlgorithm(botlvl, botcolor);
    Board[newMove.second.x][newMove.second.y] =Board[newMove.first.x][newMove.first.y];
    Board[newMove.first.x][newMove.first.y] = new Blank;
    turn = (turn + 1) % 2;
}
