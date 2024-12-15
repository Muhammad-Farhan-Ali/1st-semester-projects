#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<conio.h>
#include<windows.h>

using namespace std;

void gotoxy(int x,int y);
char getCharAtxy(short int x,short int y);

void printmaze();
void title();
void howToPlay();
void win();
void lose();

void printplayerright();
void printplayerleft();
void eraseplayer();

void moveplayerright();
void moveplayerleft();

void moveplayerdown();
void moveplayerup();
void playershoot();
void showBullets();

void player();

void print_enemy1();
void erase_enemy1();
void e1state();
void move_enemy1();

void print_enemy2();
void erase_enemy2();
void e2state();
void move_enemy2();

void print_enemy3();
void shoot_enemy3();

void gamestate(int state);
void checkstate();
void checkscore();
void checkhealth();

void readFromFile(int highscore[]);
void WriteToFile();

int px=7,py=3;                          //for player movement 
int e1x=63,e1y=9;                       //for enemy 1 movement 
int e2x=63,e2y=13;                      //for enemy 2 movement 

int e3x=28,e3y=28;                      //for enemy 3 bullet movement

int bx,by;
bool gameover;

int position=0;
int e1position=0;
int e2position=0;

int score=0;
int health=100;

bool bullets[10]={1,1,1,1,1,1,1,1,1,1};
int bulletindex=0;

int highscore[20];
int highestScore=0;
int highscoreIndex=0;

int main()
{
    system("Color 02");
    char option;
    readFromFile(highscore);

    int max=highscore[0];
    for(int i=1;i<sizeof(highscore)/sizeof(highscore[0]);i++)
    {
        if(highscore[i]>max)
        {
            max=highscore[i];
        }
    }
    highestScore=max;

    while(true)
    {
        
        option=' ';

        system("cls");
        do{
            title();
            option=getch();
            system("cls");
        }while(option!='1' && option!='2' && option!='3');

        if(option=='1')
        {
            printmaze();
            printplayerright();
            print_enemy1();
            print_enemy2();
            print_enemy3();

            while(true)
            {
                if(health==0)
                {
                    gameover=false;
                    break;
                }

                if(px>=100 && py>=31)
                {
                    gameover=true;
                    break;
                }

                player();
                move_enemy1();
                move_enemy2();
                shoot_enemy3();
                checkscore();
                checkhealth();
                showBullets();
            }

            if(gameover)
            {
                system("cls");
                win();
                //for highscore
                for(int i=0;i<sizeof(highscore)/sizeof(highscore[0]);i++)
                {
                    if(highscore[i]==0)
                    {
                        highscoreIndex=i;
                        break;
                    }
                }
                highscore[highscoreIndex]=score;
                if(score>highestScore)
                {
                    highestScore=score;
                }
                WriteToFile();
                //for highscore
                break;
            }
            else
            {
                if(score<0)
                {
                    score=0;
                }
                system("cls");
                lose();
                //for highscore
                for(int i=0;i<sizeof(highscore)/sizeof(highscore[0]);i++)
                {
                    if(highscore[i]==0)
                    {
                        highscoreIndex=i;
                        break;
                    }
                }
                highscore[highscoreIndex]=score;
                if(score>highestScore)
                {
                    highestScore=score;
                }
                WriteToFile();
                //for highscore
                break;
            }

            
        }
        else if(option=='2')
        {
            howToPlay();
            getch();
        }
        else
        {
            break;
        }
    } 
    

    return 0;
}

void gotoxy(int x,int y)
{
    COORD coordinates;
    coordinates.X=x;
    coordinates.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}
char getCharAtxy(short int x,short int y)
{
    CHAR_INFO ci;
    COORD xy = {0,0};
    SMALL_RECT rect = {x,y,x,y};
    COORD coordBufSize;
    coordBufSize.X=1;
    coordBufSize.Y=1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),&ci,coordBufSize,xy,&rect)?ci.Char.AsciiChar : ' ';
}

