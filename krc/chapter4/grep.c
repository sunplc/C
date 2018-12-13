#include <stdio.h>

#define MAXLINE 1000

int Getline(char line[], int max);
int strindex(char source[], char searchfor[]);

/* 找出所有与模式相匹配的行 */ 
int main(void)
{
	char line[MAXLINE];
	char pattern[] = "ould";
	int found = 0;

	while (Getline(line, MAXLINE) > 0) {
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
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

/* strindex：返回 t 在 s 中的位置，若未找到则返回-1 */ 
int strindex(char s[], char t[])
{
	int i, j, k;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

