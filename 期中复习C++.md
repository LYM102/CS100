# C++ Midterm Review
## "Better C"
1. `bool`,`true`,`false`是内嵌的类型不再是`int`类型的了
2. 逻辑判断返回的也是`bool`类型而不是`int`类型
3. `"hello"`这个字面量在`C++`中是`const char [N+1]`而不是`char [N+1]`。
4. 字符`'a'`不再是`int`类型，而是`char`类型。
5. `getline()`的用法：`getline(std::cin,string& str, char delim)`。`str`表示用于存储读取到的行内容的字符串对象，`delim`表示读取到什么内容就停止读取本字符串.
## `namespace`
- 作用域：
  - 命名空间内神功的实体有独立的命名空间作用域，避免与其他同名的实体冲突
  - 未在任何命名空间内声明的实体属于全局命名空间
```c++
namespace MathOperations{
  int add(int a,int b){
    return a+b;
  }
}
//注意namespace命名空间的后面不需要;

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
调用`Global namespace`的函数可以直接使用`::add`来完成。

在`class`中的定义
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
在这里如果在父类中变量或者是函数是子类可访问的`protected`或者是`public`的那么就可以在子类中使用`using`将其引入基类版本。

同样的因为是在子类中的`public`中进行声明的，所以这里的`protected_member`就可以通过子类在外部访问。

同样的，这个`using`还能够方便父类成员函数的重载。
```c++
class Base {
public:
    void foo(int x) { cout << "Base::foo(int)" << endl; }
    void foo(double d) { cout << "Base::foo(double)" << endl; }
};

class Derived : public Base {
public:
    using Base::foo; // 引入 Base 的所有 foo 函数

    void foo(string s) { cout << "Derived::foo(string)" << endl; } // 新增一个重载
};
```

命名空间指令的优先级的问题
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

### `using`
| 使用场景 | 示例 | 说明 |
|----------|------|------|
| 引入命名空间 | `using namespace std;` | 所有内容可用 |
| 引入特定名称 | `using std::cout;` | 更安全的方式 |
| 类型别名 | `using MyVec = std::vector<int>;` | 支持模板 |
| 暴露基类成员 | `using Base::value;` | 控制访问级别 |
| 防止函数隐藏 | `using Base::foo;` | 引入所有重载 |
| 命名空间别名 | `namespace util = mylib::utils;` | 简化嵌套命名空间 |
| 模板中定义类型别名 | `using type = T;` | 常用于元编程 |
| 继承构造函数 | `using Base::Base;` | 自动继承构造函数 |
- **为类型定义别名（C++11 起）**
功能类似于 `typedef`，但支持模板和更清晰的语法。

```cpp
using MyInt = int;
using Vec2 = std::pair<int, int>;
```

与 `typedef` 对比：

```cpp
typedef int MyInt;         // 传统方式
using MyInt = int;         // C++11 推荐方式
```

- **在结构体/类中继承构造函数（C++11 起）**

允许派生类继承基类的所有构造函数：

```cpp
class Base {
public:
    Base(int x) { /* ... */ }
};

class Derived : public Base {
public:
    using Base::Base; // 继承所有构造函数
};
```

这样可以直接调用 `Derived d(10);`，它会调用 `Base(int)` 构造函数。

## 类型转换
### `const`转换
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
### `void*`与`nullptr`
和C语言不同，在c++中`void*`指针确实能够接受任何类型的转换，但是不能够隐式转换成为任何其他类型，需要显示转换

相反`nullptr`能够隐式转换成为任何类型的指针。

怎么才能将一个`const int*`转换成为`void*`，首先需要`const_cast<int*>`然后再`static_cast<void*>`

## `auto`与`decltype`
```c++
auto str = "hello"//`const char*`
const int x = 10;
auto y = x//`int`Not`const int`!!
auto&py = x;//`const int&`!!
auto *ptry = &x;//`const int*`
```
- `auto`不会保留顶层的`const`
- 只有在`auto &`,`auto *`的情况的时候才会保留`const`
- `auto str = "hello"`中`auto`是`const char*`
- `decltype(x) y = 10;`如果`x`是`int`则会有`int y = 10;`如果`x`是`double`则会有`double y = 10;`但是如果`decltyoe(foo(x))`这里的`foo`函数并不会被调用，这里完全是计算机基于代码推测的。
- 同时`auto`也不会对于`int`类型的越界有所操作

## `string`
### `string`的初始化
```c++
#include <string>
std::string s1;
std::string s2 = "Hello";//s2("Hello")\s2{"Hello"}
std::string s3 = s2;
std::string s5(5, 'a'); // "aaaaa"
const char* cstr = "Hello World";
std::string s6(cstr, 5); // "Hello"
std::string s7(cstr.begin(), cstr.begin() + 5);
```
### C++'s string vs C's string
1. 内存自动管理，`std::string`会自动处理内存分配和释放，创建`std::string`对象的时候，内部会根据储存需求自动分配内存；对象生命周期结束，会自动释放内存，无需手动处理。
2. 动态调整储存内存，对`std::string`执行操作插入，如`insert`方法或者是删除方法，内部的内存会自动调整。
3. 无需先是终止符`\0`，与C风格的字符串不同，`std::string`内部通过记录字符串长度而不是`\0`来识别字符出啊结尾。这使得`std::string`可以安全储存`'\0'`的字符
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
如果是将`std::string`和`char[N]`或者是`char`使用`+`连接的结果是什么？
```c++
#include <iostream>
#include <string>

int main() {
  std::string s1{"Hello"};
  char s2[4] = "Lym";
  std::cout << s1 + s2 << std::endl;//HelloLym
  std::cout << s1 + '3';//Hello3
}
```
但是c风格的字符串之间不能够使用`+`连接。那么就会存在`+`的左连接问题

Question:Is this ok?
```c++
std::string hello = "Hello";
std::string s = hello+"World"+"C++";
```
**Yes！`+` is left-associated**

### Use `+=`
- 在C++中`a+=b`是直接在字符串后面`append`新的字符串
- 但是如果`a = a+b`那么表示的是首先拷贝一遍`a`再将`b``append`到后面最后再拷贝回`a`（速度很慢）

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

### range-based for loop
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
### stringstream
```c++
#include <iostream>
#include <sstream>//包括字符串流的定义
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
### Lvalue Reference
```c++
int &r1 = 42;    
// Error: binding a reference to a literal
int &r2 = 2 + 3; // Error: binding a reference to a temporary object
int a = 10, b = 15;
int &r3 = a + b; // Error: binding a reference to a temporary object

int arr[10];
int (&arrRef)[10] = arr;
int arr_2[3][5];
int (&two_dimension_arr)[3][5] = arr_2;
```
**引用没有“引用的引用”也不存在指针指向的引用**
```c++
int ival = 42;
int &ri = ival;
int & &rr = ri;//Error 不存在引用的引用
int &*pr = &ri;//Error，这里ri是一个int &的引用，但是不能够使用指针指向它
```
**但是存在指针的引用**
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
- 传递引用加快速度
```c++
int count_lowercase(const std::string &str) {
    int cnt = 0;
    for (char c : str)
        if (std::islower(c))
            ++cnt;
    return cnt;
}
```
- 使用引用来进行修改
```c++
for(char &c:string)
    if(std::islower(c))
        c = std::touppper(c);
```
### Rvalue Reference
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
v1 = v2;//deep copy(拷贝赋值)
```
### Functions in vector
- `v.size()`returns the sizeof the vector.
- `v.empty()`returns 1 whether the vector is empty.
- `v.clear()`:Remove all the elememts
- `v.back()`and `v.front`retruns the **Reference** to the last element
- `v.at(Index)`returns the **Reference** element of the index.(`.at()`function has boarder chechk)
- `v[]`equivalent to the `.at()` but it doesn't have board check.
- `v.resize(size_type n,const value_type& val)`,`n`表示目标大小，表示调整之后`vecotr`中的元素的个数。`val`如果大小大于当前大小新增元素将用该初始值初始化。
- `push_back(const T& value)`在vecvtor的末尾在添加一个元素`calue`
- `push_back(T&& value)`用右值的形式在`vector`的末尾添加一个元素
- `insert(iterator position,const T& value)`在指定的`posirion`处添加一个元素`value`返回指向新元素的迭代器。
- `insert(iterator position, InputIt first, InputIt last)`:在指定位置`position`处插入来自范围`[first,last)`,返回指向第一个新插入元素的迭代器。 
- `pop_back()`删除`vector`末尾的元素，没有返回值
- `iterator erase(iterator position)`删除指定位置的元素，返回一个迭代器，指向删除元素之后的那个元素
- `iterator erase(iterator first, iterator last)`删除`[first,last)`范围内的元素，返回一个迭代器，指向最后一个被删除元素之后的一个元素。
### `vector`扩容的策略
- `vector`会申请一块更大的连续内存空间，常见的增长策略是当前容器的容量的两倍。
    - 元素的拷贝或者是移动：
    1. 如果类型支持移动语义（c++11以上），优先使用移动构造函数
    2. 否则使用拷贝构造函数进行复制
- 然后释放先前的内存地址
## Function
### 函数的默认值
```c++
int fun(int a = 3, int b = 5);
int x = 1,y = 2;
fun();//fun(a = 3,b = 5);
fun(x);//fun(a = 1,b = 5);
fun(x,y);//fun(a = 1,b = 2);
```
### `Lambda`函数与表达式
C++11中提供了对匿名函数的支持，称为`Lambda`函数，`Lambda`将函数看成对象，比如可以将他们赋值给变量作为参数传递，还可以像函数一样对他求值。`[capture list] (parameter list) mutable(可选) exception(可选) -> return type(可选) { function body }`，其中`capture list`用于指定`lambda`函数中可以访问那些外部的变量，以及如何访问这一些变量（按值捕捉或者是按照引用捕捉）`mutable`表示的意思是按值捕捉的变量内容可以被修改（注意只是能够修改副本，如果没有这个`mutable`就不能够修改传递进来的副本的数值）`reutrn type`表示的是如果存在返回值那么返回值的类型是什么.
- 几个注意事项
1. 如果在括号中没有参数的传递，那么就没有办法对外部的参数进行引用
2. 如果要将所有的外部的副本全部传递进来，应该使用`[=]{}`
3. 如果要将外部的所有的变量都引用调入则应该使用`[&]`
4. 如果只需要外部的某个参数，只需要将某个参数传入即可
5. 和正常函数相同，传入和传出的参数有拷贝和引用的不同
- 使用返回对象延长函数的生命周期
```c++
int k = 42;
auto f = [k](int x)->bool {return x<k ;};
bool b1 = f(10);//调用刚才的函数
fool b2 = f(100);
```
### Function Overloading
#### 构成函数重载的条件

- 要构成合法的函数重载，必须满足以下至少一个区别：

| 区别点 | 说明 |
|--------|------|
| **1. 参数个数不同** | 函数的形参个数不同即可构成重载。 |
| **2. 参数类型不同** | 函数的形参类型不同可以构成重载。 |
| **3. 参数顺序不同** | 形参类型的顺序不同也可以构成重载。 |

> **注意：仅返回值类型不同不能构成重载！**

- 示例：合法的重载

```cpp
void foo(int a);            // 版本1
void foo(double a);         // 版本2：参数类型不同
void foo(int a, int b);     // 版本3：参数个数不同
void foo(double a, int b);  // 版本4：参数顺序不同
```

以上四个 `foo` 函数是合法的重载版本。

- 不构成重载的情况

| 情况 | 是否构成重载 | 说明 |
|------|----------------|------|
| **仅返回值类型不同** | ❌ 不构成重载 | 编译器无法通过返回值判断应调用哪个函数。 |
| **顶层 const 不同** | ❌ 不构成重载 | 如 `void foo(int)` 和 `void foo(const int)` 被视为同一函数。 |
| **只有默认参数不同** | ❌ 不构成重载 | 默认参数不会改变函数签名。 |
- 示例：不合法的重载
```cpp
int bar();          // 合法
double bar();       // 错误：仅返回值不同，不构成重载

