## 变量

C 语言中有三个地方可以声明变量：

+ 在函数或块内部的局部变量
+ 在所有函数外部的全局变量
+ 在形式参数的函数参数定义中

### 局部变量

在某个函数或块的内部声明的变量称为**局部变量**。这些变量只能在该函数或该代码块内被调用。局部变量在函数的外部是不可知的。

```C
#include <stdio.h>

int main()
{
    /* 局部变量声明 */
    int a, b;
    int c;

    /* 实际初始化*/
    a = 10;
    c = 20;
    c = a + b;

    printf("value of a = %d, b = %d and c = %d\n", a, b, c);

    return 0;
}
```

### 全局变量
全局变量是定义在函数外部，通常是在程序的顶部。全局变量在整个程序生命周期内都是有效的，在任意的函数内部能访问全局变量。全局变量可以被任何函数访问。也就是说，全局变量在声明后整个程序中都是可用的。下面是一个例子：
```c
#include <stdio.h>
 
/* 全局变量声明 */
int g;
 
int main ()
{
  /* 局部变量声明 */
  int a, b;
 
  /* 实际初始化 */
  a = 10;
  b = 20;
  g = a + b;
 
  printf ("value of a = %d, b = %d and g = %d\n", a, b, g);
 
  return 0;
}
```

在程序中，局部变量和全局变量的名称可以相同，但是在函数内，如果两个名字相同，会使用局部变量值，全局变量不会被使用。下面是一个实例：

```c
#include <stdio.h>
 
/* 全局变量声明 */
int g = 20;
 
int main ()
{
  /* 局部变量声明 */
  int g = 10;
 
  printf ("value of g = %d\n",  g);
 
  return 0;
}
```
当上面的代码被编译和执行时，它会产生下列结果：

```
value of g = 10
```

### 形式参数

函数的参数，形式参数，被当作该函数内的局部变量，如果与全局变量同名它们会优先使用。下面是一个实例：

```c
#include <stdio.h>
 
/* 全局变量声明 */
int a = 20;
 
int main ()
{
  /* 在主函数中的局部变量声明 */
  int a = 10;
  int b = 20;
  int c = 0;
  int sum(int, int);
 
  printf ("value of a in main() = %d\n",  a);
  c = sum( a, b);
  printf ("value of c in main() = %d\n",  c);
 
  return 0;
}
 
/* 添加两个整数的函数 */
int sum(int a, int b)
{
    printf ("value of a in sum() = %d\n",  a);
    printf ("value of b in sum() = %d\n",  b);
 
    return a + b;
}
```

执行结果如下：

```C
value of a in main() = 10
value of a in sum() = 10
value of b in sum() = 20
value of c in main() = 30
```

> 全局变量与局部变量在内存中的区别：
>+ 全局变量保存在内存的全局存储区中，占用静态的存储单元；
> + 局部变量保存在栈中，只有在所在函数被调用时才动态地为变量分配存储单元。


### 初始化局部变量和全局变量

在局部变量被定义时，系统不会对其初始化，你必须自行对其初始化。定义全局变量时，系统会自动对齐初始化。
