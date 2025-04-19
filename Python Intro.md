# Python 笔记精要（期中）
> by YiMing Li
---
## 基础知识：
1. 保留小数的做法：
    - `round`函数方法：
    `round(round_num,num_digits)`,`round_num`表示的是需要四舍五入的数字,`num_digitis`表示的是需要精确的位置。
    ```python
        # 四舍五入到整数
        print(round(3.6))  
        # 输出: 4

        # 保留指定小数位数
        print(round(3.1415926, 2))  
        # 输出: 3.14

        # 对整数进行四舍五入
        print(round(12345, -2))  
        # 输出: 12300

        # 特殊情况，当小数部分恰好为0.5时，round函数会将数字舍入到最接近的偶数
        print(round(2.5))  
        # 输出: 2
        print(round(3.5))  
        # 输出: 4
    ```
    - 格式化输出方式：
    ```python
        num = 10.798641599795182

        print("%.3f" % num) # 10.799 四舍五入
        print(f"{num:.3f}") # 常用
    ```
    两者的区别：
    1. `round` 方法在保留`0.5`结尾的小数时候存在问题
    2. `%.3f `方法会自动占三位小数，如果是`num = 10.5`，`print("%.3f" % num)`则会导致答案为`10.500`
2. `decimal`模块：
    ```python
    from decimal import Decimal

    # 从整数创建
    num1 = Decimal(10)
    # 从字符串创建，推荐使用字符串来避免精度问题
    num2 = Decimal('0.1')
    num3 = Decimal('0.2')
    print(num2+num3)
    ```
    - 注意： `decimal`的里面传入的一定是字符串。同时这个不是``int``或者是`float`的类型，而是`decimal`的类型（可以转化成为`int,float`）