void baz(int x);    // 合法
void baz(const int x); // 错误：顶层 const 不影响函数签名
```
#### 函数匹配原则（Overload Resolution）

当有多个重载函数时，C++ 编译器会进行**重载解析（Overload Resolution）**，按照以下优先级从高到低选择最合适的函数：

- 1️⃣ 精确匹配（Exact Match）
- 实参与形参类型完全一致。
- 或者可以通过**隐式转换**（如数组退化为指针、函数退化为函数指针等）匹配。

- 2️⃣ 提升转换（Promotion）
- 如 `char → int`、`float → double`、`bool → int` 等基本类型的提升。

- 3️⃣ 标准类型转换（Standard Conversion）
- 如 `int → long`、`int → float`、`void* → int*` 等。

- 4️⃣ 用户自定义转换（User-defined Conversion）
- 如类类型之间的隐式转换（构造函数或类型转换运算符）。

## Class
### 三五原则
```c++
#include <iostream>
#include <algorithm> // std::copy

class Dynarray {
private:
    int* m_storage;
    std::size_t m_length;

public:
    // 1. 默认构造函数
    explicit Dynarray(std::size_t size = 0)
        : m_storage(size ? new int[size]{} : nullptr), m_length(size) {}

    // 2. 拷贝构造函数
    Dynarray(const Dynarray& other)
        : m_storage(new int[other.m_length]), m_length(other.m_length) {
        std::copy(other.m_storage, other.m_storage + m_length, m_storage);
    }

    // 3. 拷贝赋值运算符
    Dynarray& operator=(const Dynarray& other) {
        if (this != &other) {
            // 1. 释放当前资源
            delete[] m_storage;

            // 2. 分配新资源并拷贝
            m_length = other.m_length;
            m_storage = new int[m_length];
            std::copy(other.m_storage, other.m_storage + m_length, m_storage);
        }
        return *this;
    }

    // 4. 移动构造函数
    Dynarray(Dynarray&& other) noexcept
        : m_storage(other.m_storage), m_length(other.m_length) {
        // 将 other 置为空状态
        other.m_storage = nullptr;
        other.m_length = 0;
    }

    // 5. 移动赋值运算符
    Dynarray& operator=(Dynarray&& other) noexcept {
        if (this != &other) {
            // 1. 释放当前资源
            delete[] m_storage;

            // 2. 资源转移
            m_storage = other.m_storage;
            m_length = other.m_length;

            // 3. 将 other 置为空状态
            other.m_storage = nullptr;
            other.m_length = 0;
        }
        return *this;
    }

    // 析构函数
    ~Dynarray() {
        delete[] m_storage;
    }

    // 辅助方法：打印数组内容
    void print() const {
        for (std::size_t i = 0; i < m_length; ++i) {
            std::cout << m_storage[i] << " ";
        }
        std::cout << std::endl;
    }
};
```
### `static` member and function in class
在c++中，`static`成员变量是属于类本身的，而不是属于类的某个对象。它们在所有对象之间共享，并且只会有一份实例。由于`staic`成员变量的储存室独立于类本身的，因此需要在类的外部进行定义和初始化，来分配内存。

1. 类定义只是声明：在类内部，`static`成员变量只是声明，并没有分配内存。类外部的定义才是真正分配内存的地方。
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
在c++中的`static`函数在类的外部也受到`public`,`protected`,`private`的限制，只有在允许的情况下才能够在外部被调用

但是也可以使用**类名+作用域解析运算符**来调用
```c++
Student::getCount();//无需创建对象
```

注意事项：
1. 可以调用静态成员变量
2. 不能调用非静态成员变量
3. 可以被重载
4. 但是不能是虚函数，同时也不能够被派生类重写
5. 静态函数不能够使用`const`限定函数体本体（不存在`this`指针）
6. 可以被继承
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
3. 友元函数和友元类不能够被继承同时也不能被重写

## Smart Pointers
```c++
struct WindowPtr{
  Window *ptr;//存在一个指向Window类的ptr指针
  WindowPtr(Window *p):ptr(p){}//将Window的指针赋值给WindowPtr中的ptr
  ~WindowPtr() { delete ptr; }//通过析构函数进行管理
}
```
### `std::unique_ptr`
| 特性 | 描述 |
|------|------|
| **头文件** | `<memory>` |
| **所有权** | 独占：同一时刻只能有一个 `unique_ptr` 指向该对象 |
| **拷贝行为** | 不可拷贝（`delete` 了拷贝构造函数和赋值运算符） |
| **移动语义** | 支持移动构造和移动赋值，转移资源所有权 |
| **自动释放** | 析构时自动调用 `delete` 或自定义删除器 |
- 声明与初始化方式
1. 基本使用
```cpp
#include <memory>

std::unique_ptr<int> ptr1(new int(42)); // 初始化一个 unique_ptr
```
2. 使用 `make_unique`（推荐）
```cpp
auto ptr2 = std::make_unique<int>(42); // 推荐写法，避免裸 new
```

> ⚠️ 注意：`make_unique` 在 C++14 中引入。C++11 只支持 `make_shared`。
- 移动语义（Move Semantics）

由于 `unique_ptr` **不能复制**，但可以**移动**：

```cpp
auto ptr1 = std::make_unique<int>(10);
auto ptr2 = std::move(ptr1); // OK: 所有权转移到 ptr2

// 此时 ptr1 == nullptr，ptr2 拥有资源
```
- 移动后状态：
- `ptr1` 被置为空；
- `ptr2` 成为唯一拥有资源的对象。

- 作为类成员或容器元素

1. 类中使用 `unique_ptr`
```cpp
class MyClass {
    std::unique_ptr<int> data;

public:
    MyClass(int value) : data(std::make_unique<int>(value)) {}
};
```
2. 存储在容器中（如 `vector`）
```cpp
std::vector<std::unique_ptr<int>> vec;
vec.push_back(std::make_unique<int>(1));
vec.emplace_back(new int(2)); // 不推荐，避免裸 new
```
✅ `unique_ptr` 支持移动操作，因此可以在容器中安全使用。
- 常用操作方法

| 方法 | 说明 |
|------|------|
| `operator*` / `operator->` | 解引用访问对象 |
| `get()` | 获取原始指针（不建议长期保存） |
| `release()` | 释放资源所有权，返回原始指针 |
| `reset()` | 替换当前资源或释放资源 |
| `swap()` | 交换两个 `unique_ptr` 的资源 |

```cpp
auto ptr = std::make_unique<int>(100);

std::cout << *ptr << '\n';      // 输出：100
std::cout << ptr.get() << '\n'; // 输出指针地址

ptr.reset(new int(200));        // 释放旧内存并指向新资源
ptr.release();                   // 返回指针，ptr 变成 null
```
- 禁止的操作

以下操作会导致编译错误：

```cpp
std::unique_ptr<int> p1 = ptr; // ❌ 错误：拷贝构造被禁用
std::unique_ptr<int> p2;
p2 = ptr;                        // ❌ 错误：拷贝赋值被禁用
```

✅ 正确做法是使用 `std::move`：

```cpp
std::unique_ptr<int> p1 = std::move(ptr); // ✅ 正确：移动构造
std::unique_ptr<int> p2;
p2 = std::move(p1);              // ✅ 正确：移动赋值
```

---

- 自定义删除器（Deleter）

你可以为 `unique_ptr` 提供一个自定义删除器来处理特殊资源（如句柄、文件等）。

```cpp
struct MyDeleter {
    void operator()(int* ptr) const {
        std::cout << "Custom delete\n";
        delete ptr;
    }
};

