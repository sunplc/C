#include <stdio.h>

#define OUT 0		//不在注释中
#define INLINE_IN 1 //在单行注释中
#define BLOCK_IN 2	//在块注释中

//练习 1-23. 编写一个程序，用于去掉 C程序的所有注释。
//注意正确地处理带引号的字符串和字符常量。
//C 语言的注释不允许嵌套。
//
// c语言的注释有 单行注释和块注释 两种
// 测试输入文本 comments.txt

int main()
{
	int c, state, first = 0, second = 0;
	state = OUT; //当前字符是否在注释字符串中，IN是，OUT不是

	while ((c = getchar()) != EOF) {
		first = second;
		second = c;
		if (first == '/' && second == '/') {
			if (state == OUT)
				state = INLINE_IN;

		} else if (first == '/' && second == '*') {
			if (state == OUT)
				state = BLOCK_IN;

		} else if (second == '\n') {
			if (state == INLINE_IN) {
				state = OUT;
				putchar(second);
			} else if (state == BLOCK_IN) {
				;
			} else {
				putchar(first);
				putchar(second);
			}
			first = second = 0;

		} else if (first == '*' && second == '/') {
			if (state == BLOCK_IN) {
				state = OUT;
				first = second = 0;
			} else if (state == INLINE_IN) {
				;
			} else {
				putchar(first);
			}

		} else {
			if (state == OUT)
				if (first)
					putchar(first);
		}
	}
	return 0;
}

