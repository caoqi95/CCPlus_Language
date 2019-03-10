#include <stdio.h>

const int MAX = 3;

int main()
{
    int var[] = {10, 100, 200};
    int i, *ptr;

    /* 指针中的数组地址 */
    ptr = var;
    for(i=0; i < MAX; i++)
    {

        printf("Address: var[%d] = %x\n", i, ptr);
        printf("value: var[%d] = %d\n", i, *ptr);

        /* 移到下一个位置 */
        ptr++;
    }
    return 0;
}