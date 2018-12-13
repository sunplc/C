/* 打印华氏温度-摄氏温度对照表 */
#include <stdio.h>

float fahr_to_celsius(int f)
{
    return (5.0 / 9.0) * (f - 32);
}

int main()
{
    int fahr;
    printf("fahr celsius\n");
    for (fahr = 0; fahr <= 300; fahr = fahr + 20) {
        printf("%3d %6.1f\n", fahr, fahr_to_celsius(fahr));
    }

    return 0;
}
