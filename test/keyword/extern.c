#include <stdio.h>

#define MAXLINE 1000

int Getline(void);
void copy(void);

// 如果一个源文件中的外部变量的定义出现在某个使用该变量的具体函数之前，
// 那么在该函数中就无需使用extern声明该变量。
int main(void)
{
	int len;
	extern int max;
	extern char longest[];
	max = 0;
	while ((len = Getline()) > 0) {
		//printf("%d", len);
		if (len > max) {
			max = len;
			copy();
		}
	}
	if (max > 0)
		printf("%s", longest);
	return 0;
}

int Getline(void)
{
	int c, i;
	extern char line[];
	for (i = 0; i < MAXLINE && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}

void copy(void)
{
	extern char line[], longest[];
	int i = 0;
	while((longest[i] = line[i]) != '\0')
		++i;
}

int max;
char line[MAXLINE];
char longest[MAXLINE];
