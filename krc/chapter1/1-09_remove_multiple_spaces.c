#include <stdio.h>
#define IN 1
#define OUT 0

/* 练习 1-9 将输入拷贝到输出，并且将输入中的多个空格替换为一个空格 */
int main()
{
	int c, state = IN;
	while ( (c = getchar()) != EOF) {
		if ( c == ' ' || c == '\n'){
			if (state == IN) {
				putchar(c);
				state = OUT;
			}
		} else {
			putchar(c);
			if (state == OUT)
				state = IN;
		}
	}
	return 0;
}