void gamestate(int state)           //% barriers remove krnay k liye 
{
    if(state==1)                    //first % barrier remove krnay k liye
    {
    gotoxy(53,7);
    cout<<" ";
    gotoxy(53,8);
    cout<<" ";
    gotoxy(53,9);
    cout<<" ";
    gotoxy(53,10);
    cout<<" ";
    gotoxy(53,11);
    cout<<" ";
    score+=500;
    }
    
    if(state==2)                     //second % barrier remove krnay k liye
    {
    gotoxy(106,19);
    cout<<" ";
    gotoxy(106,20);                
    cout<<" ";
    gotoxy(106,21);
    cout<<" ";
    gotoxy(106,22);
    cout<<" ";
    gotoxy(106,23);
    cout<<" ";
    score+=500;
    }

    if(state==3)                     //third % barrier remove krnay k liye
    {
    gotoxy(47,30);
    cout<<"             ";
    score+=1000;
    }

    if(state==4)                     //fourth % barrier remove krnay k liye
    {
    gotoxy(78,31);
    cout<<" ";
    gotoxy(78,32);                
    cout<<" ";
    gotoxy(78,33);
    cout<<" ";
    gotoxy(78,34);
    cout<<" ";
    gotoxy(78,35);
    cout<<" ";
    score+=2000;
    }

}
void checkstate()                   // for checking state of game i.e gamestate
{
    if(((getCharAtxy(px+7,py) == '@') || (getCharAtxy(px+7,py+1) == '@') || (getCharAtxy(px+7,py+2) == '@')) 
    || ((getCharAtxy(px-1,py) == '@') || (getCharAtxy(px-1,py+1) == '@') || (getCharAtxy(px-1,py+2) == '@')))
        {
            if(py<6)                     //for first @ in maze
            {
            gamestate(1);
            }
            else if(py>6 && py<21)       //for second @ in maze
            {
            gamestate(2);
            } 
            else if(py>21 && py<30)       //for third @ in maze
            {
            gamestate(3);
            } 
            else if(py>30 && py<37)       //for forth @ in maze
            {
            gamestate(4);
            } 

        }
}
void checkscore()
{
    if(score<0)
    {
        score=0;
    }
    gotoxy(0,37);
    cout<<"Score:       ";
    gotoxy(0,37);
    cout<<"Score:"<<score;

    gotoxy(50,37);
    cout<<"Highscore:       ";
    gotoxy(50,37);
    cout<<"Highscore:"<<highestScore;
}
void checkhealth()
{
    //right ki collision
    if(getCharAtxy(px+7,py)!=' ' && getCharAtxy(px+7,py)!='@' && getCharAtxy(px+7,py)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+7,py+1)!=' ' && getCharAtxy(px+7,py+1)!='@' && getCharAtxy(px+7,py+1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+7,py+2)!=' ' && getCharAtxy(px+7,py+2)!='@' && getCharAtxy(px+7,py+2)!='#')
    {
        health-=5;
        score-=10;
    }
    //right ki collision

    //left ki collision
    if(getCharAtxy(px-1,py)!=' ' && getCharAtxy(px-1,py)!='@' && getCharAtxy(px-1,py)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px-1,py+1)!=' ' && getCharAtxy(px-1,py+1)!='@' && getCharAtxy(px-1,py+1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px-1,py+2)!=' ' && getCharAtxy(px-1,py+2)!='@' && getCharAtxy(px-1,py+2)!='#')
    {
        health-=5;
        score-=10;
    }
    //left ki collision

    //up ki collision
    if(getCharAtxy(px,py-1)!=' ' && getCharAtxy(px,py-1)!='@' && getCharAtxy(px,py-1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+1,py-1)!=' ' && getCharAtxy(px+1,py-1)!='@' && getCharAtxy(px+1,py-1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+2,py-1)!=' ' && getCharAtxy(px+2,py-1)!='@' && getCharAtxy(px+2,py-1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+3,py-1)!=' ' && getCharAtxy(px+3,py-1)!='@' && getCharAtxy(px+3,py-1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+4,py-1)!=' ' && getCharAtxy(px+4,py-1)!='@' && getCharAtxy(px+4,py-1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+5,py-1)!=' ' && getCharAtxy(px+5,py-1)!='@' && getCharAtxy(px+5,py-1)!='#')
    {
        health-=5;
        score-=10;
    }
    else if(getCharAtxy(px+6,py-1)!=' ' && getCharAtxy(px+6,py-1)!='@' && getCharAtxy(px+6,py-1)!='#')
    {
        health-=5;
        score-=10;
    }
    //up ki collision

    //down ki collision
    if(py<23)
    {
        if(getCharAtxy(px,py+3)!=' ' && getCharAtxy(px,py+3)!='@' && getCharAtxy(px,py+3)!='#')
        {
            health-=5;
            score-=10;
        }
        else if(getCharAtxy(px+1,py+3)!=' ' && getCharAtxy(px+1,py+3)!='@' && getCharAtxy(px+1,py+3)!='#')
        {
            health-=5;
            score-=10;
        }
        else if(getCharAtxy(px+2,py+3)!=' ' && getCharAtxy(px+2,py+3)!='@' && getCharAtxy(px+2,py+3)!='#')
        {
            health-=5;
            score-=10;
        }
        else if(getCharAtxy(px+3,py+3)!=' ' && getCharAtxy(px+3,py+3)!='@' && getCharAtxy(px+3,py+3)!='#')
        {
            health-=5;
            score-=10;
        }
        else if(getCharAtxy(px+4,py+3)!=' ' && getCharAtxy(px+4,py+3)!='@' && getCharAtxy(px+4,py+3)!='#')
        {
            health-=5;
            score-=10;
        }
        else if(getCharAtxy(px+5,py+3)!=' ' && getCharAtxy(px+5,py+3)!='@' && getCharAtxy(px+5,py+3)!='#')
        {
            health-=5;
            score-=10;
        }
        else if(getCharAtxy(px+6,py+3)!=' ' && getCharAtxy(px+6,py+3)!='@' && getCharAtxy(px+6,py+3)!='#')
        {
            health-=5;
            score-=10;
        }
    }
    //down ki collision

    gotoxy(0,38);
    cout<<"Health:   "; 
    gotoxy(0,38);
    cout<<"Health:"<<health; 
}


