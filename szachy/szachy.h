
#define CZARNE 1//AI
#define BIALE -1//gracz

enum FIGURY
{
    PUSTY,
    PIONEK,
    SKOCZEK,
    GONIEC,
    WIEZA,
    HETMAN,
    KROL,
};

void show(int tab[8][8]);
bool move(int tab[8][8],int WhichMove, int colFrom ,int rowFrom, int colTo, int rowTo, int *zbita);
int WinCheck(int tab[8][8]);
int MiniMax(int tab[8][8], int depth, int Alpha, int Beta, bool bAITurn, int *BFR, int *BFC, int *BTR, int *BTC);