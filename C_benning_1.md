# C_beginning_1
## C语言中常见的未定义行为（C11）
### 什么叫做未定义
未定义行为(undefined behavior)(简称 UB)指编译器允许编译, 但是语言标准中没有定义的行为. 这种现象的出现并不是语言标准不完善, 而是因为这种行为在编译时无法检查其错误或者受限于具体的 cpu 指令以及操作系统优化等使其会有在编译时不可预知的运行结果.

最简单的就是数组越界, 这种错误在 c 语言编译时无法检查, 而 c 标准也没有定义越界后会访问到什么.

未定义行为在不同编译器上或者不同操作系统或者不同架构 cpu 上会产生不同的结果, 所以在任何代码中都应当避免未定义行为.
### 常见的未定义行为
#### 数组越界(array index outof bounds)
```c
void func()
{
    int array[5] = {0};
    printf("%d",array[5]);
}
```
而至于 `array[5]` 到底会访问到什么取决于操作系统和编译器. 例如 windows 平台的 msvc 编译器的 debug 模式会将所有未初始化内存都用特定值来充填, 在未初始化内存的边缘会用另一个值来充填(详见烫烫烫屯屯屯问题). 但是在 linux 平台的 gcc 中此时只会访问到一个普通的未初始化内存, 因此其值是不可预期的.
#### 修改字符串字面量
字面量(literal)是写在源代码中的表示固定值的符号(token). 平时俗称的硬编码(hard coding)大多数时候就是在说字面量(有时指常量). 举个例子
```c
const int var1 = 1;
int var2 = 1;
var2 = 2;
```
其中 `var1` 是常量, `var2` 是变量, 1 是字面量.

基本类型的字面量在机器码里也是字面量. 修改字符串字面量说的是这种情况

```c
char *string = "Hello";
string[0] = 'h';
```
上述代码会在第二行产生段错误.
#### 除以零
```c
#include <stdio.h>

int main()
{
    int a = 1, b = 0;
    int result = a / b;
    printf("%d", result);
    return 0;
}
```
#### 有返回值的函数没有return
```c
#include <stdio.h>

int func() {

}

int main() {
    printf("Hello\n");
    printf("%d\n", func());
    return 0;
}
```
#### 存在副作用的子表达式
副作用(side effect)的意思是函数会对其调用者的上下文中的某些东西产生改变, 比如函数内部改变了全局变量, 或者函数传入值的表达式本身会改变其调用者所在的上下文中的变量.
```c
#include<stdio.h>
int main()
{
    int i = 1;
    printf("%d %d ",i++,i);
    retrun 0;
}
```
(输出 "1 2")(以 linux 平台的 gcc 编译器为例, 下同)

然后开始盲目分析: "i++" 是用完了再加, 所以输出 1, 而到了第二个参数时 i 已经被加过了, 所以输出 2. 谭浩强直呼闭门大弟子.

那我们来试试给第二个 i 再加 1
```c
printf("%d %d\n", i++, i + 1);
```
此时同样输出 1 和 2
```c
printf("%d %d\n", i++, i++);
```
这样甚至输出 2 和 1
```c
printf("%d %d\n", i++, ++i);
```
这更是输出了不可理喻的 2 和 3

