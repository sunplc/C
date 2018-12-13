#include <stdio.h>
#define RECTANGULAR 1 
#define POLAR 2

enum coordinate_type { RECTANGULR = 1, POLAR };

int main(void)
{
	int RECTANGULAR;
	printf("%d %d\n", RECTANGULAR, POLAR);
	return 0;
}
