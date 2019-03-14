## C 指针

每一个变量都有一个内存位置，每一个内存位置都定义了可使用连字号（&）运算符访问的地址，它表示了在内存中的一个地址。请看下面的实例，它将输出定义的变量地址：
```C
#include <stdio.h>
 
int main ()
{
   int  var1;
   char var2[10];
 
   printf("var1 变量的地址： %p\n", &var1  );
   printf("var2 变量的地址： %p\n", &var2  );
 
   return 0;
}
```
执行结果如下：
```C
var1 变量的地址： 0x7fff5cc109d4
var2 变量的地址： 0x7fff5cc109de
```

通过上面的实例，我们了解了什么是内存地址以及如何访问它。接下来让我们看看什么是指针。

### 什么是指针

**指针**是一个变量，其值为另一个变量的地址，即，内存位置的直接地址。就像其他变量或常量一样，您必须在使用指针存储其他变量地址之前，对其进行声明。指针变量声明的一般形式为：

```C
type *var-name;
```
在这里，`type` 是指针的基类型，它必须是一个有效的 C 数据类型，`var-name` 是指针变量的名称。用来声明指针的星号 * 与乘法中使用的星号是相同的。但是，在这个语句中，星号是用来指定一个变量是指针。以下是有效的指针声明：
```C
int    *ip;    /* 一个整型的指针 */
double *dp;    /* 一个 double 型的指针 */
float  *fp;    /* 一个浮点型的指针 */
char   *ch;     /* 一个字符型的指针 */
```
所有指针的值的实际数据类型，不管是整型、浮点型、字符型，还是其他的数据类型，都是一样的，都是一个代表内存地址的长的十六进制数。不同数据类型的指针之间唯一的不同是，指针所指向的变量或常量的数据类型不同。

### 如何使用指针
使用指针时会频繁进行以下几个操作：定义一个指针变量、把变量地址赋值给指针、访问指针变量中可用地址的值。这些是通过使用一元运算符 * 来返回位于操作数所指定地址的变量的值。下面的实例涉及到了这些操作：
```C
#include <stdio.h>
 
int main ()
{
   int  var = 20;   /* 实际变量的声明 */
   int  *ip;        /* 指针变量的声明 */
 
   ip = &var;  /* 在指针变量中存储 var 的地址 */
 
   printf("Address of var variable: %p\n", &var  );
 
   /* 在指针变量中存储的地址 */
   printf("Address stored in ip variable: %p\n", ip );
 
   /* 使用指针访问值 */
   printf("Value of *ip variable: %d\n", *ip );
 
   return 0;
}
```
结果如下：

```C
Address of var variable: 0060FF08
Address oof var variable: 0060FF08
Value of *ip variable: 20
```

### NULL 指针

在变量声明的时候，如果没有确切的地址可以赋值，为指针变量赋一个 NULL 值是一个良好的编程习惯。赋为 NULL 值的指针被称为空指针。NULL 指针是一个定义在标准库中的值为零的常量。可以看下面的例子：

```C
#include <stdio.h>
 
int main ()
{
   int  *ptr = NULL;
 
   printf("ptr 的地址是 %p\n", ptr  );
 
   return 0;
}
```

运行结果为：

```C
Address of ptr is: 00000000
```

在大多数的操作系统上，程序不允许访问地址为 0 的内存，因为该内存是操作系统保留的。然而，**内存地址 0 有特别重要的意义，它表明该指针不指向一个可访问的内存位置。但按照惯例，如果指针包含空值（零值），则假定它不指向任何东西**。

如需检查一个空指针，您可以使用 if 语句，如下所示：
```C
if(ptr)     /* 如果 p 非空，则完成 */
if(!ptr)    /* 如果 p 为空，则完成 */
```

### `malloc()` 函数

前面讲过指针都是指向地址的，有些情况下是我们先生请内存再往这块内存里面存数据。 C 语言提供一个分配内存的函数 -- `malloc()` 函数，该函数的使用方法如下：

```C
p = (char *) malloc(100);
```

需要注意的是，`malloc()` 和 `free()` 是成对出现的，分配完内存后必须记得要释放。`free()` 的使用方法如下：

```C
free(p);
```
代码示例：

