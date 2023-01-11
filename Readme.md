# MineDataStructure

*名字灵感来源于我喜欢的游戏——Minecraft*

*缩写为MDS*


### 1. 基本属性

- 语言：采用标准C语言编写，最低兼容版本： ISO C99 。
- 目的：学习数据结构。
- 目标：实现完整而标准的数据结构。
- 模块：Graph, Heap, List, Queue, Stack, String, Table, Tree.
- 简洁：Stay simple, stay young. 在保证好用和安全的前提下，尽量简洁，便于维护和阅读。
- 好用：提供了许多方便的函数，比如String类提供了像Python的str那样的替换、分割、查找等操作，比如List类和String类都支持像Python那样的负数下标等等。当然，功能与标准库重合的部分的性能肯定比不上标准库，但是简单用用是完全没问题的。唯一的缺点，就是不支持泛型，所以我还写了C++版本的，目标是像Python的内置类型一样好用又优雅。
- 安全：安全的扩容机制，防止溢出。对容器的增删改查都有相应的检查。这么多检查，肯定会对性能有一定影响，但是这个库追求的并不是性能，而是简洁，好用和安全。
- 优雅：经过我的精心设计，使用者无法通过主函数访问或修改到对象（结构体）的内部变量，几乎可以说等同于实现了 private 的效果。
- 风格：大部分遵循 [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) ，小部分基于项目规模和源码简洁性的考虑采用自己的风格。
- 测试：用 assert 宏函数编写的简单测试，所有测试代码同样符合 ISO C99 标准。

### 2. 面向对象

采用面向对象的设计理念：

`ClassName_MethodName(ObjectType* self, args...)` 是实例方法，比如

```C
int ArrayList_Find(const List* self, ListItem data);
String** String_Split(const String* self, const String* sep);
```

`ClassName_MethodName(args...)` 是静态方法，比如

```C
List* ArrayList_Create(void);
String* String_From(const char* chars);
```

### 3. 开发历史

这个库经过了五年的发展（2018-2023）。

最开始是我在大二自学数据结构时边学边写的，当做练手项目。起源详情请见： https://zhuanlan.zhihu.com/p/92786307 。因为本科专业并不是计算机，所以当时没有学软件工程，写出来的代码只是能用，但是非常不优雅。后来大三大四接触到了面向对象思想和软件工程实践，我把整个库推翻重写了好几次，毕业后也时不时更新一下。

最开始那几年我根本没有把这个库开源的想法，因为我觉得这只是我的一个个人练手作品，网上一搜一大把，没什么开源价值。但是后来陆陆续续把它功能写得很完善的时候，我发现其中有些功能的实现互联网上基本搜不到，比如`String_ToDecimal`方法（类似标准库的`atof`，但是这个库不依赖 string.h ，没错我是重新造轮子），我能找到的都不能与标准库相媲美，各种瑕疵（不能处理类似".123e-2"这种情况，或者不能识别nan以及inf），而有些又太冗杂（各种if else嵌套），我想了两天最后用FPGA里面的独热码思想+有限状态机实现了。类似的还有许多，都是我在日积月累的学习中，一行一行写出来的。有时候是灵光乍现，有时候是从其他语言的标准库中得到的灵感。

### 4. 开源目的

- 为开源世界做一点微小的贡献。里面的代码对于许多初学数据结构的新手来说，能有一定的帮助。
- 期待有大佬加入，或者提出改进意见，一起把库进一步完善。

### 5. C++版本

这个是C版本的数据结构库，目标是实现完整而标准的数据结构。

我还写了C++版本的： [MDSPP (GitHub)](https://github.com/chen-qingyu/MDSPP) [MDSPP (Gitee)](https://gitee.com/ChobitsY/mdspp) （还在开发中），目标是像Python的内置类型一样好用又优雅。

### 6. 内存安全

使用 Dr. Memory 进行了内存检查：

```
Dr. Memory version 2.5.0

FINAL SUMMARY:

DUPLICATE ERROR COUNTS:

SUPPRESSIONS USED:

NO ERRORS FOUND:
      0 unique,     0 total unaddressable access(es)
      0 unique,     0 total uninitialized access(es)
      0 unique,     0 total invalid heap argument(s)
      0 unique,     0 total GDI usage error(s)
      0 unique,     0 total handle leak(s)
      0 unique,     0 total warning(s)
      0 unique,     0 total,      0 byte(s) of leak(s)
      0 unique,     0 total,      0 byte(s) of possible leak(s)
```
