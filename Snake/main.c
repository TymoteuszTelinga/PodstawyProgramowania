
#include <stdio.h>
#include <graphics.h>
#include <string.h>

#include "list.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))

const int Width = 20, Height = 20;
const float CellSize = 30, Delay =200;

typedef enum direcion
{
    UP,
    DOWN,
    LEFT,
    RIGHT
}Direcion;

typedef enum Opcja
{
    GAME,
    MENU,
    ENDSCR,
    HELP,
    EXIT
}Opcja;

void drawRec(int X, int Y,int Color)
{
    int tmpX=X*CellSize;
    int tmpY=Y*CellSize;

    setcolor(Color);
    setfillstyle(SOLID_FILL,Color);
    rectangle(tmpX,tmpY,tmpX+CellSize,tmpY+CellSize);
    floodfill(tmpX+1,tmpY+1,Color);
}

void DrawSnake(List *snake)
{
    while (snake)
    {   
        drawRec(snake->pos.X,snake->pos.Y,GREEN);
        snake = snake->next;
    }
}

bool Move(List **snake,Direcion dir,Position *Food)
{
    Position NextStep = get(*snake);
    switch (dir)
    {
    case UP:
        NextStep.Y--;
        break;
    case DOWN:
        NextStep.Y++;
        break;
    case LEFT:
        NextStep.X--;
        break;
    case RIGHT:
        NextStep.X++;
        break;
    }

    if( NextStep.Y >= 0 && NextStep.Y < Height && NextStep.X >= 0 && NextStep.X < Width && !find(*snake,NextStep))
    {
        drawRec(get(*snake).X,get(*snake).Y,COLOR( 17, 132, 26 ));
        push(snake,NextStep);
        drawRec(NextStep.X,NextStep.Y,GREEN);

        if(!(NextStep.X == Food->X && NextStep.Y == Food->Y))
        {
            drawRec((*snake)->pos.X,(*snake)->pos.Y,COLOR(33,47,60));
            pop(snake);
            drawRec((*snake)->pos.X,(*snake)->pos.Y,COLOR( 17, 132, 26 ));
        }
        else
        {
            do
            {
                Food->X=rand()%Width;
                Food->Y=rand()%Height;
            } while (find(*snake,*Food));
        }
        
        //drawRec(NextStep.X,NextStep.Y,GREEN);
        //push(snake,NextStep);

        
        return true;
    }

    return false;
}

void read(int tab[5])
{
    FILE *fp;
    fp=fopen("wyniki.txt", "r");
    //int tab[5];
    if (fp==NULL)
    {
        for(int i=0;i<5;i++)
            tab[i]=0;
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            fscanf(fp,"%d",&tab[i]);
        }
    }
    fclose (fp);
}

void save(int tab[5], int score)
{

    for (int i = 0; i < 5; i++)
    {
        if (score > tab[i])
        {
            int tmp = tab[i];
            tab[i]= score;
            score = tmp;
        }
        
    }
    FILE *fp;
    fp=fopen("wyniki.txt", "w");
    if (fp==NULL)
    {
        //BLEDY
    }
    for (int i = 0; i < 5; i++)
    {
        fprintf(fp,"%d\n",tab[i]);
    }
    fclose(fp);

}

char *append(char str1[], char str2[])
{
    char *str3 = (char *)malloc(sizeof(char)*(strlen(str1)+strlen(str2)));
    for (int i = 0; i < strlen(str1); i++)
    {
        str3[i]=str1[i];
    }
    for (int i = 0; i < strlen(str2); i++)
    {
        str3[strlen(str1)+i]=str2[i];
    }
    str3[strlen(str1)+strlen(str2)]='\0';

    return str3;
}

void EndScrean(int score)
{
    clearviewport();
    score *=100;
    char str[10];
    setcolor(WHITE);
    settextstyle(SMALL_FONT,HORIZ_DIR,64);

    if (score > 0)
    {
        sprintf(str, "%d",score);
        char text[] = "score: ";
        char *str3 = append(text,str);
        outtextxy(150,50,str3);
    }

    int wyniki[5];
    read(wyniki);

    outtextxy(150,120,"Best Scors");

    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
        case 0:
            setcolor(YELLOW);
            break;
        case 1:
            setcolor(DARKGRAY);
            break;
        case 2:
            setcolor(BROWN);
            break;
        
        default:
            setcolor(WHITE);
            break;
        }
        sprintf(str, "%d", wyniki[i]);
        char text[]="0";
        sprintf(text,"%d",i+1);
        char dot[] = ". ";
        char *str3 = append(text,dot);
        str3 = append(str3,str);
        outtextxy(150,170+i*50,str3);
    }

    save(wyniki,score);

    settextstyle(DEFAULT_FONT,HORIZ_DIR,64);
    outtextxy(220,435,"Back");
    rectangle(150,430,450,530);

    int x,y;
    do
    {
        clearmouseclick(WM_LBUTTONDOWN);
        do
        {
            delay(100);
            x=mousex();
            y=mousey();
        }while(!ismouseclick(WM_LBUTTONDOWN));

    } while (!(x> 150 && x < 450 && y > 430 && y < 530));
}

