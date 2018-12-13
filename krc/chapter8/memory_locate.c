#include <stdio.h>
#include <stdlib.h>

int g = 123;

int main(int argc, char *argv[])
{
	// 全局变量在 data segment ，在低地址
	printf("&g = %p\n", &g);

	// 局部变量在函数栈帧中，在高地址；
	// 栈帧中的变量的地址逐个减小，即向低地址方向分配
	int a = 3;
	int b = 4;
	int c = 5;
	int d = 6;
	printf("&a = %p\n", &a);
	printf("&b = %p\n", &b);
	printf("&c = %p\n", &c);
	printf("&d = %p\n", &d);


	// malloc分配的地址在堆中，在低地址；
	// 堆中的变量的地址逐个增大的，即向高地址方向分配
	char *p;
	p = malloc(16);
	printf("p =  %p\n", p);
	p = malloc(16);
	printf("p =  %p\n", p);
	p = malloc(160);
	printf("p =  %p\n", p);

	static char str[5];
	printf("str = %p\n", str);
	p = str;
	*p = 'a';

#include <string.h>
	strcpy(p, "abc");
	puts(p);

	return 0;
}

