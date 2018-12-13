#include <stdio.h>
#include <unistd.h>

#include "syscalls.h"

/* getchar: unbuffered  single character input */
int Getchar(void)
{
	char c;
	return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

/* Getchar_buffered: simple buffered version */
int GetcharBuffered(void)
{
	static char buf[BUFSIZ];
	static char *bufp = buf;
	static int n;

	if (n == 0) {
		n = read(0, buf, sizeof(buf));
        printf("n = %d\n", n);
		bufp = buf;
	}

	return (--n > 0) ? (unsigned char) *bufp++ : EOF;
}

int main(int argc, char *argv[])
{
    printf("BUFSIZ = %d\n", BUFSIZ);

	int c, i;
    for (i = 0; i < 5; i++) {

	    //c = Getchar();
        c = GetcharBuffered();
        printf("c = %c\n", c);
    }

	return 0;
}

