#include <stdio.h>

int main()
{
    int num;

    printf("Input a number: ");
    scanf("%d", &num);

    /*
    condition?block1:block2;
    如果 condition 为 true，执行 block1，否则执行 block2
    */

    (num%2==0)?printf("even"):printf("odd");

}