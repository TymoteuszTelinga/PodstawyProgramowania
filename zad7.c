
#include <stdio.h>

int main()
{
	float Temp;

	char i;
	scanf("%c", &i);
    scanf("%f", &Temp);
    if(i =='K')
    {
        printf("%f",Temp-273.15);

    }
    else
    {
        printf("%f",Temp+273.15);
    }

	return 0;
}
