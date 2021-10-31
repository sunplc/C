#include "../csapp.h"

void try()
{
	if (Fork() == 0) {
        Fork();
        Fork();
        printf("Example\n");
        return;
    }
	return;
}

int main()
{
	try();
	printf("Example\n");
	exit(0);
}
