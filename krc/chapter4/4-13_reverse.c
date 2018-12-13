#include <stdio.h>
#include <string.h>	// strlen()

void reverse(char str[], int i, int j)
{
	int temp;
	temp = str[i];
	str[i] = str[j];
	str[j] = temp;
	if (i < j - 2) {
		reverse(str, ++i, --j);
	}
}

// 练习 4-13. 编写一个递归版本的 reverse(s)函数，
// 该函数将字符串 s 本身颠倒过来。
int main()
{
	char str[] = "hello, world!";
	reverse(str, 0, 12);
	puts(str);
	return 0;
}

