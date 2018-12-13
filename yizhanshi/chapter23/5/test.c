#include <stdio.h>

int main(int argc, char *argv[])
{
	struct unit {
		char c;
		int i;
	};
	struct unit u;
	u.c = 'a';
	u.i = 3;
	printf("%c %d\n", u.c, u.i);

	struct unit *p = &u;
	printf("%c %d\n", (*p).c, (*p).i);
	printf("%c %d\n", p->c, p->i);

//	struct unit *p2 = ('E', 7);
//	p2->c = 'W';
//	p2->i = 5;
//	printf("%c %d\n", p2->c, p2->i);

	return 0;
}

