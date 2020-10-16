
#include <stdio.h>

int main()
{

	char *tab[3]={"słynął z mondrości","słynął z mondrości","poszedł do łączności"};
	unsigned int i;

	scanf("%i", &i);
	if( i <= 3)
	{
        printf("%s", tab[i-1]);
	}
	else
	{
        printf("Nie było takich synów");
	}
	return 0;
}
