/*
   putchar() equals fgetc(stdin);
   getchar() equals fputc(c, stdout);
   EOF equals -1
*/
#include <stdio.h>

int main(void)
{
	printf("input an character:\n");
	char c;
	c = fgetc(stdin);
	printf("Character is %c\n", c);
	printf("%d\n", EOF);
	fputc(c, stdout);
	return 0;
}

