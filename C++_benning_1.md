# C++_benning_1
>*From SHTU LYM*
## "Better C"
1. `bool`,`true`,`false`是内嵌的类型不再是`int`类型的了
2. 逻辑判断返回的也是`bool`类型而不是`int`类型
3. `"hello"`这个字面量在`C++`中是`const char [N+1]`而不是`char [N+1]`。
4. 字符`'a'`不再是`int`类型，而是`char`类型。
### 输入输出
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
- 和进制相关的输入输出的函数
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
- getline的用法
    - 读取C++类型的字符串`istream& getline(istream&is,string& str,char delim)`:`is`表示的是输入流对象，`str`表示用于存储读取到的行内容的字符串对象，`delim`表示读取到什么内容就停止读取本字符串
    - 读取C风格的字符串`getline(char *s,streamsize n,char delim)`：`s`表示的是存储的字符串的位置，`n`表示最多读取字符数,`delim`表示的是指定结束符
    ```c++
    getline(std::cin,str,'\n');
    ```
### 命名空间`namespace`
- 目的：
缓解复杂软件系统（尤其是多文件项目）中的标识符冲突。
- 作用域：
  - 命名空间内神功的实体有独立的命名空间作用域，避免与其他同名的实体冲突
  - 未在任何命名空间内声明的实体属于全局命名空间
```c++
namespace MathOperations{
  int add(int a,int b){
    return a+b;
  }
}

//Global namespace
int add(int a,int b){
  return a-b;
}

int main(){
  int x = 10,y = 5;
  add(x,y);
  MathOperatios::add(x,y);
  return 0;
}
```
解释：在这个实例中，我们定义了一个`MathOperations`的一个命名空间，这个空间中可以集成一些函数。
#### Namespaces:Definning a Namespace
```c++
namespace namespace_name{
  int a;
  void add(){
    //...
  }
  class ClassName{
    //..
  };
}
```
- 注意，`namespace`定义后面不用打上`;`
- Extention:A namespace can be re-opened to add further declarations
```c++
namespace namespace_name{
  //Additional declarations add to the exiting namespace
}
```
#### Scope Resolution Operator `::`
- Definition:
  - The operator `::` is uesd to explicitly specify the scope of an identifier,ensuring clarity in situations where multiple scopes define the same name.
- 还是再看刚才的代码：
```c++
namespace MathOperations{
  int add(int a,int b){
    return a+b;
  }
}

//Global namespace
int add(int a,int b){
  return a-b;
}

int main(){
  int x = 10,y = 5;
  add(x,y);
  MathOperatios::add(x,y);
  return 0;
}
```
在C++中，`::`是作用域解析运算符，用于明确指定标识符所属的命名空间。例如：

1. 单独使用`::`（前面没有命名空间名）表示全局命名空间：
```cpp
::foo(); // 调用全局命名空间中的foo函数
```
2. `std::`这是定义在标准库中的函数，通常使用`std`来描述。
- 应用：在类的外部定义成员函数或者是访问全局的公开的变量或函数
```c++
class MyClass{
  void display();
  static int a;
};
void MyClass::display(){
  std::cout<<"Hello";
}
int main(){
  MyClassName::a = 42;
}
```
3. In Function(Block) Scope.
```c++
using std::cout;
using std::endl;

int main() {
    std::string first_name;
    std::cin >> first_name;

    // No need to prefix with `std::`.
    cout << "Hello " << first_name << endl;

    return 0;
}
```
代码解释：
  1. 这里将`std`中的`cout`和`endl`函数导入进全局
  2. 所以在使用`cout`的时候不用在前面再加上前缀
4. In class Definition
```c++
class Base {
protected:
    int protected_member;
};

class Derived : public Base {
public:
    using Base::protected_member; // Exposes the protected member as public.
};
```
在 `Derived` 类中，使用`using Base::protected_member;` 将 `Base` 类的 `protected_member` 成员提升为 `Derived` 类的公共成员。
#### Nested Namespaces
namespaces can be nested,meaning you can define one namespace inside another.
```c++
namespace outer_namespace{
  namespace inner_namespace{
    //code
  }
}
```
示例：
```c++
#include <iostream>

namespace first_space {
void func() {
  std::cout << "Inside first_space" << std::endl;
}

namespace second_space {
void func() {
  std::cout << "Inside second_space" << std::endl;
}
} // namespace second_space
} // namespace first_space

int main() {
  first_space::func();
  first_space::second_space::func();
  return 0;
}
/*
Inside first_space
Inside second_space
*/
```
### `using`-Declarations
`using`声明用于将其他声明空间的特定名称引入当前作用域，在不牺牲代码的清晰度的前提下使代码更加简洁
```c++
#include <iostream>

void foo() {
  std::cout << "foo" << std::endl;
};

namespace A {
void goo() {
  std::cout << "goo" << std::endl;
}
} // namespace A

namespace X {
using ::foo;
using A::goo;
} // namespace X

using namespace X;

int main() {
  goo();
  foo();
}
```

- 在`using ::foo`中这里是将全局的(`::`)`foo`引入,`A::foo`表示将`A`这个命名空间中的函数`goo`引入这里

- `using namepace`表示的是将`X`命名空间引入到当前的作用域

