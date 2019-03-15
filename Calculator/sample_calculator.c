/*
    用 C 语言实现一个建议的计算器:
    - 两个数字之间的加，减，乘，除
*/

#include <stdio.h>

int main()
{
    double number1=0.0;
    double number2=0.0;
    char operation;
    // 获取用户输入的计算表达式
    printf("\nPlease input your number and operation:\n");
    scanf("%lf%c%lf", &number1, &operation, &number2);

    switch (operation)
    {
        case '+':
            printf("Answer: %lf\n", number1 + number2);
            break;
        case '-':
            printf("Answer: %lf\n", number1 - number2);
            break;
        case '*':
            printf("Answer: %lf\n", number1 * number2);
            break;
        case '/':
            if (number2 == 0)
            {
                printf("\n\n\aDivision by zero error!\n");
            }
            else
            {
                printf("Answer: %lf\n", number1 / number2);
            }
            break;
        case '%':
            if((long)number2==0)
            {
                printf("\n\n\aDivision by zero error!\n");
            }
            else
            {
                printf("Answer: %ld\n", (long)number1%(long)number2);
            }
            break;
        default:
            printf("\n\n\aDivision by zero error!\n");
            break;
    }

    return 0;

}