3. **字符容器**（重点部分）
    知识点全览：

    | 名称 | list | turple | str | set | dict |
    | :----: | :----: | :----: | :----: | :----: | :----: |
    | 元素要求 | 没有要求 | 没有要求 | 只能是字符串 | 没有要求 | key:除了字典;value:任意字符串 |
    | index | T | T | T | F | F |
    | repeatale | T | T | T | F | F |
    | reversable | T | F* | F | T | T |

    ---
    *:如果是元组中的列表也是可以进行修改的

    1. `list`:
        - `append`和`extend`的区别：`append`表示的是将它作为一个元素添加到后面。而`extend`是将列表整合。
        - `clear()`方法，`my_list.clear()`清空列表
        - `my_list.insert(index_1,elememt)`表示在`index_1`之后插入`element`
        - `list`的整合
            ```python
            my_list = [1,2,3,4,5]
            print(my_list[1:4]+my_list[2:3]*2)


            my_list = (1,2,3,4,5)
            print(my_list[1:4]+ my_list[2:3]*2)
            ```
            输出:`[2,3,4,3,3];(2,3,4,3,3)`
        - `remove`方法：`reomve(element)`表示的是移除第一个满足要求的`element`
        - `pop`方法：`pop([index])`表示的是取出（注意在集合中的`pop`表示的就是随机删除）
        -  `del my_list[2]`表示删除特定的元素
    2. `str`:
        - `relpace(num_1,num_2)`得到一个新的字符串
        - `strip()`方法：将前后的换行符和空格删除


    上面的都可以进行切片处理

    ---

    3. `set`:
        - `my_set.add()`方法：添加一个新的元素
        - `my_st.remove()`方法：移除一个元素
        - 集合的计算：
        ```python
        set1 = {1,2,3}
        set2 = {1,5,6}
        set3 = set1.difference(set2) # 集合1有但是集合2没有
        set4 = set1.union(set2)# 集合的并集（去重）
        ```
        - `remove()`方法：同上
    4. `dict`:
        - 对于字典而言我们可以获得它的keys或者是value可以使用`my_dict.keys()`;`my_dict.value()`;需要用list()函数将他转换成列表的形式
        - 同样的使用`my_dict.items()`方法的时候可以获得键值对，但是是`iter`类型，所以还要转化成为`list`
        - 注意在字典转化成为其他的数据类型的时候只能转化他的`keys`的部分
        - 通过`value` 找 `key`:
        ```python
        my_dict = {'a': 1, 'b': 2, 'c': 3, 'd': 2}
        target_value = 2
        keys = [key for key, value in my_dict.items() if value == target_value]
        print(keys)  
        ```
        - 通过`key`,找`value`：
        ```python
        my_dict = {'name': 'Alice', 'age': 25, 'city': 'New York'}
        print(my_dict.get('name'))  
        print(my_dict.get('gender', 'unknown'))
        ```  
        - **合并字典**
        - 可以使用`**`运算符来合并多个字典。例如，有两个字典`dict1 = {'a': 1, 'b': 2}`和`dict2 = {'c': 3, 'd': 4}`，可以使用`{**dict1, **dict2}`来合并这两个字典，得到`{'a': 1, 'b': 2, 'c': 3, 'd': 4}`。不过需要注意的是，如果有相同的键，后面字典中的键 - 值对会覆盖前面字典中的键 - 值对。
        - 示例代码：
        - ```python
            dict1 = {'a': 1, 'b': 2}
            dict2 = {'c': 3, 'd': 4}
            combined_dict = {**dict1, **dict2}
            print(combined_dict)  
            # 输出: {'a': 1, 'b': 2, 'c': 3, 'd': 4}
            ```
        - `del my_dict[key1]`删除键值对
        -  `pop(keys)`删除键值对
    5. `count()`方法：
        `___.count(element)`:只有字典和集合（不重复）没有这个方法
    6. `sourt()`方法：
        `____.sourt(key = ,reverse = )`
        `____ = sourted(____,key = ,reverse = )`
    7. 推导式：
        - **列表推导式**（List Comprehension）是一种简洁且高效的创建新列表的方法。它允许你在一行代码中创建新的列表，同时可以包含条件判断和其他逻辑。

            **基本语法**

            列表推导式的语法如下：

            ```python
            new_list = [expression for item in iterable if condition]
            """
            其实使用方括号表示的就是创建一个新的list
            """
            expression：对每个元素执行的操作。(注意这个操作也可以是:[e,e**2]这样的一个列表,也可以是一个方法例如:len(x))
            item：当前迭代到的元素。
            iterable：可迭代的对象，如列表、元组、字符串等。
            if condition：可选的条件判断语句，只有满足条件的元素才会被添加到新列表中。
            ```
            示例

            假设有一个列表 numbers，我们想创建一个新的列表，其中包含原列表中所有偶数的平方：

            ```python
            numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
            squares_of_even_numbers = [x ** 2 for x in numbers if x % 2 == 0]
            print(squares_of_even_numbers)  # 输出 [4, 16, 36, 64, 100]
            ```
            更复杂的示例

            假设有一个字典 my_dict，我们想创建一个列表，包含字典中所有值大于 10 的键：

            ```python
            my_dict = {"a": 5, "b": 15, "c": 10, "d": 20}
            keys_with_large_values = [key for key, value in my_dict.items() if value > 10]
            print(keys_with_large_values)  # 输出 ['b', 'd']
            ```
            多重循环

            列表推导式还可以包含多重循环：

            ```python
            matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
            flattened_matrix = [item for row in matrix for item in row]
            print(flattened_matrix)  # 输出 [1, 2, 3, 4, 5, 6, 7, 8, 9]
            ```
            多说一嘴:`row`表示的是列表当中的每一个新的数据容器
            ```python
            matrix = [[1, 2, 3], "456", (7, 8, 9),{"10":1,"11":2,"13":3},[14,15],[16]]
            flattened_matrix = [item for row in matrix for item in row]
            print(flattened_matrix)  # 输出 [1, 2, 3, '4', '5', '6', 7, 8, 9, '10', '11', '13', 14, 15, 16]
            ```
            这么写都可以,你会发现只要是数据容器就可以.如果其中有一个是某一个元素,就会报错
            ```python
            matrix = [[1, 2, 3], "456", (7, 8, 9),{"10":1,"11":2,"13":3},[14,15],16]
            flattened_matrix = [item for row in matrix for item in row]
            print(flattened_matrix)  # 输出 报错!!
            ```
            注意:上面的`item`,`row`都不是固定的,你可以使用你自己定义的变量来完成
            ```python
            matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
            flattened_matrix = [item for y in matrix for item in y]
            print(flattened_matrix)  # 输出 [1, 2, 3, 4, 5, 6, 7, 8, 9]
        - 字典推导式    
        ```python
            # 从列表创建字典
            numbers = [1, 2, 3, 4, 5]
            squares = {x: x**2 for x in numbers}
            print(squares)  # 输出 {1: 1, 2: 4, 3: 9, 4: 16, 5: 25}

            # 使用条件语句
            even_squares = {x: x**2 for x in numbers if x % 2 == 0}
            print(even_squares)  # 输出 {2: 4, 4: 16}   
        ```
        ```python
        my_dict = {"abc": 1234, "bdfaa": 322, "fscg": 312345}
        my_keys = sorted(my_dict.keys(),key=lambda x:len(x))#这里的key传入的是一个排序的参考的函数,根据这个函数所要求的顺序对字典进行排序
        print(my_keys)
        my_value = sorted(my_dict.values(),key=lambda x:10000-x)#也就是根据每一个1000-x的答案进行排序
        print(my_value)
        # 同样的对于一个键值对,我们如果传入比较的参数时它的value那么不久表明我们按照value的值来进行排序
        my_dict_item = sorted(my_dict.items(),key = lambda x :x[1],reverse=True)
        print(my_dict_item)
        my_dict_new = {key:value for key,value in my_dict_item}#for 循环的写法
        print(my_dict_new)
        ```
        ```python
        my_keys = [1,2,3,4,5]
        my_values = ['a','b','c','d','e']
        my_dict = {keys:value for keys,value in zip(my_keys,my_values)}
        print(my_dict)
        ```
    8. 元组命名法
    方法一：直接返回元组
        最简单的方法是直接在函数中返回一个元组。

        ```python
        def get_name_and_age():
            name = "Alice"
            age = 30
            return name, age  # 返回一个元组

        # 调用函数并解包元组
        name, age = get_name_and_age()
        print(f"Name: {name}, Age: {age}")  # 输出 Name: Alice, Age: 30
        ```
        方法二：显式返回元组

        你也可以显式地创建一个元组并返回。

        ```python
        def get_name_and_age():
            name = "Alice"
            age = 30
            return (name, age)  # 显式返回一个元组

        # 调用函数并解包元组
        name, age = get_name_and_age()
        print(f"Name: {name}, Age: {age}")  # 输出 Name: Alice, Age: 30
        ```
        方法三：返回多个值并解包

        即使函数返回的是一个元组，你也可以在调用时直接解包。

        ```python
        def get_name_and_age():
            name = "Alice"
            age = 30
            return name, age  # 返回一个元组

        # 调用函数并解包元组
        result = get_name_and_age()
        name, age = result
        print(f"Name: {name}, Age: {age}")  # 输出 Name: Alice, Age: 30
        ```
        方法四：使用命名元组（NamedTuple）

        为了使返回值更具可读性和自解释性，可以使用 collections.namedtuple。

        ```python
        from collections import namedtuple

        # 定义一个命名元组
        Person = namedtuple('Person', ['name', 'age'])

        def get_person_info():
            name = "Alice"
            age = 30
            return Person(name, age)

        # 调用函数并解包命名元组
        person = get_person_info()
        print(f"Name: {person.name}, Age: {person.age}")  # 输出 Name: Alice, Age: 30
        ```

    - 字典和集合中 `in` 查找更快的原因
    - 当使用`in`关键字在字典或集合中查找元素时，实际上是在查找键。对于字典，由于键是通过哈希值来快速定位的，不需要像列表那样逐个元素比较。它直接根据键的哈希值就能快速找到对应的存储位置，然后判断该位置上的键是否是要查找的键。集合也是类似的原理，集合中的元素就相当于字典中的键，通过哈希函数快速定位元素是否存在。这种基于哈希的查找方式，时间复杂度接近常数时间O1，而列表的查找时间复杂度是On，其中是列表的长度，所以字典和集合中的in查找更快。
    9. 拷贝：
    `[:]`：浅拷贝；`import copy | copy.copy(my_list)`
    `copy.deepcopy(my_list)`深拷贝
4.  函数
    1. 函数的多返回值：
    ```python 
    def name():
        print("注意函数有多个返回值")
        return 1, "第二个返回值", True


    x, y, z = name()
    print(x, y, z)
    ```
    2. 关键字传参
    3. `**kwargs,*args`的传参方式
    ```python 
    def my_function(*args, **kwargs):
        print("非关键字参数:")
        for arg in args:
            print(arg)
        print("关键字参数:")
        for key, value in kwargs.items():
            print(f"{key}: {value}")

    my_function(1, 2, 3, name='Alice', age=25)
    ```
    4. 闭包
    ```python
    def outer_function(param1):
        def inner_function(param2):
            return param1 + param2
        return inner_function

    # 创建一个闭包
    add_five = outer_function(5)

    # 调用内层函数
    result = add_five(10)
    print(result)  # 输出: 15
    ```
    在这个例子中：
    - `outer_function` 接受一个参数 `param1`，并返回一个内层函数 `inner_function`。
    - `inner_function` 接受一个参数 `param2`，并返回 `param1 + param2`。
    - `add_five` 是 `outer_function(5)` 的结果，它是一个闭包，记住了 `param1` 的值为 5。
    - `add_five(10)` 调用 `inner_function`，传入 `param2` 为 10，返回 15。
    5. 装饰器
    ```python
    import time

    def timer(threshold):
        def actual_decorator(func):
            def wrapper(*args, **kwargs):
                start_time = time.time()
                result = func(*args, **kwargs)
                end_time = time.time()
                execution_time = end_time - start_time
                if execution_time > threshold:
                    print(f"{func.__name__} execution time: {execution_time} seconds")
                return result
            return wrapper
        return actual_decorator

    # 使用装饰器语法糖
    @timer(0.2)
    def sleep_04():
        time.sleep(0.4)

    # 等价的函数调用
    def sleep_04_original():
        time.sleep(0.4)

    sleep_04_decorated = timer(0.2)(sleep_04_original)

    # 调用装饰后的函数
    sleep_04()
    sleep_04_decorated()
    ```
5. OOP
    ```python
    class MyDate:
        def __init__(self,year,month):
            self.year = year
            self.month = month
            self.day = display
        def __repr__(self):
            return f"mydate{self.year},{self.month}"
        def __eq__(self,other):
            print('__eq__ is called')
            if not isinstance(other,MyDate):
                # 判断两者的类别是否相同
                return False
            
            return self.year == other.year and self.month == other.month

    my_date_1 = MyDate(2024,11)
    my_date_2 = MyDate(2024,11)
    my_date_3 = my_date_1
    # 解释一下：这样的一种赋值的方式表示的是
    # 将my_date_1的对象的地址
    # 复制到my_date_3上面
    print(my_date_1 == my_date_2) # false
    print(my_date_1 == my_date_1) # True
    # '=='其实是调用__eq__的内容
    # 但是我们在对于面对对象的比较的时候不要使用‘==’，我们建议使用‘is’
    print(my_date_1 is my_date_1) # True
    print(my_date_1 is my_date_2) # Flase
    print(my_date_1 is my_date_3) # True
    ```
    ```python
    class Student:
        def __init__(self, name, age):
            self.name = name
            self.age = age

        def __lt__(self, other):
            return self.age == other.age

        """
            __lt__ 是一个特殊方法，用于定义对象之间的“小于”关系。
            如果再最后使用<符号来进行比较的话会调用这个方法
            self 是当前对象，other 是另一个 Student 对象。
            实际上这里使用的是判断两者是否相等
        """


    stu_1 = Student("Liyiming", 18)
    stu_2 = Student("ZhouJieLun", 32)
    print(stu_1 < stu_2)
    ```
    ```python
    class Phone:

        __current_voltage = 0.5  # 私有的成员变量
        # 虽然不能被外部利用，但是可以被类中的使用

        def __keep_single_core(self):
            print("让CPU以单核模式运行")

        def call_by_5G(self):
            if self.__current_voltage >= 1:
                print("5G通话已经开启")
            else:
                self.__keep_single_core()
                print("电量不足不能使用5G通话,已经设置成为单核模式")


    phone = Phone()
    # phone.__keep_single_core()
    # print(phone.__current_voltage)
    phone.call_by_5G()
    ```
    ```python
    class Parent1:
        def render(self):
            print('parent 1')
        
        def hello(self):
            print('hello parent 1')

    class Parent2:
        def hello(self):
            print('hello parent 2')
        
        def render(self):
            print('parent 2')

    class Child(Parent2):
        def hello(self):
            Parent1.hello(self)
            # 建议使用设个方法调用父类的重名方法，或者是其他的类（不一定是父类）都可以

    if __name__ == '__main__':
        child = Child()
        child.render()
        child.hello()
    ```
    ```python
    class ParentClass:
    class_variable = "父类的类变量"

    def print_class_variable(self):
        print(self.class_variable)

    class ChildClass(ParentClass):
        pass

    # 子类实例可以访问父类的类变量
    child_obj = ChildClass()
    child_obj.print_class_variable()  
    print(ChildClass.class_variable)  

    class AnotherChildClass(ParentClass):
        class_variable = "子类重新定义的类变量"

    # 子类重新定义了类变量，优先使用子类的类变量
    another_child_obj = AnotherChildClass()
    another_child_obj.print_class_variable()  
    print(AnotherChildClass.class_variable)  

    # 通过super()访问父类的类变量
    print(super(AnotherChildClass, another_child_obj).class_variable)  
    ```
    ```
    输出：
    父类的类变量
    父类的类变量
    子类重新定义的类变量
    子类重新定义的类变量
    父类的类变量
    ```
## 课程代码：
1. 利用循环找到某个数据的三次方根
    ```python
    cube = int(input("Enter an integer: "))
    for guess in range(abs(cube)+1):
        if guess**3 >= abs(cube):
        break
    if guess**3 != abs(cube):
        print(cube, "is not a perfect cube")
    else:
        if cube < 0:
            guess = -guess
        print("Cube root of "+str(cube)+" is "+str(guess))
    ```
2. 利用guess-check方法来解决相关的计算题：
    ```
    Remember those word problems from your childhood?
     For example:
     Alyssa, Ben, and Cindy are selling tickets to a fundraiser
     Ben sells 2 fewer than Alyssa
     Cindy sells twice as many as Alyssa
     10 total tickets were sold by the three people
     How many did Alyssa sell?
     Could solve this algebraically, but we can also use
    guess-and-check

    ```
    ```python 
    for alyssa in range(11):
        for ben in range(11):
            for cindy in range(11):
                total = (alyssa +ben +cindy == 10)
                two_less = (ben == alyssa -2)
                twice = (cindy == 2*alyssa)
                if total and two_less and twice:
                    print(f"Alyssa sold {alyssa} tickets")
                    ···
    ```
    more efficient solution:
    ```python
    for alyssa in range(1001):
        ben = max(alyssa - 20, 0)
        cindy = alyssa * 2`
    if ben + cindy + alyssa == 1000:
        print("Alyssa sold " + str(alyssa) + " tickets")
        print("Ben sold " + str(ben) + " tickets")
        print("Cindy sold " + str(cindy) + " tickets")
    ```
