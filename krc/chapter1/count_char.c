/* 统计输入的字符总数 */
#include <stdio.h>

int main()
{
    long nc;
	for (nc = 0; getchar() != EOF; ++nc)
		;
	printf("%ld characters\n", nc);
	return 0;
}