std::unique_ptr<int, MyDeleter> ptr(new int(42), MyDeleter());
```
- 数组版本 `unique_ptr<T[]>`

C++11 支持对数组进行管理，使用 `unique_ptr<T[]>`：

```cpp
std::unique_ptr<int[]> arr(new int[5]{1, 2, 3, 4, 5});
arr[0] = 100; // 合法
```

⚠️ 注意：
- 必须使用 `T[]` 模板参数；
- `unique_ptr<T[]>` 不支持 `operator*()` 和 `operator->()`；
- 只能通过索引访问元素。

当然，智能指针会在指针声明周期结束的时候同时`delete`指针和指针指向的数组。

### `shared_ptr`
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
同样的存在初始化
```c++
#include <memory>
auto ptr1 = std::make_shared<int>(42); // 推荐写法，更高效安全
int* rawPtr = new int(42);
auto ptr2 = std::shared_ptr<int>(rawPtr);
```
和之前的`unique_ptr`不同的是，`shared_ptr`支持移动和拷贝
```c++
auto ptrA = std::make_shared<int>(100);

// 拷贝构造：引用计数 +1
auto ptrB = ptrA;

// 移动构造：ptrC 获取所有权，ptrA 变为空指针
auto ptrC = std::move(ptrA);

// 拷贝赋值
auto ptrD = ptrB; // 引用计数再 +1

std::cout << "Use count: " << ptrB.use_count() << '\n';//获取引用计数
```
### Transferrring Ownership
1. **`.release()` 方法**

**`.release()`** 方法的主要功能是将智能指针管理的原始指针释放给调用者，并将智能指针本身设置为 `nullptr`（即不再管理任何资源）。

- **返回值**：返回当前智能指针所持有的原始指针。
- **智能指针状态**：调用 `.release()` 后，智能指针会被设置为 `nullptr`，即它不再管理任何资源。

**示例代码解释**：

```cpp
unique_ptr<int> x(new int(5));
cout << "x: " << x.get() << endl;

unique_ptr<int> y(x.release());  // x abdicates ownership
```

- **`x.release()`**：这行代码调用了 `x` 的 `.release()` 方法，将 `x` 管理的指针（指向值为 5 的 `int`）释放出来，并将 `x` 设置为 `nullptr`。
- **`unique_ptr<int> y(x.release())`**：使用 `x.release()` 返回的指针来初始化一个新的 `unique_ptr` 对象 `y`。此时，`y` 接管了原来由 `x` 管理的资源。

因此，执行上述代码后：

- `x` 不再持有任何指针（`x.get()` 将返回 `nullptr`）。
- `y` 持有指向值为 5 的 `int` 的指针。

2. **`.reset()` 方法**

**`.reset()`** 方法用于重置智能指针的状态，具体行为如下：

- **参数**：可以接受一个新指针 `p` 作为参数。
- **行为**：
  - **删除当前指针**：如果智能指针当前持有某个指针，则会先删除该指针所指向的对象（调用其析构函数并释放内存）。
  - **接管新指针**：然后，智能指针会接管传入的新指针 `p`，开始管理 `p` 所指向的资源。
### Example of use smart pointer
```c++
#include <iostream>

template <typename T>
class SimpleSmartPtr {
private:
  T *ptr; // 管理的资源指针

public:
  // 构造函数，接收原始指针
  explicit SimpleSmartPtr(T *p = nullptr) : ptr(p) {}

  // 析构函数，释放资源
  ~SimpleSmartPtr() {
    delete ptr;
    ptr = nullptr;
  }

  // 解引用操作符重载
  T &operator*() const { return *ptr; }

  // 箭头操作符重载
  T *operator->() const { return ptr; }

  // 获取原始指针
  T *get() const { return ptr; }

  // 禁用拷贝构造和赋值（确保独占性）
  SimpleSmartPtr(const SimpleSmartPtr &) = delete;
  SimpleSmartPtr &operator=(const SimpleSmartPtr &) = delete;

  // 允许移动构造（转移资源所有权）
  SimpleSmartPtr(SimpleSmartPtr &&other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }

  // 允许移动赋值（转移资源所有权）
  SimpleSmartPtr &operator=(SimpleSmartPtr &&other) noexcept {
    if (this != &other) {
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }
};

template <typename T>
class RefCountSmartPtr {
private:
  T *ptr;        // 管理的资源指针
  int *refCount; // 引用计数器

public:
  // 构造函数，接收原始指针
  RefCountSmartPtr(T *p = nullptr) : ptr(p), refCount(new int(1)) {
    if (ptr == nullptr) {
      delete refCount;
      refCount = nullptr;
    }
  }

  // 析构函数，减少引用计数并释放资源
  ~RefCountSmartPtr() {
    if (refCount != nullptr && --*refCount == 0) {
      delete ptr;
      delete refCount;
      ptr = nullptr;
      refCount = nullptr;
    }
  }

  // 拷贝构造函数，增加引用计数
  RefCountSmartPtr(const RefCountSmartPtr &other) : ptr(other.ptr), refCount(other.refCount) {
    if (refCount != nullptr) {
      ++*refCount;
    }
  }

  // 赋值运算符重载
  RefCountSmartPtr &operator=(const RefCountSmartPtr &other) {
    if (this != &other) {
      // 处理旧资源
      if (refCount != nullptr && --*refCount == 0) {
        delete ptr;
        delete refCount;
      }
      // 复制新资源
      ptr = other.ptr;
      refCount = other.refCount;
      if (refCount != nullptr) {
        ++*refCount;
      }
    }
    return *this;
  }

  // 解引用操作符重载
  T &operator*() const { return *ptr; }

  // 箭头操作符重载
  T *operator->() const { return ptr; }

  // 获取原始指针
  T *get() const { return ptr; }

  // 获取引用计数（调试或测试用）
  int use_count() const { return refCount ? *refCount : 0; }
};

int main() {
  // 普通智能指针（独占资源）
  {
    SimpleSmartPtr<int> sp1(new int(42));
    std::cout << "*sp1 = " << *sp1 << std::endl;
    SimpleSmartPtr<int> sp2 = std::move(sp1); // 移动语义转移所有权
                                              // SimpleSmartPtr<int> sp3 = sp2;  // 编译错误，拷贝被禁用
  } // sp2 析构，释放资源

  // 带引用计数器的智能指针（共享资源）
  {
    RefCountSmartPtr<int> sp1(new int(100));
    RefCountSmartPtr<int> sp2(sp1);                                 // 拷贝构造，引用计数+1
    RefCountSmartPtr<int> sp3 = sp2;                                // 赋值，引用计数+1
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl; // 输出 3
    std::cout << "*sp3 = " << *sp3 << std::endl;                    // 输出 100
  } // sp1、sp2、sp3 析构，引用计数递减，最后资源释放

  return 0;
}
```
## Operator Overloading

**Operator Overloading :Provide the behaviors of operators for class type**

- 类型
  - 作为成员函数，这一些绑定到`a`这个类中，定义在类的内部
    - `a[i]`&`a.operator[](i)`
    - `a = b`&`a.operator=(b)`
    - `*a`&`a.operator*()`
  - 不是一个成员函数,定义在类的外部
    - `a == b`&`operator==(a,b)`
    - `a+b`&`operator+(a,b)`
  - 有一些操作符是不能够重载的
    - `.`,`::`,`?:`
    - 内嵌类型的操作符是不能够重载的
      - `MyInt operator+(int ,int)//Error`
    - 自己定义的符号是不能重载的
      - `double operator**(double x,double exp)//error`
  - 有一些操作符是能够重载的，但是不推荐
    - `cond1 && cond2`,`cond1 || cond2`
- 重载运算符不会改变连结关系和优先级

- 例子：有理数的表示
```c++
class Rational {
  int m_num;
  // numerator
  unsigned m_denom; // denominator

  void simplify() {                     // Private, because this is our implementation detail.
    int gcd = std::gcd(m_num, m_denom); // std::gcd in <numeric> (since C++17)
    m_num /= gcd;
    m_denom /= gcd;
  }

  friend Rational operator-(const Rational &); // Unary `operator-` as in `-x`.
// 将其定义在类的外部，使得other+this的情况也能得到满足。

public:
  Rational(int x = 0) : m_num{x}, m_denom{1} {} // Also a default constructor.

  Rational(int num, unsigned denom) : m_num{num}, m_denom{denom} { simplify(); }

  double to_double() const { return static_cast<double>(m_num) / m_denom; }

  Rational &operator+=(const Rational &rhs) {
    m_num = m_num * static_cast<int>(rhs.m_denom) // Be careful with `unsigned`!
            + static_cast<int>(m_denom) * rhs.m_num;
    m_denom *= rhs.m_denom;
    simplify();
    return *this; // `x += y` should return a reference to `x`.
  }

  Rational &operator-=(const Rational &rhs) {
    // Makes use of `operator+=` and the unary `operator-`.
    return *this += -rhs;
  }

  Rational &operator++() {//前置++
    ++m_num;
    simplify();
    return *this;
  }

  Rational operator++(int) {//后置++，这里的int没有实际的含义仅仅只是表示后置
    auto temp = *this;
    ++*this;//调用前置++
    return temp;
  }
};

Rational operator-(const Rational &x) {
  return {-x.m_num, x.m_denom};
  // The above is equivalent to `return Rational(-x.m_num, x.m_denom);`.
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
  return Rational(lhs) += rhs; // Makes use of `operator+=`.
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
  return Rational(lhs) -= rhs; // Makes use of `operator-=`.
}

bool operator<(const Rational &lhs,const Rational &rhs){
  return (lhs.m_num * rhs.m_denom < rhs.m_num * lhs.m_denom);
}
```
以上是一些常见的重载运算符，下面我们再来看IO的operator的重载

Input Operator:

`std::istream &operator>>(std::istream &,Rational &);`

Output Operator:

`std::ostream &operator<<(std::ostream &,const Rational &);`

`std::cin`is type `std::istream`, and `std::cout` is of type `std::ostream`
（`std::cin`是`ostream`的一个具体的实例）

所以我们根据这个原理构造一个`operator<<`和`operator>>`
```c++
class Rational{
  friend std::ostream &operator<<(std::ostream &,const Rational &);
};

std::ostream &operator<<(std::ostream &os,const Rational &r){
  return os << r.m_num << '/' << r.m_denom;
}
```

`Rational`:input operator

```c++
std::istream &operator>>(std::istream &is,Rational &r){
  int x,y;is>>x>>y;//定义两个整数，同时从输入流中依次读取这两个整数
  if(!is){//表示判断是否正确读取
    x = 0;
    y = 1;
  }
  if(y<0){y = -y;x = -x}//保证负号一定在分子上
  r = Rational(x,y);
  return is;//确保可以继续输入
}
```

- 例子：Dynarray

- `Operator[]`
```c++
class Dynarray {
public:
  int &operator[](std::size_t n) { return m_storage[n]; }

  const int &operator[](std::size_t n) const { return m_storage[n]; }
};
```

- 例子`WindowPtr`
```c++
struct WindowWithCounter {
  Window theWindow;
  int refCount = 1;
};

class WindowPtr {
  WindowWithCounter *m_ptr;

public:
  Window &operator*() const { // Why should it be const?
    return m_ptr->theWindow;
  }
};
```
为什么这里要是`const`?
  1. `operator*()`函数没有修改`WindowPtr`本身
  2. 这是一个顶层`const`，指针本身不可变，被管理的`Window`对象`(m_ptr->theWindow)`并非`const`声明`operator*()`为`cosnt`既保证了`m_ptr`不会指向其他的对象，同时也可以对`theWindow`进行修改。
  3. 但是你也可以通过重载函数来定义一个`const`,与非`const`的版本。例如
```cpp
Window &operator*()const

同样的我们还可以定义`operator->()`
```c++
class WindowPtr {
public:
  Window *operator->() const { return std::addressof(operator*()); }
};
```
对于基层的指针而言，`->`操作符直接返回底层对象的成员指针，等价于`(*ptr).mem`，它返回的还是一个指针?

为什么不直接返回原指针？因为如果在获得指针的地址的时候对指针包括逻辑的判断，那么就不能够直接返回原指针。

完整示例
```c++
#include <iostream>
#include <memory> // std::addressof

class Window {
  // 假设 Window 是一个普通类
public:
  void display() const { std::cout << "Window displayed\n"; }
};

class WindowPtr {
private:
  Window *ptr; // 假设 WindowPtr 内部管理一个 Window 指针

public:
  // 构造函数
  explicit WindowPtr(Window *p = nullptr) : ptr(p) {}

