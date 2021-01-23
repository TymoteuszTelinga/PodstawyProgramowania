
#include <stdlib.h>

typedef struct Position
{
    int X;
    int Y;
}Position;

//one way
typedef struct unit
{
    Position pos;
    struct unit *next;
}List;

void push(List **wsk, Position data); //BACK
void pop(List **wsk); //FRONT
bool find(List *wsk,Position wanted); //return index
Position get(List *wsk); //return value
int size(List *wsk); //return size
void clear(List **wsk); //clear list 
