#include <stdio.h>
#include <math.h>

double distance(double, double, double, double);
double area(double);

int main()
{
	double radius = distance(1.0, 2.0, 4.0, 6.0);
	double result = area(radius);
	printf("radius = %f\n", radius);
	printf("area = %f\n", result);
	return 0;
}

double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double area(double radius)
{
	double pi = 3.14169;
	return pi * radius * radius;
}
