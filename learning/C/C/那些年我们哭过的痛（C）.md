# 那些年我们哭过的痛
## 作者——YiMingLi
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
## 类型转换(From SHTU)
在C语言中，当一个`int`类型和一个`unsigned`类型（例如`unsigned int`）的整数相加时，最终结果的类型取决于整数提升规则（integer promotion rules）和算术转换规则（ellipsis arithmetic conversion rules）。以下是详细的解释：

### 1. **算术转换规则（Usual Arithmetic Conversions）**
C语言有一套规则，称为“ usual arithmetic conversions”，用于在混合类型表达式中确定操作数的共同类型。这些规则基于以下原则：
   - 设法保持操作数的值，如果可能的话。
   - 确保结果类型可以容纳所有可能的中间结果。

### 2. **具体规则**
当`int`和`unsigned int`相加时：
   - 如果`int`类型的取值范围可以完全包含`unsigned int`类型的取值范围，那么`unsigned int`会被转换为`int`。
   - 否则，`int`会被转换为`unsigned int`。

但是，在大多数常见的系统中（例如，使用32位或64位整数），`int`的取值范围通常为`-2,147,483,648`到`2,147,483,647`，而`unsigned int`的取值范围为`0`到`4,294,967,295`。所以`int`的取值范围并不能完全包含`unsigned int`的范围，因此在相加时会发生以下情况：

   - `int`会被转换为`unsigned int`类型，因为`unsigned`类型的取值范围更广且没有负数。
   - 结果的类型是`unsigned int`。

### 3. **示例代码**
```c
#include <stdio.h>

int main() {
    int a = -1;          // 有符号整数
    unsigned int b = 1;  // 无符号整数

    unsigned int result = a + b;

    printf("a: %d (int)\n", a);
    printf("b: %u (unsigned int)\n", b);
    printf("result: %u (unsigned int)\n", result); 

    return 0;
}
```

#### 输出：
```
a: -1 (int)
b: 1 (unsigned int)
result: 4294967296 (unsigned int)
```

#### 解释：
- `a`是`int`类型，值为`-1`。
- `b`是`unsigned int`类型，值为`1`。
- 在计算`a + b`时，`a`被隐式地转换为`unsigned int`，因为`int`的范围无法完全包容`unsigned int`。
  - `a`（`-1`）转换为`unsigned int`时，结果为`4294967295`（即`UINT_MAX`，因为 `-1` 的补码是全 `1`）。
- `4294967295 (unsigned int)` + `1 (unsigned int)` = `4294967296 (unsigned int)`。

### 4. **注意事项**
   - 如果`int`可以完全容纳`unsigned int`的范围，例如在某些特殊的系统架构中，`int`可能是 `64` 位，而`unsigned int`是 `32` 位，那么`unsigned int` 可能会被提升为 `int`。
   - 如果存在负数，转换为`unsigned`会导致值的变化（例如，`-1`转换为`unsigned int`得到`4294967295`）。
   - 了解系统的整数大小是理解这种行为的关键（通常可以通过`<limits.h>`头文件中的常量来确认）。

总之，在`int`和`unsigned int`相加时，结果类型通常是`unsigned int`，因为`unsigned`类型的转换级别更高。