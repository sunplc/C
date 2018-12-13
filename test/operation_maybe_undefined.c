#include <stdio.h>

// 编译时增加 -Wall 选项
// operation may be undefined 操作可能是未定义的
//
// 可能原因：++a 和 a++ 的顺序是不确定的
int main()
{
	int a = 3;
	int b = ++a + a++;
	printf("%d\n", b);

	return 0;
}

