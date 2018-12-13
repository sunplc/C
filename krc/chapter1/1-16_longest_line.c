#include <stdio.h>

#define MAXLINE 20 //MAXLINE改为20，更好测试

int Getline(char line[], int limit);
void copy(char to[], char from[]);

/* 练习 1-16 打印最长的输入行 */
int main(void)
{
	int len, max = 0;
	char line[MAXLINE], longest[MAXLINE];
	char c;
	
	while ((len = Getline(line, MAXLINE)) > 0) {
		// 获取的行的最后一个字符不是\n或\0，说明由于MAXLINE的长度限制，没有读完该行；
		// 获取改行的长度，尽可能多的显示最长行，即显示MAXLINE长度
		if (line[len-1] != '\n' && line[len-1] != '\0') {
			while ( (c = getchar()) != '\n' && c != EOF) {
				++len;
			}
		}
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)
		printf("%s", longest);
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

void copy(char to[], char from[])
{
	int i = 0;
	while ( (to[i] = from[i]) != '\0' )
		++i;
}

