#include <stdio.h>

#define ALLOCSIZE 10000		// 可用空间大小

static char allocbuf[ALLOCSIZE];	//用于分配的存储
static char *allocp = allocbuf;		//头一个空闲的位置

// 返回指向n个字符空间的指针
char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {	//满足
		allocp += n;
		return allocp -n;
	} else	//没有足够的空间
		return 0;
}

// 释放p指向的存储
void afree(char  *p)
{
	if (p >= allocbuf && p <  allocbuf + ALLOCSIZE)
		allocp = p;
}

int main()
{

	return 0;
}

