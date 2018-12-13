/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Wed 14 Sep 2016 11:20:25 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void print_in_binary(int x);
void to_binary(unsigned long n);

int main()
{
	//char str[100];
	//scanf("%s", str);
    //int a = atoi(str);
	//int a = 0b1111111111111111001111111111; //使用二进制整数常量赋值
	int a = 3, b = 17;
	print_in_binary(a);
	print_in_binary(b);
	a = a ^ b;
	print_in_binary(a);
	b = a ^ b;
	print_in_binary(b);
	a = a ^ b;
	print_in_binary(a);
    return 0;
}

// 将一个整数以二进制的形式打印出来
void to_binary(unsigned long n)
{
    int r = n % 2;
    if (n >= 2) {
        to_binary(n / 2);
    }
    putchar('0' + r);
}

// 将int类型变量按照二进制形式打印出来
void print_in_binary(int x)
{
	int i, arr[32];
	for (i = 0; i < 32; i++) {
		if ((x & 0x00000001) == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		x = x >> 1;
	}
	for (i = 32; i > 0; i--) {
		if (i < 32 && i % 8 == 0)
			putchar(' ');
		printf("%d", arr[i-1]);	
	}
	putchar('\n');
}

