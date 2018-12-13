#include <stdio.h>

void print_day(int day)
{
	char days[8][10] = {
		"", "Monday", "Tuesday", "Wednesday", "Thursday",
		"Friday", "Saturday", "Sunday"
	};
	if (day < 1 || day > 7)
		printf("Illegal day number!\n");
	else
		printf("%s\n", days[day]);
}

int main(void)
{
	printf("please input the day number:\n");
	int day = 0;
	scanf("%d", &day);
	print_day(day);
	return 0;
}
