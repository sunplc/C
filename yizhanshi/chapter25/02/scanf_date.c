#include <stdio.h>
#include <stdlib.h>

int main(void)
{
//	int day, year;
//	char monthname[20];	
//	printf("Input date like \"25 Dec 1998\":\n");
//	scanf("%d %s %d", &day, monthname, &year);
//	printf("year = %d, month = %s, day = %d\n", year, monthname, day);
//
//	printf("Input date like \"1998/2/14\":\n");
//	int month;
//	scanf("%d/%d/%d", &year, &month, &day);
//	printf("year = %d, month = %d, day = %d\n", year, month, day);

	printf("Input date like \"25 Dec 1998\" OR \"1992/2/14\" :\n");
	int year, month, day;
	char monthname[20];
	char *line = malloc(1000);
	if (fgets(line, sizeof(line), stdin) > 0) {
		//printf("%s\n", line);
		if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
			printf("Valid: %s\n", line);
		else if (sscanf(line, "%d/%d/%d", &year, &month, &day) == 3)
			printf("Valid: %s\n", line);
		else
			printf("Invalid %s\n", line);
	}
	free(line);
	return 0;
}

