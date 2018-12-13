#include <stdio.h>

#define MAXLINE 1000

int Getline(char line[], int limit);
void reverse(char to[], char from[], int len);
void Reverse(char line[]);

/* 练习 1-19 将所有的输入行反转输出,每次翻转一行 */
int main(void)
{
	int len;
	char line[MAXLINE];
	
	while ((len = Getline(line, MAXLINE)) > 0) {
		Reverse(line);
		printf("%s", line);
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

// 字符串反转
void Reverse(char line[])
{
	int i, j;
	char tmp[MAXLINE];

    // copy line to tmp
	for (i = 0; i < MAXLINE; ++i) {
		tmp[i] = line[i];
		if (line[i] == '\0' || line[i] == '\n')
			break;
	}
	--i; // omit last character

	for (j = 0; i >= 0; --i, ++j) {
		line[j] = tmp[i];
	}
	line[j] = '\n';
}

