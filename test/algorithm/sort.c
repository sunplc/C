#include <stdio.h>
#include <string.h> // memcpy()
#include <time.h>	// time()
#include <stdlib.h>	// srand() rand()

// 循环次数、排序次数
int loop_times = 0, swap_times = 0;

void swap(int v[], int i, int j)
{
	++swap_times;
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

//冒泡排序
void bubble_sort(int v[], int len)
{
	int i, j;
	for (i = 0; i < len-1; ++i) {
		for (j = 0; j < len-i-1; ++j) {
			++loop_times;
			if (v[j] > v[j+1])
				swap(v, j, j+1);
		}
	}
}

// 快速排序（quicksort）。该算法是 C. A. R. Hoare 于 1962年发明的。
// 对于一个给定的数组，选取一个元素，并以该元素为界将其他元素分为两个子集，
// 一个子集的所有元素都小于选定元素，另一个子集的所有元素都大于或等于该元素，
// 然后对两个子集递归执行同一过程。当某个子集的元素少于 2个时，
// 该子集就不需要再进行排序，于是递归就终止了。
void quick_sort(int v[], int left, int right)
{
	int i, last;
	if (left >= right) {
		return;
	}
	//选取last元素作为比较，将小于last的元素排列到last的左边，大于等于last的元素排列到last右边
	//将last左右两边分为两个数组，再对这两个数组递归执行上述过程，直到子数组的元素数量小于两个时停止。
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; ++i) {
		++loop_times;
		if (v[i] < v[left])
			swap(v, ++last, i);
	}
	swap(v, left, last);
	quick_sort(v, left, last-1);
	quick_sort(v, last+1, right);
}


// 希尔排序函数用于整数数组的排序。
// 该排序算法由 D.L.Shell 于 1959年发明，其基本思想是：
// 在初始阶段对相隔较远的元素进行比较，
// 而不是像简单交换排序那样比较相邻的元素。
// 这样有助于快速消除大量乱序情况，从而减少后续阶段的工作量。
// 比较元素的间隔会逐渐递减为1，
// 此刻的排序实质上已变成一种相邻交换的方法。
void shell_sort(int v[], int n)
{
	int gap, i, j;
	for (gap = n/2; gap > 0; gap /= 2) {
		//printf("gap = %d\n", gap);
		for (i = 0; i < n-gap; ++i) {
			//printf("\ti = %d\n", i);
			//for (j = i; j >= 0 && v[j] > v[j+gap]; j -= gap) {
			for (j = i; j >= 0; j -= gap) {
				if (v[j] > v[j+gap]) {
					++loop_times;
					//printf("\t\tj=%d exchange\n", j);
					swap(v, j, j+gap);
				} else {
					//printf("\t\tj=%d break\n", j);
					break;
				}
			}
		}
	}
}

// 直接插入排序
// 根据i将数组分为有序区 arr[0...i] 和 无序区 arr[i+1...n-1],
// 将无序区的第一个元素arr[i+1] 插入有序区中的正确位置,
// 不断递增i，重复上述过程
void directly_insert_sort(int v[], int len)
{
	int i, j, tmp;

	for (i = 0; i < len - 1; ++i) {
		if (v[i+1] < v[i]) {
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

// 直接选择排序
// 根据i将数组分为有序区 arr[0...i] 和 无序区 arr[i+1...n-1],
// 从无序区选出最小的元素arr[index]，交换 arr[i+1] 和 arr[index] 的值,
// 不断递增i，重复上述过程
void directly_select_sort(int v[], int len)
{
	int i, j, tmp = 0, index;

	for (i = 0; i < len - 1; ++i) {
		for (j = i, tmp = v[i], index = i; j < len; ++j) {
			++loop_times;
			if (v[j] < tmp) {
				tmp = v[j];
				index = j;
				++swap_times;
			}
		}

		if (index != i) {
			v[index] = v[i];
			v[i] = tmp;
		}
	}
}

// 各种排序算法的比较
// 最快的是 shell_sort
int main(void)
{
	srand(time(NULL));
	// 随机数组长度
	int len = rand() % 1000;
	int v1[len], v2[len], v3[len], v4[len], v5[len];

	printf("array_length = %d \n", len);
	int i, max = 10000;
	for (i = 0; i < len; ++i) {
		// 随机产生 -max 与 max 之间的整数
		v1[i] = rand() % (2 * max) - max;
		//printf("%d ", v1[i]);
	}
	putchar('\n');
	
	int array_bytes = len * sizeof(int);

	// 复制数组v1 到 v2 ... v5 中
	memcpy(v2, v1, array_bytes);
	memcpy(v3, v1, array_bytes);
	memcpy(v4, v1, array_bytes);
	memcpy(v5, v1, array_bytes);

	printf("%-30s %-20s %-20s\n", "Algorithm Name:", "loop_times:", "swap_times:");

	char format[] = "%-30s %-20d %-20d\n";
	loop_times = swap_times = 0;
	shell_sort(v1, len);
	printf(format, "shell_sort", loop_times, swap_times);
	
	loop_times = swap_times = 0;
	quick_sort(v2, 0, len-1);
	printf(format, "quick_sort", loop_times, swap_times);

	loop_times = swap_times = 0;
	bubble_sort(v3, len);
	printf(format, "bubble_sort", loop_times, swap_times);

	loop_times = swap_times = 0;
	directly_insert_sort(v4, len);
	printf(format, "directly_insert_sort", loop_times, swap_times);

	loop_times = swap_times = 0;
	directly_select_sort(v5, len);
	printf(format, "directly_select_sort", loop_times, swap_times);

	putchar('\n');

	if (0) {
		for (i = 0; i < len; ++i) {
			printf("%d ", v1[i]);
		}
		putchar('\n');

		for (i = 0; i < len; ++i) {
			printf("%d ", v2[i]);
		}
		putchar('\n');

		for (i = 0; i < len; ++i) {
			printf("%d ", v3[i]);
		}
		putchar('\n');

		for (i = 0; i < len; ++i) {
			printf("%d ", v4[i]);
		}
		putchar('\n');

		for (i = 0; i < len; ++i) {
			printf("%d ", v5[i]);
		}
		putchar('\n');
	}

	return 0;
}

