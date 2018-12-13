#include <stdio.h>

int main()
{
	char c;
	double lc = 0;
	while ( (c = getchar()) != EOF ) {
		if ( c == '\n' )
			++lc;
	}
	printf("%.0f lines\n", lc);
	return 0;
}
