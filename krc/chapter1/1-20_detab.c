#include <stdio.h>

#define TAB_WIDTH 4 //制表符宽度，即每n列一个制表符停止位

// 练习 1-20 将输入中的制表符替换为恰当数目的空格，使间隔达到下一个制表符停止位
int main()
{
	int c, column = 1, tmp = 0, i;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			putchar(c);
			column = 1;
			continue;
		} else if (c == '\t') {
			tmp = (TAB_WIDTH - (column - 1) % TAB_WIDTH); //需要补齐几个空格才能到停止位
			for (i  = 0; i < tmp; ++i)
				putchar(' ');
			column += tmp;
		} else {
			putchar(c);
			++column;
		}
	}
}
