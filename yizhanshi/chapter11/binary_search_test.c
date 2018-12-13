// 如果在包含assert.h之前定义一个NDEBUG宏(表示No Debug)
// 就可以禁用assert.h中的assert宏定义
// 使代码中所有的assert测试都不起作用
// 在编译命令行加上选项-DNDEBUG就相当于在源文件开头定义了NDEBUG宏

//#define NDEBUG

#include <stdio.h>
#include <assert.h>

#define LEN 15
int a[LEN] = {1,2,2,3,4,5,5,9,10,11,12,13,13,13,14};
// 数组是否是已排序的
int is_sorted(void)
{
	int i;
	for (i = 0; i < LEN - 1; i++)
		if (a[i] > a[i+1])
			return 0;
	return 1;
}
// 数组在start-end区间外是否不含有该数字
int mustbe(int start, int end, int number)
{
	int i;
	for (i = 0; i < start; i++)
		if (a[i] == number)
			return 0;
	for (i = end + 1; i < LEN; i++)
		if (a[i] == number)
			return 0;
	return 1;
}
// 数组是否含有给数字
int contains(int n)
{
	int i;
	for (i = 0; i < LEN; i++)
		if (a[i] == n)
			return 1;
	return 0;
}

int binary_search(int number)
{
	int mid, start = 0, end = LEN - 1;
	assert(is_sorted()); // Precondition

	while (start <= end) {
		assert(mustbe(start, end, number)); // Maintenance	
		mid = (start + end) / 2;
		//printf("%d %d %d\n", start, end, mid);
		if (a[mid] < number)
			start = mid + 1;
		else if (a[mid] > number)
			end = mid - 1;
		else {
			// Postcondition 1
			assert(mid >= start && mid <= end && a[mid] == number);
			// 搜索结果为从左到右该数字第一次在数组中出现的下标
			int i;
			for (i = mid; i >= start; i--) {
				//printf("mark i = %d\n", i);
				if (a[i] != number)
					break;
			}
			return i + 1;
		}
	}
	assert(!contains(number));
	return -1;
}

int main(void)
{
	printf("%d\n", binary_search(5));
	return 0;
}
