#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int * getRandom()
{
    static int r[10];
    int i;

    /* 设置种子 */
    srand((unsigned)time(NULL));
    for(i=0;i<10;i++)
    {
        r[i] = rand();
        printf("%d\n", r[i]);
    }

    return r;
}

int main()
{
    /* 一个指向整数的指针 */
    int *p;
    int i;

    p = getRandom();

    for(i = 0; i<10;i++)
    {
        printf("*(p + [%d]): %d\n", i, *(p+i));
    }
    return 0;
}