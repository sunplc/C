#include <stdio.h>
#define LEN 10

void print_array(int a);

int a[LEN] = { 5, 2, 4, 7, 1, 3, 2, 6, 34, -88 };

// 将两个数组用新数组保存起来，然后排序后替换原数组
void merge(int start, int mid, int end)
{
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int left[n1], right[n2];

	// 创建left和right两个数组，用于暂时保存将要替换的a数组的部分
	int i, j;
	for (i = 0; i < n1; ++i)
		left[i] = a[start + i];	

	for (j = 0; j < n2; ++j)
		right[j] = a[mid + 1 + j];

	i = j = 0;
	int k = start;
	// 比较left和right中各个数的大小，将数组a的各个数依次替换
	while (i < n1 && j < n2) {
		if (left[i] < right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];
	}
	// 当left数组或right数组中的数没有替换完时，继续替换
	while (i < n1)
		a[k++] = left[i++];	
	while (j < n2)
		a[k++] = right[j++];
}

// 将数组分割为左右两个
void split(int start, int end)
{
	int mid;
	if(start < end) {
		mid = (start + end) / 2;
		split(start, mid);
		split(mid + 1, end);
		merge(start, mid, end);
		print_array(LEN);
	}
}
// 打印数组
void print_array(int len)
{
	int i;
	for (i = 0; i < len; ++i)
		printf("%d\t", a[i]);
	printf("\n");		
}

// 先分割数组,然后合并排序
int main(void)
{
	split(0, LEN-1);
	return 0;
}
