#include <stdio.h>

/*
 * high address
 *
 *     stack (contains program stack, LIFO structure, function stack frame)
 * 
 *     heap (dynamic memory allocate, ie malloc/calloc/free)
 *     bss	(uninitialized data)
 *     data (initialized data)
 *     text (code segment)
 *
 * low address
 *
 */


/* 使用命令 size memory_layout.out 来查看各个segment的大小变化 */
int global = 1;
int main(int argc, char *argv[])
{
	static int i;
	int a = 1;
	return 0;
}

