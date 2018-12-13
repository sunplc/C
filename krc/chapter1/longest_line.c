#include <stdio.h>
#define MAXLINE 1000

int my_getline(char line[], int limit);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
	int len = 0;		/* current line length */
	int max = 0;		/* maximum length seen to far */
	char line[MAXLINE];		/* current input line */
	char longest[MAXLINE];  /* longest lint saved here */

	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0) /* there was a line */
		printf("%s",longest);
	return 0;				
}

/* my_getline: read a line into line, return length */
int my_getline(char line[], int limit)
{
	int c, i;
	for (i = 0; i < limit -1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = '\n';
		++i;
	}
	line[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume 'to' is bigest enough */
void copy(char to[], char from[])
{
	int i = 0;
	while ( (to[i] = from[i]) != '\0' )
		++i;	
}
