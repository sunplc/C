/* ret_ptr.c */
#include <string.h>
#include "ret_ptr.h"
#include <stdio.h>

static char *week[] = {"Sunday","Monday","Tusday","Wednesday",
	"Thursday","Friday","Saturday"};

char *get_a_day(int index)
{
	static char buf[20];
	strcpy(buf, week[index]);
	printf("buf: %s\n", buf);
	printf("week[%d]=%s\n", index, week[index]);
	printf("&buf=%p\n", &buf);
	return buf;
}
