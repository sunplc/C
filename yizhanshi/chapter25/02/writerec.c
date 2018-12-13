/* 将结构体存入文件中 */
#include <stdio.h>
#include <stdlib.h>

struct record{
	char name[10];
	int age;
};

int main(int argc, char *argv[])
{
	struct record array[2] = {{"John", 24},{"Jack", 28}};
	FILE *fp = fopen("recfile", "w");
	if (fp == NULL) {
		perror("Open file recfile");
		exit(1);
	}
	fwrite(array, sizeof(struct record), 2, fp);
	fclose(fp);
	return 0;
}

