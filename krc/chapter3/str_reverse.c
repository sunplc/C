#include <stdio.h>
#include <string.h>

void str_reverse(char s[])
{
	int c, i, j, len;
	len = strlen(s);
	for (i = 0, j = len - 1; i < j; ++i, --j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

int main(void)
{
	char s[] = "hello world!";
	str_reverse(s);
	printf("%s\n", s);
	return 0;
}

