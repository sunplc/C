#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	printf("%g %g\n", v1, v2);
	if (v1 > v2) {
		return 1;
	} else if (v1 < v2) {
		return -1;
	} else {
		return 0;
	}
}

int main()
{
	char *a = "123.12";
	char *b = "123";
	int (*fp)(char *s1, char *s2);
	fp = numcmp;
	printf("%p\n", fp);
	printf("%p\n", a);
	printf("%p\n", b);
	printf("%d\n", fp(a, b));

	char *s = "hello";
	putchar(*(++s));
	putchar(*(++s));
	putchar(*(++s));
	putchar(*(++s));
	putchar(*s);
	putchar('\n');

	char *v[10];
	v[0] = "1234";
	printf("%s\n", v[0]);

	char str[] = "abc";
	char *p[4];
	p[0] = str;
	p[1] = str;
	p[2] = str;
	printf("%s\n", *p);

	char (*ps[2])[4]; 
	ps[0] = &str;
	ps[1] = &"cvb";
	printf("%c\n", (*ps[0])[1]);
	printf("%s\n", *ps[1]);
	//return 0;

	//包含两个指向13个元素的数组的指针的数组
	int (*daytab[2])[13];
	int commonyear[] ={ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	//平年 
	int leapyear[] ={ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	//闰年 
	daytab[0] = &commonyear;	//平年
	daytab[1] = &leapyear;	//闰年
	printf("%d\n", (*daytab[1])[2]);

	return 0;
}

