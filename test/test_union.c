#include <stdio.h>

int main(int argc, char *argv[])
{
	union data {
		int i;
		char c;
		short s;
	};

	union data a;
	printf("%ld %ld\n", sizeof(a), sizeof(union data));

	a.i = 0x40;
	printf("%X %c %hX\n", a.i, a.c, a.s);

	a.c = '9';
	printf("%X %c %hX\n", a.i, a.c, a.s);

	a.s = 0x2059;
	printf("%X %c %hX\n", a.i, a.c, a.s);

	a.i = 0x3e25ad54;
	printf("%X %c %hX\n", a.i, a.c, a.s);

	// @ Y T

    union {
        short int  i[2];
        long k;
        char c[4];
    } r, *s = &r;
    s->i[0] = 0x39;
    s->i[1] = 0x38;
    printf("%lx\n", s->k);


	return 0;
}

