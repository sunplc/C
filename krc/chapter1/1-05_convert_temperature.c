#include <stdio.h>

#define LOWER 0		/* 温度表的下限 */
#define UPPER 300	/* 温度表的上限 */
#define STEP 20		/* 步长 */

float convert_temperature(int f);

/* 练习 1-5 打印华氏-摄氏温度对照表 */
int main()
{
	int i;
	float c;
	printf("%s\t%s\n", "fahr", "celsius");
	for (i = UPPER; i >= LOWER; i-=STEP) {
		c = convert_temperature(i);
		printf("%3d\t%-6.1f\n", i, c);
	}
	return 0;
}

// 根据华氏温度计算出摄氏温度
float convert_temperature(int f)
{
	return (f - 32) * 5 / 9.0;
}