简单地说, 如果一个很长的表达式有多个子表达式, 并且子表达式存在副作用, 那么其运行顺序就是未定义的. 到底是哪个先运行取决于编译器. 所以不要分析了, 这是没有道理的.
```c
int array[5] = {0};
int i = 1;
array[i] = i++;
```
像这种因为先运行哪一个函数后运行那一个函数而导致结果不同的情况一般都是UD
#### 解引用空指针
当我们尝试对空指针进行解引用操作的时候编译器无法确定要访问的内存空间中储存的内容。例如：
```c
int *ptr = NULL;
printf("%d\n",*ptr);
```
#### 为初始化的局部变量
当我们使用未初始化的局部变量时，其值是未定义的，因此会导致未定义行为。例如：
```c
int x;
printf("%d\n",x);
```
#### signed整数的溢出
```c
int a = INT_MAX;  // 假设 INT_MAX 是 2147483647
a++;              // 未定义行为
```
```c
unsigned int b = UINT_MAX;  // 假设 UINT_MAX 是 4294967295
b++;                        // b 变为 0
```
- 当使用`unsigned`的情况的时候，如果你超过范围了就会从最小的开始算起。
#### 错误的类型转换以及错误的格式输出的匹配
```c
int *ptr = (int *)malloc(sizeof(int));
float *fptr = (float *)ptr; // 错误的类型转换，结果未定义
```
#### 函数参数数量并不匹配
调用函数时提供的参数数量与函数定义不匹配，如`printf("%s %d","Name");`
### 练习（From SHTU）
- 假设`int`类型是32位的。选择设计未定义行为的代码片段
```c
unsigned uval = -111;
printf("%u%%\n", uval);
```
- 这个是正确的，因为这是`unsigned`的内容所以不会超过循环而是从头开始。
```c
int x = 96;
printf("%f\n", x/100);
```
- 这里是未定义行为，这里的`%f`适用于`float`的数值，而这里属于错误匹配格式化输出符。
```c
int i = 42;
printf("%d%d\n", ++i, i);
```
- 这是经典的副作用的未定义的情况，这里的`i`和`++i`无法确定哪一个会先被调用
```c
int helper(int value) {
  printf("value is %d\n", value);
}
int main(void) {
  int x = helper(42);
  int y = helper(x);
  printf("%d\n", x + y);
}
```
- 这里涉及设计了没有返回值的情况，也是未定义行为
```c
int random(void) {
  int x;
  return x;
}
int main(void) {
  printf("%d\n", random());
}
```
- 这里涉及没有定义自变量的情况
```c
double lim(int condition, double formula){
    double d = 0.000618, dx = 1.0;
    return condition ? 0 : d*formula/dx;
}
int main(void){
    int _x = 1, x = 4399, inf = 2147483647;
    double e = lim(_x --> inf, (1 + 1/x)^x);
}
```
- 这并不是一个未定义的代码，而是一个语法错误的代码
## 了解`scanf()`
- `scanf("%d %d",&a,&b);`和`scanf("%d%d",&a,&b);`之间到底是什么关系？
   1. 在C中`' '`,`'\n'`,`'\f'`,`'\t'`,`'\v'`;这几个都叫做空白字符，而在`scanf`中的`%d`和空白字符可以跳过任意的空白字符
   2. 当且仅当遇到下一个非空字符的时候才会去对应到下一个值，或推退出语句
- `scanf()`的返回值
   - 如果`scnaf()`返回值是合法的，`scanf()`的返回值和预期输入数量匹配。
   - 如果`scnaf()`返回值是非法的，`scnaf()`的返回值是零。
**示例**
```c
int num;
float fnum;
int result = scanf("%d %f", &num, &fnum);
if (result == 2) {
    // 输入合法
} else {
    // 输入不合法
}
```
```c
int num;
int result = scanf("%d", &num);
if (result == EOF) {
    // 输入结束或错误
}
```
## 数据类型
### 不同类型的字节大小
| 数据类型              | 32位 | 64位 | 说明                                                                 |
|:---------------------:|:----:|:----:|:-------------------------------------------------------------------:|
| `char`                | 1    | 1    | 始终为 1 字节，表示单个字符。                                        |
| `short int`           | 2    | 2    | 通常为 2 字节，表示短整数。                                          |
| `int`                 | 4    | 4    | 通常为 4 字节，表示整数。                                            |
| `long int`            | 4    | 8    | 在 32 位系统中通常为 4 字节，在 64 位系统中通常为 8 字节，表示长整数。|
| `long long int`       | 8    | 8    | 始终为 8 字节，表示长长整数。                                        |
| `float`               | 4    | 4    | 始终为 4 字节，表示单精度浮点数。                                    |
| `double`              | 8    | 8    | 始终为 8 字节，表示双精度浮点数。                                    |
| `long double`         | 12 或 16 | 16 | 在 32 位系统中通常为 12 或 16 字节，在 64 位系统中通常为 16 字节，表示扩展精度浮点数。 |
| `unsigned char`       | 1    | 1    | 始终为 1 字节，表示无符号字符。                                      |
| `unsigned short`      | 2    | 2    | 通常为 2 字节，表示无符号短整数。                                    |
| `unsigned int`        | 4    | 4    | 通常为 4 字节，表示无符号整数。                                      |
| `unsigned long`       | 4    | 8    | 在 32 位系统中通常为 4 字节，在 64 位系统中通常为 8 字节，表示无符号长整数。 |
| `unsigned long long`  | 8    | 8    | 始终为 8 字节，表示无符号长长整数。                                  |
| `void*`               | 4    | 8    | 在 32 位系统中通常为 4 字节，在 64 位系统中通常为 8 字节，表示指针。  |
| `_Bool`               | 1    | 1    | 始终为 1 字节，表示布尔值（0 或 1）。                                |
| `enum`                | 通常与 `int` 相同 | 通常与 `int` 相同 | 枚举类型的大小通常与 `int` 类型相同。                                |

