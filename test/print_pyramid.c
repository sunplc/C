/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Apr 2016 02:51:23 AM PDT
 ************************************************************************/

#include<stdio.h>

int main()
{
    int i, j, k;
    for (i = 0; i < 20; i+=2)
    {
        for (k = 0; k < (20 - i)/2; ++k)
        printf(" ");
        for (j = 0; j <= i; ++j)
            printf("*");
        printf("\n");
    }
}
