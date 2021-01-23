
#include "list.h"
#include <stdbool.h>

void push(List **wsk, Position data) //BACK
{
    List *New = (List *)malloc(sizeof(List));
    New->pos = data;
    New->next = NULL;

    if(!*wsk)
    {
        *wsk=New;
    }
    else
    {
        List *tmp = *wsk;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next=New;   
    }
}

void pop(List **wsk) //FRONT
{
    if(*wsk)
    {
        List *tmp = (*wsk)->next;
        free(*wsk);
        *wsk = tmp;
    }
}

bool find(List *wsk,Position wanted) //return index
{
    int i=0;
    while (wsk)
    {
        if(wsk->pos.X == wanted.X && wsk->pos.Y == wanted.Y)
        {
            return true;
        }
        else
        {
            i++;
            wsk = wsk->next;
        }
    }
    return false;
}

Position get(List *wsk) //return value
{
    while (wsk->next)
    {
        wsk = wsk->next;
    }

    return wsk->pos;
}

int size(List *wsk) //return size
{
    int i=0;
    while (wsk)
    {   
        i++;
        wsk = wsk->next;
    }
    return i;    
}

void clear(List **wsk) //clear list 
{
    while (*wsk)
    {
        pop(wsk);
    }
}