### 不同类型的格式转换符（占位符）

| 数据类型              | `printf` 占位符 | `scanf` 占位符 | 示例值             | 示例代码（`printf`）                    | 示例代码（`scanf`）                     |
|:---------------------:|:---------------:|:--------------:|:------------------:|:---------------------------------------:|:---------------------------------------:|
| `char`                | `%c`            | `%c`           | `'A'`              | `printf("%c", 'A');`                    | `scanf("%c", &ch);`                     |
| `int`                 | `%d` 或 `%i`    | `%d` 或 `%i`   | `42`               | `printf("%d", 42);`                     | `scanf("%d", &num);`                    |
| `unsigned int`        | `%u`            | `%u`           | `42`               | `printf("%u", 42);`                     | `scanf("%u", &unum);`                   |
| `short int`           | `%hd`           | `%hd`          | `42`               | `printf("%hd", (short)42);`             | `scanf("%hd", &snum);`                  |
| `unsigned short`      | `%hu`           | `%hu`          | `42`               | `printf("%hu", (unsigned short)42);`    | `scanf("%hu", &usnum);`                 |
| `long int`            | `%ld`           | `%ld`          | `42L`              | `printf("%ld", 42L);`                   | `scanf("%ld", &lnum);`                  |
| `unsigned long`       | `%lu`           | `%lu`          | `42L`              | `printf("%lu", 42L);`                   | `scanf("%lu", &ulnum);`                 |
| `long long int`       | `%lld`          | `%lld`         | `42LL`             | `printf("%lld", 42LL);`                 | `scanf("%lld", &llnum);`                |
| `unsigned long long`  | `%llu`          | `%llu`         | `42LL`             | `printf("%llu", 42LL);`                 | `scanf("%llu", &ullnum);`               |
| `float`               | `%f`            | `%f`           | `3.14f`            | `printf("%f", 3.14f);`                  | `scanf("%f", &fnum);`                   |
| `double`              | `%f` 或 `%lf`   | `%lf`          | `3.14`             | `printf("%f", 3.14);`                   | `scanf("%lf", &dnum);`                  |
| `long double`         | `%Lf`           | `%Lf`          | `3.14L`            | `printf("%Lf", 3.14L);`                 | `scanf("%Lf", &ldnum);`                 |
| `char[]` 或 `char*`   | `%s`            | `%s`           | `"Hello"`          | `printf("%s", "Hello");`                | `scanf("%s", str);`                     |
| `void*`               | `%p`            | N/A            | `&var`             | `printf("%p", &var);`                   | N/A                                     |
| `_Bool`               | `%d`            | `%d`           | `true` 或 `false`  | `printf("%d", true);`                   | `scanf("%d", &boolvar);`                |

### 不同进制的表示方式

