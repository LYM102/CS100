# C语言入门（*CS100*）Part Six
> *-- By Yiming Li*

> 本文章的内容参考至*Stephen Prata*的《C Primer Plus》

> 本内容适用于*CS*专业学生
## 共同体
- 核心：一种数据存在多种可能的类型
### 定义
```c
union Money
{
    double mond;
    int moni;
    char mons;
}

int main()
{
    union Money m;
    m.moneyi = 100;
    printf("%d\n",m.money);
}
```
- 共用体的特点
    1. 共用体，也叫做联合体
    2. 所有的变量都是用同一个内存空间
    3. 每次只能够给一个变量进行赋值，因为第二次赋值的时候会覆盖原来的数据
    4. 所占的内存大小 = 最大成员的长度（也受对齐因素的影响）
        - 注意对齐因素中的字符串`char name [100]`但是按照**单个成员**为主（数组也要拆开）
        - 总大小是**单个成员**中占据字节数最大的成员的整数倍
    5. 共同体每次只能够有一个成员被使用，不能够同时储存多个数据。
## 动态内存分配
- 常见函数：在`<stdlib.h>`头文件当中
1. `malloc`:`memory allocation`作用是申请连续的空间
2. `calloc`:`contiguous allocation`申请连续的空间+数据初始化
3. `realloc`:`re-allocation`修改空间的大小
4. `free`：释放空间
```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *p0 = malloc(100); // 申请了100个字节的空间（注意这里是字节数量，如果要储存int类型的内容只能够储存25个整数）
    int *p1 = malloc(100 * sizeof(int));
    printf("%p\n", p0);
    printf("%p\n", p1);
    for (int i = 0; i < 100; i++)
    {
        //*(p1 + i) = (1 + i) * 10;
        p1[i] = (1 + i) * 10;
    }
    for (int i = 0; i < 100; i++)
    {
        // printf("%d\t", *(p1 + i));
        printf("%d\t", p1[i]);
    }
    return 0;
}
```
```c
int *p0 = calloc(10, sizeof(int));//int *p0 = malloc(10*sizeof(int));
int *pp = realloc(p0,20*sizeof(int));//扩容函数
free(pp);//释放空间
```

几个小细节
1. `malloc`创建的是字节
2. `malloc`返回的是`void`类型的指针，没有步长的概念，无法获取空间中的数据，需要强转
3. `malloc`返回的仅仅是首地址，没有总大小，最好定义一个变量来记录大小
4. `malloc`申请的空间不会消失，如果不能够正确释放会导致内存泄漏
5. `malloc`申请的空间不能够过多，会产生虚拟空间
6. `malloc`申请的内容没有初始化，所以需要先赋值后使用
```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int number = 1024 * 1024 * 1024, count = 0;
    while (1)
    {
        int *p = malloc(number);
        if (p == NULL)
        {
            printf("Error!");
            break;
        }
        else
        {
            count++;
            printf("succeed!%d\t%p\n", count, p);
        }
    }
    return 0;
}
```
```
succeed!1       0000025C34F08040
succeed!2       0000025C74F1E040
succeed!3       0000025CB4F22040
succeed!4       0000025CF4F3F040
succeed!5       0000025D34F5E040
succeed!6       0000025D74F6E040
succeed!7       0000025DB4F79040
succeed!8       0000025DF4F80040
succeed!9       0000025E34F9E040
succeed!10      0000025E74FA7040
succeed!11      0000025EB4FBC040
succeed!12      0000025EF4FC2040
succeed!13      0000025F34FD1040
succeed!14      0000025F74FEB040
succeed!15      0000025FB4FFD040
succeed!16      0000025FF5005040
succeed!17      0000026035013040
succeed!18      000002607502B040
succeed!19      00000260B5032040
succeed!20      00000260F5047040
succeed!21      000002613505E040
succeed!22      0000026175067040
succeed!23      00000261B5073040
succeed!24      00000261F5081040
succeed!25      0000026235090040
succeed!26      00000262750A4040
succeed!27      00000262B50B9040
succeed!28      00000262F50CC040
succeed!29      00000263350DE040
succeed!30      00000263750EE040
succeed!31      00000263B50F5040
succeed!32      00000263F510E040
succeed!33      0000026435110040
succeed!34      0000026475122040
succeed!35      00000264B5138040
succeed!36      00000264F514D040
succeed!37      000002653515D040
succeed!38      0000026575162040
succeed!39      00000265B5172040
succeed!40      00000265F5186040
succeed!41      000002663519A040
succeed!42      00000266751A9040
succeed!43      00000266B51B0040
succeed!44      00000266F51C8040
succeed!45      00000267351D0040
succeed!46      00000267751E2040
succeed!47      00000267B51FB040
succeed!48      00000267F5208040
succeed!49      0000026835219040
succeed!50      000002687522C040
succeed!51      00000268B5231040
succeed!52      00000268F5248040
succeed!53      000002693525B040
succeed!54      000002697526E040
succeed!55      00000269B5272040
succeed!56      00000269F5280040
succeed!57      0000026A3529F040
succeed!58      0000026A752B6040
succeed!59      0000026AB52CC040
succeed!60      0000026AF52D1040
succeed!61      0000026B352EA040
succeed!62      0000026B752FC040
succeed!63      0000026BB530D040
succeed!64      0000026BF531B040
succeed!65      0000026C35326040
succeed!66      0000026C75336040
succeed!67      0000026CB5344040
succeed!68      0000026CF5359040
succeed!69      0000026D35361040
succeed!70      0000026D75373040
succeed!71      0000026DB5388040
succeed!72      0000026DF539E040
succeed!73      0000026E353A8040
succeed!74      0000026E753BE040
succeed!75      0000026EB53C1040
succeed!76      0000026EF53DE040
succeed!77      0000026F353E8040
succeed!78      0000026F753F0040
Error!
```
C语言不会立马就在内存中去开辟空间，而是什么时候储存数据了，才会真正的分配空间

目的：为了提高内存的使用效率