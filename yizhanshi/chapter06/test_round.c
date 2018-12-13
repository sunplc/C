#include <stdio.h>

double myround(double f);

int main(void)
{
	double d = 9.75;
	printf("d = %lf\n", d);
	d = myround(d);
	printf("d = %lf\n", d);
	return 0;
}

double myround(double d)
{
	double result = d - (int)d;
	if (d <= 0) {
		if (result <= -0.5)
			d -= (1 + result);
		else
			d -= result;
	} else {
		if (result >= 0.5)
			d += (1 - result);
		else
			d -= result;
	}
	return d;
}
