
#include <stdbool.h>

#define ROW 10
#define COL 10
#define Connected 5

void init(char Board[ROW][COL]);
void show(char Board[ROW][COL]);
bool CanPlay(char Board[ROW][COL], int row, int col);
void Play(char Board[ROW][COL], char player, int row, int col);
int WinCheck(char Board[ROW][COL]);
int MiniMax(char Board[ROW][COL], int depth, bool bAITurn, int Alpha, int Beta, int *BestRow, int *BestCol);