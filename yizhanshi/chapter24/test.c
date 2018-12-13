#include <stdio.h>
#include <string.h>

void mystrcpy(char *dest, const char *src)
{
	int i;
	for (i = 0; ; i++) {
		dest[i] = src[i];
		if (src[i] == '\0') break;
	}
}

char *shrink_space(const char *src)
{
	char dest[100];
	int is_prev_letter_space = 0, i, j = 0;
	for (i = 0; src[i] != '\0' && j < 100; i++) {
		char c = src[i];
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
			if (is_prev_letter_space == 0)
				dest[j++] = ' ';
			is_prev_letter_space = 1;	
		} else {
			dest[j++] = src[i];
			is_prev_letter_space = 0;	
		}
	}
	dest[j] = '\0';
	char *ps = dest;
	return ps;
}

int main(int argc, char *argv[])
{
	char buf[10] = "ttttttttt\0";
	printf("size = %ld\n", sizeof(buf));
	mystrcpy(buf, "123456789abcd");
	//strcpy(buf, "123456789abcd");
	//strncpy(buf, "123456789abcd", sizeof(buf));
	//buf[sizeof(buf)-1] = '\0';
	printf("%s\n", buf);

	char *src = "This is hoho		jj\
DFD           S    dsf\
";
	char *dest = shrink_space(src);
	printf("%s\n", dest);
	return 0;
}

