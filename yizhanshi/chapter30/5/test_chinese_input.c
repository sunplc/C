#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 80

int main(void)
{
    char str[80];
    int n;
    n = read(STDIN_FILENO, str, MAXLINE);
    if (n < 0) {
        perror("read");
    }
    //write(STDOUT_FILENO, str, strlen(str));
    printf("result: %s", str);
	return 0;
}

