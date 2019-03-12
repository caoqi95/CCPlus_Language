#include <stdio.h>

const int MAX = 3;

int main()
{
    const char *name[] = {
                "cao",
                "qi",
                "95",
    };

    int i = 0;

    for(i; i<MAX; i++){
        printf("Value of name[%d] = %s\n", i, *name[i]);
    }
    return 0;
}