
#include <stdio.h>
#include <limits.h>

#include "kolko.h"

int main()
{
    char Plansza[ROW][COL];
    init(Plansza);

    bool bPlayerTurn=true;
    int Prow,Pcol;
    int tura=0;

    while (!WinCheck(Plansza)&& tura < ROW*COL)
    {   
        tura++;
        show(Plansza);
        if (bPlayerTurn)
        {   //gracz
            printf("Player Turn (o) \n");
            printf("podaj wiersz i kolumne np: 4 5\n");
            do
            { ;
                fflush(stdin);
                scanf("%i %i",&Prow,&Pcol);
            } while (!CanPlay(Plansza,Prow,Pcol));
            Play(Plansza,'o',Prow,Pcol);
            bPlayerTurn=false;
        }
        else
        {   //AI
            printf("AI Turn(x)\n");
            int Arow,Acol;
            do
            {
                MiniMax(Plansza,4,true,INT_MIN,INT_MAX,&Arow,&Acol);
            } while (!CanPlay(Plansza,Arow,Acol));
            Play(Plansza,'x',Arow,Acol);
            bPlayerTurn=true;
        }
    }

    show(Plansza);
    if (tura == ROW*COL)
    {
        printf("tie\n");
    }
    else
    {
        if(bPlayerTurn)
        {
            printf("x win\n");
        }
        else
        {
            printf("o win\n");
        }
    }

    return 0;
}