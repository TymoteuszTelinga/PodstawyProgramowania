
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "szachy.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int heurytyki[13][8][8] = {
    // --PLAYER-- (BIALE)
    // KROL
    {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}
    },
    // HETMAN
    {
        {-176, -178, -178, -179, -179, -178, -178, -176},
        {-178, -180, -180, -180, -180, -180, -180, -178},
        {-178, -180, -181, -181, -181, -181, -180, -178},
        {-179, -180, -181, -181, -181, -181, -180, -179},
        {-180, -180, -181, -181, -181, -181, -180, -179},
        {-178, -181, -181, -181, -181, -181, -180, -178},
        {-178, -180, -181, -180, -180, -180, -180, -178},
        {-176, -178, -178, -179, -179, -178, -178, -176}
    },
    // WIEZA
    {
        {-100, -100, -100, -100, -100, -100, -100, -100},
        {-101, -102, -102, -102, -102, -102, -102, -101},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-99, -100, -100, -100, -100, -100, -100, -99},
        {-100, -100, 100, -101, -101, -100, -100, -100}
    },
    // GONIEC
    {
        {-56, -58, -58, -58, -58, -58, -58, -56},
        {-58, -60, -60, -60, -60, -60, -60, -58},
        {-58, -60, -61, -62, -62, -61, -60, -58},
        {-58, -61, -61, -62, -62, -61, -61, -58},
        {-58, -60, -62, -62, -62, -62, -60, -58},
        {-58, -62, -62, -62, -62, -62, -62, -58},
        {-58, -61, -60, -60, -60, -60, -61, -58},
        {-56, -58, -58, -58, -58, -58, -58, -56}
    },
    // SKOCZEK
    {
        {-50, -52, -54, -54, -54, -54, -52, -50},
        {-52, -56, -60, -60, -60, -60, -56, -52},
        {-54, -60, -62, -63, -63, -62, -60, -54},
        {-54, -61, -63, -64, -64, -63, -61, -54},
        {-54, -60, -63, -64, -64, -63, -60, -54},
        {-54, -61, -62, -63, -63, -62, -61, -54},
        {-52, -56, -60, -61, -61, -60, -56, -52},
        {-50, -52, -54, -54, -54, -54, -52, -50}
    },
    // PIONEK
    {
        {-20, -20, -20, -20, -20, -20, -20, -20},
        {-30, -30, -30, -30, -30, -30, -30, -30},
        {-22, -22, -24, -26, -26, -24, -22, -22},
        {-21, -21, -22, -25, -25, -22, -21, -21},
        {-20, -20, -20, -24, -24, -20, -20, -20},
        {-21, -19, -18, -20, -20, -18, -19, -21},
        {-21, -22, -22, -16, -16, -22, -22, -21},
        {-20, -20, -20, -20, -20, -20, -20, -20}
    },
    // --PUSTE--
    {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    },
    // --AI-- (CZARNE)
    // PIONEK
    {
        {20, 20, 20, 20, 20, 20, 20, 20},
        {21, 22, 22, 16, 16, 22, 22, 21},
        {21, 19, 18, 20, 20, 18, 19, 21},
        {20, 20, 20, 24, 24, 20, 20, 20},
        {21, 21, 22, 25, 25, 22, 21, 21},
        {22, 22, 24, 26, 26, 24, 22, 22},
        {30, 30, 30, 30, 30, 30, 30, 30},
        {20, 20, 20, 20, 20, 20, 20, 20}
    },
    // SKOCZEK
    {
        {50, 52, 54, 54, 54, 54, 52, 50},
        {52, 56, 60, 60, 60, 60, 56, 52},
        {54, 60, 62, 63, 63, 62, 60, 54},
        {54, 61, 63, 64, 64, 63, 61, 54},
        {54, 60, 63, 64, 64, 63, 60, 54},
        {54, 61, 62, 63, 63, 62, 61, 54},
        {52, 56, 60, 61, 61, 60, 56, 52},
        {50, 52, 54, 54, 54, 54, 52, 50}
    },
    // GONIEC
    {
        {56, 58, 58, 58, 58, 58, 58, 56},
        {58, 61, 60, 60, 60, 60, 61, 58},
        {58, 62, 62, 62, 62, 62, 62, 58},
        {58, 60, 62, 62, 62, 62, 60, 58},
        {58, 61, 61, 62, 62, 61, 61, 58},
        {58, 60, 61, 62, 62, 61, 60, 58},
        {58, 60, 60, 60, 60, 60, 60, 58},
        {56, 58, 58, 58, 58, 58, 58, 56}
    },
    // WIEZA
    {
        {100, 100, 100, 101, 101, 100, 100, 100},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {99, 100, 100, 100, 100, 100, 100, 99},
        {101, 102, 102, 102, 102, 102, 102, 101},
        {100, 100, 100, 100, 100, 100, 100, 100}
    },
    // HETMAN
    {
        {176, 178, 178, 179, 179, 178, 178, 176},
        {178, 180, 180, 180, 180, 180, 180, 178},
        {178, 180, 181, 181, 181, 181, 180, 178},
        {179, 180, 181, 181, 181, 181, 180, 179},
        {180, 180, 181, 181, 181, 181, 180, 179},
        {178, 181, 181, 181, 181, 181, 180, 178},
        {178, 180, 181, 180, 180, 180, 180, 178},
        {176, 178, 178, 179, 179, 178, 178, 176}
    },
    // KROL
    {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    }
    };

