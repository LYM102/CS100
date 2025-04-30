# C++_benning_2
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
- 通过定义一个`discountedItem`这个类，每一个`DiscountedItem`这个类中都存在一个它对应的父类`Item`
- 所有的成员变量和成员函数,(除去构造函数和析构函数)，都继承自父类

- 同样的我们有一些需要注意的内容：
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
  - 如果不显示调用基类的构造函数，会调用基类的默认构造函数
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
if `D` is a subclass of `B`
`B`的指针可以指向`D`,同样的`B`的引用也可以指向`D`:
```c++
DiscountedItem di = someValue();
Item &ir = di;
Item *ip = &di;
```c++
void printItemName(const Item &item) {
  std::cout << "Name: " << item.getName() << std::endl;
}

DiscountedItem di("A", 10, 2, 0.8);
Item i("B", 15);
printItemName(i);  // "Name: B"
printItemName(di); // "Name: A"
```
`const Item &item`can be bound to either an `Item` or a `DiscountedItem`.

但是虽然是`DiscountedItem`但是你如果是使用`Item`的指针进行传递，那么你的可见范围就只存在于父类当中。

同样的，也可以定义一个外部函数接受的是一个`const Item &it`,那么你在传入的时候既可以传入`Item`，同样也可以传入`DiscountedItem`,这两者都可行。但是如果是传入的子类的部分，可见范围也只有父类的部分

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
要覆盖（覆写）一个虚函数：
- 函数参数列表必须与基类版本的参数列表相同。
- 返回类型应与基类中对应函数的返回类型相同（或协变 ）。
  - 我们将在后续的课程或辅导课中讨论“协变”。 
- 常性（const 修饰）必须相同！

为确保你确实在覆盖虚函数（而不是创建一个重载版本），请使用 `override` 关键字。

* 不要与“重载”混淆。 

一个覆盖函数也是虚函数，即使没有显式声明。

```cpp
class DiscountedItem : public Item {
    virtual double netPrice(int cnt) const override; // 正确，显式声明为虚函数
};
class DiscountedItem : public Item {
    double netPrice(int cnt) const; // 也正确，但不推荐
};
```

`override` 关键字让编译器检查并报告函数是否并非真正的覆盖。

[最佳实践] 要覆盖虚函数，显式写出 `override` 关键字。`virtual` 关键字可以省略。 

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
在上述函数中，形参 `item` 的静态类型是 `const Item` ，这在编译时就确定了。但在程序运行时，传递给该函数的实参可能是 `Item` 类对象，也可能是从 `Item` 派生的 `DiscountedItem` 类对象等。所以直到运行时，才能知道 `item` 所代表对象的动态类型到底是什么。

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

### Slicing
Dynamic binding only happens on references or pointers to base class.
```c++
DiscountedItem di("A",10,2,0.8);
Item i = di;
auto x = i.netPrice(3);
```
`Item i = di;`calls the copy constructor of `Item`
- but Item 's copy constructors handles only the base part.
- so discountedItem's own members are ignored of sliced down 
- i.netPrice(3) calls `Item::netPrice`
### Downcasting
```cpp
Base *bp = new Derived{};
```
这里创建了一个基类 `Base` 指针 `bp`，并让它指向一个派生类 `Derived` 对象。在C++ 中，这种通过基类指针指向派生类对象是多态的常见用法。

-  面临问题
   - **成员访问限制**：虽然 `bp` 实际上指向一个派生类对象，但仅通过 `bp` 直接访问派生类 `Derived` 特有的成员是不被允许的 。因为从类型系统角度看，`bp` 是基类指针，编译器只知道它指向基类对象，不清楚派生类特有的成员。
   - **向下转型需求**：所以就引出了如何进行 “向下转型” 的问题。向下转型是指将基类指针或引用转换为派生类指针或引用，以便能访问派生类特有的成员。但直接转换存在风险，因为如果转换错误（比如实际上指向的不是派生类对象 ），会导致未定义行为，因此需要使用合适的转换方式，如 `dynamic_cast`（用于有虚函数的类层次结构 ）、`static_cast`（需确保类型转换的正确性 ）等。  

### Polymorphic class(多态类)
#### 多态类定义
一个类如果（声明或继承）至少有一个虚函数，就被称为多态类 。这里的虚函数可以是普通的虚成员函数，也可以是虚析构函数。比如，只要类中存在 `virtual void func();` 这样的普通虚成员函数，或者 `virtual ~ClassName();` 这样的虚析构函数，该类就是多态类。 

#### 派生类相关特性
- **多态继承性**：如果一个类是多态类，那么从它派生出来的所有类也都是多态类 。这是因为在C++ 中，无法拒绝继承成员函数，虚成员函数自然也会被继承。例如，基类 `Base` 是多态类，有虚函数 `virtual void baseFunc();` ，派生类 `Derived` 继承 `Base` 时，会自动继承这个虚函数，所以 `Derived` 也是多态类。
- **析构函数特性**：若基类的析构函数是虚函数，那么派生类的析构函数也必须是虚函数 。这是为了保证在通过基类指针删除派生类对象时，能正确调用派生类的析构函数，妥善释放派生类对象资源，避免内存泄漏等问题。 

### Dynamic_cast<>转换
#### 转型语法
`dynamic_cast<Target>(expr)` ，其中 `Target` 必须是引用或指针类型 。它用于将表达式 `expr` 转换为 `Target` 类型。

```cpp
Base *bp = new Derived{};
Derived *dp = dynamic_cast<Derived *>(bp);
Derived &dr = dynamic_cast<Derived &>(*bp);
```
- 首先创建了基类 `Base` 指针 `bp` 并指向派生类 `Derived` 对象。
- 然后使用 `dynamic_cast` 将 `bp` 转换为派生类指针 `dp` ，以及将 `*bp` 转换为派生类引用 `dr` 。

#### 工作原理及结果
- **运行时类型识别（RTTI）**：`dynamic_cast` 会在运行时执行类型识别（RTTI）来检查表达式的动态类型 。
- **转换成功情况**：如果表达式的动态类型是 `Derived` ，或者是 `Derived` 的（直接或间接 ）派生类，那么向下转型成功。
- **转换失败情况**：如果转型失败，当 `Target` 是指针类型时，`dynamic_cast` 返回空指针；当 `Target` 是引用类型时，会抛出 `std::bad_cast` 异常 。 这样能在一定程度上保证类型转换的安全性，避免因错误转换导致的未定义行为。 

#### 效果
使用`dynamic_cast`转换的指针在转换成功的情况下不会截断， 同时可以将指针转换为一个引用的原因是，基类指针指向派生类的时候，通过`dynamic_cast`进行引用转换（`Derived &dr = dynamic_cast<Derived &>(*bp)`）本质上是让引用`dr`成为派生类对象的别名

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
只能够通过子类对象的声明来完成对他构建实例化

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

##### 示例代码解释

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

##### 示例代码解释

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
