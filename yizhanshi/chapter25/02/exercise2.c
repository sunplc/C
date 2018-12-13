#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
	FILE *fp = fopen("test.ini", "r");
	if (fp == NULL) {
		perror("Error opening file");
		exit(1);
	}
	
	FILE *destfp = fopen("test.xml", "w");
	if (destfp == NULL) {
		perror("Error opening file");
		exit(1);
	}

	char *line = malloc(MAXLINE);
	char *xmlline;
	while (fgets(line, MAXLINE, fp) != NULL) {
		xmlline = malloc(MAXLINE);
		//fputs(line, stdout); // print each line of the ini file

		// get the first char
		char c, first_char;
		int i;
		for (i = 0; i < strlen(line); i++) {
			//printf("%c", line[i]);	
			c = line[i];
			if (c != ' ' && c != '\t') {
				first_char = c;
				break;
			}
		}
		printf("first_char is %d\n", first_char);

		char buf[MAXLINE];
		// judge if first char is ';', if the line is comment line
		if (first_char == ';') {
			memcpy( xmlline, &line[i+1], strlen(line)-i-2);
			xmlline[ strlen(line) -i -2] = '\0';
			snprintf(buf, MAXLINE, "<!-- %s -->\n", xmlline);
			puts(buf);
			fputs(buf, destfp);
		} else if (first_char == '[') {
			int j = 0;
			for (++i; i < strlen(line); i++) {
				if (line[i] == ']')
					break;	
				buf[j] = line[i];	
				++j;
			}
			buf[j] = '\0';
			puts(buf);
			char *buf2[MAXLINE];
			snprintf(buf2, MAXLINE, "<%s>\n", buf);
			fputs(buf2, destfp);
			snprintf(buf2, MAXLINE, "<%s/>\n", buf);
			fputs(buf2, destfp);
			int rs = fseek(destfp, 0-strlen(buf2), SEEK_CUR);
			printf("rs = %d\n", rs);
		} else if (first_char == '\n') {
			fputs("\n\n", destfp);
			fseek(destfp, 0, SEEK_END);
		} else {
			char buf2[100];
			fread(buf2, MAXLINE, 1, destfp);
			puts("mark");
			puts(buf2);
			fputs("ABCD", destfp);
			fwrite(buf, strlen(buf2)+1, 1, destfp);
			break;
		}
		free(xmlline);
	}

	free(line); // release memory
	fclose(destfp);
	fclose(fp); // close file pointer
	return 0;
}

