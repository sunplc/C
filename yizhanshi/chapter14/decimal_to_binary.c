#include <stdio.h>

int main(void)
{
	printf("input an integer:");
	int a, temp;
	while (1) {
		scanf("%d", &a);
		if (a == 0)
			break;
		char str[30];
		int i = 0;
		char c;
		while (a > 0) {
			temp = a % 2;	
			if (temp == 0)
				c = '0';
			else
				c = '1';
			str[i] = c;
			a = a / 2;
			++i;
		}
		int j;
		for (j = i; j >= 0; j--)
			putchar(str[j]);
		putchar('\n');
	}
	return 0;
}