  // operator* 的定义
  Window &operator*() const {
    if (ptr == nullptr) {
      throw std::runtime_error("Dereferencing null pointer");
    }
    return *ptr;
  }

  // operator-> 的定义
  Window *operator->() const {
    if (ptr == nullptr) {
      throw std::runtime_error("Accessing null pointer");
    }
    return std::addressof(operator*());
  }
};

int main() {
  Window window;
  WindowPtr ptr(&window);

  // 测试 operator->
  ptr->display(); // 应输出 "Window displayed"

  // 测试 operator*
  (*ptr).display(); // 应输出 "Window displayed"

  return 0;
}
```
## User-defined type conversions
- 底层逻辑：一个类中恰好有一个参数类型是`T`的构造函数，可实现从`T`到`X`的类型转换。实例`std::string`有一个接受`const char*`的构造函数，因此`const char*`可以隐式转换成为`std::string`;
```c++
class Rational {  
public:  
    // 定义从 Rational 到 double 的转换操作符  
    operator double() const { return 1.0 * m_num / m_denom; }  
};  
Rational r(3, 4);  
double dval = r;  // 调用 operator double()，将 r 转换为 double，结果为 0.75  
```
### 类转换符(Type conversion operator)
```c++
class Rational {  
public:  
    // 定义从 Rational 到 double 的类型转换操作符  
    operator double() const { return 1.0 * m_num / m_denom; }  
};  
Rational r(3, 4);  
double dval = r;  // 自动调用 operator double()，将 r 转换为 double，结果为 0.75  
```
- 函数命名：
  - 函数名固定为`operator T()`其中`T`表示的是目标类型。
  - 返回类型：返回类型是`T`但在函数定义的时候不用显示的写出来
  - 常量属性：类型转换通常是只读形式，因此该操作符通常被声明为`cosnt`函数
- 但是我们并不是每次都希望这样的转换产生
  - 我们可以定义`explicit`关键字，表示不能通过构造函数来进行隐式转换
  ```c++
  class string { // Suppose this is the `std::string` class.
  public:
    string(const char *cstr); // Not marked `explicit`. Implicit use is allowed.
  };

  template <typename T>
  class vector { // Suppose this is the `std::vector` class.
  public:
    explicit vector(std::size_t n); // Implicit use is not allowed.
  };

