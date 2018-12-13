#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int Getline(char *line, int max, FILE *in)
{
	if (fgets(line, max, in) == NULL)
		return 0;
	else
		return strlen(line);
}

/* 从输入流in中，找出所有与模式相匹配的行，并输出到标准输出 */ 
void grep_print(FILE *in, int maxline, char *pattern, char *filename)
{
	char line[maxline];
	while (Getline(line, maxline, in) > 0) {
		if (strstr(line, pattern) != NULL) {
			printf("%s: %s", filename, line);
		}
	}
}

/*
 * 练习 7-07. 修改第五章的模式查找程序，使其从一组文件中读取输入，
 * 并在没有文件作为参数时从标准输入中读取输入
 */
int main(int argc, char *argv[])
{
	char *program = argv[0]; //程序名称
	if (argc < 2) {
		fprintf(stderr, "Usage: %s pattern [file1 file2...]\n", program);
		return 0;
	}

	char *pattern = argv[1];

	FILE *in;
	char filename[FILENAME_MAX];

	if (argc > 2) {
		argv += 2;
		while (argc-- > 2) {
			strcpy(filename, argv[0]);
			++argv;
			in = fopen(filename, "r");
			if (in == NULL) {
				fprintf(stderr, "%s can't open file %s\n", program, filename);
				return 1;
			}
			grep_print(in, MAXLINE, pattern, filename);
		}
	} else {
		in = stdin;
		strcpy(filename, "stdin");
		grep_print(in, MAXLINE, pattern, filename);
	}

	return 0;
}

