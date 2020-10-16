
#include <stdio.h>
#include <cmath>

int main()
{

    int a,b,c;

    scanf("%i%i%i",&a,&b,&c);

    int delta = b*b - 4*a*c;

    if(delta>0)
    {
        float x1,x2;

        x1 = (-b - sqrt(delta))/(2*a);
        x2 = (-b + sqrt(delta))/(2*a);

        printf("%f\t%f", x1, x2);
    }
    else
    {
        if(delta == 0)
        {
            float x = -b/(2*a);
            printf("f", x);
        }
        else
        {
            printf("brak pierwiastlków");
        }
    }

    printf("%i%i%i", a,b,c);

	return 0;
}