#### 命名空间指令的使用以及优先级的问题
```c++
#include <iostream>  
namespace A{  
    namespace B {  
        int k = 9; // 定义 A::B::k  
    }  
    using namespace B; // 引入命名空间 B 的所有成员  
    int k = 10; // 定义 A::k  
    int l = k; // 错误：A::k 和 A::B::k 同时可见，产生歧义  
}  
int main(){  
    std::cout << A::l;  
}  
```
```c++
#include <iostream>  
namespace B {  
    int k = 9; // 定义全局命名空间下的 B::k  
}  
namespace A{  
    using namespace B; // 引入命名空间 B 的所有成员  
    int k = 10; // 定义 A::k  
    int l = k; // 正确：A::k 优先于 B::k  
}  
int main(){  
    std::cout << A::l;  
}  
```
- 当前作用域引入的名称始终优先于外层作用域的名称。
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
### 类型转换
类型转换是将一个数据类型的值转换成为另一个数据类型的值，`C++`中有四种类型转换：静态转换、动态转换、常量转换和重新解释转换。
#### Static Cast
静态转换是将一种数据类型的值强制转换成为另一种数据类型的值。静态类型转换同煮成用于比较类型相似的对象之间的转换，例如将`int`类型转换成为`float`静态转换的时候不会有任何的类型检查，所以可能会导致运行时候的错误。
```c++
int i =10;
float f = static_cast<float>(i);
```
#### const_cast
```c++
const int a = 10;
int *ptr = &a;//这里会导致错误因为使用ptr可以改变const的值(在C中只是Warning,但是在c++中就是Error)
int *ptr2 = const_cast<int*>(&a);//强制转换成为int*
*ptr2++;//UB本质上不能够改变const的数值
```
```c++
const int a = 10;
int &b = a;//Error!
int &b = const_cast<int &>(a);
b++;//UB
```
#### `reinterpret_cast`
```c++
int ival = 42;
char *pc = reinterpret_cast<char *>(&ival);//Dangerous
// 重新解释了二进制的解读方式
```
#### `dynamic_cast<target-type>(expression)`
- 作用：用于多态类对象的安全转换，在运行的时候检查类型
- 场景：基类指针，引用与派生类指针/引用之间的转换
#### 继承自C的强制转换说明
```c++
int i = 10;
cout<<(double)i<<endl;
```
#### C++ 中也存在隐式转换
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
- (Better C)但是注意在C++中不能够通过`void*`将两个不同类别的指针进行转换。同时还有`const int*`这样类型的指针不能够转换成为`void*`类型的指针,如果要将一个`const int*`类型的指针转换成为`void*`类型的指针：`const_cast<void*>(static_cast<const void*>(p))`要转换两次
- `bool`类型的转换：在条件判断语句中，非布尔类型的值会被隐式转换为布尔类型。通常，零值会被转换为 `false`，非零值会被转换为 `true`。
- 所有的浮点计算都是双精度进行的，也就是说所有的`float`都会转换成为`double`
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
### `auto`与`decltype`
```c++
auto str = "hello"//`const char*`
const int x = 10;
auto y = x//`int`Not`const int`!!
auto&py = x;//`const int&`!!
auto *ptry = &x;//`const int*`
```
- `decltype(x) y = 10;`如果`x`是`int`则会有`int y = 10;`如果`x`是`double`则会有`double y = 10;`但是如果`decltyoe(foo(x))`这里的`foo`函数并不会被调用，这里完全是计算机基于代码推测的。
- 同时`auto`也不会对于`int`类型的越界有所操作

## C++'s string vs C's string
1. 内存自动管理，`std::string`会自动处理内存分配和释放，创建`std::string`对象的时候，内部会根据储存需求自动妇女配内存；对象生命周期结束，会自动释放内存，无需手动处理。
2. 动态调整储存内存，对`std::string`执行操作插入，如`insert`方法或者是删除方法，内部的内存会自动调整。
3. 无需先是终止符`\0`，与C风格的字符串不同，`std::string`内部通过记录字符串长度而不是`\0`来识别字符出啊结尾。这使得`std::string`可以安全储存`'\0'`的字符
4. `std::stirng`无需初始化，如果你定义一个s但是没有初始化，会自动给你默认为是一个空的字符串。
### Length of string
- Member function `s.size()` and `s.empty()`
- ```c++
    std::string str{"hello world"};
    std::cout << str.size() << std::endl;
  ```
    Not `strlen`, not `sizeof`.
- `if(str.empty()){...}`
### Concatenation of strings
Use `+` and `+=` directly!
- Not need to care about the memory alloction
- No awkward functions like `strcat()`
```c++
std::string s1 = "Hello";
std::string s2 = "world";
std::string s3 = s1 + ' ' + s2; // "Hello world"
s1 += s2; // s1 becomes "Helloworld"
s2 += "C++string"; // s2 becomes "worldC++string"
```
如果是将原来的C风格的string和C++风格的字符串相比较的结果是什么？
```c++
const char *old_bad_ugly_C_style_string = "hello";
std::string good_beautiful_Cpp_string = "hello";
std::string s1 = good_beautiful_Cpp_string + "aaaaa"; // OK.
std::string s2 = "aaaaa" + good_beautiful_Cpp_string; // OK.
std::string s3 = old_bad_ugly_C_style_string + "aaaaa"; // Error
```
至少需要1个是`std::string`这样才能够运行，但是如果存在C风格的字符串，程序会`warnning`.

Question:Is this ok?
```c++
std::string hello = "Hello";
std::string s = hello+"World"+"C++";
```
**Yes！`+` is left-associated**
- 注意：
- 在c++中完成了对`operator+`的重载，可以使用`+`对`std::string`进行重载，但是至少有一个操作的对象必须是`std::string`类型的才能实现。
```c++
std::string s1{"hello"};  
std::string s2 = "world";  
std::string s3 = s1 + "world" + "C++"; // 合法，`s1` 是 `std::string`，先与 `"world"` 拼接，再与 `"C++"` 拼接  
s1 += s2; // 等价于 `s1 = s1 + s2`，使用复合赋值运算符拼接  
std::string str = "Hello " + "World"; // 错误：两个操作数都是字符串字面量（`const char[N]`），无匹配的 `operator+`  
```

### Use `+=`
- 在C++中`a+=b`是直接在字符串后面`append`新的字符串
- 但是如果`a = a+b`那么表示的是首先拷贝一遍`a`再将`b``append`到后面最后再拷贝回`a`（速度很慢）

### Operator`[]`
和python中的一样，我们可以通过`[]`来直接获得某个index下的元素的引用.但是在`c++`中区分了`const`下的访问和非`const`下的访问。
```c++
std::string s("Exampl ");  
s[s.size() - 1] = 'e'; // 使用非 `const` 版本，修改字符串最后一个字符  
std::cout << s << '\n'; // 输出 "Example"  
```
```c++
const std::string e("Example");  
for (unsigned i = e.length() - 1; i != 0; i /= 2)  
    std::cout << e[i]; // 使用 `const` 版本，只能读取字符  
std::cout << '\n'; // 输出 "emx"  
```
### Comparison Operators for `std::string`
- `operator==`：判断两个`std::string`是否相等（内容完全相同）
- `operator!=`：判断两个 `std::string` 是否不等（内容存在差异）
- `operator<`：判断一个 `std::string` 是否小于另一个（按词典顺序）。
- 同样的还有`operator<=``operator>=`...
### Deep copy in c++ string
```c++
std::string s1{"Hello"};
std::string s2{"world"};
s2 = s1; // s2 is a copy of s1
s1 += 'a'; // s2 is still "Hello"
```
这里的copy很明显是深拷贝

