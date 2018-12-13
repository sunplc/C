#include <stdio.h>
#include <math.h>

int main()
{
	int a=2,b=8,c=8;
	printf("please input three double number for quadratic!\n");
	scanf("%d,%d,%d",&a,&b,&c);
	int flag = b*b - 4*a*c;
	if(flag > 0)
	{
		double x1 = (b*-1 + sqrt(flag))/(2*a); 
		double x2 = (b*-1 - sqrt(flag))/(2*a);
		printf("flag>0,x1=%f,x2=%f.\n",x1,x2);
	}
	else if(flag == 0)
	{
		double x = (b*-1)/(2*a);
		printf("flag=0, x=%f.\n",x);

	}
	else
	{
		printf("flag<0.\n");
	}
}

