#include <stdio.h>
#include <time.h>

int main()
{
	puts("wait a minute...");
	char *p = "hello";
	//测试前缀自增自减 与 后缀自增自减的耗时
	clock_t time_taken = clock();
	int i, j;
	for (i = 0; i < 50000; ++i)
		for (j = 0; j < 50000; ++j)
			if (i % 2 == 0) {
				//p++;
				++p;
			} else {
				//p--;
				--p;
			}

	time_taken = clock() - time_taken;

	printf("time_taken =  %lu / %lu = %lf seconds.\n", 
			(unsigned long)time_taken, CLOCKS_PER_SEC, (double)time_taken / CLOCKS_PER_SEC);
	return 0;
}

