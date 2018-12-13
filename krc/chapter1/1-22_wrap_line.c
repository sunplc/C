#include <stdio.h>

#define MAX_LINE_WIDTH 80

int Getline(char line[]);

// 练习 1-22 编写一个程序，其将一个长输入行“折”为较短的几行，折行的位置为输入的第 n
// 列之前的最后一个非空白符之后。确保你的程序能够智能地处理很长的输入行，以及在指定列
// 之前没有空格或制表符的情况。
int main()
{
	int len;
	//line的最大长度设置为MAX_LINE_WIDTH + 2（行尾补上换行符\n和结束符\0）
	char line[MAX_LINE_WIDTH + 2];
	while ( (len = Getline(line)) > 0) {
		//printf("len = %d: %s", len, line);
		printf("%s", line);
	}
	return 0;
}

int Getline(char line[])
{
	int i, c, isWrap = 0;
	for (i = 0; i < MAX_LINE_WIDTH && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = c;
	}

	if (i ==  MAX_LINE_WIDTH)
		isWrap = 1;

	for(i = i - 1; i >= 0; --i) {
		if (line[i] == ' ' || line[i] == '\t') {
			line[i] = '\0';
		} else {
			break;
		}
	}

	if (isWrap || c == '\n')
		line[++i] = '\n';
	line[++i] = '\0';

	return i;
}
