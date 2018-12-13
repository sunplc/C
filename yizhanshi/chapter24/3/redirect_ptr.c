/* redirect_ptr.c */
#include "redirect_ptr.h"

static const char *week[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
	"Thursday", "Friday", "Saturday"};

void get_a_day(const char **pp)
{
	static int i = 0;
	*pp = week[i%7];
	i++;
}
