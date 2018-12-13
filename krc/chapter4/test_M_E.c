#include <stdio.h>
#include <math.h> // pow() M_E

int main(void)
{	
	int i;
	printf("e = %E\n", M_E);
	for (i = -10; i <= 10; i++) {
		printf("pow(e, %d) = \t%lf \t %g\n", i, pow(M_E, i), pow(M_E, i));
	}
	return 0;
}

