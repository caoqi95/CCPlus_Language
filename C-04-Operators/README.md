## C operators

C 语言中有下面这些类型的运算符：
+ 算术运算符
+ 关系运算符
+ 逻辑运算符
+ 位运算符
+ 赋值运算符
+ 杂项运算符


### 算术运算符

| 运算符            | 描述       | 
| -------    |:-------------:| :-----------------------:| :----------------------:|
| +    | 两数相加       | 
| -   | 两数相减         |
| *    | 两数相乘        | 
| /    | 两数相除       | 
| %    |  取模，整除后的余数            |
| ++   |  自增，整数值增加 1       |
| --   |  自减，整数值减少 1           |

主要说说 a++ 与 ++a 的区别，首先看看下面的示例代码：
```c
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

}
```
观察运行结果后，可以发现以下规律：

+ a++：先赋值后运算
+ ++a：先运算后赋值

### 关系运算符

| 运算符            |
| -------    |:-----------------------:| 
| ==    | 
| !=  | 
| >   |
| <    | 
| >=    | 
| <=   | 


### 逻辑运算符

| 运算符            | 描述|
| -------    |:-----------------------:| 
| &&    | 与|
| `||`  | 或|
| !  | 非|


### 位运算符

位运算符作用于位，并逐位执行操作。&、 | 和 ^ 的真值表如下所示：

| p  | q | p&q|p`|`q |p^q|
| -------    |:-------------:| :----------------------:|:----------------------:|:-----------------------:| :----------------------:|
| 0    | 0      | 0|0|0|
| 0   | 1         |0|1|1|
| 1    | 0        |1|1|0|
| 0    | 0       |0|1|1|
假设如果 A = 60，且 B = 13，现在以二进制格式表示，它们如下所示：

A = 0011 1100

B = 0000 1101

-----------------

A&B = 0000 1100

A|B = 0011 1101

A^B = 0011 0001

~A  = 1100 0011

位运算符有以下几种：

| 运算符            | 描述|说明|
| -------    |:-----------------------:| :-----------------------:| 
| &  | 与|
| `|`  | 或|
| ^  | 异或| 相同为 0，不同为 1
| ~ | 取反|
|<<| 左移|左边的二进制位丢弃，右边补0
|>>| 右移|正数左补0，负数左补1，右边丢弃


### 赋值运算符

| 运算符            | 实例|
| -------    |:-----------------------:| :-----------------------:| 
| =  | C = A + B 将把 A + B 的值赋给 C|
| += | C += A 相当于 C = C + A|
| -=  | C -= A 相当于 C = C - A| 
| *= | C *= A 相当于 C = C * A|
|/=| C /= A 相当于 C = C / A|
|%=| C %= A 相当于 C = C % A|
|<<= |	C <<= 2 等同于 C = C << 2|
|>>= |C >>= 2 等同于 C = C >> 2|
|&=|C &= 2 等同于 C = C & 2|
|^=|	C ^= 2 等同于 C = C ^ 2 |
|`|`=|C `|`= 2 等同于 C = C `|` 2|

### 杂项运算符
| 运算符            | 描述|实例|
| -------    |:-----------------------:| :-----------------------:| 
| sizeof  | 返回变量的大小|sizeof(a) 将返回 4，其中 a 是整数
| &  | 返回变量的地址|	&a; 将给出变量的实际地址
| *  | 	指向一个变量| 	*a; 将指向一个变量
| ? :| 	三元运算符，条件表达式|	如果条件为真 ? 则值为 X : 否则值为 Y