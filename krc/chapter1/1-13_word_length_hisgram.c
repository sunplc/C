#include <stdio.h>
#include <ctype.h>

#define IN 1
#define OUT 0
#define MAX_WORD_LEN 25         //最大单词长度，大于等于该值的都计为该值
#define MAX_SCREEN_WIDTH 80     //水平统计直方图的最大宽度
#define MAX_SCREEN_HEIGHT 30    //垂直统计直方图的最大高度

#define GET_ARR_LEN(arr)(sizeof(arr)/sizeof(arr[0]))    //计算数组长度

void hisgram_print(int *p, int len);
void hisgram_print_vertical(int *p, int len);

/* 练习 1-13 打印输入中所有单词的单词长度的统计直方图 */
int main()
{
	int c, state = OUT, word_len = 0, i;

	int word_length_count[MAX_WORD_LEN];

	for (i = 0; i < MAX_WORD_LEN; ++i)
		word_length_count[i] = 0;

	while ( (c = getchar()) != EOF ) {
		if (isspace(c)) {
			if (state == IN) {
				state = OUT;
				if (word_len > 0) {
                    if (word_len > MAX_WORD_LEN)
                        word_len = MAX_WORD_LEN;
					++word_length_count[word_len - 1];
					word_len = 0;
				}
			}
		} else {
			if (state == OUT) {
				state = IN;
			}
			++word_len;
		}
	}

	hisgram_print((int *)word_length_count, MAX_WORD_LEN);
	hisgram_print_vertical((int *)word_length_count, MAX_WORD_LEN);

	return 0;
}

//水平方向打印单词长度频率统计
void hisgram_print(int *p, int arr_len)
{
	int i, j, max_count = 0, step;

	for (i = 0; i < arr_len; ++i) {
		if (*(p + i) > max_count)
			max_count = *(p + i);
	}

	step = max_count/MAX_SCREEN_WIDTH;
	if (step < 1) step = 1;

    printf("单词长度统计直方图（水平方向）\n");
	printf("%10s\t| %-11s\n", "单词长度", "计数");

	for (i = 0; i < arr_len; ++i) {
		printf("%10d\t| ", i+1);

		for (j = 0; j < *(p + i); j+=step) {
			putchar('*');
		}
		printf("(%d)\n", *(p + i));
	}
	putchar('\n');
}

//垂直方向打印单词长度频率统计
void hisgram_print_vertical(int *p, int arr_len)
{
	int i, j, max_count = 0, step, cur_heigth;

	for (i = 0; i < arr_len; ++i) {
		if (*(p + i) > max_count)
			max_count = *(p + i);
	}

	step = max_count/MAX_SCREEN_HEIGHT;
	if (step < 1) step = 1;

    printf("单词长度统计直方图（垂直方向）\n");

	for (i = 0; i < MAX_SCREEN_HEIGHT + 1; ++i) {
		cur_heigth = (MAX_SCREEN_HEIGHT - i + 1) * step;
		printf("%6d  | ", cur_heigth);

		for (j = 0; j < arr_len; ++j) {
			if (*(p + j) >= cur_heigth){
				printf("*   ");
			} else {
                if ( *(p + j) > 0  && *(p + j) < cur_heigth
                        && *(p + j) + step >= cur_heigth) {
                    printf("%-4d", *(p + j));
                } else {
                    printf("    ");
                }
			}
		}
		putchar('\n');
	}
	
    // 打印直方图的底部信息
	printf("        | ");
	for (i = 0; i < arr_len; ++i) {
		printf("%-4d", i + 1);
	}
    puts("\n计数/单词长度");
}
