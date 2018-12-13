#include <stdio.h>

void say_hello(const char *str)
{
	printf("Hello, %s!\n", str);
}

void say_what(const char *str)
{
	printf("What %s?\n", str);
}

int main(int argc, char *argv[])
{
	void (*pf)(const char *) = say_hello;
	pf("Scarlett");
	pf = &say_what;
	pf("Arthur");
	(*pf)("Jack");
	return 0;
}