| 类型                  | 十六进制         | 八进制           | 十进制             |
|:---------------------:|:----------------:|:----------------:|:------------------:|
| `char`                | `\x41`           | `\0101`          | `\65`/`65`         |
| `int`                 | `0x41`           | `0101`           | `65`               |
| `unsigned int`        | `0x41u`          | `0101u`          | `65u`              |
| `long`                | `0x41L`          | `0101L`          | `65L`              |
| `unsigned long`       | `0x41UL`         | `0101UL`         | `65UL`             |
| `long long`           | `0x41LL`         | `0101LL`         | `65LL`             |
| `unsigned long long`  | `0x41ULL`        | `0101ULL`        | `65ULL`            |
| `float`               | `0x1.9p-4f`      | `01.443242e-4f`  | `6.5f`             |
| `double`              | `0x1.9p-4`       | `01.443242e-4`   | `6.5`              |
| `unsigned float`      | `0x1.9p-4uf`     | `01.443242e-4uf` | `6.5uf`            |
| `long double`         | `0x1.9p-4L`      | `01.443242e-4L`  | `6.5L`             |
| `unsigned long double`| `0x1.9p-4uL`     | `01.443242e-4uL` | `6.5uL`            |
### C语言逻辑运算结果类型及与int的关系
- C语言逻辑运算结果类型及与int的关系:
在C语言中，逻辑运算的结果类型和值有明确的定义。即使在C99标准引入布尔类型后，逻辑运算的结果仍然可以被看作是int类型。以下是详细解释。
1. C99标准引入的布尔类型
  - C99标准引入了`_Bool`类型，表示布尔值（`true`或`false`），并通过`stdbool.h`头文件提供了`bool`类型别名，以及`true`和`false`宏定义。例如：
```c
#include <stdbool.h>
bool flag = true;
```
  - _Bool类型是一个独立的类型，其大小通常为1字节，且只有两个可能的值：`true`（非零值）`false`（零值）
2. 逻辑运算的结果类型
- 尽管引入了布尔类型，但C语言的逻辑运算（`&&`、`||`、`!`）的结果类型仍然是`int`，而不是`_Bool`。原因如下：
  - 历史兼容性：C语言的逻辑运算结果一直是`int`类型，为了保持与早期代码的兼容性，C99标准没有改变这一行为。
  - 隐式转换：在C语言中，`_Bool`类型可以隐式转换为`int`类型，反之亦然。因此，即使逻辑运算的结果是int类型，它也可以被用在布尔上下文中。
3. 逻辑运算结果的值
逻辑运算的结果值仍然是0或1：

   - 0表示false（假）。

   - 1表示true（真）。

    这意味着，即使你使用bool类型来存储逻辑运算的结果，它也会被隐式转换为int类型。例如：
```c
#include <stdio.h>
#include <stdbool.h>

int main() {
    bool result = (5 > 3); // 逻辑运算结果为 1（true）
    printf(" =result %d\n", result); // 输出 1
    printf("sizeof(result) = %zu\n", sizeof(result)); // 输出 1（_Bool类型大小）
    
    int int_result = (5 > 3); // 逻辑运算结果为 1（int类型）
    printf("int_result = %d\n", int_result); // 输出 1
    printf("sizeof(int_result) = %zu\n", sizeof(int_result)); // 输出 4（int类型大小）

    return 0;
}
```
4. 为什么可以将结果看作`int`类型
- 类型兼容性：`_Bool`类型和`int`类型之间可以隐式转换。`_Bool`类型在存储时通常会被提升为`int`类型，因此逻辑运算的结果（`int`类型）可以直接赋值给`_Bool`类型变量。
- 值兼容性：逻辑运算的结果只有0和1，这两个值在`int`类型和`_Bool`类型中都具有相同的语义。
### 计算时的隐式转换
- `char`和`short`类型在运算的时候发生隐式转换位`int`。但是只会在计算或者比较大小的时候发生转变，在计算完成之后就还是原来的类型。
```c
#include <stdio.h>

int main() {
    char a = 5;
    char b = 10;
    char c = a + b;//先变成int，再变成char

    printf("a + b = %d\n", c);
    return 0;
}
```
```c
#include <stdio.h>

int main() {
    short a = 5;
    short b = 10;
    short c = a + b;//会先转换为int然后再变成short

    printf("a + b = %d\n", c);
    return 0;
}
```
### 未定义的情况
1. 超过范围的情况：例如int超过范围
2. 未使用正确的占位符
3. `i++ + ++i`的情况
```c
#include <stdio.h>

int main()
{
    int a = 64;
    char b = 64;
    long long c = 64LL;
    float d = 64.00;
    double e = 64.00;
    unsigned int f = 64;
    short g = 64;
    printf("%f,%lld,%c,%hd,%u\n", a, a, a, a, a);
    printf("%f,%lld,%d,%hd,%u\n", b, b, b, b, b);
    printf("%f,%d,%c,%hd,%u\n", c, c, c, c, c);
    printf("%d,%lld,%c,%hd,%u\n", d, d, d, d, d);
    printf("%d,%lld,%c,%hd,%u\n", e, e, e, e, e);
}
```
```
0.000000,64,@,64,64
0.000000,64,64,64,64
0.000000,64,@,64,64
0,4634204016564240384,,0,0
0,4634204016564240384,,0,0
```
## 运算符
### 运算符的优先级和结合性
以下是C语言中不同运算符的优先级和结合性：

