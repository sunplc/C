#include <stdio.h>

int main(int argc, char *argv[])
{
	typedef int T3[10];
	typedef T3 *T2;
	typedef T2 T1(void *);
	T1 *fp;
	
	int (*(*fp1)(void *)) [10];
	return 0;
}

