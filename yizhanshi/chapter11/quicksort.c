#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 12
void print_array();
//int a[LEN] = { 5, 2, 4, 7, 1, 3, 2, 6, 34, -88 };
int a[LEN] = {55,9,6,6,6,5,-33,4,3,2,1,0};

int partition(int start, int end)
{
	int length = end - start + 1; //本次需要分割的数组的长度
	int middle = start + rand() % length;	//取start和end之间的随机值
	//int middle = (end + start) / 2;	//取start和end的平均值
	int pivot = a[middle];	//被选取的一个pivot元素，比它小的存入left，比它大的存入right数组

	int i = 0, j = 0;
	int left[length], right[length];
	int k = start;
	while (k <= end) {
		if (k != middle) {
			if (a[k] < pivot)
				left[i++] = a[k++];	
			else
				right[j++] = a[k++];
		} else {
			++k;	
		}
	}
	// 将数组a的对应索引的元素依次替换为left、pivot和right
	int m;
	for (m = 0; m < i; ++m)
		a[start + m] = left[m];
	a[start + m] = pivot;
	int ret = start + m; 
	for (m = 0; m < j; ++m)
		a[start + i + m + 1] = right[m];
	
	//printf("start = %d, end = %d, length = %d, middle = %d, pivot = %d, ret = %d\n", start, end, length, middle, pivot, ret);
	//print_array();
	return ret;
}

// 递归分割
void quicksort(int start, int end)
{
	int mid;
	if (start < end) {
		mid = partition(start, end);
		if(start == 2 && end == 5) exit(666);
		quicksort(start, mid - 1);
		quicksort(mid + 1, end);
	}
}

// 打印数组
void print_array()
{
	int i;
	for (i = 0; i < LEN; ++i)
		printf("%d\t", a[i]);
	printf("\n");		
}

// 分割排序
int main(void)
{
	int a;
	for (a = 0; a < LEN; ++a)
		printf("%d--\t", a);
	putchar('\n');
	putchar('\n');
	print_array();

	srand(time(NULL));
	
	quicksort(0, LEN-1);
	print_array();
	return 0;
}
