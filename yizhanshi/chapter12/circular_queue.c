// 广度优先搜索解迷宫问题 使用环形队列

#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5
#define QUEUE_MAX_INDEX 24

struct point {int row, col, predecessor;} queue[QUEUE_MAX_INDEX];
int head = 0, tail = 0;

void enqueue(struct point p)
{
	// tail指向数组最大值时，重新从0开始，否则自增1
	if (tail == QUEUE_MAX_INDEX) {
		queue[tail] = p;	
		tail = 0;
	} else 
		queue[tail++] = p;
}

struct point dequeue(void)
{
	// head指向数组最大值时，重新从0开始，否则自增1
	if (tail == QUEUE_MAX_INDEX) {
		head = 0;
		return queue[QUEUE_MAX_INDEX];
	} else 
		return queue[head++];
}

int is_empty(void)
{
	return head == tail;
}

int maze[MAX_ROW][MAX_COL] = {
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0}
};

void print_maze(void)
{
	int i, j;
	for (i = 0; i < MAX_ROW; i++) {
		for (j = 0; j < MAX_COL; j++)
			printf("%d ", maze[i][j]);
		putchar('\n');
	}
	printf("*********\n");
}

void visit(int row, int col)
{
	struct point visit_point = { row, col, head-1 };
	maze[row][col] = 2;
	enqueue(visit_point);
}

int main(void)
{
	struct point p = { 0, 0, -1 };

	maze[p.row][p.col] = 2;
	enqueue(p);

	while (!is_empty()) {
		p = dequeue();	
		if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1)
			break;
		if (p.col + 1 < MAX_COL && maze[p.row][p.col + 1] == 0) // right
			visit(p.row, p.col + 1);
		if (p.row + 1 < MAX_ROW && maze[p.row + 1][p.col] == 0) // down
			visit(p.row + 1, p.col);
		if (p.col - 1 >= 0 && maze[p.row][p.col - 1] == 0) // left
			visit(p.row, p.col - 1);
		if (p.row - 1 >= 0 && maze[p.row - 1][p.col] == 0) // up
			visit(p.row - 1, p.col);
		print_maze();
	}
	
	if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1) {
		printf("(%d, %d)\n", p.row, p.col);	
		while (p.predecessor != -1) {
			p = queue[p.predecessor];
			printf("(%d, %d)\n", p.row, p.col);
		}
	} else
		printf("No path!\n");

	return 0;
}
