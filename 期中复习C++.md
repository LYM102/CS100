##### `c`
- 系统操作：
  - `gcc -o file_out file_name.c`(编译)
  - `./ file_out`(运行)
  - `./ file_out <1.in >1.out`(默认输入流是`1.in`,输出流是`1.out`)
- 常见的未定义行为
1.数组越界2.修改字面量3.除零4.有返回值的函数没有`return`/没有返回值的函数返回了一个值5.存在副作用的式子6.解引用空指针/野指针/悬垂指针7.未初始化的局部变量8.`signed`整数溢出9.错误的类型转化9.函数参数数量不匹配
- 逗号运算符是存在从左到右的顺序的但是要注意逗号运算符`int j = (i++,i+5);`仅仅再赋值或者是初始化的时候存在`for(int i = 0,j = 0...)`要注意和函数的参数传递的逗号不一样，函数传参的顺序无法确定。
- `scanf("%d",&(++i))`正确，但是对`i`的值没有影响
- 通过输入流或者是`""`定义的字符串是默认含有`\0`在末尾，但是如果使用的是`char str[2] = {'a','b'};`就不会补充`'\0'`，但是如果传入的参数小于`char[N]`的个数，后面的会自动初始化为`\0`
- 数组的指针会在初始化之后退化，但是如果存在`sizeof()`,`&arr`的时候不会退化（仅仅在统一作用域下，如果传递到函数中就会退化）。
- `sizeof(arr)`会返回含有`\0`的数组的大小（仅仅在使用`char[]`定义的时候，如果使用指针定义的就返回的是指针的大小），但是`strlen()`会忽略`\0`
- 如果`scanf()`返回值是合法的，`scanf()`的返回值和预期输入数量匹配。如果`scanf()`返回值是非法的，`scanf()`的返回值是零。（`fget(str,max(包括'/0'),stdin)`最多读`100-1`个）
- 赋值运算符右连结，算数运算符左连结
- `int arr[100] = {1}`:表示的是第一个元素为`1`，后面的元素都是`0`.
- `int *a/a[]/a[N]`,但是如果是传递的引用会限制大小必须相同，`int (*)p[]`数组的指针；`int* p[]`指针的数组；`int arr[2][3]`传入函数`int (*arr)[3]`（第二个参数大小一定要相同，第一个参数类型大小无关），`int (&arr)[9][10]`表示的是传入的是引用类型,这个时候要求引用类型的两个参数大小都必须完美匹配。
- `malloc(size_t size)`声明指针，若失败传出`NULL`;`calloc(size_t n,size_t size)`分配`num`个`size`大小的内存。初始化为0.`realloc(void* ptr,size_t size)`重新分配未被`free`的内存，如果`ptr`是`NULL`则等价于`malloc(size)`如果不是，则等价于`free(pre);malloc(size)`内存不够的时候`realloc`返回`NULL`,原内存不变，成功则会返回相应的指针，同时原指针失效
- 申请二维数组`malloc(sizeof(int *)* n);for(int i = 0;i<n;i++);p[i] = malloc(sizeof(int)*m)`
- 数组的首地址不能够改变，但是传入函数之后退化成为指针可以改变地址（实际上是一个指针副本）
- 函数指针`int(return_type) (*fun_name)(int,int)`，函数指针数组：`void (*ops[3])(int) = {add, sub, mul};`,通常其`top const`会被忽略
- `struct`解构体写在全局中作为全局变量一样的也是初始化为0;`union`联合体，只能储存一个成员，大小等于最大的成员的大小。
- `ptrdiff_t`是两个指针相减的结果，结果类型：`signed`
- `strcat(dest,src)`将`src`的`copy`追加到`dest`;`strcmp(str,ch)`返回`ch`出现的地址（找不到返回`NULL`,注意`\0`是可以被查找的）；`strcmp(s1,s2)`按照字典序比较两个字符串`strcpy(dest,src)`将`stc`复制到`dest`

