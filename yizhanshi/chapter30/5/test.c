#include <stdio.h>
#include <string.h>

int main(void)
{
    char one[] = "> 1.txt";
    if (one[0] == '>') {
        char *token;
        token = strtok(one, ">");
        token = strtok(token, " ");
        printf("%s\n", token);
        printf("mark");
    }
	return 0;
}

