#include <stdio.h>
#include <string.h>

#define MAXLINE 200

int Getline(char *line, int max, FILE *in)
{
	if (fgets(line, max, in) == NULL)
		return 0;
	else
		return strlen(line);
}

// 使用 fgets 函数实现 getline 函数
int main(int argc, char *argv[])
{
	FILE *fp = fopen("test1.txt", "r");
	char line[MAXLINE];
	while (Getline(line, MAXLINE, fp)) {
		printf("%s", line);
	}
	return 0;
}