  class Dynarray {
  public:
    explicit Dynarray(std::size_t n) : m_length{n}, m_storage{new int[n]{}} {}
  };
  ```
  - 同样的，我们自己定义的类型转换的时候如果加上`explicit`那么就只能接受显示转换不能够隐式调用
```c++
class Rational {
public:
  explicit operator double() const { return 1.0 * m_mun / m_denom; }
};

Rational r(3, 4);
double d = r; // Error

void foo(double x) {}

foo(r);                      // error
foo((double)r);              // ok
foo(static_cast<double>(r)); // ok
```  

同样的我们还可以定义`bool`类型的类型转化

```c++
class WindowPtr {
    WindowWithCounter *m_ptr;
public:
    // 假设已有其他成员函数（如构造函数等）
    explicit operator bool() const {
        return m_ptr != nullptr;
    }
};
```
- 这里使用`explicit operator bool()`来实现`WindowPtr`到`bool`的转换。
  - 使用`explicit`是为了避免意外导致的隐式转换
  - 函数体内通过`return m_ptr != nullptr`来判断`WindowPtr`管理的指针是否是空指针。

## Iterator(类似于一个指针)
- `.begin()`表示的是迭代器的首元素
- `.end()`返回的是最后一个元素的`next`叫做`off-the-end`

### Iterators:

范围是从$[c.begin(),c.end())$,`c.end()-c.begin()=length`如果有`c.begin() == c.end()`那么可知这个是一个空的迭代器

和指针类似，迭代器也存在一些相关的特殊符
- `*it`:returns a reference to the element that `it` refers to 
- `it->mem`:equivalent to `(*it).mem`
- `++it`:`it++` move `it` one step forward, so that `it` refers to the `next` elememt.注意`++it`返回的是`it`的引用，但是`it++`返回的是一个自增前的一个`copy`
- `it1==it2`:checks whether `it1` and `it2` refer to the same position in the container.
- `it1 != it2`:equivalent to `!(it1 == it2)`

```c++
void sqapcase(std::string &str){
  for(auto it = str.begin();it != str.end() ; ++it){
    if(std::islower(*it))
      *it = std::toupper(*it);
    else if(std::isupper(*it))
      *it = std::tolower(*it);
  } 
}
void print(const std::vector<int> &vec){
  for(auto it = vec.begin(); it!= vec.end(); ++it)
    std::cout << *it << ' ';
}
```
### 内置指针作为迭代器

内置指针作为迭代器，他们充当数组的迭代器来实现相同的功能。

例子1：数组的迭代器（内置指针）
```c++
#include <iostream>
#include <iterator> // 包含 std::begin 和 std::end

int main() {
    int arr[] = {10, 20, 30, 40}; // 长度为 4 的数组
    int* begin_iter = arr;         // 等价于 std::begin(arr)，指向首元素 10
    int* end_iter = arr + 4;       // 等价于 std::end(arr)，指向尾元素下一位置（越界指针）

    // 使用迭代器遍历数组
    for (int* it = begin_iter; it != end_iter; ++it) {
        std::cout << *it << " "; // 输出：10 20 30 40
    }
    return 0;
}
```

例子2：容器的迭代器
```c++
#include <vector>
#include <iostream>
#include <iterator> // 包含 std::begin 和 std::end（其实这里不写也是可以的，因为这里的vector重载了迭代器的内容）

int main() {
    std::vector<int> vec = {1, 2, 3, 4}; // vector 容器
    auto vec_begin = std::begin(vec);    // 等价于 vec.begin()，指向首元素 1    这里的vec_begin的类型是std::vector<int>::iterator
    auto vec_end = std::end(vec);        // 等价于 vec.end()，指向尾元素下一位置

    // 使用迭代器遍历容器
    for (auto it = vec_begin; it != vec_end; ++it) {
        std::cout << *it << " "; // 输出：1 2 3 4
    }
    return 0;
}
```

例子3：`std::begin/std::end`统一处理数组和容器

Range-for demystified
```c++
#include <array>      // C++11 数组容器
#include <iostream>
#include <iterator>

template <typename Container>
void print_elements(Container& c) {
    auto begin = std::begin(c); // 自动适配数组或容器
    auto end = std::end(c);
    for (; begin != end; ++begin) {
        std::cout << *begin << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {5, 10, 15};           // 普通数组
    std::array<double, 3> arr_container = {1.1, 2.2, 3.3}; // 数组容器

    print_elements(arr);          // 输出：5 10 15
    print_elements(arr_container); // 输出：1.1 2.2 3.3
    return 0;
}
```

### 是否可以解引用

和指针相似，只有当迭代器指向一个实际存在的元素的时候才能对它进行解引用（`*it`）.若迭代器不指向有效元素，会导致未定义行为。

实例说明：
- `*v.end()`是未定义行为。因为`v.end()`返回的只是一个有效位置但是并不会指向一个存在的元素
- 注意`it`如果不能够解引用，那么`++it`是未定行为，这意味着将迭代器移动到`[begin,off_the_end]`范围之外（超出合法元素区间）

### 迭代器失效（Iterators:invalidation）

例子：
```c++
Type *storage = new Type[n];  
Type *iter = storage;  
delete[] storage;  
// 此时 `iter` 不再指向任何存在的元素  
```

容器操作导致迭代器失效：
1. `std::vecotr`插入导致迭代器失效

当`vector`容量不足的时候，插入元素会触发内存重新分配，所有原有的迭代器都会失效
```c++
#include <vector>  
int main() {  
    std::vector<int> vec = {1, 2, 3};  
    auto it = vec.begin(); // 记录初始迭代器  
    vec.push_back(4);      // 假设触发扩容，内存重新分配  
    // 此时 `it` 失效，指向已释放的旧内存，解引用会导致未定义行为  
    // *it; // 危险！  
    return 0;  
}  
```

2. `std::vector`删除导致迭代器失效

删除元素之后，被删除元素及后续的迭代器失效

```c++
#include <vector>  
int main() {  
    std::vector<int> vec = {1, 2, 3, 4, 5};  
    auto it = vec.begin() + 2; // 指向元素 3  
    vec.erase(vec.begin() + 1); // 删除元素 2，后续元素前移  
    // 此时 `it` 实际指向原元素 4（逻辑上位置改变），若继续按原逻辑操作会出错  
    return 0;  
}  
```

3. `std::deque`中间插入导致迭代器失效
```c++
#include <deque>  
int main() {  
    std::deque<int> dq = {1, 2, 3};  
    auto it = dq.begin() + 1; // 指向元素 2  
    dq.insert(dq.begin() + 1, 0); // 中间插入元素 0  
    // 此时 `it` 失效，指向无效位置  
    // *it; // 危险！  
    return 0;  
}  
```

4. `std::list`删除当前迭代器指向的元素
```c++
#include <list>  
int main() {  
    std::list<int> lst = {1, 2, 3};  
    auto it = lst.begin();  
    lst.erase(it); // 删除元素 1，`it` 失效  
    // ++it; // 危险！失效迭代器递增无意义  
    return 0;  
}  
```

### More operations on iterators
 

1. **前向迭代器（ForwardIterator）**：

   支持 `*it`（解引用获取元素）、`it->mem`（通过迭代器访问元素成员）、`++it`（前置递增）、`it++`（后置递增）、`it1 == it2`（相等判断）和 `it1 != it2`（不等判断）的迭代器。这类迭代器只能单向移动，逐个访问元素。  

2. **双向迭代器（BidirectionalIterator）**：  

   在 `ForwardIterator` 基础上，支持双向移动，额外增加了 `--it`（前置递减）和 `it--`（后置递减）操作，允许反向遍历元素。  

3. **随机访问迭代器（RandomAccessIterator）**：  

   是 `BidirectionalIterator` 的扩展，能在常数时间内直接移动到任意位置，支持更多操作：  
   - 算术运算：`it + n`（迭代器后移 `n` 个位置）、`n + it`（同上）、`it - n`（迭代器前移 `n` 个位置）、`it += n`（复合后移）、`it -= n`（复合前移）。  
   - 下标访问：`it[n]`，等价于 `*(it + n)`。  
   - 距离计算：`it1 - it2`，返回两个迭代器之间的元素个数。  
   - 关系比较：`<`（小于）、`<=`（小于等于）、`>`（大于）、`>=`（大于等于），可直接比较迭代器位置。  
   **`std::string::iterator` and `std::vector<T>::iterator` are in this category**

### Initialization from iterator range
```c++
std::vector<char> v = {'a','b','c','d'};
std::vector v2(v.begin(),v.end()-1);
std::string s(v.begin()+1,v.end());
```

## Algorithms
定义对象
```c++
int a[N],b[N];
std::vector<int> v;
```
1. 对数组排序
```c++
std::sort(a,a+N);
```
使用`std::sort`算法对数组`a`排序，`a`和`a+N`构成迭代器范围（数组指针本质是迭代器）
2. 对容器排序
```c++
std::sort(a,a+N);
```
使用`std::sort`算法对数组`a`，进行排序`a`,`a+N`构成迭代器范围（数组指针本质也是迭代器）
3. 对容器排序
```c++
std::sort(v.begin(),v.end());
```
对`vector`容器`v`排序，`v.begin()`指向首元素，`v.end()`指向末尾元素
4. 元素复制
```c++
std::copy(a,a+N,b);
```
将`[a,a+N)`范围的元素赋值到以`b`开头的空间，`std::copy`利用空间迭代器对指定源范围和目标起始位置。
5. 部分元素排序
```c++
std::sort(v.begin(),v.begin()+10)
```
仅对`v`的前十个元素排序,通过`v.begin()`和`v.begin()+10`限定范围

### 算法接口特性
后缀为`_n`的算法如(`copy_n`,`fill_n`)通过其实起始迭代器`begin()`和整数`n`表示操作范围`[begin,begin+n)`

- 实例：
```c++
Dynarray::Dynarray(const int *begin, const int *end)  
    : m_storage{new int[end - begin]}, m_length(end - begin) {  
    std::copy(begin, end, m_storage); // 用 `copy` 算法（非 `_n` 后缀，用迭代器对）复制 `[begin, end)` 范围元素到 `m_storage`  
}  
```
利用`std::copy`，通过迭代器对`begin`和`end`界定范围，将元素复制到新分配的`m_storage`

```c++
Dynarray::Dynarray(const Dynarray &other)  
    : m_storage{new int[other.size()]}, m_length{other.size()} {  
    std::copy_n(other.m_storage, other.size(), m_storage); // 用 `copy_n`，从 `other.m_storage` 开始复制 `other.size()` 个元素到 `m_storage`  
}  
```

```c++
Dynarray::Dynarray(std::size_t n, int x = 0)  
    : m_storage{new int[n]}, m_length{n} {  
    std::fill_n(m_storage, m_length, x); // 用 `fill_n`，将 `m_storage` 开始的 `m_length` 个元素填充为 `x`  
}  
```

### Algorithms:requirements
1. 对迭代器类型的要求
- `std::sort`算法需要**随机访问迭代器**，因为内部实现以来随机访问的特性
- `std::copy`算法允许**输入迭代器**，只要逐个读取元素即可。

2. 元素类型的要求
需要比较元素的算法，通常仅以来元素的`operator<`和`operator==`例如，对`std::vecotr<X>`进行排序的时候，无需定义`X`的全部六个比较操作符`<`,`>`

3. Predicate
```c++
struct Point2d{
  double x,y;
};
std::vector<Point2d> points = someValue();
```
如果我们要对他进行排序，要么你要定义一个`operator<`或者是采用自定义外部函数进行构造

```c++
bool cmp_by_x(const Point2d &lhs,const Point2d &rhs){
  return lhs.x < rhs.x;
}
std::sort(point.begin(),point.end(),cmp_by_x);
```
也就是定义一个规则，因为`sort()`最终会达到的结果是`sort()`中的左侧的每一个元素和每一个元素后面的一个元素之间满足`cmp_by_x`的结果返回`true`（从小到大）。

```c++
// 从大到小排序
bool greater_than(int a, int b) { return a > b; }
std::sort(v.begin(), v.end(), greater_than);
```

```c++
//绝对值得判断方法
bool abs_less(int a, int b) { return std::abs(a) < std::abs(b); } // <cmath>
std::sort(v.begin(), v.end(), abs_less)
```

```c++
//同样的也可以只传入一个参数（本质还是让每一次`sort`返回的都是`true`）
bool less_than_10(int x) {
  return x < 10;
}
std::vector<int> v = someValues();
auto pos = std::find_if(v.begin(), v.end(), less_than_10);
```

同样的，你也可以传递一个`struct`
```c++
struct LessThan {
  int k_;
  LessThan(int k) : k_{k} {}
  bool operator()(int x) const {
    return x < k_;
  }
};
auto pos = std::find_if(v.begin(), v.end(), LessThan(k));
```

这个时候在`find_if`在操作的时候会默认为`LessThan`为一个函数，调用`()`的重载函数

```c++
struct LessThan {
  int k_;
  bool operator()(int x) const {
    return x < k_;
  }
};
auto pos = std::find_if(v.begin(), v.end(), LessThan{k});
```
使用大括号的形式，避免了构造函数的重复定义

```c++
struct AbsCmp {
  bool operator()(int a, int b) const {
    return std::abs(a) < std::abs(b);
  }
};
std::sort(v.begin(), v.end(), AbsCmp{});
```
同样的使用`(a,b)`双参数的构造形式，来完成传递两个参数的情况的定义。
### 算法和容器长度的关系
由于向算法传递的是迭代器而不是容器本身，**标准库算法不会修改容器的长度**.例如`std::copy`仅仅是复制元素，不会插入新的元素。
```c++
std::vector<int> a = someValues();  
std::vector<int> b(a.size());  
std::vector<int> c{};  
std::copy(a.begin(), a.end(), b.begin()); // 合法操作，b 有足够空间容纳复制的元素  
std::copy(a.begin(), a.end(), c.begin()); // 未定义行为！c 无足够空间，算法不会自动调整容器大小  
```
#### 常见分类
##### 1. 非修改性序列操作（Non - modifying sequence operations）  
这类算法不会修改容器中的元素，仅用于查找或统计：  
- **`count(begin, end, x)`**：统计区间 `[begin, end)` 内等于 `x` 的元素个数。  
- **`find(begin, end, x)`**：在区间 `[begin, end)` 中查找第一个等于 `x` 的元素。  
- **`find_end(begin, end, x)`**：在区间 `[begin, end)` 中查找最后一个等于 `x` 的元素。  
- **`find_first_of(begin, end, x)`**：在区间 `[begin, end)` 中查找第一个与 `x` 匹配的元素。 
  - 使用`if`来判断是否查找到相应元素
    - `if(std::find(v.begin(),v.end(),something) != v.end()){/*...*/}`
    - `if(auto pos = std::find(v.begin(),v.end(),something;pos != v.end()))`
  - 这两种方式都是正确的，只是第二种属于`if`的特殊操作`if(init_expr;condition)` 
- **`search(begin, end, pattern_begin, pattern_end)`**：在区间 `[begin, end)` 中查找与子序列 `[pattern_begin, pattern_end)` 匹配的位置。  

##### 2. 修改性序列操作（Modifying sequence operations）  
这类算法会修改容器元素的排列或值：  
- **`copy(begin, end, dest)`**：将区间 `[begin, end)` 的元素复制到以 `dest` 开头的位置。  
- **`fill(begin, end, x)`**：将区间 `[begin, end)` 的元素填充为 `x`。  
- **`reverse(begin, end)`**：反转区间 `[begin, end)` 内元素的顺序。  
- **`unique(begin, end)`**：  
  - 要求区间 `[begin, end)` 内的元素 **已排序**（默认升序）。  
  - 它不会真正删除重复元素，而是将重复元素移动到区间末尾，并返回一个迭代器 `pos`，使得 `[begin, pos)` 内没有重复元素。例如，对于已排序的序列，它会整理出不重复的前端子序列。 

## Inheritantce
```c++
class Item{
    std::string m_name;
protected:
    double m_price = 0.0;
public: 
    Item() = defaut;
    Item(const std::string &name,double price)
        : m_name(name),m_price(price){}
    const auto &getName() const {return m_name;} 
    auto netPrice(int cnt) const {
      return cnt * m_price;
    }
};
class DiscountedItem : public Item{
    int m_minQuantity = 0;
    double m_discount  = 1.0;
public:
    // constructor;
    // NetPrice
};
```
- 需要注意的内容：
  - `DiscountedItem`的构造函数需要先调用`Item`的构造函数，来初始化它的子类对象。
  - `DiscountedItem`的析构函数再销毁**自身**成员后，必须调用`Item`的析构函数。析构时，**先释放子类自身的资源，再处理基类资源，**来保证资源释放的完整性和正确性
  - 对象大小关系：`sizeof(Derived) >= sizeof(Base)`.由于派生类`discountedItem`对象包含基类`Item`的子对象，还可能有自己的成员`m_mimQuantity`,`m_discount`，因此派生类对象的大小必然大于或者等于基类对象的大小。
```c++
class Animal {
protected:
    std::string name;
public:
    // 基类构造函数
    Animal(const std::string& n) : name(n) {}
    void introduce() {
        std::cout << "I'm an animal named " << name << std::endl;
    }
};

// 子类
class Dog : public Animal {
private:
    // 子类新定义的成员变量
    int age;
public:
    // 子类构造函数
    Dog(const std::string& n, int a) : Animal(n), age(a) {}
    void bark() {
        std::cout << name << " who is " << age << " years old says Woof!" << std::endl;
    }
};
```
在上面的代码中，可以看到在写子类的构造函数的时候需要调用父类的构造函数。

如果在写子类的构造函数的时候没有写出基类的构造函数将会如何？
  - 如果不显示调用基类的构造函数，会调用**基类**的默认构造函数
  - 如果基类没有可以访问的默认构造函数（也就是基类不是默认可以构造的），则会导致错误

例如下面这一段代码：
```c++
class Item {
protected:
  std::string m_name;
  double m_price;

public:
  Item(const std::string &name, double p) : m_name(name), m_price(p) {}
};

class DiscountedItem : public Item {//public 表示对于父类中的原有的对外最高权限表示不变；如果写成protected,表示所有的对外权限中的最高权限都是protected;同理如果是private，那么所有的对外权限都是private（一般都是public）
  int m_minQuantity;
  double m_discount;

public:
  DiscountedItem(const std::string &name, double p, int mq, double disc) {
    m_name = name;
    m_price = p;
    m_minQuantity = mq;
    m_discount = disc;
  }
};
```
- 基类中：定义类`Item(const std::string &name,double p)`使用成员初始化列表初始化`m_name`，`m_price`。该类没有默认的初始化构造函数
- 派生类：`DiscountedItem(const std::string&name,double p,int mq,double disc)`直接在函数体内对基类的`m_name`和`m_price`复制，没有通过成员初始化列表调用基类的`Item`的构造函数。
- 在`c++`中没有在基类中定义默认的构造函数，派生类的构造函数必须是在成员初始化中显示调用基类的构造杉树，以正确的初始化基类的子对象。由于`Item`没有默认的构造函数，且`DiscountedItem`的构造函数没有显示调用`Item`已有的构造函数`Item(const std::string &name,double p)`因此，会报错

## Dynamic Bounding
### Upcasting
以下是一个更完整的示例，涵盖了`Item`和`DiscountedItem`类的定义，还有更多向上转型的演示：

```cpp
#include <iostream>
#include <string>

// 基类 Item
class Item {
protected:
    std::string name;
    double price;
public:
    Item(const std::string& n, double p) : name(n), price(p) {}
    std::string getName() const { return name; }
    double getPrice() const { return price; }
};

// 派生类 DiscountedItem
class DiscountedItem : public Item {
private:
    int quantity;
    double discount;
public:
    DiscountedItem(const std::string& n, double p, int q, double d) 
        : Item(n, p), quantity(q), discount(d) {}
    double getDiscountedPrice() const {
        return price * quantity * discount;
    }
};

// 接受基类引用的函数
void printItemName(const Item &item) {
    std::cout << "Name: " << item.getName() << std::endl;
}

int main() {
    DiscountedItem di("A", 10, 2, 0.8);
    Item i("B", 15);

    // 调用 printItemName 函数
    printItemName(i);
    printItemName(di);

    // 使用基类指针
    Item* ip = &di;
    std::cout << "Name (using pointer): " << ip->getName() << std::endl;
    // 无法通过基类指针访问派生类特有的成员
    // std::cout << "Discounted Price: " << ip->getDiscountedPrice() << std::endl; // 编译错误

    return 0;
}
```
- 代码解释
1. **类的定义**：`Item`是基类，包含`name`和`price`成员；`DiscountedItem`是派生类，在`Item`的基础上添加了`quantity`和`discount`成员，还有`getDiscountedPrice`方法。
2. **向上转型的使用**：在`main`函数中，`Item* ip = &di;`把`DiscountedItem`对象的地址赋给了`Item`类型的指针，这属于向上转型。
3. **可见范围限制**：在`printItemName`函数里，只能访问`Item`类的成员；通过`Item`类型的指针`ip`也只能访问`Item`类的成员，无法访问`DiscountedItem`类特有的`getDiscountedPrice`方法。

通过向上转型，你能够以统一的方式处理基类和派生类对象，增强代码的灵活性与可扩展性。 

### Virtual functions
`Item` and `DiscountedIten` hace different ways of computing the net price.

我们要怎么做来解决这个问题呢？
```c++
class Item {
public:
  virtual double netPrice(int cnt) const { return m_price * cnt; }

  // other members
};

class DiscountedItem : public Item {
public:
  double netPrice(int cnt) const override { return cnt < m_minQuantity ? cnt * m_price : cnt * m_price * m_discount; }

  // other members
};
```
  - If the dynamic type of `item` is `Item` ,it calls `Item::netPrice`
  - If the dynamic type of `item` is `DiscountedItem`,it calls `DiscountedItem::netPrice`

### `virtual-override`
```cpp
class Base {
public:
    virtual void func() {
        // 基类虚函数的实现
    }
};

class Derived : public Base {
public:
    void func() override {
        // 覆盖基类的虚函数
    }
};
```
override 关键字能让编译器对函数是否真正覆盖基类的虚函数进行检查。要是函数签名（参数列表、返回类型、常性等）和基类的虚函数不匹配，编译器就会报错，从而避免因疏忽造成的错误。
```c++
class Base {
public:
    virtual void func() {
        // 基类虚函数的实现
    }
};

class Derived : public Base {
public:
    void func() override { // 这里省略了 virtual 关键字
        // 覆盖基类的虚函数
    }
};
```
如果写了`override`那么`virtual`可以省略。
### virtual destruction
```cpp
Item *ip = nullptr;
if (some_condition)
    ip = new Item(/* ... */);
else
    ip = new DiscountedItem(/* ... */);
// ...
delete ip;
```
Whose destructor should be called? -It needs to be determined at run-time!
  - To use dynamic binding correctely ,you almost always neeed a virtual destructor.

- **隐式析构函数**：编译器自动生成的析构函数是非虚的。但我们可以显式要求虚析构函数，如 `virtual ~Item() = default;` ，这样就将 `Item` 类的析构函数声明为虚析构函数，同时使用 `= default` 让编译器生成默认实现。

- **派生类情况**：如果基类的析构函数是虚函数，那么编译器为派生类生成的析构函数也会是虚函数。这确保了在通过基类指针删除派生类对象时，能正确调用派生类的析构函数，避免内存泄漏等问题 。 

通常，在基类把析构函数声明成虚析构函数后，派生类的析构函数会自动成为虚析构函数，而且派生类析构函数名称和参数列表与基类析构函数是固定的，不会有重载情况。所以，即便不使用`override`关键字，编译器也能明确派生类析构函数覆盖了基类的虚析构函数。

示例：
```c++
#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() override { // 这里的 override 是可选的
        std::cout << "Derived destructor" << std::endl;
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr;
    return 0;
}
```
在这个例子中，`Derived`类的析构函数使用了`override`关键字，但实际上，就算不写`override`，`Derived`的析构函数也会覆盖`Base`的析构函数。

### static type and dynamic type
- 静态类型：表达式在编译时已知的类型 。编译器在编译阶段就能够确定表达式的静态类型，这是基于声明来判断的。
- 动态类型：表达式所代表对象的真实类型，在运行时才能确定 。因为程序运行时，对象可能是基类类型，也可能是派生类类型，只有运行到相关代码处才能知晓其确切类型。
```c++
void printItemName(const Item &item) {
    std::cout << "Name: " << item.getName() << std::endl;
}
```
在上述函数中，形参 `item` 的静态类型是 `const Item` ，这在编译时就确定了。但在程序运行时，传递给该函数的实参可能是 `Item` 类对象，也可能是从 `Item` 派生的 `DiscountedItem` 类对象等。这里，如果传入的是一个派生类，那么在这里会进行向上转换，但是如果是有重写的虚函数，那么会调用派生类的虚函数。所以直到运行时，才能知道 `item` 所代表对象的动态类型到底是什么。

### Usage with smart pointers
智能指针通过封装原始指针来实现，正因如此，它们也能用于动态绑定。动态绑定是 C++ 多态性的一种体现，运行时根据对象实际类型调用对应函数。


```cpp
std::vector<std::shared_ptr<Item>> myItems;
for (auto i = 0; i != n; ++i) {
    if (someCondition) {
        myItems.push_back(std::make_shared<Item>(someParams));
    } else {
        myItems.push_back(std::make_shared<DiscountedItem>(someParams));
    }
}
```
这里创建了一个 `std::vector`，元素类型是 `std::shared_ptr<Item>` ，即指向 `Item` 类（及其派生类对象 ）的共享智能指针。在循环中，根据条件将指向 `Item` 或 `DiscountedItem`（可能是 `Item` 的派生类 ）的共享智能指针添加到容器中。这样在后续使用容器中智能指针调用虚函数时，就能实现动态绑定，根据对象实际类型调用相应函数。 

- 智能指针类型转换
  - `std::unique_ptr<Derived>`（指向派生类的独占智能指针 ）可以隐式转换为 `std::unique_ptr<Base>`（指向基类的独占智能指针 ）。
  - `std::shared_ptr<Derived>`（指向派生类的共享智能指针 ）可以隐式转换为 `std::shared_ptr<Base>`（指向基类的共享智能指针 ）。这种隐式转换使得在处理基类和派生类关系时，智能指针能更灵活地使用，方便实现多态等特性 。 

### Copy control
- 拷贝控制要点
在实现派生类的拷贝构造函数和拷贝赋值运算符时，要记得对基类子对象进行拷贝或移动操作 。因为派生类对象包含基类子对象，若不处理好基类部分，会导致基类成员未正确初始化或赋值，引发错误。

- **拷贝构造函数**：
```cpp
Derived(const Derived &other) : Base(other), /* Derived's own members */ { /*... */ }
```
这里派生类 `Derived` 的拷贝构造函数使用成员初始化列表，通过 `Base(other)` 调用基类 `Base` 的拷贝构造函数，完成基类子对象的拷贝 ，同时后续可对派生类自身成员进行初始化。
- **拷贝赋值运算符**：
```cpp
Derived &operator=(const Derived &other) {
    Base::operator=(other); // call Base's operator= explicitly
    // copy Derived's own members
    return *this;
}
```
此拷贝赋值运算符函数中，先通过 `Base::operator=(other)` 显式调用基类的拷贝赋值运算符，完成基类子对象的赋值 ，然后再对派生类自身成员进行拷贝赋值，最后返回 `*this` 以支持链式赋值。

- 原理说明
`Base(other)` 和 `Base::operator=(other)` 能正常工作，是因为它们的参数类型是 `const Base &` ，而派生类对象可以隐式转换为基类对象引用，所以能将派生类对象 `other` 绑定到 `const Base &` 类型参数上 ，从而调用基类相应的拷贝构造函数和拷贝赋值运算符。 

### Synthesized copy-control members
#### 处理顺序
在处理派生类的合成拷贝控制成员时，总是先处理基类子对象。这是因为派生类对象由基类子对象和派生类自身成员组成，基类部分是派生类对象的基础。

#### 合成拷贝控制成员行为
- 编译器生成的拷贝控制成员（如拷贝构造函数、拷贝赋值运算符等 ），首先会调用基类对应的拷贝控制成员 。这是为了正确初始化或赋值派生类对象中的基类子对象部分。
- 然后，再对派生类自身的数据成员执行相应操作 。比如，若为拷贝构造，在基类部分拷贝完成后，会对派生类新增的数据成员进行拷贝。

#### 合成拷贝控制成员被删除的情况
- **基类成员不可访问**：如果基类对应的拷贝控制成员不存在，或者是 `private` 等不可访问的情况，编译器合成的派生类拷贝控制成员会被标记为删除 。因为无法正确处理基类子对象的拷贝控制操作。
- **数据成员成员不可访问**：若派生类任何数据成员对应的拷贝控制成员不可访问，编译器合成的拷贝控制成员也会被删除 。例如，类中包含 `std::unique_ptr` 且未提供合适移动操作，或者有不可访问的自定义数据成员拷贝控制函数等情况。 

### Polymorphic class(多态类)
#### 多态类定义
一个类如果（声明或继承）至少有一个虚函数，就被称为多态类 。这里的虚函数可以是普通的虚成员函数，也可以是虚析构函数。比如，只要类中存在 `virtual void func();` 这样的普通虚成员函数，或者 `virtual ~ClassName();` 这样的虚析构函数，该类就是多态类。 

#### 派生类相关特性
- **多态继承性**：如果一个类是多态类，那么从它派生出来的所有类也都是多态类 。这是因为在C++ 中，无法拒绝继承成员函数，虚成员函数自然也会被继承。例如，基类 `Base` 是多态类，有虚函数 `virtual void baseFunc();` ，派生类 `Derived` 继承 `Base` 时，会自动继承这个虚函数，所以 `Derived` 也是多态类。
- **析构函数特性**：若基类的析构函数是虚函数，那么派生类的析构函数也必须是虚函数 。这是为了保证在通过基类指针删除派生类对象时，能正确调用派生类的析构函数，妥善释放派生类对象资源，避免内存泄漏等问题。 

### `Dynamic_cast<>`转换
#### 转型语法
`dynamic_cast<Target>(expr)` ，其中 `Target` 必须是引用或指针类型 。它用于将表达式 `expr` 转换为 `Target` 类型。

```cpp
Base *bp = new Derived{};
Derived *dp = dynamic_cast<Derived *>(bp);
Derived &dr = dynamic_cast<Derived &>(*bp);
```
- 首先创建了基类 `Base` 指针 `bp` 并指向派生类 `Derived` 对象。
- 然后使用 `dynamic_cast` 将 `bp` 转换为**派生类指针** `dp` ，以及将 `*bp` 转换为派生类引用 `dr` 。

#### 工作原理及结果
- **运行时类型识别（RTTI）**：`dynamic_cast` 会在运行时执行类型识别（RTTI）来检查表达式的动态类型 。
- **转换成功情况**：如果表达式的动态类型是 `Derived` ，或者是 `Derived` 的（直接或间接 ）派生类，那么向下转型成功。
- **转换失败情况**：如果转型失败，当 `Target` 是指针类型时，`dynamic_cast` 返回空指针；当 `Target` 是引用类型时，会抛出 `std::bad_cast` 异常 。 这样能在一定程度上保证类型转换的安全性，避免因错误转换导致的未定义行为。 

```c++
class Base {};
class Derived : public Base {};

Base baseObj;
Base* bp = &baseObj;
Derived* dp = dynamic_cast<Derived*>(bp); // 这里转换会失败
//这里的实际类型不是`Derived`而是`Base`,会导致报错
```
```c++
class Base {};
class Derived : public Base {};
class AnotherDerived : public Base {};

AnotherDerived anotherDerivedObj;
Base* bp = &anotherDerivedObj;
Derived* dp = dynamic_cast<Derived*>(bp); // 转换会失败
```
```c++
class Base {};
class Derived : public Base {};
class Unrelated {};

Unrelated unrelatedObj;
Base* bp = reinterpret_cast<Base*>(&unrelatedObj); // 强制转换，仅为示例不合理性
Derived* dp = dynamic_cast<Derived*>(bp); // 转换会失败
```
- 只有清晰的继承关系才能够转换成功。

### Dynamic_cast can be very slow

- `dynamic_cast`性能劣势
`dynamic_cast` 执行向下转型时，会在运行时进行检查 ，利用运行时类型信息（RTTI）来判断转型是否应该成功。这种运行时检查机制使其比其他类型转换（如`const_cast` 或算术转换 ）慢很多。因此，最佳实践是尽可能避免使用 `dynamic_cast` ，以提升程序性能。

- 替代方案 - `static_cast`
如果能确保向下转型一定成功 ，可以使用`static_cast` 。例如`auto dp = static_cast<Derived *>(bp);` ，`static_cast` 比`dynamic_cast` 快，因为它不进行运行时检查。但弊端是，如果实际动态类型不是`Derived` ，就会导致未定义行为（UB ） 。这意味着使用`static_cast` 时，程序员需要自行确保类型转换的正确性，否则可能引发严重错误。 

### Avoid Dynamic_cast
```cpp
struct A {
  virtual ~A() {}
};

struct B : A {};

struct C : A {};

std::string getType(const A *ap) {
  if (dynamic_cast<const B *>(ap))
    return "B";
  else if (dynamic_cast<const C *>(ap))
    return "C";
  else
    return "A";
}
```

- 代码功能
这段代码定义了一个继承体系，基类为 `A`，派生类为 `B` 和 `C`。`getType` 函数接受一个指向基类 `A` 的指针 `ap`，通过 `dynamic_cast` 尝试将其转换为指向 `B` 和 `C` 的指针，根据转换结果返回对应的类型名称字符串。

- 效率问题
- **运行时类型检查开销**：`dynamic_cast` 是一个运行时类型转换操作符，它会在运行时进行类型检查，以确保转换的安全性。这涉及到查询对象的运行时类型信息（RTTI），需要额外的开销。在 `getType` 函数中，每次调用都会进行至少一次 `dynamic_cast`，如果第一次转换失败，还会进行第二次转换，这会导致性能下降。
- **多次检查**：对于每个传入的指针，都需要依次尝试转换为 `B` 和 `C` 的指针，这增加了不必要的检查次数，尤其是当继承体系更加复杂时，性能问题会更加明显。


```cpp
struct A {
  virtual ~A() {}

