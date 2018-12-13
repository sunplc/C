#include <stdio.h>

int Strend(char *s, char *t)
{
	char *tmp = t;
	if (*t == '\0' || *s == '\0') {
		return -1;
	} else {
		while (*t != '\0')
			++t;
		while (*s != '\0')
			++s;
		while (*s == *t) {
			--s;
			--t;
		}
		//printf("%p %p\n", t, tmp);
		if (++t == tmp)
			return 1;
		else
			return 0;
	}
}

// 编写函数 strend(s, t)
// 如果字符串 t 出现在字符串 s 的末尾处函数返回 1，否则返回 0。
int main(void)
{
	char *s = "hello, world!";
	char *t = "world";
	t = "rld!";

	printf("%d\n", Strend(s, t));
	return 0;
}