```C
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *p;
    p = (char *)malloc(1); // 动态分配内存
    /* 分配内存后如果指针还为 NULL 就是没有分配成功*/
    if(p == NULL){
        printf("failed!");
        exit(-1); // 退出
    }

    *p = 'c';
    printf("p pointing value: %c", *p);
    free(p); // 释放内存
    return 0;
}
```

## C 指针的算术运算

C 指针是一个用数值表示的地址。因此，可以对指针执行算术运算。即可以对指针进行四种算术运算：++、--、+、-。
```C
ptr++;
```

### 指针递增
我们喜欢在程序中使用指针代替数组，因为变量指针可以递增，而数组不能递增，因为数组是一个常量指针。下面的程序递增变量指针，以便顺序访问数组中的每一个元素：

```C
#include <stdio.h>

const int MAX = 3;

int main ()
{
   int  var[] = {10, 100, 200};
   int  i, *ptr;

   /* 指针中的数组地址 */
   ptr = var; // 指向数组第一个元素
   for ( i = 0; i < MAX; i++)
   {

      printf("存储地址：var[%d] = %x\n", i, ptr );
      printf("存储值：var[%d] = %d\n", i, *ptr );

      /* 移动到下一个位置 */
      ptr++;
   }
   return 0;
}
```
执行结果如下：

```C
Address: var[0] = 60fefc
value: var[0] = 10
Address: var[1] = 60ff00
value: var[1] = 100
Address: var[2] = 60ff04
value: var[2] = 200
```

### 指针递减
同样地，对指针进行递减运算，即把值减去其数据类型的字节数，如下所示：

```C
#include <stdio.h>

const int MAX = 3;

int main ()
{
   int  var[] = {10, 100, 200};
   int  i, *ptr;

   /* 指针中最后一个元素的地址 */
   ptr = &var[MAX-1];
   for ( i = MAX; i > 0; i--)
   {

      printf("存储地址：var[%d] = %x\n", i-1, ptr );
      printf("存储值：var[%d] = %d\n", i-1, *ptr );

      /* 移动到下一个位置 */
      ptr--;
   }
   return 0;
}
```
执行结果如下：
```C
Address: var[2] = 60ff04
value: var[2] = 200
Address: var[1] = 60ff00
value: var[1] = 100
Address: var[0] = 60fefc
value: var[0] = 10
```

### 指针的比较

指针可以用关系运算符进行比较，如 ==、< 和 >。如果 p1 和 p2 指向两个相关的变量，比如同一个数组中的不同元素，则可对 p1 和 p2 进行大小比较。

下面的程序修改了上面的实例，只要变量指针所指向的地址小于或等于数组的最后一个元素的地址 &var[MAX - 1]，则把变量指针进行递增：

```C
#include <stdio.h>

const int MAX = 3;

int main ()
{
   int  var[] = {10, 100, 200};
   int  i, *ptr;

   /* 指针中第一个元素的地址 */
   ptr = var;
   i = 0;
   while ( ptr <= &var[MAX - 1] )
   {

      printf("Address of var[%d] = %x\n", i, ptr );
      printf("Value of var[%d] = %d\n", i, *ptr );

      /* 指向上一个位置 */
      ptr++;
      i++;
   }
   return 0;
}
```

执行结果如下：

```C
Address of var[0] = 60fefc
Value of var[0] = 10
Address of var[1] = 60ff00
Value of var[1] = 100
Address of var[2] = 60ff04
Value of var[2] = 200
```

### 指针数组

有时候，我们想要让数组存储指向 int 或 char 或其他数据类型的指针。下面是一个指向整数的指针数组的声明：

```C
int *ptr[MAX];
```

这里把 ptr 声明为一个数组，由 MAX 个整数指针组成。因此，ptr 中的每个元素，都是一个指向 int 值的指针。下面的实例用到了三个整数，它们将存储在一个指针数组中，如下所示：

```C
#include <stdio.h>
 
const int MAX = 3;
 
int main ()
{
   int  var[] = {10, 100, 200};
   int i, *ptr[MAX];
 
   for ( i = 0; i < MAX; i++)
   {
      ptr[i] = &var[i]; /* 赋值为整数的地址 */
   }
   for ( i = 0; i < MAX; i++)
   {
      printf("Value of var[%d] = %d\n", i, *ptr[i] );
   }
   return 0;
}
```

执行的结果如下：

