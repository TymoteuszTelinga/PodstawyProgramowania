
#include <stdio.h>

int main()
{
    int Size =3;
    int tab[Size];
    for(int i=0;i<Size;i++)
    {
        tab[i]=i;
    }
    for(int i=Size-1;i>=0;i--)
    {
        printf("%i\n", tab[i]);
    }

	return 0;
}