//kierunki
// 7 0 1
// 6   2
// 5 4 3

const int colW[6][8]={//0,1,2,3,4,5,6,7
                  {0,1,0,0,0,0,0,-1},//PIONEK
                  {-1,1,2,2,1,-1,-2,-2},//SKOCZEK
                  {0,1,0,1,0,-1,0,-1},//GONIEC
                  {0,0,1,0,0,0,-1,0},//WIEZA
                  {0,1,1,1,0,-1,-1,-1},//HETMAN
                  {0,1,1,1,0,-1,-1,-1},//KROL
                };

const int rowW[6][8]={//0,1,2,3,4,5,6,7
                  {1,1,0,0,0,0,0,1},//PIONEK
                  {2,2,1,-1,-2,-2,-1,1},//SKOCZEK
                  {0,1,0,-1,0,-1,0,1},//GONIEC
                  {1,0,0,0,-1,0,0,0},//WIEZA
                  {1,1,0,-1,-1,-1,0,1},//HETMAN
                  {1,1,0,-1,-1,-1,0,1},//KROL
                };

char fig(int value)
{
    switch (value)
    {
    case PIONEK:
        return 'P';
    case SKOCZEK:
        return 'S';
    case GONIEC:
        return 'G';
    case WIEZA:
        return 'W';
    case HETMAN:
        return 'H';
    case KROL:
        return 'K';

    case PUSTY:
        return ' ';

    case -PIONEK:
        return 'p';
    case -SKOCZEK:
        return 's';
    case -GONIEC:
        return 'g';
    case -WIEZA:
        return 'w';
    case -HETMAN:
        return 'h';
    case -KROL:
        return 'k';
    
    default:
        return 'x';
    }
}

void show(int tab[8][8])
{
    printf("\n    ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", i);
    }
    printf("\n\n");
    for (int r = 0; r < 8; r++)
    {
        printf("%d  ",r);
        for(int c=0; c < 8; c++)
        {
            printf("|%c",fig(tab[r][c]));
        }
        printf("|  %d\n",r);
    }
    printf("\n    ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
}

bool in(int c)
{
    if (c>= 0 && c < 8)
    {
        return true;
    }
    return false;
}

int sign(int value)//zwraza znak liczby
{
    if (value > 0)
    {
        return 1;
    }
    if (value < 0)
    {
        return -1;
    }
    return 0;   
}

//wywołanie tylko wtedy gdy mieścimy się na planszy oraz docelowo bijemy lub przechodzimy na puste pole
bool IsValidMove(int tab[8][8], int oldRow, int oldCol , int newRow, int newCol)
{
    int figura = tab[oldRow][oldCol];

    int dRow = newRow - oldRow;
    int dCol = newCol - oldCol;
    
    if(dRow==0&&dCol==0)
        return false;

    switch (abs(figura))
    {
    case PIONEK:
        
        if(abs(dRow) == 2 && ((oldRow == 6 && sign(figura)==BIALE) || (oldRow == 1 && sign(figura)==CZARNE)))
        {
            if(abs(dCol)==1)//Pionek prubuje bić
                return false;
            if(dCol==0 && (tab[newRow][newCol] == PUSTY && tab[oldRow+sign(dRow)][newCol] == PUSTY))
            {
                return true;
            }
        }
        for (int i = 0; i < 8; i++)
        {   
            if(dRow == rowW[abs(figura)-1][i]*sign(figura) && dCol == colW[abs(figura)-1][i]*sign(figura))
            {//zostal znaleziony wektor ruchu
                if(dCol != 0 && tab[newRow][newCol] == PUSTY)
                {//bijemy pusty
                    return false;
                }
                if(dCol == 0 && tab[newRow][newCol] != PUSTY)
                {//przed nami jest pionek
                    return false;
                }
                return true;
            }
        }
        return false;

    case SKOCZEK:
    case KROL:
        for (int i = 0; i < 8; i++)
        {     
            if(dRow == rowW[abs(figura)-1][i]*sign(figura) && dCol == colW[abs(figura)-1][i]*sign(figura))
            {//zostal znaleziony wektor ruchu
                return true;
            }
        }
        return false;

    case GONIEC:
    case WIEZA:
    case HETMAN:
        for (int i = 0; i < 8; i++)
        {   
            int len=max(abs(dRow),abs(dCol));
            if(rowW[abs(figura)-1][i]*len == dRow && colW[abs(figura)-1][i]*len == dCol)
            {//zostal znaleziony wektor ruchu
                for(int j=1; j< len; j++)
                {
                    if(tab[oldRow+j*sign(dRow)][oldCol+j*sign(dCol)] != PUSTY)
                    {//po drodze są inne pionki
                        return false;
                    }
                }
                return true;
            }
        }
        return false;

    default:
        return false;
    }
    return false;
}
//Nie uwzględnia roszady i szaha, zwraca TRUE jesli udalo sie wykonac ruch
bool move(int tab[8][8],int WhichMove, int colFrom ,int rowFrom, int colTo, int rowTo, int *zbita)
{
    //printf("\nmove %d,%d -> %d,%d\n", colFrom,rowFrom,colTo,rowTo);
    //sprawdz wspulzedne
    if (!(in(colFrom) && in(rowFrom) && in(colTo) && in(rowTo)))
    {
        //printf("zle wspulzendne\n");
        return false;
    }

    int pionek = tab[rowFrom][colFrom];
    int cell = tab[rowTo][colTo];

    //sprawdz czyj pionek
    if (sign(pionek)!=WhichMove)
    {
        //printf("zly pionek");
        return false;
    }
    
    //sprawdz pole docelowe
    if (pionek*cell > 0)
    {
        //printf("zly cel\n");
        return false;
    }

    //sprawdz czy mozna wykonac dany ruch
    if(IsValidMove(tab,rowFrom,colFrom,rowTo,colTo))
    {
        tab[rowTo][colTo] = pionek;
        tab[rowFrom][colFrom] = PUSTY;
        *zbita=cell;
        return true;
    }
    else
    {
        return false;
    }
}

