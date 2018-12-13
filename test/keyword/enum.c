#include <stdio.h>

int main()
{
	enum state {OUT = 0, INLINE_IN = 1, BLOCK_IN, QUOTE_IN};
	enum state s = INLINE_IN;
	printf("state = %d\n", s);
	s = QUOTE_IN;
	printf("state = %d\n", s);

	enum week {Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun} day = Mon;
    puts("input an number between 1 and 7:");
	scanf("%d", (int *)&day);
	switch (day) {
		case 1: puts("Monday"); break;
		case 2: puts("Tuesday"); break;
		case 3: puts("Wednesday"); break;
		case 4: puts("Thursday"); break;
		case 5: puts("Friday"); break;
		case 6: puts("Saturday"); break;
		case 7: puts("Sunday"); break;
		default: puts("Error");
	}

    enum {false, true} rs = false;
    printf("rs=%d\n", rs);
    rs = true;
    printf("rs=%d\n", rs);

    enum type {a=1,b=3,c,d,f=-2,g};
    printf("%d %d %d\n", c, d, g);

	return 0;
}
