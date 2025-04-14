# C++_Inro
> *Editor:YiMing Li*

> *Based on the knowledge of C and Python*
## C++基本语法
### 第一个C++程序
```c++
#include <iostream>
using namespace std;//告诉编译器使用std命名空间。命名空间是c++一个相对新的概念
// main() 是程序开始执行的地方
int main()
{
   cout << "Hello World"; // 输出 Hello World
   return 0;
}
```
在c++中我们不会以行来作为每一个语句的结束表示，我们是按照`;`来作为单行程序的结束的，所以我们完全可以写成`x = y; y = y+1; add(x, y);`

### 输入输出
>C++ 标准库提供了一组丰富的输入/输出功能，我们将在后续的章节进行介绍。本章将讨论 C++ 编程中最基本和最常见的 I/O 操作。

>C++ 的 I/O 发生在流中，流是字节序列。如果字节流是从设备（如键盘、磁盘驱动器、网络连接等）流向内存，这叫做输入操作。如果字节流是从内存流向设备（如显示屏、打印机、磁盘驱动器、网络连接等），这叫做输出操作。
#### 头文件
|||
|:----:|:----:|
|`<iostream>`|该文件定义了`cin`,`cout`,`cerr`,`clog`对象，分别用于标准输入流、标准输出流、非缓冲错误流和缓冲标准错误流|
|`<iomanip>`|该文件通过所谓的参数化流操作器例如`strew`,`setprecision`来声明对执行标准化I/O有用的服务|
#### 标准输入输出流
- 标准输出流：
```c++
#include <iostream>
using namespace std;
int main()
{
    char str[] = "Liyiming";
    int a = 20, b = 10;
    cout << "Value of str is " << str << endl
         << "and the a = " << a << " b = " << b << endl;
    return 0;
}
```
```
Output: Value of str is : Hello C++
```
C++ 编译器根据要输出变量的数据类型，选择合适的流插入运算符来显示值。<< 运算符被重载来输出内置类型（整型、浮点型、double 型、字符串和指针）的数据项。

流插入运算符 << 在一个语句中可以多次使用，如上面实例中所示，endl 用于在行末添加一个换行符。

