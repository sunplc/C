#include <stdio.h>

#define KEYWORD		1
#define EXTERNAL	2
#define STATIC		4

struct {
	unsigned int is_keyword : 1;
	unsigned int is_external : 2;
	unsigned int is_static : 3;
} flags;

int main()
{
	flags.is_keyword = 1;
	flags.is_external = 2;
	flags.is_static = 4;

	return 0;
}

