# HelloDS

_C++ 模板实现的完整、通用的基础数据结构_

## 1. 基本属性

- 名称：HelloDS，意为 **Hello** **D**ata **S**tructure。
- 语言：C++，要求 C++17 。
- 目标：实现完整、通用的基础数据结构。不使用任何标准库容器。全部使用模板，并且支持迭代器。
- 模块：Deque, Graph, Heap, List, Map, Queue, Set, Stack, Tree
- 简洁：Stay simple, stay young. 在保证健壮的前提下，尽量简洁，便于维护和阅读。
- 健壮：安全的扩容机制，防止溢出。对容器的增删改查都有相应的检查。
- 风格：大部分遵循 [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) ，小部分基于项目规模和源码简洁性的考虑采用自己的风格。
- 测试：使用 [Catch2](https://github.com/catchorg/Catch2) 进行了测试，确保测试全部通过。
- 安全：使用 [Dr. Memory](https://drmemory.org/) 进行了检查，确保没有安全问题。
- 文档：使用 [Doxygen](https://www.doxygen.nl/) 生成文档。
- 构建：使用 [XMake](https://xmake.io/) 进行构建。

## 2. 使用说明

可以看 [examples](./examples/) 。

其实最大的用处就是通过源码来学习/收藏/展示数据结构。

都是基础数据结构，没什么太大的亮点，中规中矩，因为这个项目的目的不是提供可使用的库，而是学习/收藏/展示数据结构。

如果你想要实用的容器库/类型库，可以看看我的另一个项目：[PyInCpp](https://github.com/chen-qingyu/pyincpp)。

## 3. 开发历史

这个项目始于 2018 年，当时自学数据结构边学边写的，用的 C 语言，当做练手项目。起源详情请见： https://zhuanlan.zhihu.com/p/92786307 。因为本科专业并不是计算机，所以当时没有学软件工程，写出来的代码只是能用，但是非常不优雅。后来接触到了面向对象思想和软件工程实践，我把整个项目推翻重写了好几次。

最开始那几年我根本没有把这个项目开源的想法，因为我觉得这只是我的一个个人练手作品，网上一搜一大把，没什么开源价值。但是后来陆陆续续把它功能写得很完善的时候，我发现其中有些功能的实现互联网上基本搜不到，比如字符串转数字（类似标准库的 atof ，但是这个库不依赖 string.h ，没错我是重新造轮子），我能找到的都不能与标准库相媲美，各种瑕疵（不能处理类似 ".123e-2" 这种情况，或者不能识别 nan 以及 inf ），而有些又太冗杂（各种 if else 嵌套），我想了两天最后用 FPGA 里面的独热码思想结合有限状态机实现了（后来把 `String` 合并到 `PyInCpp` 里去了，因为 `String` 严格来说不算数据结构而算数据类型）。类似的还有许多，都是我在日积月累的学习中一行一行写出来的。有时候是灵光乍现（比如`String_ToDecimal, String_ToInteger`的独热码结合有限状态机），有时候是从其他语言的标准库中得到的启发（比如`String_From`的命名仿照 Rust 标准库中 String 的 from 方法），有时候是网友给的建议（比如`DoublyLinkedList_At`的内部状态指针加速访问）。

因为二叉树的中序遍历需要用到队列，而 C 语言无法简洁地实现泛型，所以之前一直是把队列函数源码复制一份当成`static`的然后 `typedef const struct BinarySearchTreeNode* ArrayQueueItem;` 手动模拟泛型，但这样太不优雅了，2024 年用 C++ 重写了！