3. 将十进制转化成为二进制：
    ```python
    x =0.625

    p = 0
    while ((2**p)*x)%1 != 0:
        print('Remainder = ' + str((2**p)*x - int((2**p)*x)))
        p += 1
    num = int(x*(2**p))

    result = ''
    if num == 0:
        result = '0'
    while num > 0:
        result = str(num%2) + result
        num = num//2
    for i in range(p - len(result)):
        result = '0' + result
    result = result[0:-p] + '.' + result[-p:]

    print('The binary representation of the decimal ' + str(x) + ' is ' + str(result))
    ```
4. 循环查找近似某个点的平方根
    通过循环：
    ```python
    x = 54321
    epsilon = 0.01
    numGuesses = 0
    guess = 0.0
    increment = 0.0001
    while abs(guess**2 - x) >= epsilon and guess**2 <= x:
        guess += increment
        numGuesses += 1
    print('numGuesses =', numGuesses)
    if abs(guess**2 - x) >= epsilon:
        print('Failed on square root of', x)
    else:
        print(guess, 'is close to square root of', x)
    ```
    牛顿-拉弗森算法：
    ```python
    epsilon = 0.01
    k = 24.0
    guess = k/2.0
    num_guesses = 0

    while abs(guess*guess - k) >= epsilon:
        num_guesses += 1
        guess = guess - (((guess**2) - k)/(2*guess))
    print('num_guesses = ' + str(num_guesses))
    print('Square root of ' + str(k) + ' is about ' + str(guess))
    ```
    二分法：
    ```python
    x = 0.5
    epsilon = 0.01
    if x >= 1:
        low = 1.0
        high = x
    else:
        low = x
        high = 1.0
    guess = (high + low)/2
    while abs(guess**2 - x) >= epsilon:
        if guess**2 < x:
            low = guess
        else:
            high = guess
        guess = (high + low)/2.0
    print(f'{str(guess)} is close to square root of {str(x)}')
    ```
