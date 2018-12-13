#include <stdio.h>
#include <stdlib.h> // exit()
#include <unistd.h>
#include <fcntl.h>

void error(char *, ...);
int filecopy(int in, int out);

/*
 * 练习 8-1 使用 read,write,open和close系统调用实现 cat 程序
 */
int main(int argc, char *argv[])
{
	char *program = argv[0]; //程序名，供错误处理使用
	int fd;
	int rs;
	//如果没有传入需要连接输出的文件名，则将标准输入复制到标准输出
	if (argc == 1) {
		rs = filecopy(0, 1);
	//如果有多个命令行参数，则将命令行参数中的文件打开并写入标准输出
	} else { 
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				error("%s: can't open %s\n", program, *argv);
			} else {
				rs = filecopy(fd, 1);
			}
	}

	if (!rs)
		error("error: %s write to stdout", program);

	exit(0);
}

/* 将文件 in 复制到 out */
int filecopy(int in, int out)
{
	int n;
	char buf[BUFSIZ];
	while ((n = read(in, buf, BUFSIZ)) > 0)
		if (write(out, buf, n) != n) {
			return 0;
		}
	return 1;
}

#include <stdarg.h> // va_list va_start va_end

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