### string IO
- `std::cin>>s`的行为：`std::cin>>s`会忽略开头的空白字符（如空格、制表符），但是它不会读取整行的内容，只会读取连续的非空字符串
- `std::geiline(std::cin,s)`从输入流当前位置开始读取，遇到第一个`\n`的时候结束，将读取内容（不包含`\n`）存入`s`

### Traversing a string :Use range-based `for` loops
```c++
#include <iostream>
#include <string>
#include <cctype>
int main(void)
{
    std::string s = {"Hello"};
    for (std::size_t i = 0; i != s.size(); ++i)
        if (std::isupper(s[i]))
            std::cout << s[i];
    std::cout << std::endl;
    return 0;
}
```
Equivalent way:
```c++
#include <iostream>
#include <string>
#include <cctype>
int main(void)
{
    std::string s = {"Hello"};
    for(char c : s)
        if(std::isupper(c))
            std::cout<<c;
    std::cout << std::endl;
    return 0;
}
```
Use range-based `for` loops. They are modern ,clear and hence more recommended.
### Conversion between strings and arithmetic numbers
```c++
#include <iostream>
#include <string>
int main(void)
{
    int ival = 42;
    double dval = 3.14;
    std::string s = std::to_string(ival) + std::to_string(dval);
    std::cout << s << '\n';
    return 0;
}
```
### Conversion from string to int or long long
```c++
#include <iostream>
#include <string>

int main() {
    std::string num_str = "12345";
    
    // 使用 std::stoi 转换
    int int_val = std::stoi(num_str);
    std::cout << "std::stoi result: " << int_val << std::endl;

    // 使用 std::stol 转换
    long long_val = std::stol(num_str);
    std::cout << "std::stol result: " << long_val << std::endl;

    // 带进制和 pos 的示例
    std::string bin_str = "1010";
    std::size_t pos;
    int bin_val = std::stoi(bin_str, &pos, 2);
    std::cout << "Binary to int: " << bin_val 
              << ", end position: " << pos << std::endl; // 输出：10, 4 pos反应的是二进制数的长度，同时如果不需要这个数可以使用nullptr代替
    return 0;
}
```
### stringstream
```c++
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::string str;
    std::string input;
    std::cin >> input;
    std::stringstream ss(input);//将字符串视为一个流，常见用于将数值转换为字符串或者是将字符串进行处理
    std::vector<std::string> arr_str;
    // 读取以逗号分隔的字符串
    while (getline(ss, str, ','))
    {
        std::cout << "Read: " << str << std::endl; // 调试输出
        arr_str.push_back(str);
    }
    // 输出结果
    for (auto i : arr_str)
        std::cout << i << std::endl;

    return 0;
}
```
## Reference
- A reference defines an *alternative name* for an object("refers to" that object).

    - `ReferredType` is the type of the object that refers to
    - `&` is the symbol indicating that is a reference.
```c++
int ival = 42;
int &ri = ival;

std::cout<<ri<<'\n';
++ri;//Same as `++ival`
```
This option is defferent from `int x = ival`. They are two defferent variables.

**A Reference must be initialized**

### Reference must be bound to exisiting objects(左值)
```c++
int &r1 = 42;    
// Error: binding a reference to a literal
int &r2 = 2 + 3; // Error: binding a reference to a temporary object
int a = 10, b = 15;
int &r3 = a + b; // Error: binding a reference to a temporary object
```
### 引用没有“引用的引用”也不存在指针指向的引用，但是存在指针的引用
```c++
int ival = 42;
int &ri = ival;
int & &rr = ri;//Error
int &*pr = &ri;//Error
```
```c++
void modify(int *&ptrRef){//如果没有传递的是指针的引用，那么这里的修改是无效的（指针传入的也是指针的副本）
    static int value = 10;
    ptrRef = &value;
}
int main(){
   int a = 10;
   int *ptr = &a;
   int *&ptrRef = ptr;
   modify(ptrRef);
   std::cout<<*ptrRef<<std::endl; 
}
```
### 应用例子
- 使用引用来进行修改
```c++
for(char c:string)
    if(std::islower(c))
        c = std::toupper(c);//There is no effect
```
```c++
for(char &c:string)
    if(std::islower(c))
        c = std::touppper(c);
```
- 传递引用加快速度
```c++
int count_lowercase(std::string str) {
    int cnt = 0;
    for (char c : str)
        if (std::islower(c))
            ++cnt;
    return cnt;
}
```

