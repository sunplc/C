#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_WIDTH 100

int main()
{
	int c, n = 0;
	while ((c = getchar()) != EOF) {
		if (isgraph(c)) {
			putchar(c);
		} else {
			printf("0x%x", c);
		}

		if (n >= MAX_LINE_WIDTH) {
			putchar('\n');
			n = 0;
		} else {
			++n;
		}
	}

	return 0;
}