##### `c`vs`c++`
1. `bool`,`true`,`false`是内嵌的类型不再是`int`类型的了
2. 逻辑判断返回的也是`bool`类型而不是`int`类型
3. `"hello"`这个字面量在`C++`中是`const char [N+1]`而不是`char [N+1]`。
4. 字符`'a'`不再是`int`类型，而是`char`类型。
5. `getline()`的用法：`getline(std::cin,string& str, char delim)`。`str`表示用于存储读取到的行内容的字符串对象，`delim`表示读取到什么内容就停止读取本字符串.
6. `string`后面没有`\0`来确定最终的长度和停止位置
7. 注意传入某个类型的函数的表达式为`std::function<double(double,double)>`
8. c++中的`std::string`会自动分配内存，而不是C语言中的`char[]`它的输入要格外的小心。
9. c++中使用`new int[5]{1,2,3,4}/int int[5]()`进行开辟一个指针，这个数组的前面四个元素进行初始化，后面的元素默认是0，同时`delete`只能删除`new`出来的指针

##### `namespace`&`using`
- 关于命名空间的嵌套
  - 假如：你在`namespace A`中嵌套一个`namespace B`嵌套并不意味着继承，你不能够直接修改嵌套类型的内容，同时，你可以通过`B::k`来对`B`中的`k`进行修改。
- 关于优先级
  - 自身空间中声明的变量的优先级高于外界引入的变量的优先级
  - 自身空间中声明变量的优先级等同于引入的内嵌空间的变量（会产生歧义）
- 关于`using`
  - `using namespace std`:引入某个空间中的所有内容
  - `using std::cout`:引入某个空间中的某个函数
  - `using Myvec = std::vector<int>`:重命名别名`typedef int MyInt;`,`typedef int matrix[3][3];`,`typedef void(*fun)(int,int)`;

##### `const`&`reference`&`r(l)value`
```c++
  const int a = 10;
  int *ptr = &a;//这里会导致错误因为使用ptr可以改变const的值(在C中只是Warning,但是在c++中就是Error)
  int *ptr2 = const_cast<int*>(&a);//强制转换成为int*
  *ptr2++;//UB本质上不能够改变const的数值
  const int a = 10;
  int &b = a;//Error!
  int &b = const_cast<int &>(a);
  b++;//UB
  int arr[10];
  int (&arrRef)[10] = arr;
  int arr_2[3][5];
  int (&two_dimension_arr)[3][5] = arr_2;//注意：不存在引用的指针，但是存在指针的引用
```
- `const int/int const *ptr`底层const，指针可变，但数据不可变，`int *const ptr`顶层const，指针本身不可变，但数据可变.
- 在`const`函数中`this`指向的对象被加上了顶层`cosnt`。数据是可变的，但是指向对象是不可变的。`const`对象只能调用`cosnt`函数，但是非`const`对象可以调用`cosnt`函数。
- 引用不能够移动，同样的`const`类型的也不能够移动。
- 关于左右值
  1. `i++`是右值，`++i`是左值
  2. `ptr`是一个指针，那么`*ptr`是左值，同时`*&ptr`是左值，但是`&*ptr`是右值（返回的地址并不是原来的地址）
  3. `"hello"`是右值
  4. 左值引用和右值引用是有范围限定的，如果将右值引用传入一个函数中，那么此引用将从右值引用变成左值引用，同时你也可以在函数中写上它的引用
  5. 引用不能够重新绑定对象，使用`const std::string &`绑定的右值的生命周期会变长，但是如果使用`cosnt std::string&`绑定之后不能够进行`std::move()`的操作（也就只能进行复制操作）

##### `void*`与`nullptr`
和C语言不同，在c++中`void*`指针确实能够接受任何类型的转换，但是不能够隐式转换成为任何其他类型，需要显示转换。相反`nullptr`能够隐式转换成为任何类型的指针。怎么才能将一个`const int*`转换成为`void*`，首先需要`const_cast<int*>`然后再`static_cast<void*>`

