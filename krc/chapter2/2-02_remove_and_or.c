#include <stdio.h>

#define MAX_STRING_LENGTH 100

// 练习2-2. 编写一个与上面的for循环等价但没有采用 && 或 || 的循环
int main()
{
	/*
	 * for (i = 0; i < lim -1 && (c = getchar()) != '\n' && c != EOF; ++i)
	 *		s[i] = c;
	 */
	int i = 0, c, lim = MAX_STRING_LENGTH;
	char s[MAX_STRING_LENGTH];
	while (i < lim - 1) {
		c = getchar();
		if ( c == '\n')
			break;
		else if (c == EOF)
			break;
		s[i++] = c;
	}
	s[i] = '\0';
	printf("%s", s);
	return 0;
}