  virtual std::string name() const { return "A"; }
};

struct B : A {
  std::string name() const override { return "B"; }
};

struct C : A {
  std::string name() const override { return "C"; }
};

auto getType(const A *ap) {
  return ap->name();
}
```

- 代码功能
同样定义了一个继承体系，基类 `A` 中定义了一个虚函数 `name()`，返回字符串 `"A"`。派生类 `B` 和 `C` 分别重写了 `name()` 函数，返回各自的类型名称字符串。`getType` 函数接受一个指向基类 `A` 的指针 `ap`，直接调用 `ap->name()` 来获取对象的类型名称。

- 效率优势
- **虚函数调用机制**：虚函数是通过虚函数表（vtable）来实现的，在编译时就已经确定了虚函数表的布局，运行时只需要通过对象的指针找到对应的虚函数表，然后调用相应的函数。这种机制比 `dynamic_cast` 的运行时类型检查要快得多。
- **单次调用**：只需要进行一次虚函数调用，避免了多次类型检查，减少了不必要的开销。

## Pure virtual functions
### 定义：
```c++
class Base {
public:
    virtual void func() = 0; // 纯虚函数
    virtual ~Base() = default; // 建议将析构函数设为虚函数
};
```
### 应用：
1. 定义接口
```c++
class Shape {
public:
    virtual double area() const = 0; // 计算面积
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14 * radius * radius; }
};
```
2. 实现运行时候的多态：
```c++
Shape* shape = new Circle(5);
std::cout << shape->area(); // 调用 Circle::area()
```
但是要注意：
```c++
Shape shape;//Error
Shape *p = new Shape;//Error;
auto sp = std::make_shared<Shape>();//Error
std::shared_ptr<Shape> sp2 = std::make_shared<Rectangle>(p1,p2);//OK
```
**只能够通过子类对象的声明来完成对他构建实例化**

**纯虚函数中一样可以定义非纯虚函数，同时也可以定义成员变量，但是纯虚函数的传参等等都要通过子类进行**
```c++
#include <iostream>

