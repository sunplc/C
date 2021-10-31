#include "../csapp.h"
void try()
{
	if (Fork() != 0) {
        Fork();
        printf("Example\n");
        exit(0);
    }
	return;
}

int main()
{
	try(); Fork();
	printf("Example\n");
	exit(0);
}
