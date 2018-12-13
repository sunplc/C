#include <stdio.h>
#include <math.h>

int main()
{
	double r=1.5;
	double h=3;
	printf("pi=%le\n",M_PI);
	printf("the circle's perimeter is %.2f\n", 2*r*M_PI);
	printf("the cricle's area is %.2f\n", r*r*M_PI);
	printf("the sphere's superficial area is %.2f\n", 4*M_PI*r*r);
	printf("the sphere's volume is %.2f\n", (4/3 + 4 %3)*M_PI*r*r*r);
	printf("the cylinder's volume is %.2f\n", M_PI*r*r*h);
	return 0;
}
