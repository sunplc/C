#include <stdio.h>

void swap(int v[], int i, int j)
{
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void quick_sort(int v[], int left, int right)
{
	int i, last;
	if (left >= right) {
		return;
	}
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; ++i)
		if (v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);
	quick_sort(v, left, last-1);
	quick_sort(v, last+1, right);
}

// 快速排序（quicksort）。该算法是 C. A. R. Hoare 于 1962年发明的。
// 对于一个给定的数组，选取一个元素，并以该元素为界将其他元素分为两个子集，
// 一个子集的所有元素都小于选定元素，另一个子集的所有元素都大于或等于该元素，
// 然后对两个子集递归执行同一过程。当某个子集的元素少于 2个时，
// 该子集就不需要再进行排序，于是递归就终止了。
int main(void)
{
	int arr[] = {100, 23, 45, 65, 23, 90, -123, 456, 72, 71, 9, 7};
	int len = 12;
	quick_sort(arr, 0, len - 1);
	int i;
	for (i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	putchar('\n');
	return 0;
}

