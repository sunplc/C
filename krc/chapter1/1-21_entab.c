#include <stdio.h>

#define TAB_WIDTH 4 //制表符宽度，即每n列一个制表符停止位

// 练习 1-21 将一连串空格替换为相同间隔的最小数目的制表符和空格
int main()
{
	char c;
	int count = 0, tables_num, spaces_num, i;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			++count;
		} else {
			if (count > 0) {
				tables_num = count / TAB_WIDTH;
				spaces_num = count % TAB_WIDTH;
				for (i = 0; i < tables_num; ++i)
					putchar('\t');
				for (i = 0; i < spaces_num; ++i)
					putchar(' ');
			}
			count = 0;
			putchar(c);
		}
	}
}
