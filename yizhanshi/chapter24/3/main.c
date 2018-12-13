/* main.c */
#include <stdio.h>
#include "redirect_ptr.h"

int main(void)
{
	const char *firstday = NULL;
	const char *secondday = NULL;
	get_a_day(&firstday);
	get_a_day(&secondday);
	printf("%s\t%s\n", firstday, secondday);
	return 0;
}

