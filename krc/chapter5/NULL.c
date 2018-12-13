#include <stdio.h>

int main()
{
	//指针和整数不能互换。
	//零值是唯一的例外:
	//零值常量可以被赋值给一个指针
	//而指针可以与零值常量比较。
	//零值常常用符号常量NULL所替换，
	//更清晰的标示出这是用于指针的特殊赋值
	//NULL定义在 stddef.h 中
	int *p = 0;
	printf("p == NULL >>> %d\n", p == NULL);
	printf("%p\n", p);
	printf("%d\n", NULL);
	return 0;
}

