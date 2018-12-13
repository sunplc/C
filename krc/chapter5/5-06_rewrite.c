#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

// 练习 5-6.
// 以指针来替代数组下标，重写之前章节和练习中的相应程序。可能的好选择包括
// getline（第 1、4 章），atoi、itoa 及其变体（第 2、3、4 章），
// 以及 strindex 和gettop （第 4 章）。

// getop函数没有在本文件改写，改写了chapter4/4-10_calc_getline.c

/* 取一行放到 s 中，并返回该行的长度 */ 
int Getline(char *s, int lim)
{
	int c, i = 0;
	while ((c = getchar()) != EOF) {
		*s++ = c;
		++i;
		if (i >= lim || c == '\n') {
			break;
		}
	}
	*s = '\0';
	return i;
}

int atoi(char *s)
{
	int n = 0, sign = 1;
	while (isspace(*s))
		++s;
	if (*s == '-') {
		++s;
		sign = -1;
	}
	while (*s >= '0' && *s <= '9') {
		n =  10 * n + (*s++ - '0');
	}
	return sign * n;
}

// int转十进制字符串
void itoa(int n, char *str)
{
	static int i = 0;
	if (n < 0) {
		*(str + i++) = '-';
		n = -n;
	}

	if (n / 10)
		itoa(n / 10, str);
	*(str + i++) = n % 10 + '0';
}

/* strindex：返回 t 在 s 中的位置，若未找到则返回-1 */ 
int strindex(char *s, char *t)
{
	//int i, j, k;
	char *tmp = s, *tmp2 = t, *tmp3;
	for (; *s != '\0'; s++) {
		tmp3 = s;
		for (t = tmp2; *t != '\0' && *s == *t; s++, t++)
			;
		if (t != tmp2 && *t == '\0')
			return tmp3 - tmp;
		s = tmp3;
	}
	return -1;
}

int main()
{
	char s[MAXLINE];
	puts("Please input an number:");
	printf("LEN = %d\n", Getline(s, 6));
	printf("string = %s\n", s);

	int n = -781533;
	char str[100];
	itoa(n, str);
	printf("itoa = %s\n", str);

	char str2[] = "-5739789";
	printf("atoi = %d\n",  atoi(str2));
	
	char str3[] = "hello,world!";
	char str4[] = "ld";
	printf("strindex = %d\n", strindex(str3, str4));

	return 0;
}

