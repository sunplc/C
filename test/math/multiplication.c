/*************************************************************************
	> File Name: recursion.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Jul 2016 08:19:57 PM PDT
 ************************************************************************/

/* 用递归实现乘法 */
#include <stdio.h>

unsigned int multiply(unsigned int x, unsigned int y)
{
    if (x == 1) {
        return y;
    } else if (x > 1) {
        return y + multiply(x-1, y);
    } else {
        return 0;
    }
}

int main()
{
    printf("7 multiply 5 is %d\n", multiply(7, 5));
    return 0;
}
