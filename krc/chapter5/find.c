#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int Getline(char line[], int max);
int strindex(char source[], char searchfor[]);

/* 找出所有与模式相匹配的行 */ 
int main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-') {
		//printf("argv=%s\n", argv[0]);
		while ( (c = *++argv[0]) ) {
			//printf("c=%c\n", *(argv[0]));
			switch(c) {
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find: 非法选项 %c\n", c);
					argc = 0;
					found = -1;
					break;
			}
		}
	}
				
	if (argc != 1)
		printf("用法: find -x -n 模式\n");
	else {
		while (Getline(line, MAXLINE) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
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