##### `auto`
- 只有在`auto &`,`auto *`的情况的时候才会保留`const`（底层）
- 同样的`auto`不会保留引用，会自动进行复制构造。（但是如果是使用`auto &`的话会保留引用（以及相关的移动构造，同时还会保留`const`））
- `auto str = "hello"`中`auto`是`const char*`
- `decltype(x) y = 10;`如果`x`是`int`则会有`int y = 10;`如果`x`是`double`则会有`double y = 10;`但是如果`decltype(foo(x))`这里的`foo`函数并不会被调用，这里完全是计算机基于代码推测的。（也就是说显示的返回什么他就会推导出什么）

##### `string`and`vector`

```cpp
  std::string s1;
  std::string s2 = "Hello";   //s2("Hello")\s2{"Hello"}
  std::string s3 = s2;  //deep copy
  std::string s5(5, 'a');   // "aaaaa"
  const char* cstr = "Hello World";
  std::string s6(cstr, 5);  // "Hello"
  std::string s7(cstr.begin(), cstr.begin() + 5);
```
- string能够和`char`连接，也能够和`c`风格的字符串连接，但是一定要注意连结性，c语言的字符串之间不能够相互连接。
- 在C++中`a+=b`是直接在字符串后面`append`新的字符串。但是如果`a = a+b`那么表示的是首先拷贝一遍`a`再将`b``append`到后面最后再拷贝回`a`（速度很慢）
- 使用`for(char s :str)`来进行循环，同样的`vector`中也可以使用相关的进行循环
  ```cpp
  std::vector<std::vector<int>> vvi; // An empty vector of vector of `int`s.// "2-d" vector
  std::vector<int> v3(10);  //A vector of ten `int`s ,all initialized to 0;
  std::vector v5(10);   //Error!
  std::vector v6(10,42);  //OK,Initialized to 42
  std::vector<int> v{2,3,5,7};
  std::vector<int> v2 = v;  //`v2` is a copy of `v`(deep copy)
  std::vector<int> v3(v);   //Equivalent
  std::vector<std::vector<double>> matrix(n,std::vector<double>(m,0.0));//创建二维数组
  ```
- `v.size()`,`v.empty()`,`v.clear()`
- `v.back()`and `v.front`retruns the **Reference** to the last element
- `v.at(Index)`returns the **Reference** element of the index.
- `v.front`,`v.back`,`v[]`,`v.pop_back()`,`v.pop_front`这一些操作都是基于迭代器`v.begin()`,`v.end()-1`而实现的，因此不存在越界检查，如果是存在为空容器的情况，会导致未定义的行为
- `v.resize(size_type n,const value_type& val)`,`n`表示目标大小，表示调整之后`vecotr`中的元素的个数。`val`如果大小大于当前大小新增元素将用该初始值初始化。
- `v.reserve()`预存一定的空间，表示的是为还没有储存内容的`vector`先预存一定的内容，如果`v.capacity<n`会分配内存使得其至少装得下n,如果`v.capacity>=n`不会做其他操作
- `push_back/front(const T& value)`在vecvtor的末尾在添加一个元素`value`
- `push_back/front(T&& value)`用右值的形式在`vector`的末尾添加一个元素
- `empalce_back()`在末尾原地构造一个元素
- `insert(iterator position,const T& value)`在指定的`posirion`处添加一个元素`value`返回指向新元素的迭代器。
- `insert(iterator position, InputIt first, InputIt last)`:在指定位置`position`处插入来自范围`[first,last)`,返回指向第一个新插入元素的迭代器。 
- `pop_back()`删除`vector`末尾的元素，没有返回值
- `v.erase(it pos)`,`v.erase(it first,it last)`返回一个迭代器，指向最后一个被删除元素之后的一个元素。(注意在`string`中还存在`s.erase(pos,len)`从`pos`开始的`len`个字符)
- `auto it = std::find(v.begin(),v.end(),n)`(注意这一条在`string`中直接写成`size_t = s.find("hello")`)
- `vector`的扩容策略
  - `vector`会申请一块更大的连续内存空间，常见的增长策略是当前容器的容量的两倍。
  - 元素的拷贝或者是移动：
  1. 如果类型支持移动语义（c++11以上），优先使用移动构造函数
  2. 否则使用拷贝构造函数进行复制
  - 然后释放先前的内存地址

