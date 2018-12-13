#include <stdio.h>

int main(void)
{
	FILE *fp;
	if ( (fp = fopen("/tmp/file1", "r")) == NULL) {
		fputs("Error open file /tmp/file1\n", stderr);	
	}
	return 0;
}