这里很慢：因为每一次传递进入都会重新复制开辟一个新的字符串地址
```c++
int count_lowercase(std::string &str) {
    int cnt = 0;
    for (char c : str)
        if (std::islower(c))
            ++cnt;
    return cnt;
}
```
但是这样也存在一定的问题，因为引用只能引用左值
```c++
std::string s1 = something(),s2 = som_other_thing();
int result = count_lowercase(s1+s2)//Error
```
### reference-to-const
There is an exception to this rule:Referenc-to-const can be bound to anything.
```c++
const int &rci = 42;//OK
const std::string &rcs = a+b;//OK
std::string temp = a+b;
const std::string &rcs = temp;
```
那我们再看刚才的传递方式
```c++
int count_lowercase(const std::string &str) {
    int cnt = 0;
    for (char c : str)//可以在based range for loop中传递引用char &c:str这样就可以对原来的字符串修改
        if (std::islower(c))
            ++cnt;
    return cnt;
}
```
同时这里的`str`也是只读类型不能通过str来修改字符串。
### 对于数组的引用
```c++
int arr[10];
int (&arrRef)[10] = arr;
int arr_2[3][5];
int (&two_dimiension_arr)[3][5] = arr_2;
```
和指针不同数组的引用传递的大小一定是和原来数组的引用大小相同，但是指针的可以随意改动大小
### Rvalue References
```c++
int &a = 42;//Error!不能引用一个右值
int &&aa = 42;//Right! aa is an rvalue reference
const &aaa = 42;//也是正确的
const &&aaaa = 42;//正确的但是有点冗余（右值本来就不可被修改）

int i = 42;
int &&rr2 = i//Error! 右值引用不能够绑定到左值上
int &r2 = i*42;//Error! 左值引用也不能绑定在右值上
const int &cr2 = i*42;//Correct!
int &&rr3 = i*42;//Correct!
```
右值引用是左值还是右值？：右值引用本质上还是一个左值
- 右值引用在函数重载处的应用
```c++
void fun(const std::string &)
void fun(std::string &&)
```
那么：`fun(s)`优先匹配`fun(const std::string &)`而`fun(s1+s2)`优先匹配`fun(std::string &&)`
## `<vector>` in C++
### Define and Basic use
```c++
std::vector<int> v;
std::vector v;               // Error: missing template argument.
std::vector<int> vi;         // An empty vector of `int`s.
std::vector<std::string> vs; // An empty vector of strings.
std::vector<double> vd;      // An empty vector of `double`s.
std::vector<std::vector<int>> vvi; // An empty vector of vector of `int`s.// "2-d" vector
std::vector<int> v{2,3,5,7};
std::vector v{2,3,5,7};//自动推测
std::vector<std::string> vs{"Hello","World"};
std::vector<int> v3(10);//A vector of ten `int`s ,all initialized to 0;
std::vector<int> v4(10,42);//Initialized to 42
std::vector v5(10);//Error!
std::vector v6(10,42);//OK

std::vector<int> v{2,3,5,7};
std::vector<int> v2 = v;//`v2` is a copy of `v`(deep copy)
std::vector<int> v3(v);//Equivalent
std::vector<int> v4{v};//Equivalent

std::vector<int> v1,std::vector<int> v2(10,42);
v1 = v2;//copy
```
### `.size`and`.empty()`
- `v.size()`返回一共有多少个元素
- `v.empty()`returns 1 whether the vector is empty.
- `v.clear()`:Remove all the elememts
### Other functions
- `v.back()`and `v.front`retruns the **Reference** to the last element
- `v.at(Index)`returns the **Reference** element of the index.(`.at()`function has boarder chechk)
- `==`,`>=`,`<=`,`<`这样的一些比较运算符和`std::string`中是一样的，都可以在`vector`中使用，它的比较的原理也是相同的，即通过字典序来进行比较。
- `v.clear()`清除所有的元素
- `v.insert(c.begin()+1,9)`表示在第二个位置插入元素`9`
- `v.emplace(v.begin()+1,9)`就地构造一个元素，直接利用传入的参数在目标位置构造对象，避免额外的赋值或者移动操作。
- `v.erase(v.begin()+1,v.begin()+3)`表示的是移除从第二个元素到第三个（不包括第三个）的元素
- `v.pop_back`表示删除最后一个元素，但是如果这个`vector`本来就是空的那么会导致未定义行为。
- `v.resize(5,0)`表示将`vector`的大小调整为5,如果要构造新的元素，那么新元素的值默认为0.
## 函数
- 但是在c++中允许函数重名，但是需要能够通过传入值的不同（传递参数的个数/传递参数的类型）来区别，**注意返回值的不同不能够作为判断标准**
- 同时和python 一样C++中的函数允许存在默认值，但是不能够像python一样通过关键字传参，因此，如果存在默认值的情况，只能够在参数的最后使用，在前面参数使用默认值而后面参数没有默认值的情况是没有效率的。
### `Lambda`函数与表达式
C++11中提供了对匿名函数的支持，称为`Lambda`函数，`Lambda`将函数看成对象，比如可以将他们赋值给变量作为参数传递，还可以像函数一样对他求值。`[capture list] (parameter list) mutable(可选) exception(可选) -> return type(可选) { function body }`，其中`capture list`用于指定`lambda`函数中可以访问那些外部的变量，以及如何访问这一些变量（按值捕捉或者是按照引用捕捉）`mutable`表示的意思是按值捕捉的变量内容可以被修改（注意只是能够修改副本，如果没有这个`mutable`就不能够修改传递进来的副本的数值）`reutrn type`表示的是如果存在返回值那么返回值的类型是什么.
- 几个注意事项
1. 如果在括号中没有参数的传递，那么就没有办法对外部的参数进行引用
2. 如果要将所有的外部的副本全部传递进来，应该使用`[=]{}`
3. 如果要将外部的所有的变量都引用调入则应该使用`[&]`
### Function Overloding
- Resolution
    - An exact match
    - 数组或者是函数类型退化匹配：数组会退化陈伟指针(`int arr[]`会退化成为`int *`函数会退化成为函数指针，以实现匹配)
    - 顶层的`const`转换：忽略顶层的`const`差异，例如`int`,`const int`
    - 添加底层的`const`类型的匹配，允许实参添加底层的`cosnt`类型来匹配实参 
    - 整型类型或者是浮点类型的提升
    - 数值转换:`int -> float`但是这类转换的匹配优先级很低
- About `foo(NULL)`
    - In C `null` can be defined with `(void* 0)` or `0`  or `long 0`
    - In C++ `NULL` cannot be defined as `(void*) 0` 因为c++中不允许`void*`隐式转换成为其他的指针类型
    - 当存在函数重载（如 `void fun(int)`; 和 `void fun(int*)`;）时，调用 `fun(NULL)` 可能在某些平台上匹配 `fun(int)`（将 `NULL` 视为 `int 0`），也可能因歧义编译出错。
    - Better null pointer:`nullptr`
        - c++11 引入`nullptr`他的类型是`std::nullptr_t`既不是`void*`也不是整型，是更加纯粹的`nullptr`
        - 使用`nullptr`调用重载函数的时候:匹配更加明确`fun(nullptr)`必定匹配`func(int *)`避免了`NULL`可能引发的歧义问题。
## Class
### A Simple class
```c++
#include <iostream>
#include <string>

class Course {
public:
  std::strzheing course;

  Course() : course("") {}
};

class Student {
private: // 私有变量不能够在结构体外部直接使用函数中的变量或者是修改变量，但是能够在类内部进行修改和获取
  std::string name;
  std::string id;
  int entranceYear;
  Course course;

public:
  Student(const std::string &name, const std::string &id, int entranceYear)
      : name(name), id(id), entranceYear(entranceYear) {} // 初始化函数，通过初始化列表进行初始化

  Student() {} // 默认的构造函数，用于创建一个空的对象，不进行初始化操作

  void setName(const std::string &newName) { name = newName; }

  void printfInfo(/*可以传入外部的变量*/) const {
    std::cout << "I am " << name << ", id " << id << ", entrance year: " << entranceYear << std::endl;
  }

  bool graduated(int year) const { return 2025 - entranceYear >= 4; }
};

int main() {
  Student stu("Liyiming", "2024533011", 2024); // 调用有传参的初始化函数进行构造
  Student stu2;                                // 调用默认的初始化函数
  stu.printfInfo();
  stu.setName("LYM");
  stu.printfInfo();
  if (stu.graduated(2025))
    std::cout << "Yes" << std::endl;
  else
    std::cout << "No" << std::endl;
  stu2.printfInfo();
  return 0;
}
```
- `const`函数
    - 在`const`成员函数中，不能调用非`cosnt`成员函数，因为非`const`函数可能修改对象状态，违背`const`函数的不修改的承诺
    - `const`对象的调用限制：`const`对象只能够调用`const`成员函数。若调用非`const`函数，编译器会报错，确保`const`对象状态不被意外修改。
