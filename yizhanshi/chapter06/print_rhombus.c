#include <stdio.h>

void print_rhombus(int n, char c)
{
	if (n % 2 == 0) {
		printf("number n should be odd number\n");
		return;
	}	
	int i, j;
	int midline = n/2;
	for (i = 0; i < n; ++i) {
		int y_offset = i <= midline ? i : n - i - 1;
		//printf("y_offset = %d\t >", y_offset);
		for (j = 0; j < n; ++j) {
			int x_offset = midline - j >= 0 ? midline - j : j - midline;
			if (x_offset <= y_offset)
				printf("%c\t", c);
			else
				printf("\t");
		}	
		putchar('\n');
	}
}

int main(void)
{
	print_rhombus(15, '+');
	return 0;
}