6. 分式计算（辗转相除法）
    ```python
    class Fraction:
        def __init__(self,upper_num,down_num):
            self.up = upper_num
            self.down = down_num

        def __mul__(self,other):
            final_up = self.up*other.up
            final_down = self.down*other.down
            return Fraction(final_up,final_down)
        
        def __str__(self):
            return f"{self.up}/{self.down}"

    my_fraction1 = Fraction(1,2)
    my_fraction2 = Fraction(4,5)
    print(my_fraction1*my_fraction2)
    ```
    ```python
    class Fraction:
        def __init__(self,upper_num,down_num):
            self.up = upper_num
            self.down = down_num

        def __mul__(self,other):
            final_up = self.up*other.up
            final_down = self.down*other.down
            return Fraction(final_up,final_down)
        
        def __str__(self):
            def gcd(n,d):
                while d!=0:
                    (d,n) = (n%d , d)
                return n
            if self.down == 0:
                return None
            elif self.down == 1:
                return self.up
            else:
                greatest_common_divider = gcd(self.up,self.down)
                self.up = int(self.up/greatest_common_divider)
                self.down = int(self.down / greatest_common_divider)
            return f"{self.up}/{self.down}"
            # 辗转相除法

    my_fraction1 = Fraction(4,2)
    my_fraction2 = Fraction(4,1)
    print(my_fraction1*my_fraction2)
    ```