void printmaze()
{
system("cls");
cout<<"|#########################################################################################################################|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                                                                                                               @       #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#######################################             #####################################################################|"<<endl;
cout<<"|#                                                   %                                                                   #|"<<endl;
cout<<"|#                                                   %                                                                   #|"<<endl;
cout<<"|#                                                   %                                                                   #|"<<endl;
cout<<"|#                                                   %                                                                   #|"<<endl;
cout<<"|#                                                   %                                                                   #|"<<endl;
cout<<"|###########################################################################################################             #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                @                                                                                                      #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#             ############################################             ##################################################|"<<endl;
cout<<"|#                                                                                                        %              #|"<<endl;
cout<<"|#                                                                                                        %              #|"<<endl;
cout<<"|#                                                                                                        %              #|"<<endl;
cout<<"|#                                                                                                        %              #|"<<endl;
cout<<"|#                                                                                                        %              #|"<<endl;
cout<<"|##########################################################################################################              #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#   @                                                                                                                   #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|#                                                                                                                       #|"<<endl;
cout<<"|##############################################%%%%%%%%%%%%%##############################################################|"<<endl;
cout<<"|#                                                                            %                                          #|"<<endl;
cout<<"|#                                                                            %                               ____       #|"<<endl;
cout<<"|#   @                                                                        %                              |    |      #|"<<endl;
cout<<"|#                                                                            %                              |.   |      #|"<<endl;
cout<<"|#                                                                            %                              |    |      #|"<<endl;
cout<<"|#########################################################################################################################|"<<endl;
}

void title()
{
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#   ######   #####   ####    #####   #####   ######    ######  ##  ##  ######    ##    ##   #####   ######  ######    #"<<endl;
    cout<<"#   ##      ##      ##  ##  ##   ##  ##  ##  ##          ##    ##  ##  ##        ########  ##   ##     ##   ##        #"<<endl;
    cout<<"#   ######    ##    ##      #######  #####   ######      ##    ######  ######    ## ## ##  #######    ##    ######    #"<<endl;
    cout<<"#   ##          ##  ##  ##  ##   ##  ##      ##          ##    ##  ##  ##        ##    ##  ##   ##   ##     ##        #"<<endl;
    cout<<"#   ######  #####    ####   ##   ##  ##      ######      ##    ##  ##  ######    ##    ##  ##   ##  ######  ######    #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                         1.     START                                                                #"<<endl;
    cout<<"#                                         2.  HOW TO PLAY                                                             #"<<endl;
    cout<<"#                                         3.      EXIT                                                                #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                         SELECT ANY OPTION!                                                          #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
}

