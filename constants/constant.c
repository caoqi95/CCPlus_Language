/*
    - 01 - 整数常量
    整数常量可以是十进制、八进制或十六进制的常量。前缀指定基数：0x 或 0X 表示十六进制，0 表示八进制，不带前缀则默认表示十进制。

    整数常量也可以带一个后缀，后缀是 U 和 L 的组合，U 表示无符号整数（unsigned），L 表示长整数（long）。后缀可以是大写，也可以是小写，U 和 L 的顺序任意。

    - 02 - 浮点常量
    浮点常量由整数部分，小数点，小数部分和指数部分组成。您可以使用小数形式或者指数形式来表示浮点常量。
    当使用小数形式表示时，必须包含整数部分，小数部分，或者同时包含两者。
    当使用指数形式表示时，必须包含小数点，指数，或同时包含两者。
    带符号的指数是用 e 或 E 引入的。

    - 03 - 字符常量
    通常包含在单引号中。

    - 04 - 字符串常量
    字符串字面值或常量是括在双引号 "" 中的。

    - 05 - 定义常量
    有两种方式：
    1. 使用 # define 预处理器
    2. 使用 const 关键字
*/  

/*
    # define 预处理

#include <stdio.h>

#define LENGTH 10
#define WIDTH 5
#define NEWLINE '\n'

int main()
{
    int area;

    area = LENGTH * WIDTH;
    printf("value of area: %d", area);
    printf("%c", NEWLINE);

    return 0;
}
*/

/*
    const 关键字：
    const type variable = value；
*/
#include <stdio.h>

int main()
{
    const int LENGTH = 10;
    const int WIDTH = 5;
    const char NEWLINE = '\n';
    int area;

    area = LENGTH * WIDTH;
    printf("value of area : %d", area);
    printf("%c", NEWLINE);

    return 0;
}