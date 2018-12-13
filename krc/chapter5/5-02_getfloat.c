#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define SIZE 3
#define MAXOP 100

int getch(void);
void ungetch(int c);		//将字符压回输入缓冲中

int main()
{
	int n;
	float array[SIZE], getfloat(float *);
	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; ++n)
		;
	int i;
	for (i = 0; i < SIZE; ++i)
		printf("%g ", array[i]);
	return 0;
}

float getfloat(float *pn)
{
	int c, sign;
	
	while ( isspace(c = getch()))	// skip white space
		;
	ungetch(c);

	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		return 0.0;	// it's not a number
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();
		ungetch(c);
		if(!isdigit(c) && c != '.') {
			return 0.0;	// it is not a float number.
		}
	}

	float val = 0.0, power = 1.0;
	while (isdigit(c = getch()))
		val = 10.0 * val + (c - '0');
	if (c == '.')
		while (isdigit(c = getch())) {
			val = 10.0 * val + (c - '0');
			power *= 10.0;
		}
	printf("val=%g\n", val);
	// 统计e的指数
	int power_e = 0, sign_e = 1;
	if (c == 'e' || c == 'E') {
		c = getch();
		sign_e = c == '-' ? -1 : 1;
		if ( !(c == '+' || c == '-'))
			ungetch(c);
		while (isdigit(c = getch())) {
			power_e = power_e * 10 + (c - '0');
		}
		power_e *= sign_e;
	}
	*pn = sign * val / power * pow(M_E, power_e);

	if (c != EOF)
		ungetch(c);
	else
		return -1.0;
	return 1.0; // It is a float
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

