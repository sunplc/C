#include <stdio.h>

#define MAXLINE 1000

/* getline：取一行放到 s 中，并返回该行的长度 */ 
int Getline(char s[], int limit)
{
	int c, i;
	i = 0;
	while (--limit > 0 && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

//从标准输入中获取特定格式的日期
int main(int argc, char *argv[])
{
	int day, month, year;
	char monthname[20];
	char line[MAXLINE];
	while (Getline(line, MAXLINE) > 0) {
		if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3) {
			printf("valid: %s\n", line);
		} else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3) {
			printf("valid: %s\n", line);
		} else {
			printf("invalid: %s\n", line);
			break;
		}
	}
	return 0;
}

