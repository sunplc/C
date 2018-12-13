#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE	10 //每页显示多少行
#define TRUE			1
#define FALSE			0

void print_file(char *filename)
{
	FILE *f;
	int c, line_count = 1, page_count = 1, new_page = TRUE;

	if ((f = fopen(filename, "r")) != NULL) {
		while ( (c = fgetc(f)) != EOF ) {
			//在每页的开头输出开始标志行
			if (new_page) {
				printf("[ file: %s page: %d start]\n", filename, page_count);
				new_page = FALSE;
			}

			putchar(c);

			//在每页的末尾输出结束标志行
			if (c == '\n' && ++line_count > LINES_PER_PAGE) {
				printf("[ file: %s page: %d end]\n", filename, page_count);
				++page_count;
				new_page = TRUE;
				line_count = 1;
			}
		}
	}
}

/*
 * 练习 7-08. Write a program to print a set of files,
 * starting each new one on a new page,
 * with a title and a running page count for each file.
 */
int main(int argc, char *argv[])
{
	if (argc < 2) {
		fputs("no files specified\n", stderr);
		return EXIT_FAILURE;
	}
	int i;
	for (i = 1; i < argc; i++) {
		print_file(argv[i]);
	}
	return EXIT_SUCCESS;
}