void unDoMove(int tab[8][8], int colFrom ,int rowFrom, int colTo, int rowTo, int zbita)
{
    int pionek = tab[rowTo][colTo];
    tab[rowTo][colTo] = zbita;
    tab[rowFrom][colFrom] = pionek;
}

int WinCheck(int tab[8][8])
{
    int who=0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(abs(tab[i][j])==KROL)
            {
                who+=tab[i][j];
            }
        }
        
    }
    return who*10000;
}

int MapScore(int tab[8][8])
{
    int score=0;

    for(int r=0; r<8; r++)
    {
        for(int c=0; c<8; c++)
        {
            if (tab[r][c]!=PUSTY)
            {
                score+=heurytyki[tab[r][c]+6][r][c];
            } 
        }
    }

    return score;
}
//Mini - Gracz
//Max - Komputer
int MiniMax(int tab[8][8], int depth, int Alpha, int Beta, bool bAITurn, int *BFR, int *BFC, int *BTR, int *BTC)//Alpha Beta
{
    //static int xd=0;
    int resoult=WinCheck(tab);
    if(resoult)
    {
        return resoult;
    }

    if(depth==0)
    {
        //xd+=1;
        //printf("%d\n",xd);
        return MapScore(tab);
    }

    int BordPoints, zbita;
    int x,y,z,w;
    if(bAITurn)
    {//MAX(AI)
        int value=-1000000;
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                //figura komputera
                if (sign(tab[row][col])==CZARNE)
                {
                    for (int Nrow = 0; Nrow < 8; Nrow++)
                    {
                        for (int Ncol = 0; Ncol < 8; Ncol++)
                        {   
                            //jezeli mozna wykonac ruch
                            if (move(tab,CZARNE,col,row,Ncol,Nrow,&zbita))
                            {
                                BordPoints=MiniMax(tab,depth-1,Alpha,Beta,false,&x,&y,&z,&w);
                                if(BordPoints > value )
                                {
                                    value=BordPoints;
                                    *BFR=row;
                                    *BFC=col;
                                    *BTR=Nrow;
                                    *BTC=Ncol;
                                }
                                unDoMove(tab,col,row,Ncol,Nrow,zbita);
                                Alpha = max(Alpha,BordPoints);
                                if (Beta<=Alpha)
                                {
                                    return value;
                                }
                                
                            } 
                        } 
                    }
                } 
            }
        }
        return value;
    }
    else
    {//MINI(GRACZ)
        int value=1000000;
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                //figura gracza
                if (sign(tab[row][col])==BIALE)
                {
                    for (int Nrow = 0; Nrow < 8; Nrow++)
                    {
                        for (int Ncol = 0; Ncol < 8; Ncol++)
                        {   
                            //jezeli mozna wykonac ruch
                            if (move(tab,BIALE,col,row,Ncol,Nrow,&zbita))
                            {
                                BordPoints=MiniMax(tab,depth-1,Alpha,Beta,true,&x,&y,&z,&w);
                                if(BordPoints < value )
                                {
                                    value=BordPoints;
                                    *BFR=row;
                                    *BFC=col;
                                    *BTR=Nrow;
                                    *BTC=Ncol;
                                }
                                unDoMove(tab,col,row,Ncol,Nrow,zbita);
                                Beta = min(Beta,BordPoints);
                                if (Beta<=Alpha)
                                {
                                    return value;
                                }

                            } 
                        } 
                    }
                } 
            }
        }
        return value;
    }
}