# 那些年我们哭过的痛
## 问题1:有关于函数函数的拷贝的问题: 2024/11/1
```python
# 主文件:
import subtask_7_1 as test7 #自定义第三方库
def piz(sequence_1=list(), sequence_2=list(), check_window=0, origine_type_1=list, origine_type_2=list):
    """
        然后是一些操作:最后的结果是导致sequnce_1和sequence_2的值变化
    """
    return list(zip(sequence_1,sequence_2))
```
```python
# 这是那个subtask_7_1的文件
def check(piz):

    sq11 = [5, 5]
    sq12 = [6, 6, 6, 6]

    res = piz(sequence_1=sq11)
    res = piz(sequence_1=sq12)

    ans = [(6, 0), (6, 1), (6, 2), (6, 3)]

    if res == ans:
        print("Accepted.")
    else:
        print("Wrong Answer.")
```
我在调试的过程当中发现:

- 我在第一次的调用`piz`的时候`sequence_1`变成了`[5,5]`,`sequence_2`变成了`[0,1]`;

- 但是当我第二次再调用`piz`的时候我发现,虽然我使用了默认值(`list()`),但是`sequence_2`的值仍然是第一次改动后的`sequnce_2 = [0,1]`.

### 但是
如果我将我的原来的函数变成:
```python
def piz(sequence_1=None, sequence_2=None, check_window=0, origine_type_1=list, origine_type_2=list):
    if sequence_1 is None:
        sequence_1 = []
    if sequence_2 is None:
        sequence_2 = []
```
这样改动之后我发现在我第二次传入的时候,`sequence_2`会变成一个空的列表,也就是说他不会将第一次改动之后的`sequence_2`传入到第二次调用函数的时候

