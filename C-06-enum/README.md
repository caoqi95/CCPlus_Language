## C 枚举（enum）

枚举是 C 语言中基本的数据类型，可以让数据更简洁易读。

基本的语法结构：

```C
enum 枚举名 {枚举元素1, 枚举元素2, ...}
```

### 枚举类型

下面的例子是没有使用枚举：

```C
#define MON  1
#define TUE  2
#define WED  3
#define THU  4
#define FRI  5
#define SAT  6
#define SUN  7
```

将其改成枚举的形式：

```C
enum DAY 
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
};
```
这样看起来就简洁多了。但需要注意的是，枚举的第一个元素默认值为 0，此处我们将其设置为 1，那么后续的值都会递增 1。

也可以在定义枚举的时候就指定对应元素的值，如果没指定的话，就默认为前一个元素的值加 1。

```C
enum season {spring, summer=3, autumn, winter};
```

也就是说 spring 的值为 0，autumn 的值为 4，winter 的值为 5。


### 枚举变量的定义

枚举变量的定义有以下三种：

##### 1. 先定义枚举类型，再定义枚举bmll

```C
enum DAY 
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
};
enum Day day;
```

##### 2. 定义枚举类型的同时定义枚举变量

```C
enum DAY 
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
} day;

```

##### 3. 省略枚举名称，直接定义枚举变量

```C
enum
{
      MON=1, TUE, WED, THU, FRI, SAT, SUN
} day;
```

### 实例

```C
#include <stdio.h>

enum DAY
{
    MON=1, TUE, WED, THU, FRI, SAT, SUN
};

int main()
{
    enum DAY day;
    day = WED;
    printf("%d", day);
    return 0;
}
```


在C 语言中，枚举类型是被当做 int 或者 unsigned int 类型来处理的，所以按照 C 语言规范是没有办法遍历枚举类型的。

不过在一些特殊的情况下，**枚举类型必须连续是可以实现有条件的遍历**。

以下实例使用 for 来遍历枚举的元素：

```C
#include<stdio.h>
 
enum DAY
{
      MON=1, TUE, WED, THU, FRI, SAT, SUN
} day;

int main()
{
    // 遍历枚举元素
    for (day = MON; day <= SUN; day++) {
        printf("枚举元素：%d \n", day);
    }
    return 0;
}
```

### 枚举在 switch 中的使用

```C
#include <stdio.h>
#include <stdlib.h>
int main()
{
 
    enum color { red=1, green, blue };
 
    enum  color favorite_color;
 
    /* ask user to choose color */
    printf("请输入你喜欢的颜色: (1. red, 2. green, 3. blue): ");
    scanf("%d", &favorite_color);
 
    /* 输出结果 */
    switch (favorite_color)
    {
    case red:
        printf("你喜欢的颜色是红色");
        break;
    case green:
        printf("你喜欢的颜色是绿色");
        break;
    case blue:
        printf("你喜欢的颜色是蓝色");
        break;
    default:
        printf("你没有选择你喜欢的颜色");
    }
 
    return 0;
}
```