- 析构函数
```c++
class Student{
    Student(){
        std::cout<<"a";
    }
    ~Student(){
        std::cout<<"b";
    }
}
```
  - 在成员变量`student`的声明周期结束的时候，`~Student`的函数内容会被调用（常用于对于`malloc``new`出来的内存的释放）
#### 搭配学习`new`,`delete`
1. 分配单个对象
```c++
int* ptr = new int; // 分配一个 int 类型的内存，未初始化
*ptr = 42;          // 给分配的内存赋值
std::cout << *ptr << std::endl;
delete ptr;         // 释放内存
```
2. 分配并且初始化单个对象
```c++
int* ptr = new int(42); // 分配一个 int 类型的内存，并初始化为 42
std::cout << *ptr << std::endl;
delete ptr;            // 释放内存
```
3. 分配数组
```c++
int* arr = new int[5]; // 分配一个包含 5 个 int 的数组
for (int i = 0; i < 5; ++i) {
    arr[i] = i * 10;   // 初始化数组
    std::cout << arr[i] << " ";
}
std::cout << std::endl;
delete[] arr;          // 释放数组内存
```
4. 分配自定义类型对象
```c++
class Student {
public:
    Student(const std::string& name) : name(name) {
        std::cout << "Student " << name << " created." << std::endl;
    }
    ~Student() {
        std::cout << "Student " << name << " destroyed." << std::endl;
    }
private:
    std::string name;
};

Student* stu = new Student("Liyiming"); // 动态分配一个 Student 对象
delete stu;                             // 释放内存，调用析构函数
```
5. 分配数组的自定义类型对象
```c++
Student* students = new Student[2] { {"Alice"}, {"Bob"} }; // 分配并初始化数组
delete[] students;                                         // 释放数组内存
```
* 注意事项：
    1. 必须释放内存
    2. 数组释放要加上`[]`
    3. 避免野指针
### Copy constructor
在c++中，通过类进行拷贝操作的时，默认行为是调用拷贝构造函数(Copy Constructor)。拷贝构造函数的一个作用是用一个已经存在的对象来初始化另外一个对象。
- 默认拷贝构造函数：
    如果你没有显式定义的拷贝构造函数，编译器会为类生成一个默认拷贝构造函数。 默认拷贝构造函数会对类的每个成员变量执行逐个成员的浅拷贝（对于浅拷贝的几个说明，对于一般的元素`int`,`float`这几个类型来说浅拷贝是安全的，对于复杂的类别而言`std::string`应为在`std::string`内部就已经实现了深拷贝的内容，所以也是安全的，但是对于普通数组而言，这种方法是不安全的）
    ```c++
    #include <iostream>
    #include <string>
    
    class Student {
    private:
        std::string name;
        int age;
    
    public:
        Student(const std::string& name, int age) : name(name), age(age) {}
    
        void printInfo() const {
            std::cout << "Name: " << name << ", Age: " << age << std::endl;
        }
    };
    
    int main() {
        Student stu1("Alice", 20); // 创建对象 stu1
        Student stu2 = stu1;       // 调用默认拷贝构造函数，创建 stu2
    
        stu1.printInfo(); // 输出：Name: Alice, Age: 20
        stu2.printInfo(); // 输出：Name: Alice, Age: 20
    
        return 0;
    }
    ```
- 初始化语法
    - `Student a = b`,`Student a(b)`,`Student a{b}`这三个都是属于调用初始化语句的表达式，这里的`=`不是赋值的意思，而是初始化语句调用的意思。
- 自定义`copy constructor`
    ```c++
    class Student {
    public:
        Student(const Student & other);
    }
    ```
    1. 使用`const`防止求改外部其他的成员变量
    2. 使用`&`来表示传递的引用，避免无限递归
- 自定义默认：`Student(const Student &other) = default`
- 禁止copy：`Student (const Student &other) = delete`
- 如何做到不复制指针但是复制内容：
```c++
#include <iostream>

class Student {
  size_t size;
  int *storage = new int[size]{};

  Student(std::size_t size) : size(size), storage(new int[size]{}) {}//自定义初始化函数

  ~Student() {
    if (storage)
      delete[] storage;
  }//自定义析构函数

  Student(const Student &other) : size(other.size) {
    storage = new int[other.size]{};
    for (std::size_t i = 0; i != other.size; i++)
      storage[i] = other.at(i);
  }

  const int at(std::size_t i) const { return storage[i]; }

  int at(std::size_t i) { return storage[i]; }
};
```
### Type alias members in the standard library
```c++
std::string::size_type = s.size();
std::vector<int>::size_type = v.size();
std::list<int>::size_type = l.size();
```
### `static`member in class
在c++中，`static`成员变量是属于类本身的，而不是属于类的某个对象。它们在所有对象之间共享，并且只会有一份实例。由于`staic`成员变量的储存室独立于类本身的，因此需要在类的外部进行定义和初始化，来分配内存。

1. 类定义只是声明：在类内部，`static`成员变量只是声明，斌没有分配内存。类外部的定义才是真正分配内存的地方。
2. 分离编译：如果只是在类内部声明而不再类外部定义，连接器在链接阶段找不到该变量的定义，从而导致连接失败。
3. 初始化：`static`成员变量只能在类外部初始化，不能再类内部直接赋值(c++17之前)。这是因为类的定义只是声明，不能用于分配初始化静态变量。
```c++
#include <iostream>

class Student {
public:
  static int number;
};

int Student::number = 0;//要在外部再次声明

class Teacher {
public:
  static int number;
};

int Teacher::number = 0;

int main() {

  Student stu1;
  stu1.number = 3;
  Student stu2;
  stu2.number = 4;
  std::cout << Student::number;//4
  Teacher tea1;
  tea1.number = 3;
  std::cout << Teacher::number;//3
  return 0;
}
```
- 应用：
    - `std::string::npos`是c++标准库中`std::string`类的一个静态常量，表示一个特殊的值，用于指示“没找到”或“无效位置”。
    - `std::string::npos`通常被定义为：`static const size_type npos = -1;`
    - 使用：
    ```c++    
    #include <iostream>
    #include <string>
    
    int main() {
        std::string str = "Hello, world!";
        std::size_t pos = str.find("world");
    
        if (pos != std::string::npos) {
            std::cout << "Found 'world' at position: " << pos << std::endl;
        } else {
            std::cout << "'world' not found!" << std::endl;
        }
    
        return 0;
    }
    ```
    - 和`string`一样自定义`npos`
    ```c++
    #include <iostream>
    #include <string>

    class Student {
    std::string str{"example"}; // 初始化字符串

    public:
    static const std::size_t npos; // 定义 npos 为静态常量

    auto find(char a) {
        for (std::size_t i = 0; i < str.size(); ++i) { // 遍历字符串
        if (str[i] == a) {
            return i; // 返回找到字符的位置
        }
        }
        return npos; // 如果未找到，返回 npos
    }
    };

    // 初始化静态常量 npos
    const std::size_t Student::npos = -1;

    int main() {
    Student stu;
    char target = 'e';
    auto pos = stu.find(target); 

    if (pos != Student::npos) {
        std::cout << "Found '" << target << "' at position: " << pos << std::endl;
    } else {
        std::cout << "Character '" << target << "' not found!" << std::endl;
    }

    return 0;
    }
    ```
