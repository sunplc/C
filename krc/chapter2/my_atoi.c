#include <stdio.h>

int my_atoi(char str[]);

int main(void)
{
	char str[10];
	printf("Input an integer:");
	scanf("%s", str);
	int i = my_atoi(str);
	printf("Result: %d\n", i);
	return 0;
}

int my_atoi(char str[])
{
	int i, n = 0;
	for (i = 0; str[i] >= '0' && str[i] <= '9'; ++i) {
		n = 10 * n + (str[i] - '0');
	}
	return n;
}