// 抽象类
class Shape {
protected:
    int x;  // 成员变量
    int y;  // 成员变量
public:
    Shape(int x, int y) : x(x), y(y) {}

    // 纯虚函数
    virtual double area() const = 0;

    // 非纯虚函数
    void printPosition() const {
        std::cout << "Position: (" << x << ", " << y << ")" << std::endl;
    }
};

// 派生类
class Circle : public Shape {
private:
    double radius;
public:
    Circle(int x, int y, double r) : Shape(x, y), radius(r) {}

    // 实现纯虚函数
    double area() const override {
        return 3.14 * radius * radius;
    }
};

int main() {
    // Shape shape(1, 2); // 错误，不能实例化抽象类
    Circle circle(1, 2, 3);
    circle.printPosition();
    std::cout << "Area: " << circle.area() << std::endl;
    return 0;
}
```
### 纯虚函数与抽象类
纯虚函数是一种特殊的虚函数，他在基类中声明但是没有具体的实现，并且要求所有的派生类必须提供自己的实现。

而抽象类则是包含至少一个纯虚函数的类被称之为抽象类。抽象类不能被实例化

### Make the interface robust,not error-prone
```c++
class Shape {
public:
    virtual double area() const {
        return 0;
    }
};
```
在这个设计中，`Shape` 类提供了一个虚函数 `area()`，并且给出了一个默认实现（返回 `0`）。这种设计存在以下问题：

- **隐式错误**：如果 `Shape::area()` 被意外调用，它将默默地返回 `0`，这可能会导致程序逻辑错误但不会抛出异常或给出任何错误提示。这种“沉默的”错误很难被发现和调试。
- **不符合预期的行为**：`Shape` 作为一个基类，其目的是定义一个接口，要求所有派生类都必须实现 `area()` 方法。然而，当前的设计允许直接使用 `Shape` 实例，并且 `area()` 方法有一个默认实现，这违背了设计初衷。

#### 改进接口设计

为了使接口更加健壮，可以采用以下几种方法来改进设计：

1. 使用纯虚函数

将 `area()` 定义为纯虚函数，强制所有派生类实现该方法。

```cpp
class Shape {
public:
    virtual double area() const = 0; // 纯虚函数
    virtual ~Shape() = default; // 虚析构函数
};
```

- **优点**：
  - **强制实现**：所有派生类必须实现 `area()` 方法，否则会导致编译错误。
  - **避免默认行为**：没有默认实现，避免了意外调用基类方法的情况。

- **缺点**：
  - **不能实例化**：`Shape` 本身不能被实例化，只能作为基类使用。

2. 提供显式的错误处理

如果希望在基类中提供一个实现（例如，为了方便某些特殊情况下的使用），可以改为抛出异常，明确表示这是不应该发生的情况。

```cpp
class Shape {
public:
    virtual double area() const {
        throw std::logic_error("area() called on Shape!");
    }
};
```

- **优点**：
  - **显式错误**：如果 `Shape::area()` 被意外调用，会抛出异常，明确指出这是一个错误。
  - **可选实现**：提供了默认实现，但在实际使用中会抛出异常，提醒开发者这是不应该发生的情况。

- **缺点**：
  - **运行时开销**：抛异常会有一定的运行时开销。
  - **仍然可以实例化**：`Shape` 仍然可以被实例化，尽管这样做会导致异常。
### More on the `is - a` relationship

多态是面向对象编程中的一个核心概念，它允许使用一个接口来表示不同类型的实体。具体来说，多态可以通过运行时多态和编译时多态来实现。

1. 多态的定义

多态指的是提供单一接口来操作不同类型实体的能力，或者用单一符号来表示多种不同类型的机制。这使得代码更加灵活和可扩展。

2. 运行时多态（Run-time Polymorphism）

运行时多态通过动态绑定（dynamic binding）来实现。这意味着函数调用在运行时才确定具体要调用哪个函数实现。

```cpp
struct Shape {
    virtual void draw() const = 0; // 纯虚函数
};

