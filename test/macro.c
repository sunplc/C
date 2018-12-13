/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Mon 18 Jul 2016 07:24:36 PM PDT
 ************************************************************************/

#include <stdio.h>

#define FOREVER for(;;)
#define MAXSIZE 1000
#define ADD(a, b)(a + b)
#define MYMAX(a, b)(a > b ? a : b)
#define ARR_LEN(arr)(sizeof(arr) / sizeof(arr[0]))

int main()
{
    int x;
    x = 10;
    int y;
    y = MAXSIZE;
    printf("max = %d\n", MYMAX(x,y));

    //FOREVER

	int arr[] = {2,3,4,5,6};
	printf("array length = %ld\n", ARR_LEN(arr));

    return 0;
}