- 标准输入流
```c++
#include <iostream>
using namespace std;
int main()
{
    int height,square;
    cin>>height>>square;
}
```
- 标准错误输入流
```c++
#include <iostream>
using namespace std;
int main( )
{
   char str[] = "Unable to read....";
   cerr << "Error message : " << str << endl;//cerr对象是非缓冲的，不会经过缓冲区直接输出
}
```
- 标准日志流
```c++
#include <iostream>
using namespace std;
int main( )
{
   char str[] = "Unable to read....";
   clog << "Error message : " << str << endl;//和cerr不一样的是这个地方的clog会经过缓存，等待缓存刷新的时候才会输出
}
```
- 特殊输出方式
```c++
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    cout << setiosflags(ios::left | ios::showpoint); // 设左对齐，以一般实数方式显示，会一直影响后面的内容
    cout.precision(5);                               // 设置除小数点外有五位有效数字，没有规定ios::fixed;or;ios::sientific就会保留三位有效数字
    cout << 123.456789 << endl;
    cout.width(10);                   // 设置显示域宽10
    cout.fill('*');                   // 在显示区域空白处用*填充
    cout << resetiosflags(ios::left); // 清除状态左对齐
    cout << setiosflags(ios::right);  // 设置右对齐
    cout << 123.456789 << endl;
    cout << setiosflags(ios::left | ios::fixed); // 设左对齐，以固定小数位显示
    cout.precision(3);                           // 设置实数显示三位小数
    cout << 999.123456 << endl;
    cout << resetiosflags(ios::left | ios::fixed);    // 清除状态左对齐和定点格式
    cout << setiosflags(ios::left | ios::scientific); // 设置左对齐，以科学技术法显示
    cout.precision(3);                                // 设置保留三位小数
    cout << 123.45678 << endl;
    return 0;
}
```
#### 和进制相关的输入输出的函数
- 输入
```c++
#include <iostream>
using namespace std;
int main()
{
    int hexNumber, decNumber, octNumber;
    cin >> std::hex >> hexNumber;//以16进制输入然后存贮为10进制
    cout << hexNumber << endl;
    cin >> std::dec >> decNumber;//记得要转换成为十进制
    cout << decNumber << endl;
    cin >> std::oct >> octNumber;
    cout << octNumber << endl;
    return 0;
}
```
- 输出
```c++
#include <iostream>
using namespace std;
int main()
{
    //将十进制的数转换成为其他的进制输出
    int hexNumber = 10, decNumber = 10, octNumber = 10;
    cout << "Octal: " << std::oct << octNumber << endl;
    cout << "Decimal: " << std::dec << decNumber << endl;
    cout << "Hexadecimal: " << std::hex << hexNumber << endl;
    return 0;
}
```
```
output:
Octal: 12
Decimal: 10
Hexadecimal: a
```
#### `getchar()`与`getline()`
```c++
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string a;
    getline(cin, a);
    cout << "The string you entered is :" << a;
    return 0;
}
```
在遇到`\n`停止读取，内部的空格，制表符都能够读取。
### 数据类型
#### 常见的数据类型的类型字节大小以及范围
```c++
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << "type: \t\t" << "************size**************" << endl;
    cout << "bool: \t\t" << "size:" << sizeof(bool);
    cout << "\tmax:" << (numeric_limits<bool>::max)();
    cout << "\t\tmin:" << (numeric_limits<bool>::min)() << endl;
    cout << "char: \t\t" << "size:" << sizeof(char);
    cout << "\tmax:" << (numeric_limits<char>::max)();
    cout << "\t\tmin:" << (numeric_limits<char>::min)() << endl;
    cout << "signed char: \t" << "size:" << sizeof(signed char);
    cout << "\tmax:" << (numeric_limits<signed char>::max)();
    cout << "\t\tmin:" << (numeric_limits<signed char>::min)() << endl;
    cout << "unsigned char: \t" << "size:" << sizeof(unsigned char);
    cout << "\tmax:" << (numeric_limits<unsigned char>::max)();
    cout << "\t\tmin:" << (numeric_limits<unsigned char>::min)() << endl;
    cout << "wchar_t: \t" << "size:" << sizeof(wchar_t);//其实是由short类型别名得到的
    cout << "\tmax:" << (numeric_limits<wchar_t>::max)();
    cout << "\t\tmin:" << (numeric_limits<wchar_t>::min)() << endl;
    cout << "short: \t\t" << "size:" << sizeof(short);
    cout << "\tmax:" << (numeric_limits<short>::max)();
    cout << "\t\tmin:" << (numeric_limits<short>::min)() << endl;
    cout << "int: \t\t" << "size:" << sizeof(int);
    cout << "\tmax:" << (numeric_limits<int>::max)();
    cout << "\tmin:" << (numeric_limits<int>::min)() << endl;
    cout << "unsigned: \t" << "size:" << sizeof(unsigned);
    cout << "\tmax:" << (numeric_limits<unsigned>::max)();
    cout << "\tmin:" << (numeric_limits<unsigned>::min)() << endl;
    cout << "long: \t\t" << "size:" << sizeof(long);
    cout << "\tmax:" << (numeric_limits<long>::max)();
    cout << "\tmin:" << (numeric_limits<long>::min)() << endl;
    cout << "unsigned long: \t" << "size:" << sizeof(unsigned long);
    cout << "\tmax:" << (numeric_limits<unsigned long>::max)();
    cout << "\tmin:" << (numeric_limits<unsigned long>::min)() << endl;
    cout << "double: \t" << "size:" << sizeof(double);
    cout << "\tmax:" << (numeric_limits<double>::max)();
    cout << "\tmin:" << (numeric_limits<double>::min)() << endl;
    cout << "long double: \t" << "size:" << sizeof(long double);
    cout << "\tmax:" << (numeric_limits<long double>::max)();
    cout << "\tmin:" << (numeric_limits<long double>::min)() << endl;
    cout << "float: \t\t" << "size:" << sizeof(float);
    cout << "\tmax:" << (numeric_limits<float>::max)();
    cout << "\tmin:" << (numeric_limits<float>::min)() << endl;
    cout << "size_t: \t" << "size:" << sizeof(size_t);
    cout << "\tmax:" << (numeric_limits<size_t>::max)();
    cout << "\tmin:" << (numeric_limits<size_t>::min)() << endl;
    cout << "string: \t" << "size:(SSO)" << sizeof(string) << endl;
    // << "\t最大值：" << (numeric_limits<string>::max)() << "\t最小值：" << (numeric_limits<string>::min)() << endl;
    cout << "type: \t\t" << "************size**************" << endl;
    return 0;
}
```
```
type:           ************size**************
bool:           size:1  max:1           min:0
char:           size:1  max:            min:€
signed char:    size:1  max:            min:€
unsigned char:  size:1  max:            min:
wchar_t:        size:2  max:65535       min:0
short:          size:2  max:32767       min:-32768
int:            size:4  max:2147483647  min:-2147483648
unsigned:       size:4  max:4294967295  min:0
long:           size:4  max:2147483647  min:-2147483648
unsigned long:  size:4  max:4294967295  min:0
double:         size:8  max:1.79769e+308        min:2.22507e-308
long double:    size:16 max:1.18973e+4932       min:3.3621e-4932
float:          size:4  max:3.40282e+38 min:1.17549e-38
size_t:         size:8  max:18446744073709551615        min:0
string:         size:(SSO)32
type:           ************size**************
```
#### `typedef`声明类型
`typedef type newname;`例如`typedef int new_int`则会告诉编译器`new_int`是`int`的一个别名则会有`new_int distance;`这样的声明式合法的。

