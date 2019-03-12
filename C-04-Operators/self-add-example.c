#include <stdio.h>

int main()
{
    int c;
    int a = 10;
    c = a++;
    printf("assign before operating: \n");
    printf("Line 1 - c is %d\n", c);
    printf("Line 2 - a is %d\n", a);
    a = 10;
    c = a--;
    printf("Line 3 - c is %d\n", c);
    printf("Line 4 - a is %d\n", a);    


    printf("assign after operating: \n");
    a = 10;
    c = ++a;
    printf("Line 1 - c is %d\n", c);
    printf("Line 2 - a is %d\n", a);
    a = 10;
    c = --a;
    printf("Line 3 - c is %d\n", c);
    printf("Line 4 - a is %d\n", a);  

    return 0;
}