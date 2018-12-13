#include <stdio.h>

//返回第几月的名字
char *month_name(int n)
{
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"Apirl", "May", "June",
		"July", "August", "September",
		"Octomber", "November", "December"
	};
	return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(int argc, char *argv[])
{
	int n = 0;
	while (n != -1) {
		printf("Please input a number of month:\n");
		scanf("%d", &n);
		printf("%dth is %s\n", n, month_name(n));
	}
	return 0;
}

