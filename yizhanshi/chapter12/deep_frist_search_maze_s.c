// 使用深度优先搜索解迷宫问题

#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

struct point {
	int row;
	int col;
};

struct point stack[MAX_ROW * MAX_COL];

int top = 0;

void push(struct point p)
{
	stack[top++] = p;
}

struct point pop(void)
{
	return stack[--top];
}

int is_empty(void)
{
	return top == 0;
}

int maze[MAX_ROW][MAX_COL] = {
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
};

struct point predecessor[MAX_ROW][MAX_COL] = {
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}},
};

void visit(int row, int col, struct point pre)
{
	struct point visit_point = {row, col};
	push(visit_point);
	maze[row][col] = 2;
	predecessor[row][col] = pre;
}


int main(void)
{
	struct point p = {4, 4};
	maze[p.row][p.col] = 2;
	push(p);

	while (!is_empty()) {
		p = pop();
		if (p.row == 0 && p.col == 0) // goal
			break;
		if (p.col + 1 < MAX_COL && maze[p.row][p.col + 1] == 0) // right
			visit(p.row, p.col + 1, p);
		if (p.row + 1 < MAX_ROW && maze[p.row + 1][p.col] == 0) // down
			visit(p.row + 1, p.col, p);
		if (p.col - 1 >= 0 && maze[p.row][p.col - 1] == 0) // left
			visit(p.row, p.col - 1, p);
		if (p.row - 1 >= 0 && maze[p.row - 1][p.col] == 0) // up
			visit(p.row - 1, p.col, p);
	}
	
	if (p.row == 0 && p.col == 0) { // reached goal
		top = 0;
		//printf("(%d, %d)\n", p.row, p.col);	
		push(p);
		while (predecessor[p.row][p.col].row != -1) {
			p = predecessor[p.row][p.col];	
			//printf("(%d, %d)\n", p.row, p.col);	
			push(p);
		}

		putchar('\n');
		while (!is_empty()) {
			p = pop();	
			printf("(%d, %d)\n", p.row, p.col);	
		}
	} else
		printf("No path!\n");
	return 0;
}
