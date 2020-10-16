
#include <stdio.h>

int main()
{

	unsigned int i;

	scanf("%i", &i);


	switch(i)
	{
	case 1:
	case 2:
        {
            printf("słynął z mondrości");
            break;
        }
	case 3:
        {
            printf("poszedł do łączności");
            break;
        }
	default:
        {
            printf("Nie było takich synów");
        }
	}


	return 0;
}