void howToPlay()
{
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#   ######   #####   ####    #####   #####   ######    ######  ##  ##  ######    ##    ##   #####   ######  ######    #"<<endl;
    cout<<"#   ##      ##      ##  ##  ##   ##  ##  ##  ##          ##    ##  ##  ##        ########  ##   ##     ##   ##        #"<<endl;
    cout<<"#   ######    ##    ##      #######  #####   ######      ##    ######  ######    ## ## ##  #######    ##    ######    #"<<endl;
    cout<<"#   ##          ##  ##  ##  ##   ##  ##      ##          ##    ##  ##  ##        ##    ##  ##   ##   ##     ##        #"<<endl;
    cout<<"#   ######  #####    ####   ##   ##  ##      ######      ##    ##  ##  ######    ##    ##  ##   ##  ######  ######    #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                 HOW TO PLAY                                                         #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                            USE ARROW KEYS TO MOVE                                                   #"<<endl;
    cout<<"#                                          SPACEBAR TO SHOOT BULLETS                                                  #"<<endl;
    cout<<"#                                     DODGE ENEMIES TO PREVENT HEALTH LOSE                                            #"<<endl;
    cout<<"#                                            COLLECT @ TO OPEN DOORS                                                  #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                           PRESS ANY KEY TO GO BACK                                                  #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
}
void win()
{
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#   ######   #####   ####    #####   #####   ######    ######  ##  ##  ######    ##    ##   #####   ######  ######    #"<<endl;
    cout<<"#   ##      ##      ##  ##  ##   ##  ##  ##  ##          ##    ##  ##  ##        ########  ##   ##     ##   ##        #"<<endl;
    cout<<"#   ######    ##    ##      #######  #####   ######      ##    ######  ######    ## ## ##  #######    ##    ######    #"<<endl;
    cout<<"#   ##          ##  ##  ##  ##   ##  ##      ##          ##    ##  ##  ##        ##    ##  ##   ##   ##     ##        #"<<endl;
    cout<<"#   ######  #####    ####   ##   ##  ##      ######      ##    ##  ##  ######    ##    ##  ##   ##  ######  ######    #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                   YOU WIN!                                                          #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                             YOUR SCORE:"<<setw(4)<<score<<"                                                         #"<<endl;
    cout<<"#                                              HIGHSCORE:"<<setw(4)<<highestScore<<"                                                         #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
}
void lose()
{
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#   ######   #####   ####    #####   #####   ######    ######  ##  ##  ######    ##    ##   #####   ######  ######    #"<<endl;
    cout<<"#   ##      ##      ##  ##  ##   ##  ##  ##  ##          ##    ##  ##  ##        ########  ##   ##     ##   ##        #"<<endl;
    cout<<"#   ######    ##    ##      #######  #####   ######      ##    ######  ######    ## ## ##  #######    ##    ######    #"<<endl;
    cout<<"#   ##          ##  ##  ##  ##   ##  ##      ##          ##    ##  ##  ##        ##    ##  ##   ##   ##     ##        #"<<endl;
    cout<<"#   ######  #####    ####   ##   ##  ##      ######      ##    ##  ##  ######    ##    ##  ##   ##  ######  ######    #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                   YOU LOSE!                                                         #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                             YOUR SCORE:"<<setw(4)<<score<<"                                                         #"<<endl;
    cout<<"#                                              HIGHSCORE:"<<setw(4)<<highestScore<<"                                                         #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#                                                                                                                     #"<<endl;
    cout<<"#######################################################################################################################"<<endl;
}


void printplayerright()
{
    gotoxy(px,py);
    cout<<" ('') /"<<endl;
    gotoxy(px,py+1);
    cout<<" /__\\/"<<endl;
    gotoxy(px,py+2);
    cout<<" \\/\\/"<<endl;
}
void printplayerleft()
{
    gotoxy(px,py);
    cout<<"\\ ('') "<<endl;
    gotoxy(px,py+1);
    cout<<" \\/__\\"<<endl;
    gotoxy(px,py+2);
    cout<<"  \\/\\/"<<endl;
}
void eraseplayer()
{
    gotoxy(px,py);
    cout<<"       "<<endl;
    gotoxy(px,py+1);
    cout<<"       "<<endl;
    gotoxy(px,py+2);
    cout<<"       "<<endl;
}

