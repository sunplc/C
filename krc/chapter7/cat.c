#include <stdio.h>
#include <stdlib.h> // exit()

void filecopy(FILE *in, FILE *out);

/*
 * 实现 cat 程序
 */
int main(int argc, char *argv[])
{
	char *program = argv[0]; //程序名，供错误处理使用
	//如果没有传入需要连接输出的文件名，则将标准输入复制到标准输出
	if (argc == 1) {
		filecopy(stdin, stdout);
	//如果有多个命令行参数，则将命令行参数中的文件打开并写入标准输出
	} else { 
		FILE *fp;
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", program, *argv);
				exit(1);
			} else {
				filecopy(fp, stdout);
				fclose(fp);
			}
	}

	//检查输出时是否发生了错误
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", program);
		exit(2);
	}

	exit(0);
}

/* 将文件 in 复制到 out */
void filecopy(FILE *in, FILE *out)
{
	int c;
	while ((c = getc(in)) != EOF)
		putc(c, out);
}
