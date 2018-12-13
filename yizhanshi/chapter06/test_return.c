#include <stdio.h>

int is_leap_year(int year){
	if (year % 4 == 0 && year % 100 != 0) {
		printf("year %d is a leap year.\n", year);	
	} else if (year % 400 == 0) {	
		printf("year %d is a leap year.\n", year);	
	} else {
		printf("year %d is not a leap year.\n", year);	
	}
}

int main(void){
	int year;
	printf("please input a year:\n");
	scanf("%d", &year);
	is_leap_year(year);
	return 0;
}
