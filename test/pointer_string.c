#include <stdio.h>
#include <math.h>

int main(void)
{

	char *c[] = {
        "you can make statement",
        "for the topic",
        "the sentences",
        "How about"
    };

	char **p[] = {c+3, c+2, c+1, c};
	char ***pp = p;

	printf("%s", **++pp);
	printf("%s", *--*++pp+3);
	printf("%s", *pp[-2]+3);
	printf("%s", pp[-1][-1]+3);

	puts("\n-----------------------------");

	char *arr[2][3] = {{"abc","defgh","ijkl"},{"mnopqr","stuvw","xyz"}};
	printf("%c\n", ***(arr+1));
	printf("%c\n", **arr[0]);
	printf("%c\n", (*(*(arr+1)+1))[4]);
	printf("%c\n", *(arr[1][2]+2));
	printf("%s\n", **(arr+1));

	return 0;
}