##### `map`and`set`and`pair`
```cpp
  auto p = std::make_pair(42, "GPT");//std::pair<int, std::string> p = {1, "hello"};
  auto [first,last] = p//结构化绑定，解构pair
  std::cout << p.first << " " << p.second;
  std::set<int,Cmp(可以省略)> s; s.insert(2)//不会重复添加，同时set也可以for(int x:s){std::cout<<''}
  auto it = s.find(20);//找到了返回相关的it没找到返回.end()//.count(key)
  std::map<int,std::string> m;//m[7] = "banana"(添加或者是修改值)//m.erase(key/iterator/（begin,end）)删除键值对
  m.insert({2,"banana"})//m.insert(std::make_pair(3,"cherry"))//m.emplace(4,"apple")
  for(const auto &kvpair : counter)
  std::cout<< kvpiar.first << ...<< kvpair.second << std::endl;
  for(const auto &[word,occ]:counter)
  std::cout<<word << std::endl <<occ<<std::endl;
```

##### `lambda`
1. 如果要将所有的外部的副本全部传递进来，应该使用`[=]{}`
2. 如果要将外部的所有的变量都引用调入则应该使用`[&]`

##### 函数值重载
构成重构：1.形参个数不同2.形参类型不同3.形参类型的顺序不同

几个常见的不能够构成函数重载的情况：1. 返回值的类型不同 2.传入的参数类型是有无`const`的区别 3. 只有函数的默认值不同
- 函数重载的优先级
1.精确匹配（Exact Match）包括**隐式转换**（如数组退化为指针、函数退化为函数指针等）匹配。2. 提升转换（Promotion）3. 用户自定义转换（User-defined Conversion）

- 一个`const`对象最好不要够通过`const_cast<>()`来进行转化之后再来调用非`const`的重载函数。（要保证其不是一个常量，否则会导致未定义行为）

##### class
- 三五
  1. 防止自复制的时候应该写`this!=&other`而不是`*this!=other`
  2. 移动赋值函数的时候记得释放原来内存`delete[] storage;`
  3. 构造函数的`explicit`以及移动构造函数与移动赋值运算符的`nonexcept`
  4. `Base() = default;`,`Base() = delete;`
  5. 通过传入一个副本(根据传入的左值和右值的情况分别调用移动构造函数和拷贝构造函数来创建副本)然后再结构体中使用`swap(other)`的满足移动构造也满足赋值构造。
  6. 如果自己定义了某个函数，那么编译器将不会自动生成其功能的其他的函数（例如定义了构造函数，那么编译器不会自动生成默认的移动构造函数和拷贝构造函数）但是析构函数除外，一个类不能够不存在析构函数。
  7. `const`和引用类型的初始化都应该在初始化列表中进行不能够再函数体内部进行
  8. 默认的移动操作，每一个对象都进行`std::move`的行为，能移动的就移动移动不了的就拷贝
- `static`&`friend`&`cosnt`
  - `public`的`static`变量（函数）的初始化**一定只能够在类的外部(除非使用`inline`函数)**，同时使用`static`虽然可以通过实例访问，但是建议通过`ClassName::static_xxx`来进行访问
  - `static`的成员函数中可以调用`static`变量，但是不能调用其他的成员变量，同时在`static`函数中不存在`this`指针。
  - 友元函数和友元类的声明可以放在类的`public`,`private`,`protect`中，效果相同
  - 友元关系是单向的，且不能够被`override`
  - 在一个`const`的成员函数中`this`的类型为`A* cont`(顶层的`const`)这时候的获得的所有的成员的类型都是其`const`类型
  - 但是如果是直接在类外部添加`const`类型那么就会导致添加的是一个底层`const`,也就是`const A`（底层`const`不能修改内容，但是可以重新指向）
- 重载运算符
  - 不能够重载的：`.`,`::`,`?:`,自创的符号
  - 重载运算符并不会改变原有的优先级以及连结关系
  - 要声明在类内部：`+=`,`-=`,`->`,`*`,`[]`,`()`，类转换;要声明在类外部(友元函数):`+`,`==`,`<<`.
  - 尽管在`bool`转换类型函数中声明了`explicit`如果在`if()`等逻辑运算语句中也会被隐式转换成为`bool`类型。
