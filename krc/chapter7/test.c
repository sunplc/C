#include <stdio.h>
#include <string.h>
#include <stdlib.h> //system() calloc()
#include <math.h> // math()
#include <time.h> // time();

int main(int argc, char *argv[])
{
	printf("FILENAME_MAX = %d\n", FILENAME_MAX);
	putchar('\n');

	int x = 5;
	printf("int x's address = %p\n", &x);
	char str[] = "someone";
	char *pos = strchr(str, 'e');
	printf("pointer pos = %p\n", pos);
	printf("position = %ld\n", pos-str);
	pos = strrchr(str, 'o');
	printf("position = %ld\n", pos-str);
	putchar('\n');
	
	system("date");
	system("echo xxxx");
	//system("ls -ltr --time-style=long-iso");
	putchar('\n');

	int *ip;
	ip = (int *) calloc(4, sizeof(int));
	printf("ip = %p\n", ip);
	printf("ip = %p\n", ip+1);
	free(ip);
	putchar('\n');

	float f = 1.0;
	printf("sin(%g) = %f\n", f, sin(f));
	f = 0.5;
	printf("cos(%g) = %f\n", f, cos(f));

	int i = 5;
	printf("exp(%d) = %f\n", i, exp(i));
	printf("sprt(%d) = %g\n", i, sqrt(i));

	//生成随机数
	time_t t;
	srand((unsigned) time(&t));
	int r = rand() % 100;
	printf("rand = %d\n", r);

	return 0;
}