| 优先级 | 运算符                  | 描述                       | 结合性       |
|:------:|:-----------------------:|:--------------------------:|:------------:|
| 1      | `()`                    | 圆括号                     | 从左到右     |
| 2      | `[]`                    | 数组下标                   | 从左到右     |
| 2      | `.`                     | 结构体成员访问             | 从左到右     |
| 2      | `->`                    | 结构体指针成员访问         | 从左到右     |
| 2      | `++`                    | 后置递增                   | 从左到右     |
| 2      | `--`                    | 后置递减                   | 从左到右     |
| 3      | `++`                    | 前置递增                   | 从右到左     |
| 3      | `--`                    | 前置递减                   | 从右到左     |
| 3      | `+`                     | 一元加                     | 从右到左     |
| 3      | `-`                     | 一元减                     | 从右到左     |
| 3      | `!`                     | 逻辑非                     | 从右到左     |
| 3      | `~`                     | 按位取反                   | 从右到左     |
| 3      | `*`                     | 指针解引用                 | 从右到左     |
| 3      | `&`                     | 取地址                     | 从右到左     |
| 3      | `sizeof`                | 求大小                     | 从右到左     |
| 3      | `(type)`                | 类型转换                   | 从右到左     |
| 4      | `*`                     | 乘法                       | 从左到右     |
| 4      | `/`                     | 除法                       | 从左到右     |
| 4      | `%`                     | 取模                       | 从左到右     |
| 5      | `+`                     | 加法                       | 从左到右     |
| 5      | `-`                     | 减法                       | 从左到右     |
| 6      | `<<`                    | 左移                       | 从左到右     |
| 6      | `>>`                    | 右移                       | 从左到右     |
| 7      | `<`                     | 小于                       | 从左到右     |
| 7      | `<=`                    | 小于等于                   | 从左到右     |
| 7      | `>`                     | 大于                       | 从左到右     |
| 7      | `>=`                    | 大于等于                   | 从左到右     |
| 8      | `==`                    | 等于                       | 从左到右     |
| 8      | `!=`                    | 不等于                     | 从左到右     |
| 9      | `&`                     | 按位与                     | 从左到右     |
| 10     | `^`                     | 按位异或                   | 从左到右     |
| 11     | `\|`                     | 按位或                     | 从左到右     |
| 12     | `&&`                    | 逻辑与                     | 从左到右     |
| 13     | `\|\|`                    | 逻辑或                     | 从左到右     |
| 14     | `?:`                    | 条件运算符                 | 从右到左     |
| 15     | `=`                     | 赋值                       | 从右到左     |
| 15     | `+=` `-=` `*=` `/=` `%=`| 复合赋值运算符             | 从右到左     |
| 15     | `<<=` `>>=` `&=` `^=` `\|=`| 复合赋值运算符             | 从右到左     |
| 16     | `,`                     | 逗号运算符                 | 从左到右     |
### 算数运算与算数运算的左连接问题
```c
#include <stdio.h>

int main()
{
    int ival = 100000;
    long long llval = ival;
    int res1 = ival * ival;
    long long res2 = ival * ival;//运算结果是int再显示转换为longlong还是会溢出
    long long res3 = llval * ival;//在运算的时候ival隐式转换成long long在进行计算
    long long res4 = llval * ival * ival;//注意是从左向右的方式进行两个ival依次被转换成longlong类型
    printf("%d\n%lld\n%lld\n%lld\n", res1, res2, res3, res4);
    /*
    1410065408
    1410065408
    10000000000
    1000000000000000
    */
}
```
### 赋值运算的右连接问题
```c
#include <stdio.h>

int main()
{
    int a = 0, b = 1, c = 2;
    a = b = c;
    printf("%d %d %d", a, b, c);//2 2 2
    // 赋值运算从右往左进行
}
```
### 未定义的函数调用顺序
```c
#include <stdio.h>
int func1(void)
{
    printf("Func1 is called\n");
    return 2;
}
int func2(void)
{
    printf("Func2 is called\n");
    return 3;
}
int func3(void)
{
    printf("Func3 is called\n");
    return 4;
}
int main()
{
    int c = func1() + (func2() * func3());
    return 0;
}
```
```
Func1 is called
Func2 is called
Func3 is called
```
- Operater precedence does not determine evaluation order:`f()+g()*h()` is interpreted as `f() + (g() * h())`,but the order in which `f`,`g`,`h` are called is unspecified.
- 也就是说在对于不同函数的调用`a()+b()+c()`中，由于`operator+`的原因从左到右的结合性分析成为`(a()+b())+c()`，但是在运行时可以首先，最后或者在中间运行`c()`
- 个人的情况，其实我觉得函数的调用应该还是按照从左往右的顺序进行，但是如果是遇到逻辑判断则会出现短路现象（只要能够判断是否是真或者是假就会跳过相关的函数的调用）
## `static local`变量和`global`变量
- `static local`变量表示的是在局部声明的整体变量，他们和`global`变量一样如果没有进行初始化就会被默认为初始化为0（不同类型的0模式，同样的如果是指针都是表示的是空指针）
- 同样的`global`变量，在全局作用域外部定义的变量，这一些变量在整个程序中都可以使用
- `static local`和`global`变量的声明都是在整个程序开始运行的时候进行声明的。同时也是在整个程序结束之后在消除的。
- 例子：使用全局变量完成的只能调用一次的函数的书写
```c
bool start_game_called = false;
void start_game(Player *p1, Player *p2, int difficulty, GameWorld *world) {
if (start_game_called)
report_an_error("You cannot start the game twice!");
start_game_called = true;
// ...
}
```
## 指针
### 指针的定义
```c
    int a = 0;
    int *ptr1 = &a;
    int* ptr1 = &a;//两种写法都是正确的
    int     *   ptr4 = &a;//空格不影响
    int*ptr5 = &a;//没有空格也可以
    int *ptr2 = 0;//空指针定义
    int *ptr3 = NULL;//空指针定义
    int *ptr6 = &2;//错误的定义方式
    int *ptr7 = &(2*a);//错误的定义方式
```
- 这里的指针指向的内容必须要是一个左值（表示能够写在左侧的值）`int c = a+b`这里的`c`就是左值。
- 空指针是正确的但是空指针不能够解引用（这样也就导致了空指针是不能够赋值的）打印空指针的内容可以看到`0000000000000000`,因此为了避免空指针的使用，我们常常这么写：
```c
if (ptr != NULL && *ptr == 42) { /* ... */ }
```
这样如果指针式空的，那么后面解引用的过程就不会发生
- 野指针：野指针表示的就是没有初始值的指针，这一些指针因为不知道具体值以及地址所以几乎不能够使用，这也是未定义的行为中的一种。