注意`typedef`存在一定的作用域
#### 类型转换
类型转换是将一个数据类型的值转换成为另一个数据类型的值，`C++`中有四种类型转换：静态转换、动态转换、常量转换和重新解释转换。
##### Static Cast
静态转换是将一种数据类型的值强制转换成为另一种数据类型的值。静态类型转换同煮成用于比较类型相似的对象之间的转换，例如将`int`类型转换成为`float`静态转换的时候不会有任何的类型检查，所以可能会导致运行时候的错误。
```c++
int i =10;
float f = static_cast<float>(i);
```
##### 继承自C的强制转换说明
```c++
int i = 10;
cout<<(double)i<<endl;
```
##### C++ 中也存在隐式转换
- 在表达式中比`int`类型还小的整数类型（`char`,`short`）会被提升为`int`类型。如果`int`类型无法表示该值，会被提升为`unsigned int`类型
- 混合类型运算：在包含不同算术类型的表达式中，编译器会将操作数转换为一种共同的类型，以便进行运算。通常，类型转换的方向是从表示范围小的类型向表示范围大的类型转换，例如从 `int` 到 `double`.
- 赋值转换：在将一个值赋给不同类型的变量时，会发生隐式转换。**赋值转换会将右侧表达式的值转换为左侧变量的类型。（注意会有可能丢失精度）**
- 函数中调用的隐式转换：在调用函数时，如果实参的类型与形参的类型不匹配，编译器会尝试进行隐式转换。
- 函数中返回值的类型转换：如果函数的返回值类型与实际返回表达式的类型不匹配，编译器会进行隐式转换。
- 空指针和整数0可以隐式转换为任何指针类型：
```c++
#include <iostream>
int main() {
    int* ptr = nullptr;  // nullptr 被隐式转换为 int* 类型
    return 0;
}
```
- `bool`类型的转换：在条件判断语句中，非布尔类型的值会被隐式转换为布尔类型。通常，零值会被转换为 `false`，非零值会被转换为 `true`。
- 所有的浮点计算都是双精度进行的，也就是说所有的`float`都会转换成为`double`
### 变量作用域
完全和C一致，存在`static`变量的定义，作用也同C，本章节的内容请查看[C_beinning](https://github.com/LYM102/CS100/blob/C_benning/C_benning_1.md)
### C++中的常量
#### 整数常量和小数常量
整数常量可以是十进制或者是八进制或者是16禁止的常量。前缀指定基数：`0x`或者是`0X`表示十六进制，`0`表示八进制，不带前缀则默认表示十进制

整数常量也可以带一个后缀，后缀是`U`和`L`的组合，`U`表示无符号的整数`L`表示长整数。后缀可以大写也可以小写。(`U`和`L`的顺序随意)

```c++
212     //correct
215u    //correct
0xFee   //correct
078     //error:there are no 8 in oct
032     //error:You Can Not repeat the U
3.14159       // 合法的 
314159E-5L    // 合法的 
510E          // 非法的：不完整的指数
210f          // 非法的：没有小数或指数
.e55          // 非法的：缺少整数或分数
```
#### 字符常量
在C++中某一些字符`\`,`?`等具有一些特殊的含义，如果想要直接输出这一些字符，就需要使用转义字符`\`所以有`\?`表示的就是`?`字符。

字符串字面量或者是常量通常是引用在栓引号中但是如果这个字符串太长，我们往往将他使用`\`来进行分行
```c++
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string greeting  = "hello, runoob";
    cout << greeting;
    cout << "\n";
    string greeting2 = "hello, \
                        runoob";
    cout << greeting2;
    retrun 0;
}
```
#### `#define`和`const`变量
内容和C相同，详情查看[C_beinning](https://github.com/LYM102/CS100/blob/C_benning/C_benning_1.md)
### 运算符
基本与C一致，有几个需要注意一下：
- 整数除法或者是取余的过程中的正负号的取法
    - 整除：两者的符号相同则为正，如果两者的符号相反则为负
    - 取余：余数的正负号和被除数相同
### 循环
内容和C相同，详情查看[C_beinning](https://github.com/LYM102/CS100/blob/C_benning/C_benning_1.md)
### 条件判断
内容和C相同，详情查看[C_beinning](https://github.com/LYM102/CS100/blob/C_benning/C_benning_1.md)
### 函数
基本内容和C相同，详情查看[C_beinning](https://github.com/LYM102/CS100/blob/C_benning/C_benning_1.md)
#### `Lambda`函数与表达式
C++11中提供了对匿名函数的支持，称为`Lambda`函数，`Lambda`将函数看成对象，比如可以将他们赋值给变量作为参数传递，还可以像函数一样对他求值。`[capture list] (parameter list) mutable(可选) exception(可选) -> return type(可选) { function body }`，其中`capture list`用于指定`lambda`函数中可以访问那些外部的变量，以及如何访问这一些变量（按值捕捉或者是按照引用捕捉）`mutable`表示的意思是按值捕捉的变量内容可以被修改（注意只是能够修改副本，如果没有这个`mutable`就不能够修改传递进来的副本的数值）`reutrn type`表示的是如果存在返回值那么返回值的类型是什么.
- 几个注意事项
1. 如果在括号中没有参数的传递，那么就没有办法对外部的参数进行引用
2. 如果要将所有的外部的副本全部传递进来，应该使用`[=]{}`
3. 如果要将外部的所有的变量都引用调入则应该使用`[&]`
#### 其他的一些常见函数
- `<cmath>`中的函数
1. `double cos(double)`
2. `double sin(double)`
3. `double tan(double)`
4. `double log(double)`
5. `double pow(double,double)`
6. `double hypot(double,double)`返回两个参数的平方综合的平方根
7. `double sqrt(double)`
8. `int bas(int)`
9. `double fabs(double)`返回浮点数的绝对值
10. `double floor(double)`
- C++版本的随机数生成
```c++
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    srand(time(NULL));
    while (1)
    {
        cout << rand() << endl;
        getchar();
    }
    return 0;
}
```
### 数组
内容和C相同，详情查看[C_beinning](https://github.com/LYM102/CS100/blob/C_benning/C_benning_1.md)
### 字符串
#### C风格的字符串
内容和C相同，详情查看[C_beinning](https://github.com/LYM102/CS100/blob/C_benning/C_benning_1.md)
#### ~~Python~~(C++)风格的字符串`string`
C++中提供了`<string>`这个类，支持C的所有的操作，另外还增加了更多很像python的功能。
```c++
#include <iostream>
#include <string>
 
using namespace std;
 
int main ()
{
   string str1 = "runoob";
   string str2 = "google";
   string str3;
   int  len ;
 
   // 复制 str1 到 str3
   str3 = str1;
   cout << "str3 : " << str3 << endl;
 
   // 连接 str1 和 str2
   str3 = str1 + str2;
   cout << "str1 + str2 : " << str3 << endl;
 
   // 连接后，str3 的总长度
   len = str3.size();
   cout << "str3.size() :  " << len << endl;
 
   return 0;
}
```
看到这段代码居然一时半会傻傻分不清这是C还是python了，没错这就是c++,是否有一种自己之前的努力没白费的爽感
- 下面我们来看一些简单的使用方式
```c++
#include <iostream>
#include <string>

int main() {
    // 默认构造函数，创建空字符串
    std::string s1; 
    // 从C风格字符串构造
    std::string s2("Hello"); 
    // 重复字符构造
    std::string s3(5, 'a'); 
    // 从另一个string对象复制构造
    std::string s4(s2); 
    return 0;
}
```
```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";
    // 返回字符串的长度
    std::cout << "Length: " << str.length() << std::endl; 
    // 判断字符串是否为空
    std::cout << "Is empty: " << (str.empty() ? "Yes" : "No") << std::endl; 
    // 调整字符串的容量
    str.reserve(20); 
    return 0;
}
```
```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello World";
    // 查找子字符串第一次出现的位置
    size_t pos = str.find("World"); 
    if (pos != std::string::npos) {
        std::cout << "Found at position: " << pos << std::endl;
    }
    // 查找字符最后一次出现的位置
    size_t lastPos = str.rfind('o'); 
    if (lastPos != std::string::npos) {
        std::cout << "Last 'o' found at position: " << lastPos << std::endl;
    }
    return 0;
}
```
```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello";
    // 在字符串末尾添加字符
    str.push_back('!'); 
    // 在字符串末尾添加另一个字符串
    str.append(" World"); 
    // 替换字符串的一部分
    str.replace(6, 5, "C++"); //从index为6的开始往后的5个元素被替换为"c++"
    // 删除字符串的一部分
    str.erase(5, 1); 
    return 0;
}
```