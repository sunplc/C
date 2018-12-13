#include <stdio.h>

struct point {
	double x, y;
};

struct segment {
	struct point start, end;
};

int main(void)
{
	struct segment s = {{3.0, 4.0}, {4.0, 7.0}};
	struct segment s1 = {{1.0, 2.0},{ 3.3, 4.4}};
	struct segment s2 = {{1.11, 2.22}, {3.33, 4.4}};
	s.start.x = 3.1415;
	printf("s.start.x = %f\n", s.start.x);
	printf("s1.start.x = %f\n", s1.start.x);
	printf("s2.start.x = %f\n", s2.start.x);
	return 0;
}
