#include <stdio.h>

// 操作符结合性，即 操作符计算顺序
// 从左向右 或 从右向左
//
int main(int argc, char *argv[])
{
    // ! ~ ++ -- + - (一元 + -) *  (type) sizeof 
    // 这几个运算符的优先级相同，结合型从右向左

    int i, *p;
    p = &i;

    *p++;
    *++p;
    ++*p;


	return 0;
}

