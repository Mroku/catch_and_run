#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<time.h>


typedef unsigned int uint;
enum dir{UP,RIGHT,DOWN,LEFT};



////////////////////////////////////////////////////
class CObject{
public:

    uint x;
    uint y;

    CObject(uint _x, uint _y): x(_x), y(_y){};
    ~CObject(){};
    bool obj_move();
    bool colision();
    bool rep(){
    std::cout << "X: " <<this->x << "Y: " << this->y << std::endl;
    }
};

class CWindow{
    public:
uint rozmiar;
uint wynik;
uint life;
uint hit_box;
uint margines;


    CWindow(uint,uint,uint,uint);
    ~CWindow();
    bool refresh(CObject*, CObject*, CObject*);
    bool control();
    //bool collision();


};
////////////////////////////////////////////////////


class CPlayer :public CObject{
public:
    dir direction;
    CPlayer(uint _x, uint _y): CObject(_x, _y), direction(RIGHT){};
    ~CPlayer(){};
    dir get_direction();
    bool colision(CWindow*);
    bool obj_move();

};

class CFood :public CObject{
public:
    CFood(uint _x, uint _y): CObject(_x, _y){};
    ~CFood(){};
    bool colision(CPlayer*, CWindow*);
};

class CEnemy :public CObject{
public:
    uint enemy_speed;
    CEnemy(uint _x, uint _y, uint s): CObject(_x, _y), enemy_speed(s){};
    ~CEnemy(){};
    bool obj_move(CPlayer*);
    bool colision(CPlayer*, CWindow*);
};
////////////////////////////////////////////////////
dir CPlayer::get_direction(){

if(kbhit()){

    char znak = (char)getch();

    switch(znak){

                case KEY_UP:
                        std::cout << "Up key."     << std::endl;
                        //y=y-10;
                        this->direction = UP;
                        break;

                case KEY_LEFT:
                        std::cout << "Left key."   << std::endl;
                        //x=x-10;
                        this->direction = LEFT;
                        break;

                case KEY_DOWN:
                        std::cout << "Down key." << std::endl;
                        //y=y+10;
                        this->direction = DOWN;
                        break;

                case KEY_RIGHT:
                        std::cout << "Right key."  << std::endl;
                        //x=x+10;
                        this->direction = RIGHT;
                        break;

                default: break;

        }
    }
    switch( this-> direction){
            case UP:
                this->y=this->y-10;
                break;
            case LEFT:
                this->x=this->x-10;
                break;
            case DOWN:
                this->y=this->y+10;
                break;
            case RIGHT:
                this->x=this->x+10;
                break;
            default:
                std::cout <<"ERROR DIRECTON" << std::endl;
                break;
        }
}

bool CPlayer::colision(CWindow* W){

        if((this->x>=getmaxx()-50 || this->x<=getmaxx()-450 || this->y>=getmaxy()-50 || this->y<=getmaxy()-450)){
            this->x=getmaxx()/2;
            this->y=getmaxy()/2;
            W->life--;
            if(W->life == 0){
                outtextxy(this->x, this->y, "KONIEC GRY!!!");
                W->life = 3;
                W->wynik = 0;
                getch();
                return 0;
            }
            std::cout << "Life: " << W->life << std::endl;
        }

}
////////////////////////////////////////////////////
bool CFood::colision(CPlayer* P, CWindow* W){
if((P->x>= this->x-W->hit_box && P->x<= this->x+W->hit_box)&&(P->y>= this->y-W->hit_box && P->y<= this->y+W->hit_box)){
        W->wynik++;
        do{
                this->x=(rand()% (getmaxx() - W->margines)) + W->margines;
                this->y=(rand()% (getmaxy() - W->margines)) + W->margines;
        }while(!(this->x <= getmaxx() - W->margines && this->x >= W->margines && this->y <= getmaxy() - W->margines && this->y >= W->margines));

    std::cout << "Zlapano F. nowe wsp.: " << this->x << " , " << this->y << std::endl;
    std::cout << "Twoj wynik to: " << W->wynik << std::endl;
    }
}
////////////////////////////////////////////////////
bool CEnemy::colision(CPlayer* P, CWindow* W){

uint& Px = P->x;
uint& Py = P->y;
uint& e = this->x;
uint& r = this->y;
uint& hit_box = W->hit_box;

if((Px>= e-hit_box && Px<= e+hit_box)&&(Py>= r-hit_box && Py<= r+hit_box)){
            W->life--;
            Px=getmaxx()/2;
            Py=getmaxy()/2;
            e=100;
            r=50;


            Sleep(100);
            if(W->life == 0){
                outtextxy(Px, Py, "KONIEC GRY!!!");
                W->life = 3;
                W->wynik = 0;
                getch();
                return 0;
            }
            std::cout << "Life: " << W->life << std::endl;
        }

}
////////////////////////////////////////////////////
bool CEnemy::obj_move(CPlayer* P){

uint& x = P->x;
uint& y = P->y;
uint& e = this->x;
uint& r = this->y;
uint& enemy_speed = this-> enemy_speed;

if(x<e && y>r){
            e=e-enemy_speed;
            r=r+enemy_speed;
        }else if(x>e && y>r){
            e=e+enemy_speed;
            r=r+enemy_speed;
        }else if(x>e && y<r){
            e=e+enemy_speed;
            r=r-enemy_speed;
        }else if(x<e && y<r){
            e=e-enemy_speed;
            r=r-enemy_speed;
        }

}
////////////////////////////////////////////////////
CWindow::CWindow(uint _size, uint _life, uint _hit, uint _marg){
this->rozmiar = _size;
this->wynik = 0;
this->life = _life+1;
this->hit_box = _hit;
this->margines = _marg;
initwindow(this->rozmiar, this->rozmiar);
outtextxy(getmaxx()/2 -100, getmaxy()/2, "Streowanie strzalkami");
outtextxy(getmaxx()/2 - 150, getmaxy()/2 - 20, "Nacisnij dowolny klawisz aby kontynuowac");
getch();
}

CWindow::~CWindow(){
closegraph();
}

bool CWindow::refresh(CObject* P, CObject* F, CObject* X){
    char arr[50];

    cleardevice();
    rectangle(50,450,450,50);
    ////
    outtextxy(P->x, P->y, "O");
    outtextxy(F->x, F->y, "F");
    outtextxy(X->x, X->y, "X");

        sprintf(arr, "Wynik: %d", this->wynik);
        outtextxy(10, 10, arr);
        sprintf(arr, "Lifes: %d", this->life);
        outtextxy(10, 30, arr);
    ////
}

////////////////////////////////////////////////////




int main(){
srand (time(NULL));

CWindow W1(500, 3, 10, 75);
CPlayer P1(0,0);
CFood F1(100,100);
CEnemy X1(200,100,4);

do{
    P1.get_direction();

    P1.colision(&W1);
    F1.colision(&P1, &W1);
    X1.colision(&P1, &W1);
    X1.obj_move(&P1);
    W1.refresh(&P1, &F1, &X1);



    Sleep(100);
}while(1);


}
