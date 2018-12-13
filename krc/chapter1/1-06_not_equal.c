#include <stdio.h>

// 验证 getchar() != EOF 的值是0还是1
// 在终端使用 ctrl + d 可以输入 EOF
int main(void)
{
	int i = (getchar() != EOF);
	printf("i = %d\n", i);
	return 0;
}

