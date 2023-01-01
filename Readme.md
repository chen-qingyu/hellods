请允许我隆重介绍一下我的数据结构库：**MineDataStructure**，简称MDS（没错灵感来源于Minecraft）

### 1. 基本特性

- 语言：采用标准C语言编写，最低兼容版本： C99 。
- 目标：学习数据结构。
- 特点：简洁、优雅。
- 模块：Graph, Heap, List, Queue, Stack, String, Table, Tree.
- 封装：经过我的精心设计，使用者无法通过主函数访问或修改到对象（结构体）的内部变量，几乎可以说等同于实现了 private 的效果。

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

最开始是我在大二自学数据结构时边学边写的，当做练手项目。因为本科专业并不是计算机，所以当时没有学软件工程，写出来的代码只是能用，但是非常不优雅。后来大三大四接触到了面向对象思想和软件工程实践，我把整个库推翻重写了好几次，毕业后也时不时更新一下。

最开始那几年我根本没有把这个库开源的想法，因为我觉得这只是我的一个个人练手作品，网上一搜一大把，没什么开源价值。但是后来陆陆续续把它功能写得很完善的时候，我发现其中有些功能的实现互联网上基本搜不到，比如`String_ToDecimal`方法（类似标准库的`atof`，但是这个库不依赖 string.h ，没错我是重新造轮子），我能找到的都不能与标准库相媲美，各种瑕疵（不能处理类似".123e-2"这种情况，或者不能识别nan以及inf），而有些又太冗杂（各种if else嵌套），我想了两天最后用FPGA里面的独热码思想+有限状态机实现了。类似的还有许多，都是我在日积月累的学习中，一行一行写出来的。有时候是灵光乍现，有时候是从其他语言的标准库中得到的灵感。

### 4. 开源目的

- 为开源世界做一点微小的贡献。里面的代码对于许多初学数据结构的新手来说，能有一定的帮助。
- 期待有大佬加入，或者提出改进意见，一起把库进一步完善。

### 5. C++版本

这个是C版本的数据结构库，目标是学习数据结构，特点是简洁、优雅。

我还写了C++版本的： [MDSPP (GitHub)](https://github.com/chen-qingyu/MDSPP) [MDSPP (Gitee)](https://gitee.com/ChobitsY/mdspp) （还在开发中），目标是像Python一样方便，特点是简洁、好用、安全。
