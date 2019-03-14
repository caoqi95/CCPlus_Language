#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *p;
    p = (char *)malloc(1); // 动态分配内存
    /* 分配内存后如果指针还为 NULL 就是没有分配成功*/
    if(p == NULL){
        printf("failed!");
        exit(-1); // 退出
    }

    *p = 'c';
    printf("p pointing value: %c", *p);
    free(p); // 释放内存
    return 0;
}