void moveplayerright()
{
    if(((getCharAtxy(px+7,py) == ' ') && (getCharAtxy(px+7,py+1) == ' ') && (getCharAtxy(px+7,py+2) == ' '))
    || (getCharAtxy(px+7,py) == '@') || (getCharAtxy(px+7,py+1) == '@') || (getCharAtxy(px+7,py+2) == '@'))
    {
        checkstate();
        eraseplayer();
        px=px+1;
        printplayerright();
        Sleep(1);
        position=0;
    }
}
void moveplayerleft()
{
    if(((getCharAtxy(px-1,py) == ' ') && (getCharAtxy(px-1,py+1) == ' ') && (getCharAtxy(px-1,py+2) == ' '))
    || ((getCharAtxy(px-1,py) == '@') || (getCharAtxy(px-1,py+1) == '@') || (getCharAtxy(px-1,py+2) == '@')))
    {
        checkstate();
        eraseplayer();
        px=px-1;
        printplayerleft();
        Sleep(1);
        position++;
    }
}

void moveplayerdown()
{
    if(position==0)
    {
        if((getCharAtxy(px,py+3)==' ') && (getCharAtxy(px+6,py+3)==' '))
        {
            eraseplayer();
            py=py+1;
            printplayerright();
            Sleep(50);
        }
    }
    else if(position!=0)
    {
        if((getCharAtxy(px,py+3)==' ') && (getCharAtxy(px+6,py+3)==' '))
        {
            eraseplayer();
            py=py+1;
            Sleep(50);
            printplayerleft();
        }
    }
}
void moveplayerup()
{
    if(position==0)
    {
        if((getCharAtxy(px,py-1)==' ') && (getCharAtxy(px+6,py-1)==' '))
        {
            eraseplayer();
            py=py-1;
            printplayerright();
            Sleep(50);
        }
    }
    else if(position!=0)
    {
        if((getCharAtxy(px,py-1)==' ') && (getCharAtxy(px+6,py-1)==' '))
        {
            eraseplayer();
            py=py-1;
            Sleep(50);
            printplayerleft();
        }
    }
}
void playershoot()
{
    if(bullets[bulletindex])
    {
        if(position==0)
        {
            bx=px+9;
            by=py;
        }
        else 
        {
            bx=px-2;
            by=py;
        }
        for(int i=0;i<20;i++)
        {
            if(getCharAtxy(bx+2,by)==' ' && (getCharAtxy(px+9,py)!='@' && getCharAtxy(px+2,py)!='#') && position==0)
            {
                gotoxy(bx,by);
                cout<<"  "<<endl;
                bx=bx+1;
                gotoxy(bx,by);
                cout<<"->"<<endl;
                Sleep(1);
                gotoxy(bx,by);
                cout<<"  "<<endl;

                //bullet k liye score
                if(getCharAtxy(bx+2,by)!=' ' && getCharAtxy(bx+2,by)!='@' && getCharAtxy(bx+2,by)!='#')
                {
                    score=score+5;
                }
                //bullet k liye score
            }
            else if(getCharAtxy(bx-1,by)==' ' && (getCharAtxy(px-1,py)!='@' || getCharAtxy(px-1,py)!='#') && position!=0)
            {
                gotoxy(bx,by);
                cout<<"  "<<endl;
                bx=bx-1;
                gotoxy(bx,by);
                cout<<"<-"<<endl;
                Sleep(1);
                gotoxy(bx,by);
                cout<<"  "<<endl;
                //bullet k liye score
                if(getCharAtxy(bx-1,by)!=' ' && getCharAtxy(bx-1,by)!='@' && getCharAtxy(bx-1,by)!='#')
                {
                    score=score+5;
                }
                //bullet k liye score
            }
        }
        bullets[bulletindex]=0;
        bulletindex++;
    }
}
void showBullets()
{
    int numBullets=0;
    for(int i=0;i<sizeof(bullets)/sizeof(bullets[0]);i++)
    {
        if(bullets[i])
        {
            numBullets++;
        }
    }
    gotoxy(0,39);
    cout<<"Bullets:    ";
    gotoxy(0,39);
    cout<<"Bullets: "<<numBullets<<endl;
}

