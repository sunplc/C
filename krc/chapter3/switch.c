#include <stdio.h>

int main()
{
	char c = 'a';

	switch(c) {
		case 'a': case 'b':
			printf("mark\n");
			//break;
		case '0': 
			printf("mark0\n");
			break;
		case '1':
			printf("mark1\n");
			break;
		default:
			printf("what?\n");
	}
	return 0;
}

