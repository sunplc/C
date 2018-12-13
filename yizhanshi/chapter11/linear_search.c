#include <stdio.h>

char str[] = "hello world";

int indexof(char letter)
{
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == letter)
			return i;
		++i;
	}
	return -1;
}

//int main(int argc, char* argv[])
int main(void)
{
	char letter;
	printf("please input an character:\n");
	letter = getchar();
	int index = indexof(letter);
	printf("The letter %c in \"%s\" index is %d\n", letter, str, index);
	return 0;
}
