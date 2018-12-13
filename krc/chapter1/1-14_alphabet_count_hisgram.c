#include <stdio.h>
#include <ctype.h>

#define MAX_SCREEN_HEIGHT 30

// '0'~'9' => 48~57
// 'A'~'Z' => 65~90
// 'a'~'z' => 97~122
// 共 10 + 26 + 26 = 62 个字符，获取字符在数组中的索引
int array_index(int c)
{
	if (c >= 48 && c <= 57) {
        return c - 48;
    } else if (c >= 65 && c <= 90) {
        return c - 65 + 10;
    } else if (c >= 97 && c <= 122) {
        return c -  97 + 10 + 26;
    }

    return 0;
}

// 根据数组索引获取字符
int index_to_char(int i)
{
    if (i >= 0 && i < 10) {
        return i + 48;
    } else if (i >= 10 && i <= 35) {
        return i - 10 + 65;
    } else if (i >= 36 && i <= 61) {
        return i - 10 - 26 + 97;
    }
    return '0';
}

//垂直方向打印字母频率统计
void hisgram_print_vertical(int *p, int arr_len)
{
	int i, j, count, max_count, step, current_height;

	max_count = 0;
	for (i = 0; i < arr_len; ++i) {
        count = *(p + i);
        if(count > max_count)
            max_count = count;
	}

	step = (int)(max_count/MAX_SCREEN_HEIGHT);
	if (step < 1) step = 1;
	printf("\n\tmax_count=%d, step=%d\n", max_count, step);

	for (i = 0; i < MAX_SCREEN_HEIGHT; ++i) {
		current_height = (MAX_SCREEN_HEIGHT - i) * step;
		printf("%12d  | ", current_height);

		for (j = 0; j < arr_len; ++j) {
            count = *(p + j);
            if (count  >= current_height){
                printf("* ");
            } else {
                printf("  ");
            }
		}
		putchar('\n');
	}
	
	printf("               ");

	for (i = 0; i < arr_len; ++i) {
		printf("%2c", index_to_char(i));
    }

	putchar('\n');
}

/* 练习 1-14 打印输入中不同数字或字符出现频率的直方图 */
int main()
{
	int i, c, len = 62;

	//初始化统计数组
	int alphabet_count[len];
	for (i = 0; i < len; ++i)
        alphabet_count[i] = 0;

	while ( (c = getchar()) != EOF ) {
		if ( isalpha(c) ) {
			++alphabet_count[array_index(c)];
		}
	}

	hisgram_print_vertical((int *)alphabet_count, len);

	return 0;
}

