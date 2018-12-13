#include <stdio.h>

void squeeze(char s1[], char s2[]);

// 练习2-4. 编写squeeze函数的另一版本squeeze(s1,s2)，其从字符串s1中删除掉那些
// 但凡出现在字符串s2中的字符。
int main()
{
	char s1[] = "aabbbbccdddeeff";
	char s2[] = "acd";
	squeeze(s1, s2);
	printf("s1 = %s\n", s1);
	return 0;
}

void squeeze(char s1[], char s2[])
{
	int i, j, k = 0, flag;
	for (i = k = 0; s1[i] != '\0'; ++i) {
		flag = 0;
		for (j = 0; s2[j] != '\0'; ++j) {
			if (s1[i] == s2[j])
				flag = 1;
		}
		if (flag == 0)
			s1[k++] = s1[i];
	}
	s1[k] = '\0';
	//printf("k = %d\n", k);
}

