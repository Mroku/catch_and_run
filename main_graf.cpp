#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<time.h>

enum dir{UP,RIGHT,DOWN,LEFT};


int main(){

srand (time(NULL));

unsigned int rozmiar = 500;

initwindow(rozmiar, rozmiar);


static int margines = 75;
int wynik = 0;
int life = 3;
char znak;
static int x = getmaxx()/2;
static int y = getmaxy()/2;
static int q = 100, w = 100;
static int e = 250, r = 100;
static dir direction = RIGHT;
int hit_box = 10;

static int enemy_number = 1;
static int enemy_count =0;

unsigned int enemy_speed =4;

getch();

do{

    if(kbhit()){
    znak = (char)getch();

    switch(znak){

                case KEY_UP:
                        std::cout << "Up key."     << std::endl;
                        //y=y-10;
                        direction = UP;
                        break;

                case KEY_LEFT:
                        std::cout << "Left key."   << std::endl;
                        //x=x-10;
                        direction = LEFT;
                        break;

                case KEY_DOWN:
                        std::cout << "Down key." << std::endl;
                        //y=y+10;
                        direction = DOWN;
                        break;

                case KEY_RIGHT:
                        std::cout << "Right key."  << std::endl;
                        //x=x+10;
                        direction = RIGHT;
                        break;

                default: break;

        }
    }
        cleardevice();

        switch(direction){
            case UP:
                y=y-10;
                break;
            case LEFT:
                x=x-10;
                break;
            case DOWN:
                y=y+10;
                break;
            case RIGHT:
                x=x+10;
                break;
            default:
                std::cout <<"ERROR DIRECTON" << std::endl;
                return 0;
                break;
        }



        outtextxy(10, 10, "Wynik: ");
        outtextxy(10, 30, "Lifes: ");


        outtextxy(x, y, "O");
        outtextxy(q, w, "F");
        rectangle(50,450,450,50);

    /*
    if(enemy_count<=enemy_number){

    }
    */
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



        outtextxy(e, r, "X");

        if((x>= e-hit_box && x<= e+hit_box)&&(y>= r-hit_box && y<= r+hit_box)){
            life--;
            x=getmaxx()/2;
            y=getmaxy()/2;
            e=100;
            r=50;
            Sleep(100);
            if(life < 0){
                outtextxy(x, y, "KONIEC GRY!!!");
                getch();
                return 0;
            }
        }


    if((x>=getmaxx()-50 || x<=getmaxx()-450 || y>=getmaxy()-50 || y<=getmaxy()-450)){
            x=getmaxx()/2;
            y=getmaxy()/2;
            life--;
            if(life < 0){
                outtextxy(x, y, "KONIEC GRY!!!");
                getch();
                return 0;
            }
    }

    if((x>= q-hit_box && x<= q+hit_box)&&(y>= w-hit_box && y<= w+hit_box)){
        wynik++;
        do{
                q=(rand()% (getmaxx() - margines)) + margines;
                w=(rand()% (getmaxy() - margines)) + margines;
        }while(!(q <= getmaxx() - margines && q >= margines && w <= getmaxy() - margines && w >= margines));

    std::cout << "Zlapano F. nowe wsp.: " << q << " , " << w << std::endl;
    std::cout << "Twoj wynik to: " << wynik << std::endl;
    }



Sleep(50);

}while(1);


return 0;
}