### `friend`
#### 友元函数
在c++中，友元是一种特殊的机制，允许一个类以外的函数或者其他类访问其私有变量`private`或者是受到保护的对象`protect`，友元可以是函数，也可以是类
```c++
class ClassName{
    friend ReturnType FriendFunctionName(Parameters);//声明友元函数
}
```
示例：
```c++
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
  string name;
  int age;

public:
  Student(const string &name, int age) : name(name), age(age) {}

  friend void printStudentInfo(const Student &stu); // 声明友元函数
};

// 友元函数定义
void printStudentInfo(const Student &stu) {
  cout << "Name :" << stu.name << ",Age: " << stu.age << endl;
}

int main() {
  Student stu("Alice", 20);
  printStudentInfo(stu); // 调用友元函数
  return 0;
}
```
1. 友元函数不是类的成员函数，但是可以访问类的私有和受保护的对象
2. 友元函数的声明可以放在类的`public`,`private`,`protect`中，效果相同。
3. 友元函数的定义不需要使用作用域解析符(className::).
#### 友元类
友元类是一个类，他被声明为另一个类的友元，因此可以访问该类的私有和受保护的成员
```c++
class ClassA{
    friend class ClassB;//声明class B为友元类
}
```
示例
```c++
#include <iostream>
#include <string>
using namespace std;

class Student {
private:
  string name;
  int age;

public:
  Student(const string &name, int age) : name(name), age(age) {}
  friend class Teacher;
};

class Teacher {
public:
  void printStudentInfo(const Student &stu) { cout << "Name: " << stu.name << ",Age: " << stu.age << endl; }
};

int main() {
  Student stu("Alice", 20);
  Teacher teacher;
  teacher.printStudentInfo(stu);
  return 0;
}
```
1. 友元类可以访问另一个类的所有私有和受保护成员。
2. 友元关系是单向的，`ClassA`是`ClassB`的友元，但是`ClassB`不是`ClassA`的友元
### move assignment
- move assignment vs copy assignment
    1. 移动复制运算符和拷贝赋值运算符，他们都是特殊的成员函数，他们的作用都是对对象进行赋值操作。
    2. 两者的函数名均为`operator =`,参数通常是同类型的对象
    3. 实现机制不同，拷贝赋值运算符：创建源对象的副本，然后将这个副本赋值给目标对象。这通常意味着要复制对象的所有的成员变量，要是有动态分配的资源，就需要重新分配内润并且复制数据
    4. 移动赋值运算符：把源对象的资源所有权交给目标对象，而不进行数据的复制。
- Motivation :`copy` is slow
```c++
String a = some_value(),b = some_other_value();
String s;
s = a;  //copy
s = a+b;//move
```
- Rvalue References(右值)
```c++
int &r = 42;//Error!
const int &r = 42;//OK

int &&r = 42;//OK
int i = 42;
int &&r = i;//Error
const int &&i = 42;//可行但是没必要
```
- 与此同时我们可以通过左值和右值的接受函数不同来确定不同的重载函数
```c++
void fun(const std::string &s)//接受一个左值
void fun(std::string &&s)//接受一个右值     fun(s1+s2)
```
- Move Operations
    - 包括移动构造函数和移动赋值函数
    1. 移动构造函数
    ```c++
    class Myclass {
    public:
    Myclass(Myclass &&other) noexcept {
        // 移动资源的代码
    }
    };
    ```
    2. 移动赋值函数
    ```c++
    class Myclass {
    public:
    Myclass &operator=(Myclass &&other) noexcept {
        if (this != &other) {
        // 释放当前对象的资源
        //  移动other 的资源到当前对象
        }
        return *this;
    }
    }
    ```
    - 两者不同的应用场景
        - 移动构造函数：在创建新对象的时候调用，例如再函数返回临时对象、使用`std::move`强制转换成为右值的时候进行初始化等场景中
        - 移动复制运算符：在对已经存在的对象进行赋值操作的时候调用，例如将一个临时对象赋值给一个已经存在的对象。
