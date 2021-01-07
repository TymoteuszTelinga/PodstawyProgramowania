
#include <stdio.h>
#include <limits.h>

#include "kolko.h"

#define PlayerWin INT_MAX
#define AIWin INT_MIN
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

const int RowOrder[ROW]={4,5,3,6,2,7,1,8,0,9};
const int ColOrder[COL]={4,5,3,6,2,7,1,8,0,9};

void init(char Board[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            Board[i][j]=' ';
        }
    }
}

void show(char Board[ROW][COL]) 
{
    for (int i = 0; i < ROW; i++)
    {
        printf("%d ",i);
        for (int j = 0; j < COL; j++)
        {
            printf("|%c",Board[i][j]);
        }
        printf("|\n");
    }

    printf("   ");
    for (int i = 0; i < COL; i++)
    {
        printf("%d ", i);
    }
    printf("\n");   
}

void copy(const char Old[ROW][COL], char New[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            New[i][j]=Old[i][j];
        }
    }
}

bool CanPlay(char Board[ROW][COL], int row, int col) 
{
    if (row >=0 && row < ROW && col >=0 && col < COL )
    {
        if (Board[row][col] == ' ')
        {
            return true;
        }
    }
    return false;
}

void Play(char Board[ROW][COL], char player, int row, int col) 
{
    Board[row][col]=player;
}

int PosicionScore(char Board[ROW][COL])//heurystyka
{
    int value[ROW][COL]={
                        { 3, 4, 5, 6, 8, 8, 6, 5, 4, 3},
                        { 4, 6, 7, 9,11,11, 9, 7, 6, 4},
                        { 5, 7,10,12,14,14,12,10, 7, 5},
                        { 6, 9,12,15,17,17,15,12, 9, 6},
                        { 8,11,14,17,20,20,17,14,11, 8},
                        { 8,11,14,17,20,20,17,14,11, 8},
                        { 6, 9,12,15,17,17,15,12, 9, 6},
                        { 5, 7,10,12,14,14,12,10, 7, 5},
                        { 4, 6, 7, 9,11,11, 9, 7, 6, 4},
                        { 3, 4, 5, 6, 8, 8, 6, 5, 4, 3}
                        };

    int score=0;
    for(int r = 0; r < ROW; r++)
    {
        for (int c = 0; c < COL; c++)
        {
            switch (Board[r][c])
            {
            case 'o':
                score+=value[r][c];
                break;
            case 'x':
                score-=value[r][c];
                break;
            }
        }
    }

    return score;
}

int WinCheck(char Board[ROW][COL]) 
{
    // poziom
    for (int r = 0; r < ROW; r++)
    for (int c = 0; c < COL-Connected+1 ; c++)
    {
        if (Board[r][c] !=' ')
        {
            char check = Board[r][c];
            int count = 1;
            for (int i = 1; i < Connected && Board[r][c+i] == check; i++,count++);
            if (count == Connected)
            {
                if(check == 'o')
                    return PlayerWin;
                return AIWin;
            }
        }
    }
    //pionowo
    for (int c = 0; c < COL; c++)
    for (int r = 0; r < ROW-Connected+1 ; r++)
    {
        if (Board[r][c] !=' ')
        {
            char check = Board[r][c];
            int count = 1;
            for (int i = 1; i < Connected && Board[r+i][c] == check; i++,count++);
            if (count == Connected)
            {
                if(check == 'o')
                    return PlayerWin;
                return AIWin;
            }
        }
    }
    //ukosny \

    for (int c = 0; c < COL-Connected+1; c++)
    for (int r = 0; r < ROW-Connected+1 ; r++)
    {
        if (Board[r][c] !=' ')
        {
            char check = Board[r][c];
            int count = 1;
            for (int i = 1; i < Connected && Board[r+i][c+i] == check; i++,count++);
            if (count == Connected)
            {
                if(check == 'o')
                    return PlayerWin;
                return AIWin;
            }
        }
    }
    //ukosny /
    for (int c = Connected; c < COL; c++)
    for (int r = 0; r < ROW-Connected+1 ; r++)
    {
        if (Board[r][c] !=' ')
        {
            char check = Board[r][c];
            int count = 1;
            for (int i = 1; i < Connected && Board[r+i][c-i] == check; i++,count++);
            if (count == Connected)
            {
                if(check == 'o')
                    return PlayerWin;
                return AIWin;
            }
        }
    }
    
    return 0;
}

int MiniMax(char Board[ROW][COL], int depth, bool bAITurn, int Alpha, int Beta, int *BestRow, int *BestCol) 
{

    int resoult = WinCheck(Board);
    if (resoult)
    {
        return resoult;
    }

    if (depth == 0)
    {
        return PosicionScore(Board);
    }


    int BordPoints;
    int I,J;

    if (bAITurn)
    {//MINI AI
        int value=INT_MAX;
        for (int r = 0; r < ROW; r++)
        {
            for (int c = 0; c < COL; c++)
            {
                if (CanPlay(Board,RowOrder[r],ColOrder[c]))
                {
                    char NewBoard[ROW][COL];
                    copy(Board,NewBoard);
                    Play(NewBoard,'x',RowOrder[r],ColOrder[c]);
                    BordPoints = MiniMax(NewBoard,depth-1,false,Alpha,Beta,&I,&J);

                    if(BordPoints < value )
                    {
                    value=BordPoints;
                    *BestRow=RowOrder[r];
                    *BestCol=ColOrder[c];
                    }

                    Beta=min(Beta,BordPoints);
                    if (Beta<=Alpha)
                    {
                    return value;
                    }
                }
                
            }   
        }
        return value; 
    }
    else
    {//MAX PLAYER
        int value=INT_MIN;
        for (int r = 0; r < ROW; r++)
        {
            for (int c = 0; c < COL; c++)
            {
                if(CanPlay(Board,RowOrder[r],ColOrder[c]))
                {
                    char NewBoard[ROW][COL];
                    copy(Board,NewBoard);
                    Play(NewBoard,'o',RowOrder[r],ColOrder[c]);
                    BordPoints = MiniMax(NewBoard,depth-1,true,Alpha,Beta,&I,&J);

                    if(BordPoints > value)
                    {
                        value=BordPoints;
                        *BestRow=RowOrder[r];
                        *BestCol=ColOrder[c];
                    }

                    Alpha=max(Alpha,BordPoints);
                    if (Beta<=Alpha)
                    {
                        return value;
                    }
                }
            }
        }
        return value;
    }
}
