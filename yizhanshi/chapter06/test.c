#include <stdio.h>

void print_day(int day)
{
	switch (day) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			printf("Weekday\n");
			break;
		case 6:
		case 7:
			printf("Weekend\n");
			break;
		default:
			printf("Illegal day number!\n");
			break;
	}
}

int main(int argc, char *argv[])
{
	if (argc >= 2) {
		char *day = *(argv + 1);	
//		printf("day = %s\n", day);	
		int d = (int)*day - 48;
//		printf("d = %d\n", d);
		print_day(d);
	} else {
		printf("parameter error!, use './test 1' to dispaly.\n");	
	}
	return 0;
}