```C
Value of var[0] = 10
Value of var[1] = 100
Value of var[2] = 200
```

也可以使用一个指向字符的指针数组直接来存储一个字符串列表，如下：

```C
#include <stdio.h>
 
const int MAX = 4;
 
int main ()
{
   const char *names[] = {
                   "cao",
                   "qi",
                   "95",
   };
   int i = 0;
 
   for ( i = 0; i < MAX; i++)
   {
      printf("Value of names[%d] = %s\n", i, names[i] );
   }
   return 0;
}
```
执行结果如下：

```C
Value of name[0] = cao
Value of name[1] = qi
Value of name[2] = 95
```

### 指向指针的指针

指向指针的指针是一种多级间接寻址的形式，或者说是一个指针链。通常，一个指针包含一个变量的地址。当我们定义一个指向指针的指针时，第一个指针包含了第二个指针的地址，第二个指针指向包含实际值的位置。

![](http://www.runoob.com/wp-content/uploads/2014/09/pointer_to_pointer.jpg)


一个指向指针的指针变量必须如下声明，即在变量名前放置两个星号：

```C
int **var;
```

当一个目标值被一个指针间接指向到另一个指针时，访问这个值需要使用两个星号运算符，如下面实例所示：

```C
#include <stdio.h>

int main()
{
    int var = 20;
    int *ptr;
    int **pptr;

    ptr = &var;
    pptr = &ptr;

    printf("Value of var = %d\n", var);
    printf("Value available at *ptr = %d\n", *ptr);
    printf("Value available at **pptr = %d\n", **pptr);

    return 0;
}
```

### 传递指针给函数

C 语言中是允许传递指针给函数，只需要简单地声明函数参数为指针类型即可。
下面的例子中，传递一个无符号的 long 型指针给函数，并在函数内改变这个值：
```C
#include <stdio.h>
#include <time.h>

void getSeconds(unsigned long *par);

int main()
{
    unsigned long sec;

    getSeconds(&sec);

    /* 输出实际值 */
    printf("Number of seconds: %ld\n", sec);

    return 0;
}

void getSeconds(unsigned long *par)
{
    /* 获取当前的秒数 */
    *par = time(NULL);

    return;
}
```
能接受指针作为参数的函数，也能接受数组作为参数，如下所示：
```C
#include <stdio.h>

double getAverage(int *arr, int size);

int main()
{
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg;

    /* 传递一个指向数组的指针作为参数 */
    avg = getAverage(balance, 5);

    /* 输出返回值 */
    printf("Average value is: %f\n", avg);

    return 0;
}

double getAverage(int *arr, int size)
{
    int i, sum = 0;
    double avg;

    for(i=0; i<size; i++)
    {
        sum += arr[i];
    }

    avg = (double)sum / size;

    return avg;
}
```
执行结果如下：

```C
Average value is: 214.40000
```

### 从函数返回指针

在上一节中，已经了解了 C 语言中如何从函数返回数组，类似地，C 允许从函数返回指针。为了做到这点，必须声明一个返回指针的函数，如下所示：
```C
int * myFunction()
{
.
.
.
}
```

另外，C 语言不支持在调用函数时返回局部变量的地址，除非定义局部变量为 static 变量。

现在，让我们来看下面的函数，它会生成 10 个随机数，并使用表示指针的数组名（即第一个数组元素的地址）来返回它们，具体如下：

```C
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int * getRandom()
{
    static int r[10];
    int i;

    /* 设置种子 */
    srand((unsigned)time(NULL));
    for(i=0;i<10;i++)
    {
        r[i] = rand();
        printf("%d\n", r[i]);
    }

    return r;
}

int main()
{
    /* 一个指向整数的指针 */
    int *p;
    int i;

    p = getRandom();

    for(i = 0; i<10;i++)
    {
        printf("*(p + [%d]): %d\n", i, *(p+i));
    }
    return 0;
}
```

执行结果如下：

```C
11368
19960
14170
19439
11060
18639
18030
28717
22855
16487
*(p + [0]): 11368
*(p + [1]): 19960
*(p + [2]): 14170
*(p + [3]): 19439
*(p + [4]): 11060
*(p + [5]): 18639
*(p + [6]): 18030
*(p + [7]): 28717
*(p + [8]): 22855
*(p + [9]): 16487
```
