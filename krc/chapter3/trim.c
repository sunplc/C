#include <stdio.h>
#include <string.h>

//去除字符串首尾的空白字符(空格、换行府、制表符)，不使用break
void trim(char *s)
{
	int i, j, flag = 0;
	for (i = 0, j = 0; s[i] != '\0'; ++i) {
		if (flag == 1 || !(s[i] == ' ' || s[i] == '\n' ||  s[i] == '\t')) {
			s[j++] = s[i];
			flag = 1;
		}
	}
	s[j] = '\0';
	flag = 0;
	for (i = j - 1; flag == 0 && i >= 0; --i) {
		if (s[i] == ' ' || s[i] == '\n' ||  s[i] == '\t') {
			s[i] = '\0';
		} else {
			flag = 1;
		}
	}
}

int main()
{
	char s[] = "\t          abc   \t";
	trim(s);
	printf("s = %s, length = %d\n", s, (int)strlen(s));
	return 0;
}

