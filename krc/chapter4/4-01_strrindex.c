#include <stdio.h>

#define MAXLINE 1000

int Getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

// 练习 4-1. 编写函数 strrindex(s, t)，
// 其返回字符串 t 在 s 中最右边出现的位置，如果 s 中不包含 t，则返回-1。
int main(void)
{
	char line[MAXLINE];
	char pattern[] = "ould";
	int found = 0;
	int pos;

	while (Getline(line, MAXLINE) > 0) {
		if ( (pos = strrindex(line, pattern)) >= 0) {
			printf("position: %d - line:%s", pos, line);
			found++;
		}
	}
	printf("found = %d\n", found);
	return 0;
}

/* getline：取一行放到 s 中，并返回该行的长度 */ 
int Getline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strrindex(char s[], char t[])
{
	int i, j, k, pos = -1;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			pos = i;
	}
	return pos;
}

