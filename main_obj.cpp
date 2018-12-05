#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<time.h>


typedef unsigned int uint;
enum dir{UP,RIGHT,DOWN,LEFT};



////////////////////////////////////////////////////
class CWindow{
uint rozmiar;
uint wynik;
uint life;
uint hit_box;
uint margines;

public:
    CWindow(uint,uint,uint,uint);
    ~CWindow();
    bool refresh();
    bool control();


};
////////////////////////////////////////////////////
class CObject{
public:

    uint x;
    uint y;

    CObject();
    ~CObject();
    bool obj_move();
    bool colision();
};

class CPlayer :public CObject{
public:
    CPlayer();
    ~CPlayer();
    bool obj_move();
};

class CFood :public CObject{
public:
    CFood();
    ~CFood();
};

class CEnemy :public CObject{
public:
    CEnemy();
    ~CEnemy();
    bool obj_move();
};
////////////////////////////////////////////////////
CPlayer::CPlayer(){

}
////////////////////////////////////////////////////


////////////////////////////////////////////////////
CWindow::CWindow(uint _size, uint _life, uint _hit, uint _marg){
this->rozmiar = _size;
this->wynik = 0;
this->life = _life;
this->hit_box = _hit;
this->margines = _marg;
initwindow(this->rozmiar, this->rozmiar);
getch();
}

CWindow::~CWindow(){
closegraph();
}

bool CWindow::refresh(){

}

////////////////////////////////////////////////////



int main(){
srand (time(NULL));

CWindow W1(500, 3, 10, 50);
//CPlayer P1;

do{
    W1.refresh();
}while(1);


}
