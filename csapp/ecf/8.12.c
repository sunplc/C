#include "../csapp.h"
void try()
{
	Fork();
	printf("Example\n");
	Fork();
	return;
}

int main()
{
	try(); Fork();
	printf("Example\n");
	exit(0);
}
