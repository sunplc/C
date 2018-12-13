#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int arrLen;  // 数组长度
    int *array;  // 数组指针
    int i; // 数组下标
    printf("输入数组长度：");
    scanf("%d", &arrLen);
    
    // 动态分配内存空间，如果失败就退出程序
    array = (int*)malloc( arrLen*sizeof(int) );
    if(!array){
        printf("创建数组失败！\n");
        exit(1);
    }
    // 向内存中写入数据
    for(i=0; i<arrLen; i++){
        array[i] = i+1;
    }
    
    // 循环输出数组元素
    for(i=0; i<arrLen; i++){
        printf("%d  ", array[i]);
    }
    
    printf("\n");
    free(array); 
    
    //system("pause");
    return 0;
}