**我觉得我两次的操作都是让`sequence_1`和`sequence_2`在没有特殊参数传入的时候变成一个空的列表但是为啥第一次种代码的书写会保留原来的改动后的`sequence_2`的值?**
## 解答:
```python
def test(my_list_1 = list(),my_list_2 = list()):
    my_list_1.append(1)
    my_list_2.append(2)
    print(my_list_1,id(my_list_1),my_list_2,id(my_list_2))

test(my_list_1 = [1,2,3,4])
test(my_list_2 = [2,3,4,5])
test()
test(my_list_1 = [1,2,3,4])
# [1, 2, 3, 4, 1] 2173618606400 [2] 2173621034880
# [1] 2173621034944 [2, 3, 4, 5, 2] 2173618606400
# [1, 1] 2173621034944 [2, 2] 2173621034880
# [1, 2, 3, 4, 1] 2173618606400 [2, 2, 2] 2173621034880
```
也就是说在我没有传入参数的时候如果使用的def test(my_list_1 = list())就会自动导致my_list_1到一个固定的id位置,然后我后续的操作也是会改变这个值的

我如果传入参数,那么就会到另外的一个固定的id值,不管我传入多少的参数,都会到另外的一个id位置
## 问题2: 有关于报错的相关内容
```python
try:
    b = 1/0
except:
    raise MemoryError("this is an error")
try :
    a = 1/0
except ZeroDivisionError as e:
    print(e)
# Traceback (most recent call last):
#   File "c:\Users\liyiming\Desktop\lecture\test.py", line 2, in <module>
#     b == 1/0
#     ^
# NameError: name 'b' is not defined

# During handling of the above exception, another exception occurred:

# Traceback (most recent call last):
#   File "c:\Users\liyiming\Desktop\lecture\test.py", line 4, in <module>
#     raise MemoryError ("这是一个报错")
# MemoryError: 这是一个报错
```
为什么会这样的呢?
## 答案:
原因:
1. **异常传播机制**
   - 在程序执行过程中，当发生一个异常时，程序的正常执行流程会被中断。如果这个异常没有在当前的代码块中被捕获，那么程序会沿着调用栈（函数调用的层次结构）向外层退出。
   - 例如，假设有一个函数`func3`在执行过程中发生了一个`TypeError`异常，并且`func3`没有捕获这个异常。如果`func3`是被`func2`调用的，那么程序会从`func3`中退出，回到`func2`的调用点。如果`func2`也没有捕获这个异常，程序会继续向外层，也就是`func2`的调用者退出，以此类推。
