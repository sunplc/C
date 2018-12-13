#include <stdio.h>

int any(char s1[], char s2[]);

// 练习 2-5. 编写函数 any(s1,s2)，其返回 s1 中首次出现字符串 s2
// 中任何字符的位置；如果 s1 中不包含 s2 中的任何字符，则返回 -1 。
// （标准库函数 strpbrk 完成同样的工作，但它返回一个指向该位置的指针。 ）
int main()
{
	char s1[] = "aabbbbccdddeeff";
	char s2[] = "defc";
	//char s2[] = "00xyz";

	int index = any(s1, s2);
	printf("index = %d\n", index);
	return 0;
}

int any(char s1[], char s2[])
{

	int i, j;
	for (i = 0; s1[i] != '\0'; ++i)
		for (j = 0; s2[j] != '\0'; ++j)
			if (s1[i] == s2[j])
				return i;

	return -1;
}