#### Constructor
```c++
#include <iostream>

class Dynarray {
  int *m_storage;
  std::size_t m_length;

public:
  Dynarray(const Dynarray &other) // copy constructor
      : m_storage(new int[other.m_length]), m_length(other.m_length) {
    for (std::size_t i = 0; i != m_length; ++i) {
      m_storage[i] = other.m_storage[i];
    }
  }

  Dynarray(Dynarray &&other) noexcept // move constructor
      : m_storage(other.m_storage), m_length(other.m_length) {
    if (this != &other) {
      other.m_storage = nullptr;
      other.m_length = 0;
    }
  }
};
```
#### The Move Assignment Operator
```c++
class Dynarray {
public:
  Dynarray &operator=(Dynarray &&other) noexcept {//这里返回的是一个引用，这样可以使得其连续调用，同时也确保了将自己本身传出.
    if (this != &other) {
      delete[] m_storage;
      m_stroage = other.m_strorage;
      m_length = other.m_length;
      other.m_storage = nullptr;
      other.m_length = 0;
    }
    return *this;
  }
};
```
- Lvalues are Copied; Rvalues are Moved
Suppose we have a function that concatenates two Dynarrray S:
```c++
Dynarray concat(const Dynarray &a,const Dynarray &b){
    Dynarray result(a.size()+b.size());
    for(std::size_t i = 0;i!=a.size();++i)
        result.at(i) = a.at(i);
    for(std::size_t i = 0;i!=b.size();i++)
        result.at(a.size()+i) = b.at(i);
    return result;
}
```
那么我们现在调用`=`会调用哪一个函数呢？
```c++
a = concate(b,c);//move
a = b;//copy
```
- `std::move`
```c++
int ival = 42;
int &&rref = ival;//Error
int &&rref = std::move(ival);//OK
```
#### 复制省略
```c++
std::string foo(const std::string &a,const std::string &b){
    return a+b;
}
std::string s = foo(a,b);
```
在这里不是调用的移动复制也不是赋值复制，而是复制省略，这是在初始化的时候就直接声明一个`a+b`的对象，可以大大加快速度和效率。
#### 判断
1. 
```c++
Dynarray concat(const Dynarray &a, const Dynarray &b) {
  Dynarray result(a.size() + b.size());
  for (std::size_t i = 0; i != a.size(); ++i)
    result.at(i) = a.at(i);
  for (std::size_t i = 0; i != b.size(); ++i)
    result.at(a.size() + i) = b.at(i);
  return result;
}

a = concat(b, c);
```
这个地方的`result`虽然是一个有名字的值，但是这里还是一个右值，所以会调用`move assignment`
## Smart Pointers
### 为什么要使用智能指针？
在程序中我们为了避免内存泄露，我们要注意所有声明或者是`new`得到的指针我们都要在程序结束之前将他删除`delete`所以综上所述，我们可以采用我们在`class`中定义的析构函数来完成对于指针的管理
```c++
struct WindowPtr{
  Window *ptr;//存在一个指向Window类的ptr指针
  WindowPtr(Window *p):ptr(p){}//将Window的指针赋值给WindowPtr中的ptr
  ~WindowPtr() { delete ptr; }//通过析构函数进行管理
}
```
虽然这个问题解决了，但是我们仍然不能像使用指针一样使用这个类指针

例如我们考虑指针的复制问题：
```c++
{
    WindowPtr pWindow(new Window(settings.width,settings.height,settings.mode));
    auto copy = pWindow;
}
```
这个时候`copy`和`pWindow`都指向相同的地址，这样的话会导致一个指针被`delete`两次。

- 解决方法：
1. `WindowPtr copy(new Window(*pWindow.ptr))`深拷贝

解释：`pWindow.ptr`是原来的`pWindow`指针这个时候见他解引用然后再重新声明一个`Window`类的指针将他赋值给一个新的`copy`，这样`copy`和原来的指针的内容一样，但是拥有不同的地址。
2. `WindowPtr copy(pWindow.ptr)`浅拷贝

解释：要采用这样的拷贝方式就会导致两个指针指向的是同一个地址，这样的话，要设计特殊的计数方式来让两个指针只会被`delete`一遍

3. 禁止指针的复制
### 关于智能指针
- **智能指针定义**：智能指针是一种管理资源的指针。  
- **智能指针复制的可能行为**：  
  1. **复制对象（值语义）**：复制智能指针所指向的对象。典型例子是标准库容器，如 `std::string`、`std::vector`、`std::set` 等，它们在复制时会生成新的独立对象。  
  2. **复制指针，但有特殊设计（指针语义）**：复制指针本身，但通过特殊机制（如引用计数）避免资源管理问题。典型代表是 `std::shared_ptr<T>`，定义在标准库头文件 `<memory>` 中，它允许多个指针共享同一资源，通过引用计数管理资源的生命周期。  
  3. **禁用复制（唯一所有权）**：禁止复制操作，确保资源的唯一所有权。例如 `std::unique_ptr<T>`，也定义在 `<memory>` 中，它保证同一时刻只有一个指针拥有资源，不能共享所有权。  
- **智能指针与垃圾回收**：`std::shared_ptr<T>`、`std::unique_ptr<T>` 和 `std::weak_ptr<T>` 是 C++ 对垃圾回收机制的一种实现方式，用于自动管理动态分配的资源，避免内存泄漏等问题。其中 `std::weak_ptr<T>` 在 CS100 课程中未涉及。  


- **智能指针与垃圾回收**：`std::shared_ptr<T>`、`std::unique_ptr<T>` 和 `std::weak_ptr<T>` 是 C++ 针对垃圾回收机制的解决方案，用于自动管理动态分配的资源，避免内存泄漏等问题。  

- **智能指针与原始指针操作的相似性**：  
  - `*sp`：返回智能指针 `sp` 所指向对象的引用。  
  - `sp->mem`：等价于 `(*sp).mem`，用于访问指针所指向对象的成员 `mem`。  
  - **上下文转换为 `bool`**：智能指针 `sp` 可当作条件使用，具体表现为：  
    - 能置于 `if`、`for`、`while`、`do` 等语句的条件部分。  
    - 能作为逻辑运算符 `&&`、`||`、`!` 的操作数，或条件运算符 `?:` 的第一个操作数。  
    - 仅当 `sp` 持有对象（非空）时，转换结果为 `true`。  

- **最佳实践**：在现代 C++ 编程中，推荐优先使用智能指针，而非原始指针，以更安全、便捷地管理资源。  
### `std::unique_ptr`
```c++
class WindowPtr{
  Window* ptr;
public:
  WindowPtr(Window *p = nullptr) : ptr(p) {};//存在一个空指针作为初始化参数，如果没有内容传入就默认传入的是一个空指针
  ~WindowPtr() { delete ptr };//析构函数
  WindowPtr(const WindowPtr &) = delete;//禁止任何复制行为
  WindowPtr(WindowPtr &&other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }//构造move函数
  WindowPtr &operator=(WindowPtr &&other) noexcept{
    if(&other != this)
    {
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }
}
```
- 和`std::vector`一样，`std::unique_ptr`也是一个类模板。他并不是一个类。
  - `std::unique_ptr<PointeeType>`才是一个完整的类的名称
#### How to use?
```c++
std::unique_ptr<Student> p(new Student("Bob",2020123123));
```
同样的这里的`<Student>`可以省略，因为这里的编译器可以推测
- 相比于上面的声明一个新的智能指针而言，使用`std::make_unique<T>`更好。
```c++
std::unique_ptr<Student> p1 = std::make_unique<Student>("Bob",2020123123);
auto p2 = std::make_unique<Student>("Alice",2020123123);
```
  - `std::make_unique<T>(args...)`会将参数`args`完美的转发i个类型`T`的构造函数，效果等同于`new T(args...)`.
  - `std::make_unique<T>`最终返回一个指向新床架对象的`std::unique_ptr<T>`
  - 这两种方法都可以，但是使用`std::make_unique`更加安全，因为这样避免了`new`导致的内存泄露的可能