2. **被捕捉的概念**
   - 当异常向外层传播时，它会寻找合适的`try - except`语句来捕获它。`try - except`语句就像是一个安全网，当异常传播到有相应`catch`（`except`）块的`try`语句时，这个`except`块会尝试处理这个异常。
   - 例如：
   ```python
   def func1():
       try:
           func2()
       except TypeError as e:
           print("在func1中捕获到类型错误:", e)
   def func2():
       func3()
   def func3():
       a = "abc" + 123  # 会引发TypeError异常
   func1()
   ```
   - 在这个例子中，`func3`中发生了`TypeError`异常。因为`func3`没有捕获这个异常，程序从`func3`退出并回到`func2`的调用点。`func2`也没有捕获异常，所以继续向外退到`func1`。`func1`中有一个`try - except`语句，它的`except`块能够捕获`TypeError`异常，所以异常在这里被捕获并处理，程序不会因为这个异常而完全终止，而是会执行`print`语句输出错误信息。
3. **作用和重要性**
   - 这种异常传播和捕获机制使得程序可以在不同的层次上处理错误。在编写复杂的程序时，可能有多个函数相互调用，较低层次的函数可能不知道如何处理某些异常，而较高层次的函数可以根据具体的应用场景提供更合适的处理方式。
   - 例如，在一个Web应用程序中，数据库访问函数可能会发生各种数据库相关的异常。这些函数本身可能只负责抛出异常，而更高层次的业务逻辑函数或者请求处理函数可以捕获这些异常，并返回合适的错误信息给用户，如“数据库连接失败，请稍后再试”。
### 分析上面的这一个代码
例如这一个代码,在执行try中已经报了一个错误,但是被except捕捉到了,所以程序会进行,这里只是在这里展示罢了,但是在运行其中的except的内容的时候存在一个raise的错误,所以会在这里报错,而且会停止运行代码(之道下一次被捕捉)
```python
try:
    # 外部的 try-except 块
    try:
        # 内部的 try-except 块
        b = 1 / 0
    except:
        print("第一个地方报错了")
        raise MemoryError("第一个地方报错了")
    
    try:
        a = 1 / 0
    except:
        print("这里报错了")
except MemoryError as e:
    # 外部的 except 块捕获内部抛出的 MemoryError
    print(f"外部捕获到的错误: {e}")
```
详细解释
第一个内部 try-except 块:

b = 1 / 0 会引发一个 ZeroDivisionError。

except 块捕获了这个错误，并打印 "第一个地方
报错了"。
raise 语句抛出了一个新的 MemoryError。

外部 try-except 块:

捕获到 MemoryError 并打印 "外部捕获到的错误: 第一个地方报错了"。

由于 MemoryError 被外部的 except 块捕获，程序在这里终止，后续的代码不会执行。

第二个内部 try-except 块:

由于外部的 try-except 块已经捕获并处理了 MemoryError，程序在这里终止，第二个内部 try-except 块不会执行。

>输出

第一个地方报错了

外部捕获到的错误: 第一个地方报错了
## 问题3:有关于传出的函数的拷贝的问题
```python
def test(profile:list):
    profile.append('i')
    print(id(profile))
    return profile,id(profile)
test_list = list()
profile = [1,2,3,4]
print(id(profile))
for i in range(3):
    test_list.append(test(profile))
print(test_list)
# 2453385695552
# 2453385695552
# 2453385695552
# 2453385695552
# [([1, 2, 3, 4, 'i', 'i', 'i'], 2453385695552), ([1, 2, 3, 4, 'i', 'i', 'i'], 2453385695552), ([1, 2, 3, 4, 'i', 'i', 'i'], 2453385695552)]
```
可以看到在这个过程中你的profile的这个id,始终是一样的也就是说,在函数的传入和传出的时候所传递的值,就是原本的变量的值,他不会对此进行拷贝;因此我们常常会在return的时候返回`profile[:]`这样就可以让两次的id不同也不会导致后面修改的时候将前面的答案也一起修改.
## 问题4: python中的布尔值的判断
1. **布尔值**
   - 在Python中，`True`本身就是布尔类型中表示真的值。例如：
   ```python
   if True:
       print("This will be printed")
   ```
2. **非零数字**
   - 对于整数和浮点数，只要不是0，就会被判定为`True`。
   - 整数：
   ```python
   a = 5
   if a:
       print("a is considered True")
   ```
   - 浮点数：
   ```python
   b = 3.14
   if b:
       print("b is considered True")
   ```
3. **非空容器类型**
   - **字符串**：只要字符串长度不为0，就会被判定为`True`。
   ```python
   s = "Hello"
   if s:
       print("The string is considered True")
   ```
   - **列表**：非空列表被判定为`True`。
   ```python
   my_list = [1, 2, 3]
   if my_list:
       print("The list is considered True")
   ```
   - **元组**：同理，非空元组也是`True`。
   ```python
   my_tuple = (4, 5, 6)
   if my_tuple:
       print("The tuple is considered True")
   ```
   - **集合**：非空集合会被判定为`True`。
   ```python
   my_set = {7, 8, 9}
   if my_set:
       print("The set is considered True")
   ```
   - **字典**：非空字典在条件判断中为`True`。
   ```python
   my_dict = {"key1": "value1", "key2": "value2"}
   if my_dict:
       print("The dictionary is considered True")
   ```
