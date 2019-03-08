## C Storage Classes

存储类定义 C 程序中变量/函数范围和生命周期。
有以下存储类：
+ auto
+ register
+ static
+ extern

### auto

`auto` 存储类是所有局部变量默认的存储类。

```c
{
    int mount;
    auto int month;
}
```

上面的实例定义了两个带有相同存储类的变量，`auto` 只能用在函数内，即 `auto` 只能修饰局部变量。

### register

`register` 存储类用于定义存储在寄存器中而不是 RAM 中的局部变量。这意味着变量的最大尺寸等于寄存器的大小（通常是一个词），且不能对它应用一元的 '&' 运算符（因为它没有内存位置）。

```C
{
    register int miles;
}
```
寄存器只用于需要快速访问的变量，比如计数器。还应注意的是，定义 'register' 并不意味着变量将被存储在寄存器中，它意味着变量可能存储在寄存器中，这取决于硬件和实现的限制。

### static

`static` 存储类指示编译器在程序的生命周期内保持局部变量的存在，而不需要在每次它进入和离开作用域时进行创建和销毁。因此，使用 static 修饰局部变量可以在函数调用之间保持局部变量的值。

static 修饰符也可以应用于全局变量。当 static 修饰全局变量时，会使变量的作用域限制在声明它的文件内。

全局声明的一个 static 变量或方法可以被任何函数或方法调用，只要这些方法出现在跟 static 变量或方法同一个文件中。

以下实例演示了 static 修饰全局变量和局部变量的应用：
```C
#include <stdio.h>

/* 函数声明 */
void func1(void);

static int count=10; /* 全局变量 - static 是默认的 */

int main()
{
    while(count--){
        func1();
    }
    return 0;
}

void func1(void)
{
/* 'thingy' 是 'func1' 的局部变量 - 只初始化一次
 * 每次调用函数 'func1' 'thingy' 值不会被重置。
 */     
    static int thingy=5;
    thingy++;
    printf("thingy is %d , count are: %d\n", thingy, count);
}
```

实例中 `count` 作为全局变量可以在函数内使用，`thingy` 使用 `static` 修饰后，不会在每次调用时重置。

### extern 

`extern` 存储类用于提供一个全局变量的引用，全局变量对所有的程序文件都是可见的。

当使用 'extern' 时，对于无法初始化的变量，会把变量名指向一个之前定义过的存储位置。

当您有多个文件且定义了一个可以在其他文件中使用的全局变量或函数时，可以在其他文件中使用 extern 来得到已定义的变量或函数的引用。可以这么理解，extern 是用来在另一个文件中声明一个全局变量或函数。

extern 修饰符通常用于当有两个或多个文件共享相同的全局变量或函数的时候，如下所示：
+ 第一个文件：main.c
```c
#include <stdio.h>

int count;
extern void write_extern();

int main()
{
    count = 5;
    write_extern();
}
```

+ 第二个文件：support.c
```c
#include <stodi.h>

extern int count;

void write_extern(void)
{
    printf("count is %d\n", count);
}
```
在这里，第二个文件中的 `extern` 关键字用于声明已经在第一个文件中 main.c 中定义的 `count`。

程序执行结果如下：
```c
count is 5
```