```c++
std::unique_ptr<T> up;
```
  - 这里的`up`表示的是一个初始化的一个"空指针"，此时的`up`处于不拥有任何对象的状态。（特别强调这是一种确定的明确的行为，他并非拥有某一个不确定的值）
- 自由的使用
```c++
void foo(){
  auto pAlice = std::make_unique<Student>("Alice",2020123123);
  if(some_conditions()){
    auto pBob = std::make_unique<Student>("Bob",2020123123);
  }
}
```
`std::unique_ptr`自动会调用，所以不需要手动管理内存
#### Move_Only
同样的为了防止重复释放相同的内存地址，所以在这里不能够采用复制的防止进行内存的复制
```c++
auto p = std::make_unique<std::string>(5,'c');
std::cout<< *p<<std::endl;
auto p = q;//Error!
auto r = std::move(p);
std::cout<<*r<<std::endl;
if(!p)//True
  std::cout<<"P is \"Null\" now."<<std::endl;
```
所以在智能指针的管理中，我们只能够采用拷贝赋值的关系进行赋值而不能够通过`copy`赋值的手段进行赋值。
#### Returnning a `std::unique_ptr`
```c++
struct Window{
  // A typical "factory function"
  static std::unique_ptr<Window> create(const Settings &settings){
    auto pW = std::make_unique<Window>(/*some arguments*/);
    logWindowCreation(pW)
    //...
    return pW;
  };
}
auto state = Window::create(my_settings);
```
#### Other operations on `std::unique_ptr`
- `std::unique_ptr`与数组之间的关系
  - 默认情况下`std::unique_ptr<T>`的析构函数使用`delete`表达式销毁所有的持有对象。
  - 那如果是`std::unique_ptr<T> up(new T[n]);`呢？
    - 数组的内存是通过`new[]`来分配的，但是对于`std::unique_ptr<T>`默认西沟的时候用`delete`来释放内存。这种不匹配会导致未定义行为，因为`delete`不能够释放`new[]`的数组的内存。
  - 怎么办？——`std::unique_ptr`针对数组类型的模板特化`std::unique_ptr<T[]>`
    1. 模板特化：`std::unique_ptr<T[]>`是专门为表示指向“动态数组”的指针而设计的模板特化形式。
    2. 特性：支持数组特定的操作符`operator[]`用于访问数组元素；不支持`operator*`和`operator->`因为这些操作符更适用于单个对象，而不是数组
    3. 内存释放`delete[]`来销毁数组，与`new[]`分配的数组内存匹配，避免了普通的`std::unique_ptr<T>`管理数组是因为`delete`与`delete[]`不匹配导致的未定义行为。
    4. 示例：
    ```c++
    auto up = std::make_unique<int[]>(n);//使用`std::make_unique`创建一个包含`n`个`int`元素的动态数组由std::unique_ptr<int[]>管理（这种形式的写法不能进行逐个初始化，这样写会统一的将每一个变量声明为0）
    std::unique_ptr<int[]> up2(new int[n]{/*进行初始化*/});
### `std::shared_ptr`
我们之道刚才的`unique_ptr`其他的功能基本上都实现了，但是只能允许`move_copy`所以这里仍然存在一个问题
- Ideal :Reference Counting
set a counter that counts how many `WindowPtr` are pointing to it.
```c++
struct WindowWithCounter{
  Window theWindow;
  int refCount = 1;
}
```
When a new object is created by a `WindowPtr`,set the `redfCount` to 1.

When a `WIndowPtr` is copied, let it point to the same object , and increment the conter.
```c++
class WindowPtr {
  WindowWithCounter *ptr;  // 指向带有引用计数的Window对象

public:
  WindowPtr(const WindowPtr &other) : ptr(other.ptr) { ++ptr->refCount; }

  WindowPtr &operator=(const WindowPtr &other) {
    ++other.ptr->refCount;
    if (--ptr->refCount == 0)
      delete ptr;
    ptr = other.ptr;
    return *this;
  }

  ~WindowPtr() {
    if (--ptr->refCount == 0)
      delete ptr;
  }
  WindowPtr(WindowPtr &&other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
  WindowPtr &operator=(WindowPtr &&other) noexcept {
    if (this != &other) {
      if (--ptr->refCount == 0)
        delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }
};
```
With the counter we can know when  to destory the object.
- `std::shared_ptr`
A smart pointer that uses reference counting to manage the lifetime of an object.
```c++
std::shared_ptr<Type> sp2(new Type(args));
auto sp = std::make_shared<Type>(args);//Equivalent ,but better.
```
- `std::shared_ptr`的构造函数
  1. `std::shared_ptr<Type> sp(new Type(args));`
  2. `auto sp = std::make_shared<Type>(args);`
  3. `std::shared_ptr<Type> sp = std::make_shared<Type>(args);`
- 例子：
```c++
auto p = std::make_shared<Student>("Bob",2020123123);
auto p1 = p;
auto p2 = p;
auto pWindow = std::make_shared<Window>(80,40,my_setting.code);
```
- Operations:
  - `*`和`->`都可以像正常的指针一样使用
  ```c++
  auto sp = std::make_shared<std::string>(10,'c');
  std::cout<< *sp;
  std::cout<< sp->size();
  - counter：
  ```c++
  auto sp = std::make_shared<std::string>(10, 'c');
  {
    auto sp2 = sp;
    std::cout << sp.use_count() << std::endl; // 2
    } // `sp2` is destroyed, but the managed object is not destroyed.
    std::cout << sp.use_count() << std::endl; // 1
  ```
  - `std::shared_ptr`is relatively easy to use,since you are free to create many `std::shared_ptr`s pointing to one object.
  - However `std::shared_ptr` has time and sapce overhead.Copy of a `std::shared_ptr` requires maintenance of reference counter.
  - Does shared_ptr always correct?
    ```c++
    struct Node {
      int value;
      std::shared_ptr<Node> next;
      Node(int x, std::shared_ptr<Node> p) : value{x},next{std::move(p)} {}
    };
    void foo() {
      auto p = std::make_shared<Node>(1, nullptr);
      p->next = std::make_shared<Node>(2, p);
      p.reset();
    }
    ```
    这种交叉赋值的情况就会导致counter永远不会降为0，最终导致程序循环
## 别名
- C中的别名：`typedef long long LL;`
- C++中的别名`using LL = long long;`
- 注意这两个别名是存在范围的限定的它的作用域中的。
想在外部使用:`Classname::LL x = 42;`,注意这个要求`using LL = long long`要在类内部的`public`范围中。