## 问题5: python中的list的陷阱
```python
my_list = [1,2,3,4]
print(my_list[1:1000])
```
你会发现,在对于这样的一个列表进行操作的时候你的末尾的index是可以完全超过他的总长度的

同样的道理:你如果是按照-1的方式命名,那么你就会发现你也可以超过原来的0

而且,python中的对于index的取值也是很随意的,如果这个函数的index一个是按照1到len(list)-1的模式命名的另外一个是按照-1到0的方式命名的也不会有任何的影响

**一定一定要注意**

## 问题6：有关于OOP的一些问题？
1. 私有变量真的私有吗?
    在Python中，使用双下划线__前缀定义的变量或方法被称为“私有”成员。然而，这种私有性并不是绝对的，它主要通过名称改写（name mangling）来实现一种形式上的私有化：

    - 名称改写：当一个标识符以两个或更多的下划线字符开始且以最多一个下划线结束时，Python解释器会自动将其名称改写为_ClassName__identifier的形式，其中ClassName是当前类的名字。这种改写使得子类不会意外地覆盖父类中的私有成员。
    - 访问控制：尽管可以通过上述改写后的名称从外部访问这些所谓的“私有”成员，但这通常被认为是不好的编程实践。Python社区普遍遵循一种约定，即不应该直接从类的外部访问带有双下划线前缀的成员。
    - 总结来说，虽然Python中的__前缀可以提供一定程度的保护，防止意外的访问和覆盖，但它并不能完全阻止外部访问。因此，__定义的私有变量并不是严格意义上的私有，而是通过命名约定和名称改写机制来实现的一种软性的私有化。
2. 在python中所有的__str__的项目返回的内容一定只能是str的字符串，其他的类型（int,bool）等不可以被返回。
3. 在Python类中，`self`关键字主要用于以下几种情况：

    1. **访问实例变量**
   - 实例变量是属于类的每个实例（对象）的变量。通过`self`可以在类的方法内部访问和修改这些变量。例如：
   ```python
   class MyClass:
       def __init__(self, value):
           self.my_variable = value

       def print_variable(self):
           print(self.my_variable)
   ```
   在这个例子中，`__init__`是一个特殊的方法，用于初始化对象。`self.my_variable`在`__init__`方法中定义了一个实例变量。然后在`print_variable`方法中，通过`self`关键字访问这个实例变量并打印它。

    2. **调用实例方法**
   - 当一个类中有多个方法，并且在一个方法内部需要调用另一个方法时，要使用`self`来调用。例如：
   ```python
   class MathOperations:
       def add(self, a, b):
           return a + b

       def add_and_double(self, a, b):
           sum_result = self.add(a, b)
           return sum_result * 2
   ```
   在`add_and_double`方法中，使用`self.add`来调用`add`方法，这样可以复用代码，避免重复编写相同的加法操作逻辑。

    3. **作为对象的标识**
   - 在一些特殊情况下，`self`可以作为对象本身的引用。例如，当需要将对象作为参数传递给其他函数或者在比较对象时，`self`可以明确表示当前对象。不过这种情况相对较少，而且Python中的对象比较通常是通过`==`或`is`运算符来实现的。
   ```python
   class Person:
       def __init__(self, name):
           self.name = name

       def compare_name(self, other_person):
           return self.name == other_person.name
   ```
   在`compare_name`方法中，`self`代表当前的`Person`对象，`other_person`是另一个`Person`对象，通过比较两个对象的`name`属性来判断名字是否相同。
```python

import time

num = int(input())


def decorator(func):
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        """
        def my_function(*args, **kwargs):
            print("Positional arguments:", args)
            print("Keyword arguments:", kwargs)

        # 调用函数
        result = my_function(1, 2, 3, a=4, b=5)
        
        # 输出结果
        Positional arguments: (1, 2, 3)
        Keyword arguments: {'a': 4, 'b': 5}
        """
        end_time = time.time()
        print(f"{func.__name__} execution time: {end_time-start_time}")
        return result

    return wrapper


def square(num):
    a, b = (1, 2)
    for i in range(num):
        result = a + b
        a = b
        b = result
        yield result


decorated_square = decorator(square)
for i in range(num):
    print(decorated_square(num))
```