```cpp
  Rational &operator++(){num++;return *this;}
  Rational &operator++(int){auto = *this,++*this,return temp;};
  Rational &operator*()const{reutrn *ptr;}
  Rational &operator->()const{return std::adress(operator*());}
  operator double()const{return num*1.0;}
  std::ostream &operator<<(std::ostream &os,const Rational &r){return os<<num;}
  std::istream &operator>>(std::istream &is,Rational &r){int num;is>>num;r = Rational(num);return is;}
```
##### Iterator
- 1.前向迭代器（`std::forward_list`）2. 双向迭代器（`std::map/set/list`）3.随机访问迭代器（`std::vector/deque`）4.反向迭代器：`c.rbegin()`,`c.rend()`，`c.crbegin()`,`c.crend()`,同时`++`,`--`在反向迭代器上都是反的
- `const_iterator`:`c.cbegin()`,`c.cend()`返回的对象都是`const`类型`const T&`而不是`T &`因此无法使用其修改元素的值。
- `std::copy(v.begin()),v.end(),std::back_inserter(v);`插入迭代器，调用`push_back()`语句将内容不断放入容器的末尾。
- `std::make_move_iterator(words.begin())`移动迭代器，使得每一个被解引用得到的内容都是右值而非左值。
- `std::distance(first,last)`返回`first`和`last`之间存在多少个元素(`last`不被包括)，这个所有的迭代器都支持，但是`it2-it1`仅仅在随即迭代器中支持


##### smart_ptr
```cpp
  auto ptr2 = std::shared_ptr<int>(rawPtr);   //可以复制构造
  std::unique_ptr<int> ptr1(new int[4]{1,2,3,4}); //初始化1，2，3，4
  auto ptr2 = std::make_unique<int[]>(4);   //更推荐,但不能够初始化
  auto ptr1 = std::make_shared<int>(42);
  std::unique_ptr<std::unique_ptr<int[]>[]> matrix(new std::unique_ptr<int[]>[rows]);
  auto matrix = std::make_unique<std::unique_ptr<int[]>[]>(rows);
```
- 使用`ptr.reset(new int[N]{})`来进行释放原来的内容然后再储存新的内容。
- 这是一个转发参数，将其类型完美转发给前面`<>`的内容来进行构造一个内容指向`ptr`

##### `sort`,`copy`,`swap`
```cpp
  void sort(RandomIt first, RandomIt last, Compare comp);//默认是升序排列
  OutputIt copy(InputIt first, InputIt last, OutputIt d_first);//算法不会自动调节容器大小，所以保证有足够空间储存copy的内容
  std::swap(a, b);//不能够交换const类型的对象，只能交换引用对象的值，但是能交换指针指向的地址
```

##### `inherent`
- 一般继承
  - 构造函数：先构造父类后构造子类（应该在初始化列表中进行构造）；析构函数：先析构子类后析构父类。
  - 如果在基类中没有定义的构造函数/析构函数会默认生成一个（如果自己已经定义，那么默认构造函数将会被禁用），如果无法生成或者是被禁用默认的构造函数（**例如引用对象不能够生成默认的构造函数，`const`对象不能够生成默认的构造函数**）或是被禁用的情况都会导致报错
- 多态与`Upcasting`：
  - 构造函数不能写成虚函数
  - 析构函数在多态使用的情况下必须写成虚函数，子类的`override`可以省略（**原因：如果没有写写成虚函数则只会调用基类的析构函数导致内存泄露，写成了虚构函数则会先调用子类的析构函数再调用父类的虚析构函数**）
  - 在`upcasting`的情况下子类依然可以通过虚构函数来调用子类的函数
- 继承是可以传递的，但是继承关系不包括继承友元关系
- `Dynamic_cast<Target>(expr)`
- 纯虚函数
  - 只能够通过子类对象的声明来完成对他构建实例化
  - 抽象类中一样可以定义非纯虚函数，同时也可以定义成员变量，但是纯虚函数的传参等等都要通过子类进行（通过多态实现）
