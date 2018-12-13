#include <stdio.h>

int main(void)
{
    union {int a; char ch[2];} au;
    au.a = 298;
    printf("%d\n%d\n", au.ch[0], au.ch[1]);
	return 0;
}

