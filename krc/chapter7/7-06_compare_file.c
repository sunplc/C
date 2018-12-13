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

// 练习7-6. 比较两个文件，并打印它们第一个不相同的行
int main(int argc, char *argv[])
{
	char *program = argv[0];
	if (argc != 3) {
		fprintf(stderr, "Usage: %s file1 file2\n", program);
		return 0;
	}

	FILE *f1, *f2;
	f1 = fopen(argv[1], "r");
	f2 = fopen(argv[2], "r");
	if (f1 == NULL) {
		fprintf(stderr, "%s: can't open file %s", program, argv[1]);
		return 1;
	}
	if (f2 == NULL) {
		fprintf(stderr, "%s: can't open file %s", program, argv[2]);
		fclose(f1);
		return 1;
	}

	char line1[MAXLINE], line2[MAXLINE];
	while (Getline(line1, MAXLINE, f1) && Getline(line2, MAXLINE, f2)) {
		if (strcmp(line1, line2)) {
			printf(">>> %s>>> %s", line1, line2);
			break;
		}
	}

	return 0;
}

