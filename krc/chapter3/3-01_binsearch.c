#include <stdio.h>
#include <time.h>

#define MAX_LEN 100000

int binsearch(int x, int arr[], int len);
int binsearch2(int x, int arr[], int len);

// 练习 3-1.
// 我们的二分查找程序在循环内部进行了两次测试，其实一次测试就足够了（代价是
// 在循环之外要有更多的测试）。编写在循环内只有一次测试的版ᴀ，并比较两者运行时间的差别。
//
// 结果两个函数没有效率差别
int main()
{
	int arr[MAX_LEN];
	int i;
	for (i = 0; i < MAX_LEN; ++i)
		arr[i] = i;

	//测试下正确能否查找到数值
	int p = binsearch2(2, arr, MAX_LEN);
	printf("position: %d\n", p);

	//重复执行多次，比较耗时
	clock_t time_taken;
	time_taken = clock();
	for (i = 0; i < 100000000; ++i)
		binsearch2(2, arr, MAX_LEN);
	time_taken = clock() - time_taken;

	printf("took %lu, took %lu seconds.\n", (unsigned long)time_taken, (unsigned long)time_taken / CLOCKS_PER_SEC);
	return 0;
}

int binsearch(int x, int arr[], int len)
{
	int low, high, mid;
	low = 0;
	high = len - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < arr[mid]) {
			high = mid -1;
		} else if (x > arr[mid]) {
			low = mid + 1;
		} else {
			return mid;
		}
	}

	return -1;
}

int binsearch2(int x, int arr[], int len)
{
	int low, high, mid;
	low = 0;
	high = len - 1;
	mid = (low + high) / 2;
	while (low <= high && x != arr[mid]) {
		if (x < arr[mid]) {
			high = mid -1;
		} else {
			low = mid + 1;
		}
		mid = (low + high) / 2;
	}
	if (x == arr[mid])
		return mid;
	else
		return -1;
}