void player()
{    
    if(GetAsyncKeyState(VK_RIGHT))
    {
        moveplayerright();
    }
    else if(GetAsyncKeyState(VK_LEFT))
    {
        moveplayerleft();
    }
    else if(GetAsyncKeyState(VK_DOWN))
    {
        moveplayerdown();
    }
    else if(GetAsyncKeyState(VK_UP))
    {
        moveplayerup();
    }
    else if(GetAsyncKeyState(VK_SPACE))
    {
        playershoot();
    }
}


void print_enemy1()
{
    gotoxy(e1x,e1y);
    cout<<"(00) "<<endl;
    gotoxy(e1x,e1y+1);
    cout<<"/__\\"<<endl;
    gotoxy(e1x,e1y+2);
    cout<<"|  | "<<endl;
}
void erase_enemy1()
{
    gotoxy(e1x,e1y);
    cout<<"     "<<endl;
    gotoxy(e1x,e1y+1);
    cout<<"     "<<endl;
    gotoxy(e1x,e1y+2);
    cout<<"     "<<endl;
}
void e1state()
{
    if(getCharAtxy(e1x+5,e1y)=='#')
    {
        e1position++;
    }
    else if((getCharAtxy(e1x-1,e1y)=='#')||(getCharAtxy(e1x-1,e1y)=='%'))
    {
        e1position=0;
    }
}
void move_enemy1()
{
    e1state();
    if((getCharAtxy(e1x+5,e1y)==' ') && e1position==0)
    {
        erase_enemy1();
        e1x=e1x+1;
        print_enemy1();
        Sleep(1);
    }
    else if(getCharAtxy(e1x-1,e1y)==' ' && e1position!=0)
    {
        erase_enemy1();
        e1x=e1x-1;
        print_enemy1();
        Sleep(1);
    }
}


void print_enemy2()
{
    gotoxy(e2x,e2y);
    cout<<"(00) "<<endl;
    gotoxy(e2x,e2y+1);
    cout<<"/__\\ "<<endl;
    gotoxy(e2x,e2y+2);
    cout<<"|  | "<<endl;
}
void erase_enemy2()
{
    gotoxy(e2x,e2y);
    cout<<"     "<<endl;
    gotoxy(e2x,e2y+1);
    cout<<"     "<<endl;
    gotoxy(e2x,e2y+2);
    cout<<"     "<<endl;
}
void e2state()
{
    if(getCharAtxy(e2x,e2y-1)=='#')
    {
        e2position=0;
    }
    else if(getCharAtxy(e2x,e2y+4)=='#')
    {
        e2position++;
    }
}
void move_enemy2()
{
    e2state();
    if(((getCharAtxy(e2x,e2y+4)==' ') && (getCharAtxy(e2x+5,e2y+4)==' ')) && e2position==0)
    {
        erase_enemy2();
        e2y=e2y+1;
        print_enemy2();
        Sleep(20);
    }
    else if(((getCharAtxy(e2x,e2y-1)==' ') && (getCharAtxy(e2x+5,e2y-1)==' ')) && e2position!=0)
    {
        erase_enemy2();
        e2y=e2y-1;
        print_enemy2();
        Sleep(20);
    }
}

void print_enemy3()
{
    gotoxy(20,28);
    cout<<"/  \\--"<<endl;
    gotoxy(20,29);
    cout<<"|___|  "<<endl;
}
void shoot_enemy3()
{
    gotoxy(e3x,e3y);
    cout<<"  ";
    e3x=e3x+1;
    if(e3x==119)
    {
        e3x=28;
    }
    gotoxy(e3x,e3y);
    cout<<"=-";
    Sleep(1);
    
}

void readFromFile(int highscore[])
{
    int i=0;
    fstream file;
    file.open("gameS.txt",ios::in);

    while(!file.eof())
    {
        file>>highscore[i];
        i++;
        if(highscore[i]!=0)
        {
            highscoreIndex++;
        }
    }
    file.close();
}
void WriteToFile()
{
    fstream file;
    file.open("gameS.txt",ios::out);

    for(int i=0;i<sizeof(highscore)/sizeof(highscore[0]);i++)
    {
        file<<highscore[i]<<endl;
    }
    file.close();
}

