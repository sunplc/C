#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[12];
    int age;
} test_t;

int main(int argc, char *argv[])
{
    test_t a = {"悟空", 17};
    test_t b = {"白骨精", 20};

    printf("%s %d\n", a.name, a.age);
    a = b;
    printf("%s %d\n", a.name, a.age);
    
    char format[10];
    sprintf(format, "%%%ds", 4);
    printf("format=%s, len=%ld\n", format, strlen(format));

    int arr[3] = {-12,3,4};
    int *p = arr;
    int **pp = &p;

    printf("%d\n", *arr);
    printf("%d\n", **pp);

	return 0;
}