int SnakeGame()
{
    Direcion dir = DOWN;
    List *snake = NULL;
    Position Food={2,2};
    Position startPos={Width/2-1,Height/2-1};
    push(&snake,startPos);
    clearviewport();

    while (true)
    {
        int del = max(Delay-size(snake)*5,90);
        delay(del);
        //clearviewport();

        //obsługa klawiszy
        if(kbhit())
        {
            int c =getch();
            if (c == 0)
            {
                c=getch();
            }
            
            if(c == 'q')
            {
                clear(&snake);
                return -1;
            }

            switch (c)
            {
            case 'w':
            case KEY_UP:
                if(dir != DOWN)
                    dir=UP;
                break;

            case 's':
            case KEY_DOWN:
                if(dir != UP)
                    dir=DOWN;
                break;

            case 'd':
            case KEY_RIGHT:
                if(dir != LEFT)
                    dir=RIGHT;
                break;

            case 'a':
            case KEY_LEFT:
                if(dir != RIGHT)
                    dir=LEFT;
                break;
            }
        }

        if(Move(&snake,dir,&Food))
        {
            drawRec(Food.X,Food.Y,COLOR( 168, 0, 36 ));
            //DrawSnake(snake);
        }
        else
        {
            break;
        }
    }
    int s = size(snake);
    clear(&snake);
    return s;
}

void HelpScreen()
{
    clearviewport();

    outtextxy(150,50,"Settings");
    outtextxy(150,150,"Up - 'w'");
    outtextxy(150,200,"Down - 's'");
    outtextxy(150,250,"Left - 'a'");
    outtextxy(150,300,"Right - 'd'");

    settextstyle(DEFAULT_FONT,HORIZ_DIR,64);
    outtextxy(220,435,"Back");
    rectangle(150,430,450,530);

    int x,y;
    do
    {
        clearmouseclick(WM_LBUTTONDOWN);
        do
        {
            delay(100);
            x=mousex();
            y=mousey();
        }while(!ismouseclick(WM_LBUTTONDOWN));

    } while (!(x> 150 && x < 450 && y > 430 && y < 530));
}

Opcja MainMenu()
{
    settextstyle(DEFAULT_FONT,HORIZ_DIR,64);
    setcolor(WHITE);

    outtextxy(220,100,"Play");
    rectangle(150,100,450,200);

    outtextxy(205,260,"Score");
    rectangle(150,250,450,350);

    outtextxy(220,410,"Exit");
    rectangle(150,400,450,500);

    settextstyle(SMALL_FONT,HORIZ_DIR,16);
    outtextxy(250,530,"Help");
    rectangle(150,520,450,580);

    clearmouseclick(WM_LBUTTONDOWN);
    int x,y;

    do
    {
        delay(100);
        x=mousex();
        y=mousey();
    }while(!ismouseclick(WM_LBUTTONDOWN));

    if( x> 150 && x < 450)
    {
        if ( y >100 && y < 200)
        {
            return GAME;
        }

        if ( y > 250 && y < 350)
        {
            return ENDSCR;
        }
        
        if (y > 400 && y < 500)
        {
            return EXIT;
        }

        if (y > 520 && y < 580)
        {
            return HELP;
        }
    }

    return MENU;
}

int main()
{

    initwindow(CellSize*Width+1, CellSize*Height+1,"Snake");
    setbkcolor(COLOR(33,47,60));
    clearviewport();
    Opcja GameState = MENU;
    int score = -1;

    while (true)
    {
        clearviewport();

        switch (GameState)
        {
        case MENU:
            GameState = MainMenu();
            score = -1;
            break;
        case GAME:
            score = SnakeGame();
            GameState = ENDSCR;
            break;
        case ENDSCR:
            EndScrean(score);
            GameState = MENU;
            break;
        case HELP:
            HelpScreen();
            GameState = MENU;
            break;
        }

        if(GameState==EXIT)
        {
            break;
        } 
    }
    closegraph();
    return 0;
}