void drawStuff(const Shape &s) {
    s.draw(); // 动态绑定，根据 s 的实际类型调用相应的 draw() 实现
}
```

- **Shape 结构体**：定义了一个纯虚函数 `draw()`，这意味着 `Shape` 是一个抽象基类，不能直接实例化。
- **drawStuff 函数**：接受一个 `const Shape &` 类型的参数 `s`，并调用 `s.draw()`。这里的关键点在于 **动态绑定**：
  - 如果 `s` 实际上是一个 `Circle` 类型的对象（假设 `Circle` 继承自 `Shape` 并实现了 `draw()`），则会调用 `Circle::draw()`。
  - 如果 `s` 实际上是一个 `Square` 类型的对象（假设 `Square` 继承自 `Shape` 并实现了 `draw()`），则会调用 `Square::draw()`。

这种机制允许我们在不知道具体类型的情况下，通过基类接口来操作不同类型的对象。

3. 编译时多态（Compile-time Polymorphism）

编译时多态通过函数重载（function overloading）、模板（templates）、概念（concepts, 自 C++20 起可用）等机制来实现。这些机制在编译阶段就决定了具体的函数实现。
```cpp
template <typename T>
concept Shape = requires(const T x) {
    x.draw(); // 检查 T 类型是否有一个 draw() 成员函数
};

void drawStuff(Shape const auto &s) {
    s.draw(); // 根据 s 的静态类型调用相应的 draw() 实现
}
```

- **概念（Concept）**：`Shape` 是一个概念，它要求类型 `T` 必须有一个 `draw()` 成员函数。
- **drawStuff 函数**：接受一个满足 `Shape` 概念的 `const auto &` 类型的参数 `s`，并调用 `s.draw()`。这里的关键点在于 **静态绑定**（或称早期绑定）：
  - 如果 `s` 的静态类型是 `Circle`（假设 `Circle` 有一个 `draw()` 成员函数），则在编译时就确定调用 `Circle::draw()`。
  - 如果 `s` 的静态类型是 `Square`（假设 `Square` 有一个 `draw()` 成员函数），则在编译时就确定调用 `Square::draw()`。

这种机制在编译时就决定了具体的函数实现，因此通常比运行时多态更高效。
在 C++ 中，纯虚函数（Pure Virtual Function）的主要目的是确保所有派生类都必须提供自己的实现。因此，纯虚函数通常没有默认实现。然而，在某些情况下，你可能希望为纯虚函数提供一个默认实现，以便在派生类中可以选择性地使用或覆盖这个默认实现。

### 纯虚函数中的默认函数
**分离默认实现到另一个函数**
```cpp
class Base {
protected:
    // 默认实现
    void defaultFunc() const {
        std::cout << "Default implementation" << std::endl;
    }

public:
    virtual void func() const = 0; // 纯虚函数
};

class Derived : public Base {
public:
    void func() const override {
        // 使用默认实现
        defaultFunc();
        // 或者添加其他逻辑
        std::cout << "Derived implementation" << std::endl;
    }
};
```

- **`Base` 类**：
  - `defaultFunc`：这是一个受保护的非虚函数，提供了默认实现。
  - `func`：这是一个纯虚函数，要求所有派生类必须实现。

- **`Derived` 类**：
  - `func`：这是对 `Base::func` 的具体实现。在这个实现中，可以选择调用 `defaultFunc` 来使用默认行为，也可以添加额外的逻辑。

### Separate default implementation from interface
如果对于一个抽象类的子类而言，没有定义它的具体函数（抽象类中的纯虚函数），那么子类仍然会被解释成为抽象类，导致实例化报错。
```c++
class ModelC : public Airplane {
public:
  virtual void fly(const Airport &destination) {
    // The "Model C way" of flying.
    // Without the definition of this function, `ModelC` remains abstract,
    // which does not compile if we create an object of such type.
  }
};
```
### 总结：
- **非虚函数**指的是没有使用`virtual`关键字声明的成员函数，子类不能复写，直接在主程序中利用子类调用父类的非虚函数。
- **纯虚函数**仅指定接口的继承，子类必须实现该接口，但基类不提供默认实现
- **简单的虚函数**：指定接口的继承，同时包含一个默认实现。子类可以选择重写该默认实现，也可以直接使用基类提供的实现。