#include <stdio.h>
#include <unistd.h> // read() write() close()
#include <fcntl.h>	// open() creat()

#include "syscalls.h"

#define PERMS 0666 /* RW for owner, group, others */

void error(char *, ...);

/* cp: copy f1 to f2 */
int main(int argc, char *argv[])
{
	int f1, f2, n;
	char buf[BUFSIZ];
	
	if (argc != 3)
		error("Usage: cp f1 f2");

	//打开文件f1
	if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
		error("cp: can't open %s", argv[1]);
	//新建文件f2或清空文件f2
	if ((f2 = creat(argv[2], PERMS)) == -1)
		error("cp: can't create %s, mode %03o", argv[2], PERMS);
	//读取f1的内容并写入到f2中
	while ((n = read(f1, buf, BUFSIZ)) > 0)
		if (write(f2, buf, n) != n)
			error("cp: write error on file %s", argv[2]);

	return 0;
}

#include <stdarg.h> // va_list va_start va_end
#include <stdlib.h> // exit()

void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

