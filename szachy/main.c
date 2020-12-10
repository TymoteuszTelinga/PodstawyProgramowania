
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "szachy.h"


int main()
{
    int plansza[8][8]={
                        {WIEZA, SKOCZEK, GONIEC, HETMAN, KROL, GONIEC, SKOCZEK, WIEZA},
                        {PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {-PIONEK, -PIONEK, -PIONEK, -PIONEK, -PIONEK, -PIONEK, -PIONEK, -PIONEK},
                        {-WIEZA, -SKOCZEK, -GONIEC, -HETMAN, -KROL, -GONIEC, -SKOCZEK, -WIEZA}
                    };

    int xF,yF,xT,yT;//zmiene gracza
    int BFR, BFC, BTR, BTC;//zmiene minimaxa
    int zbita;
    int Alpha=-1000000,Beta=1000000;

    while (!WinCheck(plansza))
    {

        system("CLS");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~");
        show(plansza);

        if(true)
        {
        printf("ruch BIALYCH\n");
        do
        {
            fflush(stdin);
            scanf("%d%d%d%d",&xF,&yF,&xT,&yT);
        } while (!move(plansza,BIALE,xF,yF,xT,yT,&zbita));
        }
        else
        {
        MiniMax(plansza,5,Alpha,Beta,false,&BFR,&BFC,&BTR,&BTC);
        move(plansza,BIALE,BFC,BFR,BTC,BTR,&zbita);
        }
        
        system("CLS");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~");
        show(plansza);

        printf("ruch CZARNYCH\n");
        MiniMax(plansza,5,Alpha,Beta,true,&BFR,&BFC,&BTR,&BTC);
        move(plansza,CZARNE,BFC,BFR,BTC,BTR,&zbita);
        //show(plansza);
    }

    printf("\nEND\n");

    if(WinCheck(plansza)>0)
    {
        printf("YOU LOSE\n");
    }
    else
    {
        printf("YOU WIN!\n");
    }    
    show(plansza);
    
    return 0;
}