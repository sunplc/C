#include <stdio.h>

#define BUFSIZE 100

static char buf[BUFSIZE];	//供ungetch函数使用的缓冲区
static int bufp = 0;		//buf中的下一个空闲位置

int getch(void)
{
	if (bufp > 0) {
		return buf[--bufp];
	} else {
		int c = getchar();
		if (c == EOF) {
			return -1;
		} else {
			return c;
		}
	}
}

void ungetch(int c)
{
	if (c == EOF)
		return ;
	if (bufp >= BUFSIZE) {
		printf("ungetch: 压回字符过多\n");
	} else {
		buf[bufp++] = c;
	}
}

