#include <stdio.h>
#include <stdlib.h>

int main()
{
    enum color {red=1, green, blue};

    enum color favorite_color;

    printf("Please input your favorite color: (1.red, 2.green, 3.blue)");
    scanf("%d", &favorite_color);

    switch (favorite_color)
    {
    case red:
        printf("Your favorite color is red");
        break;
    case green:
        printf("Your favorite color is green");
        break;
    case blue:
        printf("Your favorite color is blue");
        break;
    default:
        printf("Your have not chosen any color");
    }
    return 0;
}