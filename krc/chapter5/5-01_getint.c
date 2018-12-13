#include <stdio.h>
#include <ctype.h>

#define SIZE 5

int getch(void);
void ungetch(int c);		//将字符压回输入缓冲中

int main()
{
	int n, array[SIZE], getint(int  *);
	for (n = 0; n < SIZE && getint(&array[n]) != EOF; ++n)
		;
	int i;
	for (i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);
	return 0;
}

int getint(int *pn)
{
	int c, sign;
	// skip white space
	while ( isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); // it's not a number
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);
			return 0;
		}
	}

	for (*pn = 0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
	}
	*pn *= sign;

	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100
char buf[BUFSIZE];	//供ungetch函数使用的缓冲区
int bufp = 0;		//buf中的下一个空闲位置

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
	return (bufp > 0) ? buf[--bufp] : getchar();
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

