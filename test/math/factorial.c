/*************************************************************************
	> File Name: factorial.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Jul 2016 08:28:17 PM PDT
 ************************************************************************/

/* 求阶乘 */
#include <stdio.h>

unsigned int factorial(unsigned int x)
{
    if (x > 1) {
        return x * factorial(x-1);
    } else {
        return 1;
    }
}

int main()
{
    int i = 10;
    printf("factorial %d is %d\n", i,  factorial(i));
    return 0;
}
