#include <stdio.h>
#include <string.h> // memcpy()
#include <time.h>	// time()
#include <stdlib.h>	// srand() rand()
#include <assert.h>

// 循环次数、排序次数
int loop_times = 0, swap_times = 0;

int min(int a, int b) {
	return a > b ? b : a;
}

void swap(int v[], int i, int j)
{
	++swap_times;
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void check_arr_sorted(int *arr, int len) {
	int i, prev, curr;
	for (i = 0; i < len; ++i) {
		curr = arr[i];
		if (i > 0) {
			assert(prev <= curr);
		}
		prev = curr;
	}
}

void print_arr(int *arr, int len)
{
	int i;
	for (i = 0; i < len; ++i)
		printf("%d ", arr[i]);
	putchar('\n');
}

//冒泡排序
void bubble_sort(int v[], int len)
{
	int i, j, is_ordered;
	for (i = 0; i < len-1; ++i) {
		is_ordered = 1;
		for (j = 0; j < len-1-i; ++j) {
			++loop_times;
			if (v[j] > v[j+1]) {
				is_ordered = 0;
				swap(v, j, j+1);
			}
		}
		if (is_ordered) {
			break;
		}
	}
}

// 选择排序
// 根据i将数组分为有序区 arr[0...i] 和 无序区 arr[i+1...n-1],
// 从无序区选出最小的元素arr[index]，交换 arr[i+1] 和 arr[index] 的值,
// 不断递增i，重复上述过程
void select_sort(int v[], int len)
{
	int i, j, tmp = 0, index;

	for (i = 0; i < len - 1; ++i) {
		for (j = i, tmp = v[i], index = i; j < len; ++j) {
			++loop_times;
			++swap_times;
			if (v[j] < tmp) {
				tmp = v[j];
				index = j;
			}
		}

		if (index != i) {
			++swap_times;
			v[index] = v[i];
			v[i] = tmp;
		}
	}
}

// 插入排序
// 根据i将数组分为有序区 arr[0...i] 和 无序区 arr[i+1...n-1],
// 将无序区的第一个元素arr[i+1] 插入有序区中的正确位置,
// 不断递增i，重复上述过程
void insert_sort(int v[], int len)
{
	int i, j, tmp;

	for (i = 0; i < len - 1; ++i) {
		if (v[i] > v[i+1]) {
			tmp = v[i+1];
			j = i;
			do {
				++loop_times;
				++swap_times;
				v[j+1] = v[j];
				--j;
			} while (j >= 0 && v[j] > tmp);
			v[j+1] = tmp;
		}
	}
}

// 快速排序（quicksort）。该算法是 C. A. R. Hoare 于 1962年发明的。
// 对于一个给定的数组，选取一个元素mid，并以该元素为界将其他元素分为两个子集，
// 一个子集的所有元素都小于选定元素，另一个子集的所有元素都大于或等于该元素，
// 然后对两个子集递归执行同一过程。当某个子集的元素少于 2个时，
// 该子集就不需要再进行排序，于是递归就终止了。
void quick_sort(int v[], int left, int right)
{
	int i, mid;
	if (left >= right) {
		return;
	}

	swap(v, left, (left + right)/2);

	mid = left;
	for (i = left+1; i <= right; ++i) {
		++loop_times;
		if (v[i] < v[left])
			swap(v, ++mid, i);
	}

	swap(v, left, mid);

	quick_sort(v, left, mid-1);
	quick_sort(v, mid+1, right);
}

void quick_sort_wrap(int arr[], int len)
{
	quick_sort(arr, 0, len - 1);
}


// 希尔排序函数用于整数数组的排序。
// 该排序算法由 D.L.Shell 于 1959年发明，其基本思想是：
// 在初始阶段对相隔较远的元素进行比较，
// 而不是像简单交换排序那样比较相邻的元素。
// 这样有助于快速消除大量乱序情况，从而减少后续阶段的工作量。
// 比较元素的间隔会逐渐递减为1，
// 此刻的排序实质上已变成一种相邻交换的方法。
void shell_sort(int arr[], int len) {
	int gap, i, j;
	int temp;
	for (gap = len >> 1; gap > 0; gap >>= 1)
		for (i = gap; i < len; i++) {
			temp = arr[i];
				++loop_times;
			for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap) {
				arr[j + gap] = arr[j];
				++swap_times;
			}
			arr[j + gap] = temp;
		}
}

/**
 * Merge sort is a divide-and-conquer algorithm that was invented by John von Neumann in 1945.
 * Most implementations produce a stable sort, which means that the order of equal elements 
 	is the same in the input and output. 
 * I think the biggest disadvantage of Merge sort is that it need an another array, and must 
 	copy that array back to the original array after every iteration.
 
 * Worst-case performance: O(nlog n)
 */
void merge_sort(int arr[], int len) {
	int copy[len];

	int width, i, left, mid, mid_copy, right, x = 0;

	for (width = 1; width <= len; width <<= 1) {
		for (i = 0; i < len; i += 2 * width) {
			x = left = i;
			mid_copy = mid = min((left + width), len);
			right = min((mid + width), len);
			// printf("x = %d, left = %d, mid_copy = %d, mid = %d, right = %d\n", x, left, mid_copy,mid, right);

			while (left < mid_copy && mid < right) {
				if (arr[left] > arr[mid]) {
					copy[x++] = arr[mid++];
				} else {
					copy[x++] = arr[left++];
				}
				++swap_times;
				++loop_times;
			}
			while(left < mid_copy){
				copy[x++] = arr[left++];
				++swap_times;
				++loop_times;
			}
			while(mid < right) {
				copy[x++] = arr[mid++];
				++swap_times;
				++loop_times;
			}
		}

		// print_arr(copy, len);
		memcpy(arr, copy, len * sizeof(int)); // 复制数组 copy 到 arr 中
	}
}

// 各种排序算法的比较
// 最快的是 shell_sort
int main(void)
{
	srand(time(NULL));
	
	// 数组长度
	int len = 1000;
	printf("array_length = %d \n", len);

	int arr[len], arr0[len];
	int i, max = 10000;
	for (i = 0; i < len; ++i) {
		// 随机产生 -max 与 max 之间的整数
		arr0[i] = rand() % (2 * max) - max + 1;
	}
	
	int bytes_of_array = len * sizeof(int);

	// 函数指针数组
	void (*sort_functions[])(int [], int) = {
		&bubble_sort,
		&insert_sort,
		&select_sort,
		&quick_sort_wrap,
		&shell_sort,
		&merge_sort,
	};

	char *functions_names[] = {
		"bubble_sort",
		"insert_sort",
		"select_sort",
		"quick_sort",
		"shell_sort",
		"merge_sort",
	};

	char *format = "%-30s %-20s %-20s\n";
	printf(format, "Algorithm Name:", "loop_times:", "swap_times:");
	format = "%-30s %-20d %-20d\n";

	for (i = 0; i < 6; ++i) {
		memcpy(arr, arr0, bytes_of_array); // 复制数组 arr0 到 arr 中

		loop_times = swap_times = 0;
		sort_functions[i](arr, len);
		printf(format, functions_names[i], loop_times, swap_times);
		check_arr_sorted(arr, len);
	}

	return 0;
}
