/*
 - 01 - 变量的类型
    - char: 通常是是一个字节（八位），这是一个整数类型。
    - int：整数
    - float：单精度浮点值
    - double：双精度浮点值
    - void：表示类型的缺失

 - 02 - C 中变量的定义
   type variable_list;

 - 03 - C 中变量的声明
    1. 一种是需要存储空间的。例如，int a 在声明时就已经建立了存储空间
    2. 另一种是不需要建立存储空间的，通过使用 extern 关键字声明变量而不是定义它，
    例如： extern int a；其中变量 a 可以在别的文件中定义。

    所以，除非有 extern 关键字，否则都是变量的定义

    extern int i; //声明，不是定义
    int i; //声明，也是定义
*/
#include <stdio.h>

// 函数内声明变量 x， y 
int x;
int y;


int addtwosum()
{
    // 函数内声明变量 x 和 y 为外部变量
    extern int x;
    extern int y;
    int result;

    // 给外部变量（全局变量）x 和 y 赋值
    x = 1;
    y = 2;
    result = x + y;

    return result;
}

int main()
{
    int result;
    // 调用函数 addtwosum
    result = addtwosum();

    printf("result is: %d", result);
    return 0;
}
