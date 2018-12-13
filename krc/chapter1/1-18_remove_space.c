#include <stdio.h>

#define MAXLINE 1000

int Getline(char line[], int limit);
void printline(char line[], int length);

// 练习 1-18 将每个输入行末尾的所有空格和制表符去掉,并将全空白的行删除掉
int main(void)
{
	int len;
	char line[MAXLINE];
	while( (len = Getline(line, MAXLINE)) > 0) {
		printline(line, len);
	}
	return 0;
}

int Getline(char line[], int limit)
{
	int i, c;
	for (i = 0; i < limit - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
		line[i] = c;
	}
	if (c == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return i;
}

void printline(char line[], int length)
{
	line[length-1] = '\0';
	int i, c;
	for (i = length - 1; i >= 0; --i) {
		c = line[i];
		if (c == '\t' || c == ' ' || c == '\0') {
			line[i] = '\0';
		} else {
			line[i+1] = '\n';
			break;
		}
	}
	printf("%s", line);
}
