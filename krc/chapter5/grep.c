#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int Getline(char line[], int max);
int strindex(char source[], char searchfor[]);

/* 找出所有与模式相匹配的行 */ 
int main(int argc, char *argv[])
{
	char line[MAXLINE];
	char pattern[] = "ould";
	int found = 0;
	if (argc < 2)
		printf("Usage: find pattern\n");
	else {
		while (Getline(line, MAXLINE) > 0) {
			if (strstr(line, argv[1]) != NULL) {
				printf("%s", line);
				found++;
			}
		}
		printf("found = %d\n", found);
	}

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

