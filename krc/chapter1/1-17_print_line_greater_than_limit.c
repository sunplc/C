#include <stdio.h>

#define MAXLINE 1000
#define MAX_LENGTH 20

int Getline(char line[], int limit);
void copy(char to[], char from[]);

/* 练习 1-17 打印出所有长度超过80个字符的输入行 */
int main(void)
{
	int len = 0;
	char line[MAXLINE];
	
	while ((len = Getline(line, MAXLINE)) > 0) {
		if (len > MAX_LENGTH) {
			printf("line greater than %d: %s", MAX_LENGTH, line);
		}
	}
	return 0;
}

int Getline(char line[], int limit)
{
	int i, c;
	for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

